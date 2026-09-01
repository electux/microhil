////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_dbus_helper.h
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

#include <com/ble/bluez/dbus/idbus_helper.h>
#include <mutex>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class BluezDbusHelper
    /// @brief Manages D-Bus connection and proxy calls for BlueZ.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class BluezDbusHelper : public IDbusHelper {
      public:
        explicit BluezDbusHelper(bool verbose = false);
        ~BluezDbusHelper() override = default;

        bool initConnection() override;
        Glib::RefPtr<Gio::DBus::Connection> getConnection() override;
        Glib::VariantContainerBase getManagedObjects() override;

        bool startLeDiscovery(const Glib::ustring &adapterPath) override;
        void stopDiscovery(const Glib::ustring &adapterPath) override;

        bool connectDevice(const Glib::ustring &devicePath) override;
        void disconnectDevice(const Glib::ustring &devicePath) override;

        bool isDeviceConnected(const Glib::ustring &devicePath) override;
        bool areServicesResolved(const Glib::ustring &devicePath) override;

        bool startCharacteristicNotify(const Glib::ustring &charPath) override;
        void stopCharacteristicNotify(const Glib::ustring &charPath) override;

        void writeCharacteristic(
            const Glib::ustring &charPath,
            const std::vector<uint8_t> &data
        ) override;

      private:
        bool m_verbose;
        Glib::RefPtr<Gio::DBus::Connection> m_connection;
        mutable std::mutex m_mutex;
    };
} // namespace Electux::App::Com
