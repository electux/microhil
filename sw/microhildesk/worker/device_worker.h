////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// device_worker.h
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

#include <atomic>
#include <com/icom.h>
#include <com/icom_configurator.h>
#include <command/formatter/icommand_formatter.h>
#include <command/processor/iresponse_processor.h>
#include <log/ilog.h>
#include <memory>
#include <model/imodel.h>
#include <thread>
#include <worker/connection_state.h>
#include <worker/idevice_worker.h>

namespace Electux::App::Worker {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class DeviceWorker
    /// @brief Manages background I/O communication, reconnection, and data dispatching.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class DeviceWorker : public IDeviceWorker {
      public:
        DeviceWorker(
            std::unique_ptr<Com::ICom> comChannel,
            std::unique_ptr<Com::IComConfigurator> comConfigurator,
            std::unique_ptr<Command::ICommandFormatter> commandFormatter,
            std::unique_ptr<Command::IResponseProcessor> responseProcessor,
            Logger::ILog *logger = nullptr
        );
        ~DeviceWorker() override;

        DeviceWorker(const DeviceWorker &) = delete;
        DeviceWorker &operator=(const DeviceWorker &) = delete;

        void start() override;
        void stop() override;
        void configure(const Model::IModel &model) override;
        void send(const std::string &command) override;
        void setNeedInitialQuery(bool need) override;
        bool isConnected() const override;
        ConnectionState getConnectionState() const override;
        sigc::signal<void(const std::string &)> signal_data_received() override;
        sigc::signal<void(ConnectionState)> signal_connection_state() override;

      private:
        void readLoop();
        void queryInitialDeviceStatus();
        void updateConnectionState(ConnectionState state);
        std::string getConnectionLossErrorMessage() const;

        std::unique_ptr<Com::ICom> m_comChannel;
        std::unique_ptr<Com::IComConfigurator> m_comConfigurator;
        std::unique_ptr<Command::ICommandFormatter> m_commandFormatter;
        std::unique_ptr<Command::IResponseProcessor> m_responseProcessor;
        Logger::ILog *m_logger;

        std::thread m_readThread;
        std::atomic<bool> m_stopThread{false};
        std::atomic<bool> m_needInitialQuery{true};
        std::atomic<ConnectionState> m_connectionState{ConnectionState::Disconnected};
        sigc::signal<void(const std::string &)> m_signalDataReceived;
        sigc::signal<void(ConnectionState)> m_signalConnectionState;
    };
} // namespace Electux::App::Worker
