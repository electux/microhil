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
#include <chrono>
#include <com/icom.h>
#include <com/icom_configurator.h>
#include <command/formatter/icommand_formatter.h>
#include <command/processor/response_processor.h>
#include <config/iconfig.h>
#include <format>
#include <log/ilog.h>
#include <model/model.h>
#include <string>
#include <vector>

using namespace Electux::App;

namespace {
    constexpr std::chrono::milliseconds cThreadSleepDuration{100};
} // namespace

AppController::AppController(
    std::unique_ptr<Config::IConfig> configManager,
    std::unique_ptr<Com::ICom> comChannel,
    std::unique_ptr<Com::IComConfigurator> comConfigurator,
    std::unique_ptr<Logger::ILog> logger,
    std::unique_ptr<Command::ICommandFormatter> commandFormatter,
    std::unique_ptr<Command::IResponseProcessor> responseProcessor
)
    : m_configManager(std::move(configManager)),
      m_comChannel(std::move(comChannel)),
      m_comConfigurator(std::move(comConfigurator)),
      m_logger(std::move(logger)),
      m_commandFormatter(std::move(commandFormatter)),
      m_responseProcessor(std::move(responseProcessor)) {}

AppController::~AppController() {
    m_stopThread = true;
    if (m_comChannel) {
        m_comChannel->close();
    }
    if (m_readThread.joinable()) {
        m_readThread.join();
    }
}

void AppController::startup() {
    m_configManager->init();
    configureLogger();
    configureComChannel();

    m_stopThread = false;
    m_readThread = std::thread(&AppController::readLoop, this);

    m_logger->log("Application started.", Logger::LogLevel::Info);

    if (m_commandFormatter && m_comChannel && m_comChannel->isOpen()) {
        std::string cmdBoardId = m_commandFormatter->getCommandBoardId();

        if (!cmdBoardId.empty()) {
            std::vector<uint8_t> cmdBytes(cmdBoardId.begin(), cmdBoardId.end());
            m_comChannel->write(cmdBytes);
        }

        std::string cmdVersion = m_commandFormatter->getCommandVersion();

        if (!cmdVersion.empty()) {
            std::vector<uint8_t> cmdBytes(cmdVersion.begin(), cmdVersion.end());
            m_comChannel->write(cmdBytes);
        }
    }
}

void AppController::shutdown() {
    m_stopThread = true;

    if (m_comChannel) {
        m_comChannel->close();
    }

    if (m_readThread.joinable()) {
        m_readThread.join();
    }

    if (m_logger) {
        m_logger->log("Application shutting down.", Logger::LogLevel::Info);
        m_logger->close();
    }

    m_configManager->store();
}

void AppController::configureLogger() {
    if (!m_logger) {
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

void AppController::configureComChannel() {
    if (!m_comChannel || !m_comConfigurator) {
        return;
    }

    m_comChannel->close();
    m_comConfigurator->configure(getModel(), m_comChannel.get());
}

const Model::IModel &AppController::getModel() const {
    return m_configManager->getConfig();
}

void AppController::onSetupChanged(const Model::SettingsSetup &setup) {
    const auto &oldConfig = m_configManager->getConfig();
    auto &newConfig = *setup.m_config;

    handleChannelStateChanges(oldConfig, newConfig);

    bool logChanged = hasLoggerConfigChanged(oldConfig, newConfig);
    bool comChanged = hasSerialConfigChanged(oldConfig, newConfig) ||
                      hasGeneralConfigChanged(oldConfig, newConfig) ||
                      hasBleConfigChanged(oldConfig, newConfig);

    m_configManager->setConfig(newConfig);
    m_configManager->store();

    if (logChanged) {
        configureLogger();
    }

    if (comChanged) {
        configureComChannel();
    }

    getModel().emit_changed();
}

void AppController::handleChannelStateChanges(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (size_t i = 0; i < Model::Channel::cNumOfChannels; ++i) {
        auto oldState = oldConfig.getChannelState(i);
        auto newState = newConfig.getChannelState(i);

        std::string cmd;

        // 1. Detect standard/mode changes
        if (oldState.enabled != newState.enabled ||
            oldState.mode != newState.mode ||
            oldState.toggle != newState.toggle ||
            oldState.timer != newState.timer ||
            oldState.timerEnabled != newState.timerEnabled) {

            std::string logMsg = std::format(
                "Channel {} state changed: enabled={}, mode={}, "
                "toggle={}, timer={}, timerEnabled={}",
                i, newState.enabled, static_cast<int>(newState.mode), newState.toggle,
                newState.timer, newState.timerEnabled
            );

            m_logger->log(logMsg, Logger::LogLevel::Info);

            cmd = m_commandFormatter->getCommandState(i, newState);
        }

        // 2. Detect Pulse trigger (one-shot)
        if (newState.enabled && newState.mode == Model::Channel::ChannelMode::Pulse &&
            newState.pulseTriggered && !oldState.pulseTriggered) {

            std::string logMsg = std::format(
                "Channel {} pulse triggered: duration={}ms",
                i, newState.pulseTime
            );

            m_logger->log(logMsg, Logger::LogLevel::Info);

            cmd = m_commandFormatter->getCommandPulse(i, newState);
        }

        // 3. Detect Blink changes (enable/disable)
        if (newState.enabled && newState.mode == Model::Channel::ChannelMode::Blink) {
            if (oldState.blinkEnabled != newState.blinkEnabled ||
                oldState.blinkOnTime != newState.blinkOnTime ||
                oldState.blinkOffTime != newState.blinkOffTime ||
                oldState.blinkCount != newState.blinkCount) {

                std::string logMsg = std::format(
                    "Channel {} blink state changed: enabled={}, on={}ms, off={}ms, count={}",
                    i, newState.blinkEnabled, newState.blinkOnTime, newState.blinkOffTime, newState.blinkCount
                );

                m_logger->log(logMsg, Logger::LogLevel::Info);

                if (newState.blinkEnabled) {
                    cmd = m_commandFormatter->getCommandBlink(i, newState);
                } else {
                    cmd = std::format("<mh#ch#{}#off#end>", i + 1);
                }
            }
        }

        if (!cmd.empty()) {
            std::vector<uint8_t> cmdBytes(cmd.begin(), cmd.end());

            if (m_comChannel && m_comChannel->isOpen()) {
                m_comChannel->write(cmdBytes);
            }
        }
    }
}

bool AppController::hasSerialConfigChanged(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (int k = static_cast<int>(Model::ModelSerialKey::Device);
         k <= static_cast<int>(Model::ModelSerialKey::Flow); ++k) {
        auto key = oldConfig.toString(static_cast<Model::ModelSerialKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }
    return false;
}

bool AppController::hasLoggerConfigChanged(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (int k = static_cast<int>(Model::ModelLogKey::FilePath);
         k <= static_cast<int>(Model::ModelLogKey::LogLevel); ++k) {
        auto key = oldConfig.toString(static_cast<Model::ModelLogKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }
    return false;
}

bool AppController::hasGeneralConfigChanged(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (int k = static_cast<int>(Model::ModelGeneralKey::ComType);
         k <= static_cast<int>(Model::ModelGeneralKey::TcpPort); ++k) {
        auto key = oldConfig.toString(static_cast<Model::ModelGeneralKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }
    return false;
}

bool AppController::hasBleConfigChanged(
    const Model::IModel &oldConfig, const Model::IModel &newConfig
) {
    for (int k = static_cast<int>(Model::ModelBleKey::Address);
         k <= static_cast<int>(Model::ModelBleKey::TxUuid); ++k) {
        auto key = oldConfig.toString(static_cast<Model::ModelBleKey>(k));

        if (oldConfig.getEntity(key) != newConfig.getEntity(key)) {
            return true;
        }
    }
    return false;
}

sigc::signal<void(const std::string &)> AppController::signal_data_received() {
    return m_signalDataReceived;
}

void AppController::readLoop() {
    while (!m_stopThread) {
        try {
            if (m_comChannel && m_comChannel->isOpen()) {
                std::vector<uint8_t> buffer;
                m_comChannel->read(buffer, 1);

                if (!buffer.empty()) {
                    std::string dataStr(buffer.begin(), buffer.end());

                    if (m_responseProcessor) {
                        auto payloads = m_responseProcessor->process(dataStr);

                        for (const auto &payload : payloads) {
                            m_signalDataReceived.emit(payload);
                        }

                    } else {
                        m_signalDataReceived.emit(dataStr);
                    }
                }

            } else {
                std::this_thread::sleep_for(cThreadSleepDuration);
            }
        } catch (...) {
            std::this_thread::sleep_for(cThreadSleepDuration);
        }
    }
}
