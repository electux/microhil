////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_dbus_helper.cc
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

#include <com/ble/bluez/dbus/bluez_dbus_helper.h>
#include <com/ble/bluez/dbus/bluez_dbus_utils.h>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string_view>

using namespace Electux::App::Com;

namespace {
    constexpr std::string_view cBluezService{"org.bluez"};
    constexpr std::string_view cDbusObjectManagerPath{"/"};
    constexpr std::string_view cDbusObjectManagerInterface{"org.freedesktop.DBus.ObjectManager"};
    constexpr std::string_view cGetManagedObjectsMethod{"GetManagedObjects"};
    constexpr std::string_view cAdapterInterface{"org.bluez.Adapter1"};
    constexpr std::string_view cDeviceInterface{"org.bluez.Device1"};
    constexpr std::string_view cGattCharacteristicInterface{"org.bluez.GattCharacteristic1"};
    constexpr std::string_view cDbusPropertiesInterface{"org.freedesktop.DBus.Properties"};
    constexpr std::string_view cGetMethod{"Get"};
    constexpr std::string_view cConnectMethod{"Connect"};
    constexpr std::string_view cDisconnectMethod{"Disconnect"};
    constexpr std::string_view cStartNotifyMethod{"StartNotify"};
    constexpr std::string_view cStopNotifyMethod{"StopNotify"};
    constexpr std::string_view cWriteValueMethod{"WriteValue"};
    constexpr std::string_view cSetDiscoveryFilterMethod{"SetDiscoveryFilter"};
    constexpr std::string_view cStartDiscoveryMethod{"StartDiscovery"};
    constexpr std::string_view cStopDiscoveryMethod{"StopDiscovery"};
    constexpr std::string_view cConnectedProp{"Connected"};
    constexpr std::string_view cServicesResolvedProp{"ServicesResolved"};
    constexpr std::string_view cTransportKey{"Transport"};
    constexpr std::string_view cLeTransportValue{"le"};
    constexpr std::string_view cWriteTypeKey{"type"};
    constexpr std::string_view cCommandWriteTypeValue{"command"};
    constexpr const char *cDbusSessionEnv{"MICROHIL_DBUS_SESSION_BUS"};
    constexpr std::string_view cErrDbusConn{"BluezDbusHelper D-Bus connection error: "};
} // namespace

BluezDbusHelper::BluezDbusHelper(bool verbose) : m_verbose(verbose) {}

bool BluezDbusHelper::initConnection() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_connection) {
        return true;
    }
    try {
        bool useSessionBus = (std::getenv(cDbusSessionEnv) != nullptr);
        auto busType = useSessionBus ? Gio::DBus::BusType::SESSION : Gio::DBus::BusType::SYSTEM;
        m_connection = Gio::DBus::Connection::get_sync(busType);
        return m_connection != nullptr;
    } catch (const Glib::Error &ex) {
        if (m_verbose) {
            std::cerr << cErrDbusConn << ex.what() << std::endl;
        }
        return false;
    }
}

Glib::RefPtr<Gio::DBus::Connection> BluezDbusHelper::getConnection() {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_connection;
}

Glib::VariantContainerBase BluezDbusHelper::getManagedObjects() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return {};
    }
    try {
        auto objManagerProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            cDbusObjectManagerPath.data(),
            cDbusObjectManagerInterface.data()
        );
        auto result = objManagerProxy->call_sync(cGetManagedObjectsMethod.data());
        if (!result.gobj() || result.get_n_children() == 0) {
            return {};
        }
        return Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(result.get_child(0));
    } catch (...) {
        return {};
    }
}

bool BluezDbusHelper::startLeDiscovery(const Glib::ustring &adapterPath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return false;
    }
    try {
        auto adapterProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            adapterPath,
            cAdapterInterface.data()
        );

        std::map<Glib::ustring, Glib::VariantBase> filterMap;
        filterMap[cTransportKey.data()] = Glib::Variant<Glib::ustring>::create(cLeTransportValue.data());
        auto filterVariant = Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create(filterMap);
        std::vector<Glib::VariantBase> filterArgs;
        filterArgs.push_back(filterVariant);
        try {
            adapterProxy->call_sync(cSetDiscoveryFilterMethod.data(), Glib::VariantContainerBase::create_tuple(filterArgs));
        } catch (...) {}

        adapterProxy->call_sync(cStartDiscoveryMethod.data());
        return true;
    } catch (...) {
        return false;
    }
}

void BluezDbusHelper::stopDiscovery(const Glib::ustring &adapterPath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return;
    }
    try {
        auto adapterProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            adapterPath,
            cAdapterInterface.data()
        );
        adapterProxy->call_sync(cStopDiscoveryMethod.data());
    } catch (...) {}
}

bool BluezDbusHelper::connectDevice(const Glib::ustring &devicePath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return false;
    }
    try {
        auto deviceProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            devicePath,
            cDeviceInterface.data()
        );
        deviceProxy->call_sync(cConnectMethod.data());
        return true;
    } catch (...) {
        return false;
    }
}

void BluezDbusHelper::disconnectDevice(const Glib::ustring &devicePath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return;
    }
    try {
        auto deviceProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            devicePath,
            cDeviceInterface.data()
        );
        deviceProxy->call_sync(cDisconnectMethod.data());
    } catch (...) {}
}

bool BluezDbusHelper::isDeviceConnected(const Glib::ustring &devicePath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return false;
    }
    try {
        auto propProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            devicePath,
            cDbusPropertiesInterface.data()
        );
        std::vector<Glib::VariantBase> getArgs;
        getArgs.push_back(Glib::Variant<Glib::ustring>::create(cDeviceInterface.data()));
        getArgs.push_back(Glib::Variant<Glib::ustring>::create(cConnectedProp.data()));
        auto getResult = propProxy->call_sync(cGetMethod.data(), Glib::VariantContainerBase::create_tuple(getArgs));
        Glib::VariantBase valBase;
        getResult.get_child(valBase, 0);
        return BluezDbusUtils::getBoolFromVariant(valBase);
    } catch (...) {
        return false;
    }
}

bool BluezDbusHelper::areServicesResolved(const Glib::ustring &devicePath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return false;
    }
    try {
        auto propProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            devicePath,
            cDbusPropertiesInterface.data()
        );
        std::vector<Glib::VariantBase> getArgs;
        getArgs.push_back(Glib::Variant<Glib::ustring>::create(cDeviceInterface.data()));
        getArgs.push_back(Glib::Variant<Glib::ustring>::create(cServicesResolvedProp.data()));
        auto getResult = propProxy->call_sync(cGetMethod.data(), Glib::VariantContainerBase::create_tuple(getArgs));
        Glib::VariantBase valBase;
        getResult.get_child(valBase, 0);
        return BluezDbusUtils::getBoolFromVariant(valBase);
    } catch (...) {
        return false;
    }
}

bool BluezDbusHelper::startCharacteristicNotify(const Glib::ustring &charPath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return false;
    }
    try {
        auto rxProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            charPath,
            cGattCharacteristicInterface.data()
        );
        rxProxy->call_sync(cStartNotifyMethod.data());
        return true;
    } catch (...) {
        return false;
    }
}

void BluezDbusHelper::stopCharacteristicNotify(const Glib::ustring &charPath) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return;
    }
    try {
        auto rxProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            charPath,
            cGattCharacteristicInterface.data()
        );
        rxProxy->call_sync(cStopNotifyMethod.data());
    } catch (...) {}
}

void BluezDbusHelper::writeCharacteristic(
    const Glib::ustring &charPath,
    const std::vector<uint8_t> &data
) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connection) {
        return;
    }
    try {
        auto txProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            cBluezService.data(),
            charPath,
            cGattCharacteristicInterface.data()
        );
        auto dataVariant = Glib::Variant<std::vector<uint8_t>>::create(data);
        std::map<Glib::ustring, Glib::VariantBase> optionsMap;
        optionsMap[cWriteTypeKey.data()] = Glib::Variant<Glib::ustring>::create(cCommandWriteTypeValue.data());
        auto optionsVariant = Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create(optionsMap);

        std::vector<Glib::VariantBase> writeArgs;
        writeArgs.push_back(dataVariant);
        writeArgs.push_back(optionsVariant);

        txProxy->call_sync(cWriteValueMethod.data(), Glib::VariantContainerBase::create_tuple(writeArgs));
    } catch (...) {}
}
