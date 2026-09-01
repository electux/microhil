////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// app_controller.h
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
#pragma once

#include <command/formatter/icommand_formatter.h>
#include <command/mapper/ichannel_command_mapper.h>
#include <command/processor/iresponse_processor.h>
#include <config/detector/iconfig_change_detector.h>
#include <config/iconfig.h>
#include <iapp_controller.h>
#include <log/ilog.h>
#include <memory>
#include <model/imodel.h>
#include <view/settings_setup.h>
#include <worker/connection_state.h>
#include <worker/idevice_worker.h>

namespace Electux::App {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class AppController
    /// @brief High-level application coordinator managing config, logging, mapping, and worker.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class AppController : public IAppController {
      public:
        AppController(
            std::unique_ptr<Config::IConfig> configManager,
            std::unique_ptr<Worker::IDeviceWorker> deviceWorker,
            std::unique_ptr<Logger::ILog> logger,
            std::unique_ptr<Command::ICommandFormatter> commandFormatter,
            std::unique_ptr<Command::IChannelCommandMapper> channelMapper,
            std::unique_ptr<Config::IConfigChangeDetector> configDetector,
            std::unique_ptr<Command::IResponseProcessor> responseProcessor
        );
        ~AppController() override = default;

        AppController(const AppController &) = delete;
        AppController &operator=(const AppController &) = delete;

        void startup() override;
        void shutdown() override;

        const Model::IModel &getModel() const override;
        void onSetupChanged(const Model::SettingsSetup &setup) override;

        sigc::signal<void(const std::string &)> signal_data_received() override;
        sigc::signal<void(Worker::ConnectionState)> signal_connection_state() override;
        Worker::ConnectionState getConnectionState() const override;

        void turnOnAllChannels() override;
        void turnOffAllChannels() override;
        void requestAllChannelsStatus() override;
        void resetSystem() override;
        void requestBoardId() override;
        void requestVersion() override;

      private:
        void configureLogger();
        void handleChannelStateChange(
            size_t channelIndex, const Model::ChannelState &state
        );
        void onDeviceDataReceived(const std::string &data);

        std::unique_ptr<Config::IConfig> m_configManager;
        std::unique_ptr<Worker::IDeviceWorker> m_deviceWorker;
        std::unique_ptr<Logger::ILog> m_logger;
        std::unique_ptr<Command::ICommandFormatter> m_commandFormatter;
        std::unique_ptr<Command::IChannelCommandMapper> m_channelMapper;
        std::unique_ptr<Config::IConfigChangeDetector> m_configDetector;
        std::unique_ptr<Command::IResponseProcessor> m_responseProcessor;
        sigc::signal<void(const std::string &)> m_signalDataReceived;
    };
} // namespace Electux::App
