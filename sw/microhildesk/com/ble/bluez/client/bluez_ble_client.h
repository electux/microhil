////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_ble_client.h
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

#include <com/ble/client/ible_client.h>
#include <com/ble/bluez/dbus/idbus_helper.h>
#include <string>
#include <vector>
#include <functional>
#include <mutex>
#include <atomic>
#include <memory>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class BluezBleClient
    /// @brief High-level BlueZ GATT Client managing connection, notifications and packet I/O.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class BluezBleClient : public IBleClient {
      public:
        BluezBleClient(
            const std::string &address,
            const std::string &serviceUuid,
            const std::string &rxUuid,
            const std::string &txUuid,
            bool verbose = false,
            std::unique_ptr<IDbusHelper> dbusHelper = nullptr
        );
        ~BluezBleClient() override;

        BluezBleClient(const BluezBleClient &) = delete;
        BluezBleClient &operator=(const BluezBleClient &) = delete;

        bool connect(NotificationCallback callback) override;
        bool disconnect() override;
        void abort() override;
        bool isConnected() const override;

        void write(const std::vector<uint8_t> &data) override;

      private:
        void onPropertiesChanged(
            const Glib::RefPtr<Gio::DBus::Connection>& connection,
            const Glib::ustring& sender_name,
            const Glib::ustring& object_path,
            const Glib::ustring& interface_name,
            const Glib::ustring& signal_name,
            const Glib::VariantContainerBase& parameters
        );

        std::string m_address;
        std::string m_serviceUuid;
        std::string m_rxUuid;
        std::string m_txUuid;

        bool m_connected;
        bool m_verbose;
        std::unique_ptr<IDbusHelper> m_dbusHelper;
        Glib::ustring m_devicePath;
        Glib::ustring m_rxPath;
        Glib::ustring m_txPath;

        guint m_signalSubscriptionId;
        NotificationCallback m_callback;
        mutable std::mutex m_mutex;
        std::atomic<bool> m_abort{false};
    };
} // namespace Electux::App::Com
