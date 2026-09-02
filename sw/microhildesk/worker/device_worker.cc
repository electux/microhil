////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// device_worker.cc
/// Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
///
/// microhildesk is free software: you can redistribute it and/or modify it
/// under the terms of the GNU General Public License as published by the
/// Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// microhildesk is distributed in the hope that it will be useful, but
/// WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
/// See the GNU General Public License for more details.
///
/// You should have received a copy of the GNU General Public License along
/// with this program. If not, see <http://www.gnu.org/licenses/>.
///
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <chrono>
#include <com/switchable_com.h>
#include <vector>
#include <worker/device_worker.h>

using namespace Electux::App::Worker;

namespace {
    constexpr std::chrono::seconds cHandshakeTimeout{2};
    constexpr std::chrono::milliseconds cSleepStep{100};
    constexpr std::string_view cErrGenericConnectionLost{
        "\n[Error] Connection lost."
    };
    constexpr std::string_view cErrSerialDisconnected{
        "\n[Error] Serial port is no longer available (I/O error). Device "
        "disconnected."
    };
    constexpr std::string_view cErrTcpLost{
        "\n[Error] TCP connection lost (I/O error)."
    };
    constexpr std::string_view cErrBleLost{
        "\n[Error] BLE connection lost (I/O error)."
    };
    constexpr std::string_view cErrConnectionFailed{
        "\n[Error] Connection failed: Device not "
        "reachable. Use Device -> Connect to retry."
    };
    constexpr std::string_view cErrHandshakeTimeout{
        "\n[Error] Handshake timeout: Device did not "
        "respond. Use Device -> Connect to retry."
    };
    constexpr std::string_view cLogConnectionLost{
        "Communication channel lost (I/O error)."
    };
    constexpr std::string_view cMsgPortOpenedHandshaking{
        "\n[Info] Port opened. Handshaking with microHIL device..."
    };
    constexpr std::string_view cMsgHandshakeVerified{
        "\n[Info] Device handshake verified. Hardware ready."
    };
} // namespace

DeviceWorker::DeviceWorker(
    std::unique_ptr<Com::ICom> comChannel,
    std::unique_ptr<Com::IComConfigurator> comConfigurator,
    std::unique_ptr<Command::ICommandFormatter> commandFormatter,
    std::unique_ptr<Command::IResponseProcessor> responseProcessor,
    Logger::ILog *logger
)
    : m_comChannel(std::move(comChannel)),
      m_comConfigurator(std::move(comConfigurator)),
      m_commandFormatter(std::move(commandFormatter)),
      m_responseProcessor(std::move(responseProcessor)), m_logger(logger) {
    m_dataDispatcher.connect([this]() {
        std::queue<std::string> localQueue;
        {
            std::lock_guard<std::mutex> lock(m_queueMutex);
            std::swap(localQueue, m_dataQueue);
        }

        while (!localQueue.empty()) {
            m_signalDataReceived.emit(localQueue.front());
            localQueue.pop();
        }
    });

    m_stateDispatcher.connect([this]() {
        ConnectionState state = m_pendingState.load();
        m_signalConnectionState.emit(state);
    });
}

DeviceWorker::~DeviceWorker() { stop(); }

void DeviceWorker::start() {
    m_stopThread = false;

    if (!m_readThread.joinable()) {
        m_readThread = std::thread(&DeviceWorker::readLoop, this);
    }
}

void DeviceWorker::stop() {
    m_stopThread = true;
    m_cv.notify_all();

    {
        std::lock_guard<std::mutex> lock(m_ioMutex);

        if (m_comChannel) {
            m_comChannel->close();
        }
    }

    if (m_readThread.joinable()) {
        m_readThread.join();
    }
}

void DeviceWorker::connect() {
    if (m_stopThread) {
        return;
    }

    {
        std::lock_guard<std::mutex> lock(m_stateMutex);

        if (m_connectionState == ConnectionState::Ready ||
            m_connectionState == ConnectionState::Handshaking ||
            m_connectionState == ConnectionState::Connecting) {
            return;
        }

        m_connectRequested = true;
    }

    m_cv.notify_all();
}

void DeviceWorker::disconnect() {
    if (m_stopThread) {
        return;
    }

    {
        std::lock_guard<std::mutex> lock(m_stateMutex);
        m_connectRequested = false;
    }

    updateConnectionState(ConnectionState::Disconnected);

    {
        std::lock_guard<std::mutex> lock(m_ioMutex);

        if (m_comChannel) {
            m_comChannel->close();
        }
    }

    emitData(std::string("\n[Info] Disconnected by user. Port released."));
    m_cv.notify_all();
}

void DeviceWorker::configure(const Model::IModel &model) {
    if (m_stopThread || !m_comChannel || !m_comConfigurator) {
        return;
    }

    {
        std::lock_guard<std::mutex> lock(m_stateMutex);
        m_connectRequested = false;
    }

    {
        std::lock_guard<std::mutex> lock(m_ioMutex);
        m_comChannel->close();
        m_comConfigurator->configure(model, *m_comChannel);
    }

    updateConnectionState(ConnectionState::Disconnected);
    emitData(
        std::string(
            "\n[Info] Settings updated. Previous connection closed. Use Device "
            "-> Connect to connect."
        )
    );

    if (m_stopThread) {
        return;
    }

    m_cv.notify_all();
}

void DeviceWorker::send(const std::string &command) {
    if (command.empty() || !m_comChannel || !m_comChannel->isOpen()) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_ioMutex);

    if (m_comChannel && m_comChannel->isOpen()) {
        std::vector<uint8_t> cmdBytes(command.begin(), command.end());
        m_comChannel->write(cmdBytes);
    }
}

bool DeviceWorker::isConnected() const {
    return m_connectionState == ConnectionState::Ready;
}

ConnectionState DeviceWorker::getConnectionState() const {
    return m_connectionState;
}

sigc::signal<void(const std::string &)> DeviceWorker::signal_data_received() {
    return m_signalDataReceived;
}

sigc::signal<void(ConnectionState)> DeviceWorker::signal_connection_state() {
    return m_signalConnectionState;
}

void DeviceWorker::emitData(const std::string &data) {
    if (m_stopThread) {
        return;
    }

    {
        std::lock_guard<std::mutex> lock(m_queueMutex);
        m_dataQueue.push(data);
    }

    m_dataDispatcher.emit();
}

void DeviceWorker::updateConnectionState(ConnectionState state) {
    if (m_stopThread) {
        m_connectionState = state;

        return;
    }

    if (m_connectionState != state) {
        m_connectionState = state;
        m_pendingState = state;
        m_stateDispatcher.emit();
    }
}

void DeviceWorker::queryInitialDeviceStatus() {
    if (!m_commandFormatter) {
        return;
    }

    send(m_commandFormatter->getCommandBoardId());
    send(m_commandFormatter->getCommandVersion());
}

std::string DeviceWorker::getConnectionLossErrorMessage() const {
    auto *switchable = dynamic_cast<Com::SwitchableCom *>(m_comChannel.get());

    if (switchable) {
        if (switchable->getActiveCom() == switchable->getSerialCom()) {
            return std::string(cErrSerialDisconnected);
        }

        if (switchable->getActiveCom() == switchable->getTcpCom()) {
            return std::string(cErrTcpLost);
        }

        if (switchable->getActiveCom() == switchable->getBleCom()) {
            return std::string(cErrBleLost);
        }
    }

    return std::string(cErrGenericConnectionLost);
}

void DeviceWorker::handleDisconnectedState() {
    std::unique_lock<std::mutex> lock(m_stateMutex);

    m_cv.wait(lock, [this]() {
        return m_stopThread.load() || m_connectRequested.load();
    });

    if (m_stopThread) {
        return;
    }

    if (m_connectRequested) {
        m_connectRequested = false;
        updateConnectionState(ConnectionState::Connecting);
        emitData(std::string("\n[Info] Connecting to device..."));
    }
}

bool DeviceWorker::handleConnectingState(
    std::chrono::steady_clock::time_point &handshakeStartTime
) {
    bool opened = false;

    {
        std::lock_guard<std::mutex> ioLock(m_ioMutex);

        if (m_comChannel && !m_stopThread) {
            opened = m_comChannel->open();
        }
    }

    if (opened) {
        updateConnectionState(ConnectionState::Handshaking);
        emitData(std::string(cMsgPortOpenedHandshaking));
        handshakeStartTime = std::chrono::steady_clock::now();
        queryInitialDeviceStatus();
        return true;
    }

    updateConnectionState(ConnectionState::Disconnected);
    emitData(std::string(cErrConnectionFailed));

    return false;
}

bool DeviceWorker::checkHandshakeTimeout(
    const std::chrono::steady_clock::time_point &handshakeStartTime
) {
    auto now = std::chrono::steady_clock::now();

    if (now - handshakeStartTime >= cHandshakeTimeout) {
        {
            std::lock_guard<std::mutex> ioLock(m_ioMutex);
            if (m_comChannel) {
                m_comChannel->close();
            }
        }

        updateConnectionState(ConnectionState::Disconnected);
        emitData(std::string(cErrHandshakeTimeout));

        return true;
    }

    return false;
}

void DeviceWorker::handleDataIO() {
    constexpr size_t cReadBufferSize{256};
    std::vector<uint8_t> buffer;

    if (m_comChannel && m_comChannel->isOpen()) {
        m_comChannel->read(buffer, cReadBufferSize);
    }

    if (!m_stopThread &&
        m_connectionState != ConnectionState::Disconnected &&
        (!m_comChannel || !m_comChannel->isOpen())) {

        updateConnectionState(ConnectionState::Disconnected);
        emitData(getConnectionLossErrorMessage());

        if (m_logger) {
            m_logger->log(
                cLogConnectionLost.data(), Logger::LogLevel::Error
            );
        }

        return;
    }

    if (!buffer.empty()) {
        std::string dataStr(buffer.begin(), buffer.end());
        processIncomingData(dataStr);
    }
}

void DeviceWorker::processIncomingData(const std::string &dataStr) {
    auto verifyHandshakeIfNeeded = [this]() {
        if (m_connectionState == ConnectionState::Handshaking) {
            updateConnectionState(ConnectionState::Ready);
            emitData(std::string(cMsgHandshakeVerified));

            if (m_commandFormatter) {
                send(m_commandFormatter->getCommandStatusAllChannels());
            }
        }
    };

    if (m_responseProcessor) {
        auto payloads = m_responseProcessor->process(dataStr);

        for (const auto &payload : payloads) {
            verifyHandshakeIfNeeded();
            emitData(payload);
        }
    } else {
        verifyHandshakeIfNeeded();
        emitData(dataStr);
    }
}

void DeviceWorker::readLoop() {
    auto handshakeStartTime = std::chrono::steady_clock::now();

    while (!m_stopThread) {
        try {
            if (m_connectionState == ConnectionState::Disconnected) {
                handleDisconnectedState();

                if (m_stopThread) {
                    break;
                }
            }

            if (m_connectionState == ConnectionState::Connecting) {
                if (!handleConnectingState(handshakeStartTime)) {
                    continue;
                }
            }

            if (m_connectionState == ConnectionState::Handshaking) {
                if (checkHandshakeTimeout(handshakeStartTime)) {
                    continue;
                }
            }

            if (m_connectionState == ConnectionState::Handshaking ||
                m_connectionState == ConnectionState::Ready) {
                handleDataIO();
            }
        } catch (...) {
            std::this_thread::sleep_for(cSleepStep);
        }
    }
}

