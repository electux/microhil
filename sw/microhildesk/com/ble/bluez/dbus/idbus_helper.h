////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// idbus_helper.h
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

#include <giomm/dbusconnection.h>
#include <giomm/dbusproxy.h>
#include <glibmm/variant.h>
#include <glibmm/ustring.h>
#include <atomic>
#include <string>
#include <vector>

namespace Electux::App::Com {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class IDbusHelper
    /// @brief Interface for BlueZ D-Bus proxy operations and LE discovery.
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class IDbusHelper {
      public:
        virtual ~IDbusHelper() = default;

        virtual bool initConnection() = 0;
        virtual Glib::RefPtr<Gio::DBus::Connection> getConnection() = 0;
        virtual Glib::VariantContainerBase getManagedObjects() = 0;

        virtual bool startLeDiscovery(const Glib::ustring &adapterPath) = 0;
        virtual void stopDiscovery(const Glib::ustring &adapterPath) = 0;

        virtual bool connectDevice(const Glib::ustring &devicePath) = 0;
        virtual void disconnectDevice(const Glib::ustring &devicePath) = 0;

        virtual bool isDeviceConnected(const Glib::ustring &devicePath) = 0;
        virtual bool areServicesResolved(const Glib::ustring &devicePath) = 0;

        virtual bool startCharacteristicNotify(const Glib::ustring &charPath) = 0;
        virtual void stopCharacteristicNotify(const Glib::ustring &charPath) = 0;

        virtual void writeCharacteristic(
            const Glib::ustring &charPath,
            const std::vector<uint8_t> &data
        ) = 0;
    };
} // namespace Electux::App::Com
