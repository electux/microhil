////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// idevice_worker.h
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

#include <model/imodel.h>
#include <sigc++/sigc++.h>
#include <string>
#include <worker/connection_state.h>

namespace Electux::App::Worker {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IDeviceWorker
    /// @brief Interface for device background I/O worker and connection manager.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IDeviceWorker {
      public:
        virtual ~IDeviceWorker() = default;

        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void connect() = 0;
        virtual void disconnect() = 0;
        virtual void configure(const Model::IModel &model) = 0;
        virtual void send(const std::string &command) = 0;
        virtual void setNeedInitialQuery(bool need) = 0;
        virtual bool isConnected() const = 0;
        virtual ConnectionState getConnectionState() const = 0;
        virtual sigc::signal<void(const std::string &)> signal_data_received() = 0;
        virtual sigc::signal<void(ConnectionState)> signal_connection_state() = 0;
    };
} // namespace Electux::App::Worker
