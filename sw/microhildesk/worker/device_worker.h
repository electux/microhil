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
#pragma once

#include <atomic>
#include <chrono>
#include <com/icom.h>
#include <com/icom_configurator.h>
#include <command/formatter/icommand_formatter.h>
#include <command/processor/iresponse_processor.h>
#include <condition_variable>
#include <glibmm/dispatcher.h>
#include <log/ilog.h>
#include <memory>
#include <model/imodel.h>
#include <mutex>
#include <queue>
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
        void connect() override;
        void disconnect() override;
        void configure(const Model::IModel &model) override;
        void send(const std::string &command) override;
        bool isConnected() const override;
        ConnectionState getConnectionState() const override;
        sigc::signal<void(const std::string &)> signal_data_received() override;
        sigc::signal<void(ConnectionState)> signal_connection_state() override;

      private:
        void readLoop();
        void handleDisconnectedState();
        bool handleConnectingState(
            std::chrono::steady_clock::time_point &handshakeStartTime
        );
        bool checkHandshakeTimeout(
            const std::chrono::steady_clock::time_point &handshakeStartTime
        );
        void handleDataIO();
        void processIncomingData(const std::string &dataStr);
        void queryInitialDeviceStatus();
        void updateConnectionState(ConnectionState state);
        void emitData(const std::string &data);
        std::string getConnectionLossErrorMessage() const;

        std::unique_ptr<Com::ICom> m_comChannel;
        std::unique_ptr<Com::IComConfigurator> m_comConfigurator;
        std::unique_ptr<Command::ICommandFormatter> m_commandFormatter;
        std::unique_ptr<Command::IResponseProcessor> m_responseProcessor;
        Logger::ILog *m_logger;

        std::thread m_readThread;
        std::mutex m_ioMutex;
        std::mutex m_stateMutex;
        std::condition_variable m_cv;
        std::mutex m_queueMutex;
        std::queue<std::string> m_dataQueue;
        Glib::Dispatcher m_dataDispatcher;
        Glib::Dispatcher m_stateDispatcher;
        std::atomic<bool> m_stopThread{false};
        std::atomic<bool> m_connectRequested{false};
        std::atomic<ConnectionState> m_connectionState{ConnectionState::Disconnected};
        std::atomic<ConnectionState> m_pendingState{ConnectionState::Disconnected};
        sigc::signal<void(const std::string &)> m_signalDataReceived;
        sigc::signal<void(ConnectionState)> m_signalConnectionState;
    };
} // namespace Electux::App::Worker
