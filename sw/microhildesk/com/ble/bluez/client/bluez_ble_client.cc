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

#include <chrono>
#include <com/ble/bluez/client/bluez_ble_client.h>
#include <com/ble/bluez/dbus/bluez_dbus_factory.h>
#include <com/ble/bluez/dbus/bluez_dbus_utils.h>
#include <com/ble/bluez/resolver/bluez_device_resolver.h>
#include <iostream>
#include <string_view>
#include <thread>

using namespace Electux::App::Com;

namespace {
    constexpr const char *cBluezService{"org.bluez"};
    constexpr const char *cDbusPropertiesInterface{
        "org.freedesktop.DBus.Properties"
    };
    constexpr const char *cPropertiesChangedSignal{"PropertiesChanged"};
    constexpr const char *cGattCharacteristicInterface{
        "org.bluez.GattCharacteristic1"
    };
    constexpr const char *cValueProp{"Value"};
    constexpr int cDiscoveryTimeoutSec{3};
    constexpr int cServicesResolveTimeoutSec{4};
    constexpr std::chrono::milliseconds cPollingInterval{100};
    constexpr const char *cErrDevNotFound{
        "BluezBleClient connect error: Device not found."
    };
    constexpr const char *cErrGattNotFound{
        "BluezBleClient connect error: GATT Characteristics not found."
    };
} // namespace

BluezBleClient::BluezBleClient(
    const std::string &address, const std::string &serviceUuid,
    const std::string &rxUuid, const std::string &txUuid, bool verbose,
    std::unique_ptr<IDbusHelper> dbusHelper
)
    : m_address(address), m_serviceUuid(serviceUuid), m_rxUuid(rxUuid),
      m_txUuid(txUuid), m_connected(false), m_verbose(verbose),
      m_dbusHelper(
          dbusHelper ? std::move(dbusHelper) : createBluezDbusHelper(verbose)
      ),
      m_signalSubscriptionId(0) {}

BluezBleClient::~BluezBleClient() {
    abort();
    disconnect();
}

void BluezBleClient::abort() { m_abort = true; }

bool BluezBleClient::connect(NotificationCallback callback) {
    m_abort = false;

    if (!m_dbusHelper || !m_dbusHelper->initConnection()) {
        return false;
    }

    auto objects = m_dbusHelper->getManagedObjects();
    Glib::ustring devPath =
        BluezDeviceResolver::findDevicePath(objects, m_address);

    if (devPath.empty()) {
        Glib::ustring adapterPath =
            BluezDeviceResolver::findAdapterPath(objects);
        m_dbusHelper->startLeDiscovery(adapterPath);

        auto startTime = std::chrono::steady_clock::now();
        while (devPath.empty() && !m_abort) {
            std::this_thread::sleep_for(cPollingInterval);
            auto now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(
                    now - startTime
                )
                    .count() > cDiscoveryTimeoutSec) {
                break;
            }
            auto pollObjects = m_dbusHelper->getManagedObjects();
            devPath =
                BluezDeviceResolver::findDevicePath(pollObjects, m_address);
        }

        m_dbusHelper->stopDiscovery(adapterPath);

        if (devPath.empty() || m_abort) {
            if (m_verbose && devPath.empty()) {
                std::cerr << cErrDevNotFound << " [" << m_address << "]"
                          << std::endl;
            }
            return false;
        }
    }

    if (m_abort) {
        return false;
    }

    if (!m_dbusHelper->isDeviceConnected(devPath)) {
        if (!m_dbusHelper->connectDevice(devPath)) {
            Glib::ustring adapterPath =
                BluezDeviceResolver::findAdapterPath(objects);
            m_dbusHelper->startLeDiscovery(adapterPath);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            bool connected = m_dbusHelper->connectDevice(devPath);
            m_dbusHelper->stopDiscovery(adapterPath);
            if (!connected) {
                return false;
            }
        }
    }

    if (m_abort) {
        return false;
    }

    auto startResolveTime = std::chrono::steady_clock::now();
    while (!m_dbusHelper->areServicesResolved(devPath) && !m_abort) {
        std::this_thread::sleep_for(cPollingInterval);
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(
                now - startResolveTime
            )
                .count() > cServicesResolveTimeoutSec) {
            break;
        }
    }

    if (m_abort) {
        return false;
    }

    Glib::ustring rxPath;
    Glib::ustring txPath;
    auto startGattTime = std::chrono::steady_clock::now();
    while (!m_abort) {
        auto gattObjects = m_dbusHelper->getManagedObjects();
        if (BluezDeviceResolver::findGattPaths(
                gattObjects, devPath, m_serviceUuid, m_rxUuid, m_txUuid, rxPath,
                txPath
            )) {
            break;
        }
        auto now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(
                now - startGattTime
            )
                .count() > cServicesResolveTimeoutSec) {
            break;
        }
        std::this_thread::sleep_for(cPollingInterval);
    }

    if (rxPath.empty() || txPath.empty() || m_abort) {
        if (m_verbose) {
            std::cerr << cErrGattNotFound << std::endl;
        }
        return false;
    }

    if (m_abort) {
        return false;
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    m_devicePath = devPath;
    m_rxPath = rxPath;
    m_txPath = txPath;
    m_callback = std::move(callback);

    auto connection = m_dbusHelper->getConnection();
    if (connection && m_signalSubscriptionId == 0) {
        m_signalSubscriptionId = connection->signal_subscribe(
            sigc::mem_fun(*this, &BluezBleClient::onPropertiesChanged),
            cBluezService, cDbusPropertiesInterface, cPropertiesChangedSignal,
            m_rxPath
        );
    }

    m_dbusHelper->startCharacteristicNotify(m_rxPath);
    m_connected = true;
    return true;
}

bool BluezBleClient::disconnect() {
    std::lock_guard<std::mutex> lock(m_mutex);

    if (m_signalSubscriptionId != 0 && m_dbusHelper) {
        auto connection = m_dbusHelper->getConnection();
        if (connection) {
            connection->signal_unsubscribe(m_signalSubscriptionId);
        }
        m_signalSubscriptionId = 0;
    }

    if (!m_rxPath.empty() && m_dbusHelper) {
        m_dbusHelper->stopCharacteristicNotify(m_rxPath);
    }

    if (!m_devicePath.empty() && m_dbusHelper) {
        m_dbusHelper->disconnectDevice(m_devicePath);
    }

    m_connected = false;
    m_rxPath.clear();
    m_txPath.clear();
    m_devicePath.clear();

    return true;
}

bool BluezBleClient::isConnected() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_connected;
}

void BluezBleClient::write(const std::vector<uint8_t> &data) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_connected || m_txPath.empty() || !m_dbusHelper) {
        return;
    }
    m_dbusHelper->writeCharacteristic(m_txPath, data);
}

void BluezBleClient::onPropertiesChanged(
    const Glib::RefPtr<Gio::DBus::Connection> & /*connection*/,
    const Glib::ustring & /*sender_name*/, const Glib::ustring &object_path,
    const Glib::ustring & /*interface_name*/,
    const Glib::ustring & /*signal_name*/,
    const Glib::VariantContainerBase &parameters
) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (object_path != m_rxPath || parameters.get_n_children() < 2) {
        return;
    }

    Glib::ustring iface =
        BluezDbusUtils::getStringFromVariant(parameters.get_child(0));
    if (iface != cGattCharacteristicInterface) {
        return;
    }

    Glib::VariantContainerBase changedProps =
        Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(
            parameters.get_child(1)
        );
    size_t nProps = changedProps.get_n_children();
    for (size_t i = 0; i < nProps; ++i) {
        Glib::VariantContainerBase propEntry;
        changedProps.get_child(propEntry, i);
        Glib::ustring propName =
            BluezDbusUtils::getStringFromVariant(propEntry.get_child(0));

        if (propName == cValueProp) {
            std::vector<uint8_t> bytes =
                BluezDbusUtils::getByteVectorFromVariant(
                    propEntry.get_child(1)
                );
            if (m_callback && !bytes.empty()) {
                m_callback(bytes);
            }
        }
    }
}
