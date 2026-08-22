////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_ble_client.cc
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

#include <com/ble/bluez_ble_client.h>
#include <com/ble/bluez_device_resolver.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace Electux::App::Com;

namespace {
    Glib::ustring get_string_from_variant(const Glib::VariantBase& var) {
        gsize length = 0;
        const gchar* str = g_variant_get_string(const_cast<GVariant*>(var.gobj()), &length);
        return Glib::ustring(str, length);
    }

    bool get_bool_from_variant(const Glib::VariantBase& var) {
        return g_variant_get_boolean(const_cast<GVariant*>(var.gobj())) != 0;
    }
} // namespace

BluezBleClient::BluezBleClient(
    const std::string &address,
    const std::string &serviceUuid,
    const std::string &rxUuid,
    const std::string &txUuid
) : m_address(address),
    m_serviceUuid(serviceUuid),
    m_rxUuid(rxUuid),
    m_txUuid(txUuid),
    m_connected(false),
    m_subscriptionId(0) {}

BluezBleClient::~BluezBleClient() {
    disconnect();
}

bool BluezBleClient::connect(NotificationCallback callback) {
    if (m_connected) {
        return true;
    }

    if (m_address.empty() || m_serviceUuid.empty() || m_rxUuid.empty() || m_txUuid.empty()) {
        std::cerr << "BluezBleClient connect error: BLE configuration is incomplete." << std::endl;
        return false;
    }

    try {
        bool useSessionBus = (std::getenv("MICROHILDESK_DBUS_SESSION") != nullptr);
        auto busType = useSessionBus ? Gio::DBus::BusType::SESSION : Gio::DBus::BusType::SYSTEM;
        m_connection = Gio::DBus::Connection::get_sync(busType);
        if (!m_connection) {
            std::cerr << "BluezBleClient connect error: Failed to connect to D-Bus (" 
                      << (useSessionBus ? "Session" : "System") << ")." << std::endl;
            return false;
        }

        auto objManagerProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            "org.bluez",
            "/",
            "org.freedesktop.DBus.ObjectManager"
        );

        // Find device path matching MAC address
        Glib::VariantContainerBase objectsResult = objManagerProxy->call_sync("GetManagedObjects");
        Glib::VariantContainerBase objectsBase = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(objectsResult.get_child(0));

        Glib::ustring devPath = BluezDeviceResolver::findDevicePath(objectsBase, m_address);

        if (devPath.empty()) {
            std::cerr << "BluezBleClient connect error: Device with address " << m_address << " not found in managed objects." << std::endl;
            return false;
        }

        m_devicePath = devPath;

        // Check connection status
        auto propProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            "org.bluez",
            m_devicePath,
            "org.freedesktop.DBus.Properties"
        );

        std::vector<Glib::VariantBase> getArgs;
        getArgs.push_back(Glib::Variant<Glib::ustring>::create("org.bluez.Device1"));
        getArgs.push_back(Glib::Variant<Glib::ustring>::create("Connected"));
        auto getResult = propProxy->call_sync("Get", Glib::VariantContainerBase::create_tuple(getArgs));
        Glib::VariantBase valBase;
        getResult.get_child(valBase, 0);
        GVariant* innerGVar = g_variant_get_variant(const_cast<GVariant*>(valBase.gobj()));
        Glib::VariantBase innerVal(innerGVar, true);
        bool isConnected = get_bool_from_variant(innerVal);

        if (!isConnected) {
            auto deviceProxy = Gio::DBus::Proxy::create_sync(
                m_connection,
                "org.bluez",
                m_devicePath,
                "org.bluez.Device1"
            );
            deviceProxy->call_sync("Connect");
        }

        // Wait for services to resolve (timeout after 15 seconds)
        bool servicesResolved = false;
        for (int i = 0; i < 30; ++i) {
            std::vector<Glib::VariantBase> getArgs2;
            getArgs2.push_back(Glib::Variant<Glib::ustring>::create("org.bluez.Device1"));
            getArgs2.push_back(Glib::Variant<Glib::ustring>::create("ServicesResolved"));
            auto getResult2 = propProxy->call_sync("Get", Glib::VariantContainerBase::create_tuple(getArgs2));
            Glib::VariantBase valBase2;
            getResult2.get_child(valBase2, 0);
            GVariant* innerGVar2 = g_variant_get_variant(const_cast<GVariant*>(valBase2.gobj()));
            Glib::VariantBase innerVal2(innerGVar2, true);
            bool isResolved = get_bool_from_variant(innerVal2);
            if (isResolved) {
                servicesResolved = true;
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }

        if (!servicesResolved) {
            std::cerr << "BluezBleClient connect error: GATT services could not be resolved in time." << std::endl;
            return false;
        }

        // Find RX and TX characteristics
        if (!BluezDeviceResolver::findGattPaths(objectsBase, m_devicePath, m_serviceUuid, m_rxUuid, m_txUuid, m_rxCharPath, m_txCharPath)) {
            std::cerr << "BluezBleClient connect error: GATT Characteristics matching RX/TX UUIDs not found." << std::endl;
            return false;
        }

        // Subscribe to notifications/indications on RX path
        m_notificationCallback = callback;
        m_subscriptionId = m_connection->signal_subscribe(
            sigc::mem_fun(*this, &BluezBleClient::onPropertiesChanged),
            "org.bluez",
            "org.freedesktop.DBus.Properties",
            "PropertiesChanged",
            m_rxCharPath
        );

        // Start notifications on RX Characteristic
        auto rxProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            "org.bluez",
            m_rxCharPath,
            "org.bluez.GattCharacteristic1"
        );
        rxProxy->call_sync("StartNotify");

        m_connected = true;
        std::cout << "BluezBleClient connected successfully to device: " << m_address << std::endl;
        return true;
    } catch (const Glib::Error &ex) {
        std::cerr << "BluezBleClient connect error: D-Bus call failed: " << ex.what() << std::endl;
        disconnect();
        return false;
    }
}

bool BluezBleClient::disconnect() {
    if (m_connected) {
        if (!m_rxCharPath.empty() && m_connection) {
            try {
                auto rxProxy = Gio::DBus::Proxy::create_sync(
                    m_connection,
                    "org.bluez",
                    m_rxCharPath,
                    "org.bluez.GattCharacteristic1"
                );
                rxProxy->call_sync("StopNotify");
            } catch (...) {}
        }
        if (m_subscriptionId > 0 && m_connection) {
            m_connection->signal_unsubscribe(m_subscriptionId);
            m_subscriptionId = 0;
        }
        if (!m_devicePath.empty() && m_connection) {
            try {
                auto deviceProxy = Gio::DBus::Proxy::create_sync(
                    m_connection,
                    "org.bluez",
                    m_devicePath,
                    "org.bluez.Device1"
                );
                deviceProxy->call_sync("Disconnect");
            } catch (...) {}
        }
        m_connected = false;
        m_devicePath.clear();
        m_rxCharPath.clear();
        m_txCharPath.clear();
        m_connection.reset();
        m_notificationCallback = nullptr;
        std::cout << "BluezBleClient disconnected successfully." << std::endl;
        return true;
    }
    return false;
}

bool BluezBleClient::isConnected() const { return m_connected; }

void BluezBleClient::write(const std::vector<uint8_t> &data) {
    if (!isConnected() || m_txCharPath.empty() || !m_connection) {
        std::cerr << "BluezBleClient write error: Connection is not open." << std::endl;
        return;
    }

    try {
        auto txProxy = Gio::DBus::Proxy::create_sync(
            m_connection,
            "org.bluez",
            m_txCharPath,
            "org.bluez.GattCharacteristic1"
        );

        auto dataVariant = Glib::Variant<std::vector<uint8_t>>::create(data);
        std::map<Glib::ustring, Glib::VariantBase> optionsMap;
        auto optionsVariant = Glib::Variant<std::map<Glib::ustring, Glib::VariantBase>>::create(optionsMap);

        std::vector<Glib::VariantBase> tupleChildren;
        tupleChildren.push_back(dataVariant);
        tupleChildren.push_back(optionsVariant);

        auto parameters = Glib::VariantContainerBase::create_tuple(tupleChildren);
        txProxy->call_sync("WriteValue", parameters);
    } catch (const Glib::Error &ex) {
        std::cerr << "BluezBleClient write error: " << ex.what() << std::endl;
        disconnect();
    }
}

void BluezBleClient::onPropertiesChanged(
    const Glib::RefPtr<Gio::DBus::Connection>& connection,
    const Glib::ustring& sender_name,
    const Glib::ustring& object_path,
    const Glib::ustring& interface_name,
    const Glib::ustring& signal_name,
    const Glib::VariantContainerBase& parameters
) {
    (void)connection;
    (void)sender_name;
    (void)signal_name;
    if (parameters.get_n_children() < 2) return;

    Glib::Variant<Glib::ustring> interfaceVariant;
    parameters.get_child(interfaceVariant, 0);
    Glib::ustring targetInterface = interfaceVariant.get();

    if (targetInterface == "org.bluez.GattCharacteristic1" && object_path == m_rxCharPath) {
        Glib::VariantContainerBase changedProps = Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(parameters.get_child(1));
        size_t nProps = changedProps.get_n_children();
        for (size_t i = 0; i < nProps; ++i) {
            Glib::VariantContainerBase propEntry;
            changedProps.get_child(propEntry, i);

            Glib::ustring keyStr = get_string_from_variant(propEntry.get_child(0));

            if (keyStr == "Value") {
                Glib::VariantBase valBase = propEntry.get_child(1);
                GVariant* innerGVar = g_variant_get_variant(const_cast<GVariant*>(valBase.gobj()));
                Glib::VariantBase actualVal(innerGVar, true);
                if (actualVal.get_type_string() == "ay") {
                    gsize n_elements = 0;
                    gconstpointer data_ptr = g_variant_get_fixed_array(const_cast<GVariant*>(actualVal.gobj()), &n_elements, 1);
                    if (data_ptr && n_elements > 0) {
                        const uint8_t* raw_bytes = static_cast<const uint8_t*>(data_ptr);
                        std::vector<uint8_t> bytes(raw_bytes, raw_bytes + n_elements);

                        if (m_notificationCallback) {
                            m_notificationCallback(bytes);
                        }
                    }
                }
            }
        }
    }
}
