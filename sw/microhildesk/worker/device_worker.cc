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
    constexpr std::chrono::seconds cReconnectInterval{3};
    constexpr std::chrono::seconds cHandshakeTimeout{2};
    constexpr std::chrono::milliseconds cSleepStep{100};
    constexpr int cSleepIterations{5};
    constexpr std::string_view cErrGenericConnectionLost{"\n[Error] Connection lost."};
    constexpr std::string_view cErrSerialDisconnected{
        "\n[Error] Serial port is no longer available (I/O error). Device disconnected."
    };
    constexpr std::string_view cErrTcpLost{"\n[Error] TCP connection lost (I/O error)."};
    constexpr std::string_view cErrBleLost{"\n[Error] BLE connection lost (I/O error)."};
    constexpr std::string_view cLogConnectionLost{"Communication channel lost (I/O error)."};
    constexpr std::string_view cLogReconnecting{
        "Communication channel closed. Attempting to reconnect..."
    };
    constexpr std::string_view cMsgPortOpenedHandshaking{
        "\n[Info] Port opened. Handshaking with microHIL device..."
    };
    constexpr std::string_view cMsgHandshakeVerified{
        "\n[Info] Device handshake verified. Hardware ready."
    };
    constexpr std::string_view cMsgHandshakeTimeout{
        "\n[Warning] Handshake timeout: Device did not respond. Retrying..."
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
      m_responseProcessor(std::move(responseProcessor)),
      m_logger(logger) {}

DeviceWorker::~DeviceWorker() {
    stop();
}

void DeviceWorker::start() {
    m_needInitialQuery = true;
    m_stopThread = false;
    if (!m_readThread.joinable()) {
        m_readThread = std::thread(&DeviceWorker::readLoop, this);
    }
}

void DeviceWorker::stop() {
    m_stopThread = true;

    if (m_comChannel) {
        m_comChannel->close();
    }

    if (m_readThread.joinable()) {
        m_readThread.join();
    }
}

void DeviceWorker::configure(const Model::IModel &model) {
    if (m_stopThread || !m_comChannel || !m_comConfigurator) {
        return;
    }

    m_comChannel->close();
    updateConnectionState(ConnectionState::Disconnected);

    if (m_stopThread) {
        return;
    }

    m_needInitialQuery = true;
    m_comConfigurator->configure(model, *m_comChannel);
}

void DeviceWorker::send(const std::string &command) {
    if (command.empty() || !m_comChannel || !m_comChannel->isOpen()) {
        return;
    }

    std::vector<uint8_t> cmdBytes(command.begin(), command.end());
    m_comChannel->write(cmdBytes);
}

void DeviceWorker::setNeedInitialQuery(bool need) {
    m_needInitialQuery = need;
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

void DeviceWorker::updateConnectionState(ConnectionState state) {
    if (m_connectionState != state) {
        m_connectionState = state;
        m_signalConnectionState.emit(state);
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

void DeviceWorker::readLoop() {
    auto lastReconnectTry =
        std::chrono::steady_clock::now() - std::chrono::seconds(10);
    auto handshakeStartTime = std::chrono::steady_clock::now();

    while (!m_stopThread) {
        try {
            if (m_comChannel && m_comChannel->isOpen()) {
                if (m_needInitialQuery) {
                    m_needInitialQuery = false;
                    updateConnectionState(ConnectionState::Handshaking);
                    m_signalDataReceived.emit(std::string(cMsgPortOpenedHandshaking));
                    handshakeStartTime = std::chrono::steady_clock::now();
                    queryInitialDeviceStatus();
                }

                if (m_connectionState == ConnectionState::Handshaking) {
                    auto now = std::chrono::steady_clock::now();
                    if (now - handshakeStartTime >= cHandshakeTimeout) {
                        handshakeStartTime = now;
                        m_signalDataReceived.emit(std::string(cMsgHandshakeTimeout));
                        queryInitialDeviceStatus();
                    }
                }

                std::vector<uint8_t> buffer;
                m_comChannel->read(buffer, 1);

                if (!m_stopThread && !m_comChannel->isOpen()) {
                    updateConnectionState(ConnectionState::Disconnected);
                    m_signalDataReceived.emit(getConnectionLossErrorMessage());
                    if (m_logger) {
                        m_logger->log(
                            cLogConnectionLost.data(),
                            Logger::LogLevel::Error
                        );
                    }
                } else if (!buffer.empty()) {
                    std::string dataStr(buffer.begin(), buffer.end());

                    if (m_responseProcessor) {
                        auto payloads = m_responseProcessor->process(dataStr);
                        for (const auto &payload : payloads) {
                            if (m_connectionState == ConnectionState::Handshaking) {
                                updateConnectionState(ConnectionState::Ready);
                                m_signalDataReceived.emit(std::string(cMsgHandshakeVerified));
                                if (m_commandFormatter) {
                                    send(m_commandFormatter->getCommandStatusAllChannels());
                                }
                            }
                            m_signalDataReceived.emit(payload);
                        }
                    } else {
                        if (m_connectionState == ConnectionState::Handshaking) {
                            updateConnectionState(ConnectionState::Ready);
                            m_signalDataReceived.emit(std::string(cMsgHandshakeVerified));
                            if (m_commandFormatter) {
                                send(m_commandFormatter->getCommandStatusAllChannels());
                            }
                        }
                        m_signalDataReceived.emit(dataStr);
                    }
                }
            } else {
                updateConnectionState(ConnectionState::Disconnected);
                auto now = std::chrono::steady_clock::now();
                if (!m_stopThread && now - lastReconnectTry >= cReconnectInterval) {
                    lastReconnectTry = now;
                    if (m_logger) {
                        m_logger->log(
                            cLogReconnecting.data(),
                            Logger::LogLevel::Warning
                        );
                    }
                    if (m_comChannel && !m_stopThread) {
                        if (m_comChannel->open()) {
                            m_needInitialQuery = true;
                        }
                    }
                }
                for (int s = 0; s < cSleepIterations && !m_stopThread; ++s) {
                    std::this_thread::sleep_for(cSleepStep);
                }
            }
        } catch (...) {
            for (int s = 0; s < cSleepIterations && !m_stopThread; ++s) {
                std::this_thread::sleep_for(cSleepStep);
            }
        }
    }
}
