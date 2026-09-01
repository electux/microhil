////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_controller.cc
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
#include <app_controller.h>
#include <model/model.h>
#include <string>

using namespace Electux::App;

namespace {
    constexpr std::string_view cAppStartedLog{"Application started."};
    constexpr std::string_view cAppShuttingDownLog{"Application shutting down."};
} // namespace

AppController::AppController(
    std::unique_ptr<Config::IConfig> configManager,
    std::unique_ptr<Worker::IDeviceWorker> deviceWorker,
    std::unique_ptr<Logger::ILog> logger,
    std::unique_ptr<Command::ICommandFormatter> commandFormatter,
    std::unique_ptr<Command::IChannelCommandMapper> channelMapper,
    std::unique_ptr<Config::IConfigChangeDetector> configDetector,
    std::unique_ptr<Command::IResponseProcessor> responseProcessor
)
    : m_configManager(std::move(configManager)),
      m_deviceWorker(std::move(deviceWorker)),
      m_logger(std::move(logger)),
      m_commandFormatter(std::move(commandFormatter)),
      m_channelMapper(std::move(channelMapper)),
      m_configDetector(std::move(configDetector)),
      m_responseProcessor(std::move(responseProcessor)) {
    if (m_deviceWorker) {
        m_deviceWorker->signal_data_received().connect(
            sigc::mem_fun(*this, &AppController::onDeviceDataReceived)
        );
    }
}

void AppController::startup() {
    if (m_configManager) {
        m_configManager->init();
    }
    configureLogger();

    if (m_deviceWorker) {
        if (m_configManager) {
            m_deviceWorker->configure(m_configManager->getConfig());
        }
        m_deviceWorker->start();
    }

    if (m_logger) {
        m_logger->log(cAppStartedLog.data(), Logger::LogLevel::Info);
    }
}

void AppController::shutdown() {
    if (m_deviceWorker) {
        m_deviceWorker->stop();
    }

    if (m_logger) {
        m_logger->log(cAppShuttingDownLog.data(), Logger::LogLevel::Info);
        m_logger->close();
    }

    if (m_configManager) {
        m_configManager->store(true);
    }
}

const Model::IModel &AppController::getModel() const {
    return m_configManager->getConfig();
}

void AppController::onSetupChanged(const Model::SettingsSetup &setup) {
    const auto &oldConfig = m_configManager->getConfig();
    auto &newConfig = *setup.m_config;

    Config::ConfigChanges changes;
    if (m_configDetector) {
        changes = m_configDetector->detectChanges(oldConfig, newConfig);
    }

    for (size_t channelIdx : changes.changedChannels) {
        handleChannelStateChange(
            channelIdx, newConfig.getChannelState(channelIdx)
        );
    }

    m_configManager->setConfig(newConfig);
    m_configManager->store();

    if (changes.logChanged) {
        configureLogger();
    }

    if (changes.hasComChanged() && m_deviceWorker) {
        m_deviceWorker->configure(newConfig);
    }

    getModel().emit_changed();
}

void AppController::handleChannelStateChange(
    size_t channelIndex, const Model::ChannelState &state
) {
    if (!m_channelMapper || !m_commandFormatter) {
        return;
    }

    auto [cmd, logMsg] = m_channelMapper->map(
        channelIndex, state, *m_commandFormatter
    );

    if (!logMsg.empty() && m_logger) {
        m_logger->log(logMsg, Logger::LogLevel::Info);
    }

    if (!cmd.empty() && m_deviceWorker) {
        m_deviceWorker->send(cmd);
    }
}

void AppController::turnOnAllChannels() {
    if (m_commandFormatter && m_deviceWorker) {
        m_deviceWorker->send(m_commandFormatter->getCommandOnAllChannels());
    }
}

void AppController::turnOffAllChannels() {
    if (m_commandFormatter && m_deviceWorker) {
        m_deviceWorker->send(m_commandFormatter->getCommandOffAllChannels());
    }
}

void AppController::requestAllChannelsStatus() {
    if (m_commandFormatter && m_deviceWorker) {
        m_deviceWorker->send(m_commandFormatter->getCommandStatusAllChannels());
    }
}

void AppController::resetSystem() {
    if (m_commandFormatter && m_deviceWorker) {
        m_deviceWorker->send(m_commandFormatter->getCommandReset());
    }
}

void AppController::requestBoardId() {
    if (m_commandFormatter && m_deviceWorker) {
        m_deviceWorker->send(m_commandFormatter->getCommandBoardId());
    }
}

void AppController::requestVersion() {
    if (m_commandFormatter && m_deviceWorker) {
        m_deviceWorker->send(m_commandFormatter->getCommandVersion());
    }
}

sigc::signal<void(const std::string &)> AppController::signal_data_received() {
    return m_signalDataReceived;
}

sigc::signal<void(Worker::ConnectionState)> AppController::signal_connection_state() {
    if (m_deviceWorker) {
        return m_deviceWorker->signal_connection_state();
    }
    static sigc::signal<void(Worker::ConnectionState)> dummy;
    return dummy;
}

Worker::ConnectionState AppController::getConnectionState() const {
    return m_deviceWorker ? m_deviceWorker->getConnectionState()
                          : Worker::ConnectionState::Disconnected;
}

void AppController::onDeviceDataReceived(const std::string &data) {
    if (m_responseProcessor && m_configManager) {
        auto event = m_responseProcessor->parseChannelEvent(data);
        if (event.valid) {
            auto newConfig = m_configManager->getConfig().clone();
            auto state = newConfig->getChannelState(event.channelIndex);
            if (event.active) {
                if (state.mode == Model::Channel::ChannelMode::Toggle) {
                    state.toggle = true;
                }
            } else {
                state.toggle = false;
                state.timerEnabled = false;
                state.pulseTriggered = false;
                state.blinkEnabled = false;
            }
            newConfig->setChannelState(event.channelIndex, state);
            m_configManager->setConfig(*newConfig);
            getModel().emit_changed();
        }
    }
    m_signalDataReceived.emit(data);
}

void AppController::configureLogger() {
    if (!m_logger || !m_configManager) {
        return;
    }

    m_logger->close();

    auto &config = getModel();
    auto pathKey = config.toString(Model::ModelLogKey::FilePath);
    auto levelKey = config.toString(Model::ModelLogKey::LogLevel);

    m_logger->setOutputFile(config.getEntity(pathKey));

    uint32_t levelIdx =
        static_cast<uint32_t>(std::stoul(config.getEntity(levelKey)));
    m_logger->setLevel(static_cast<Logger::LogLevel>(levelIdx));

    m_logger->open();
}
