////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_device_resolver.cc
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

#include <algorithm>
#include <com/ble/bluez/dbus/bluez_dbus_utils.h>
#include <com/ble/bluez/resolver/bluez_device_resolver.h>
#include <map>
#include <string_view>

using namespace Electux::App::Com;

namespace {
    constexpr const char *cAdapterInterface{"org.bluez.Adapter1"};
    constexpr const char *cDeviceInterface{"org.bluez.Device1"};
    constexpr const char *cAddressProp{"Address"};
    constexpr const char *cNameProp{"Name"};
    constexpr const char *cAliasProp{"Alias"};
    constexpr const char *cGattCharacteristicInterface{
        "org.bluez.GattCharacteristic1"
    };
    constexpr const char *cUuidProp{"UUID"};
    constexpr const char *cServiceProp{"Service"};
    constexpr const char *cGattServiceInterface{"org.bluez.GattService1"};
    constexpr const char *cDeviceProp{"Device"};
    constexpr const char *cDefaultAdapterPath{"/org/bluez/hci0"};
    constexpr const char *cEmptyString{""};
} // namespace

Glib::ustring BluezDeviceResolver::findAdapterPath(
    const Glib::VariantContainerBase &objectsBase
) {
    if (!objectsBase.gobj()) {
        return cDefaultAdapterPath;
    }

    size_t nObjects = objectsBase.get_n_children();

    for (size_t i = 0; i < nObjects; ++i) {
        Glib::VariantContainerBase objEntry;
        objectsBase.get_child(objEntry, i);
        if (!objEntry.gobj()) {
            continue;
        }

        Glib::ustring path =
            BluezDbusUtils::getStringFromVariant(objEntry.get_child(0));

        Glib::VariantContainerBase interfacesVar =
            Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(
                objEntry.get_child(1)
            );
        if (!interfacesVar.gobj()) {
            continue;
        }

        size_t nInterfaces = interfacesVar.get_n_children();

        for (size_t j = 0; j < nInterfaces; ++j) {
            Glib::VariantContainerBase intEntry;
            interfacesVar.get_child(intEntry, j);
            if (!intEntry.gobj()) {
                continue;
            }

            Glib::ustring interfaceName =
                BluezDbusUtils::getStringFromVariant(intEntry.get_child(0));

            if (interfaceName == cAdapterInterface) {
                return path;
            }
        }
    }

    return cDefaultAdapterPath;
}

Glib::ustring BluezDeviceResolver::findDevicePath(
    const Glib::VariantContainerBase &objectsBase, const std::string &address
) {
    if (!objectsBase.gobj()) {
        return cEmptyString;
    }

    std::string formattedAddr = BluezDbusUtils::normalizeMacAddress(address);
    if (formattedAddr.empty()) {
        formattedAddr = address;
    }

    size_t nObjects = objectsBase.get_n_children();

    for (size_t i = 0; i < nObjects; ++i) {
        Glib::VariantContainerBase objEntry;
        objectsBase.get_child(objEntry, i);
        if (!objEntry.gobj()) {
            continue;
        }

        Glib::ustring path =
            BluezDbusUtils::getStringFromVariant(objEntry.get_child(0));

        Glib::VariantContainerBase interfacesVar =
            Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(
                objEntry.get_child(1)
            );
        if (!interfacesVar.gobj()) {
            continue;
        }

        size_t nInterfaces = interfacesVar.get_n_children();

        for (size_t j = 0; j < nInterfaces; ++j) {
            Glib::VariantContainerBase intEntry;
            interfacesVar.get_child(intEntry, j);
            if (!intEntry.gobj()) {
                continue;
            }

            Glib::ustring interfaceName =
                BluezDbusUtils::getStringFromVariant(intEntry.get_child(0));

            if (interfaceName == cDeviceInterface) {
                if (!formattedAddr.empty() &&
                    path.find(formattedAddr) != std::string::npos) {
                    return path;
                }

                Glib::VariantContainerBase propertiesVar =
                    Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(
                        intEntry.get_child(1)
                    );
                if (!propertiesVar.gobj()) {
                    continue;
                }

                size_t nProps = propertiesVar.get_n_children();

                for (size_t k = 0; k < nProps; ++k) {
                    Glib::VariantContainerBase propEntry;
                    propertiesVar.get_child(propEntry, k);
                    if (!propEntry.gobj()) {
                        continue;
                    }

                    Glib::ustring propName =
                        BluezDbusUtils::getStringFromVariant(
                            propEntry.get_child(0)
                        );

                    if (propName == cAddressProp || propName == cNameProp ||
                        propName == cAliasProp) {
                        Glib::ustring val =
                            BluezDbusUtils::getStringFromVariant(
                                propEntry.get_child(1)
                            );
                        if (g_ascii_strcasecmp(val.c_str(), address.c_str()) ==
                            0) {
                            return path;
                        }
                    }
                }
            }
        }
    }
    return cEmptyString;
}

bool BluezDeviceResolver::findGattPaths(
    const Glib::VariantContainerBase &objectsBase,
    const Glib::ustring &devicePath, const std::string &serviceUuid,
    const std::string &rxUuid, const std::string &txUuid, Glib::ustring &rxPath,
    Glib::ustring &txPath
) {
    if (!objectsBase.gobj()) {
        return false;
    }

    struct CharInfo {
        Glib::ustring uuid;
        Glib::ustring servicePath;
    };
    std::map<Glib::ustring, CharInfo> characteristics;
    std::map<Glib::ustring, Glib::ustring> servicePathToUuid;
    std::map<Glib::ustring, Glib::ustring> servicePathToDevice;

    size_t nObjects = objectsBase.get_n_children();

    for (size_t i = 0; i < nObjects; ++i) {
        Glib::VariantContainerBase objEntry;
        objectsBase.get_child(objEntry, i);
        if (!objEntry.gobj()) {
            continue;
        }

        Glib::ustring path =
            BluezDbusUtils::getStringFromVariant(objEntry.get_child(0));

        Glib::VariantContainerBase interfacesVar =
            Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(
                objEntry.get_child(1)
            );
        if (!interfacesVar.gobj()) {
            continue;
        }

        size_t nInterfaces = interfacesVar.get_n_children();

        for (size_t j = 0; j < nInterfaces; ++j) {
            Glib::VariantContainerBase intEntry;
            interfacesVar.get_child(intEntry, j);
            if (!intEntry.gobj()) {
                continue;
            }

            Glib::ustring interfaceName =
                BluezDbusUtils::getStringFromVariant(intEntry.get_child(0));

            if (interfaceName == cGattCharacteristicInterface) {
                Glib::VariantContainerBase propertiesVar =
                    Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(
                        intEntry.get_child(1)
                    );
                if (!propertiesVar.gobj()) {
                    continue;
                }

                size_t nProps = propertiesVar.get_n_children();
                CharInfo info;

                for (size_t k = 0; k < nProps; ++k) {
                    Glib::VariantContainerBase propEntry;
                    propertiesVar.get_child(propEntry, k);
                    if (!propEntry.gobj()) {
                        continue;
                    }

                    Glib::ustring propName =
                        BluezDbusUtils::getStringFromVariant(
                            propEntry.get_child(0)
                        );

                    if (propName == cUuidProp) {
                        info.uuid = BluezDbusUtils::getStringFromVariant(
                            propEntry.get_child(1)
                        );
                    } else if (propName == cServiceProp) {
                        info.servicePath = BluezDbusUtils::getStringFromVariant(
                            propEntry.get_child(1)
                        );
                    }
                }
                characteristics[path] = info;
            } else if (interfaceName == cGattServiceInterface) {
                Glib::VariantContainerBase propertiesVar =
                    Glib::VariantBase::cast_dynamic<Glib::VariantContainerBase>(
                        intEntry.get_child(1)
                    );
                if (!propertiesVar.gobj()) {
                    continue;
                }

                size_t nProps = propertiesVar.get_n_children();
                Glib::ustring uuid;
                Glib::ustring devPath;

                for (size_t k = 0; k < nProps; ++k) {
                    Glib::VariantContainerBase propEntry;
                    propertiesVar.get_child(propEntry, k);
                    if (!propEntry.gobj()) {
                        continue;
                    }

                    Glib::ustring propName =
                        BluezDbusUtils::getStringFromVariant(
                            propEntry.get_child(0)
                        );
                    if (propName == cUuidProp) {
                        uuid = BluezDbusUtils::getStringFromVariant(
                            propEntry.get_child(1)
                        );
                    } else if (propName == cDeviceProp) {
                        devPath = BluezDbusUtils::getStringFromVariant(
                            propEntry.get_child(1)
                        );
                    }
                }
                if (!uuid.empty()) {
                    servicePathToUuid[path] = uuid;
                    servicePathToDevice[path] = devPath;
                }
            }
        }
    }

    rxPath.clear();
    txPath.clear();

    for (const auto &[cPath, cInfo] : characteristics) {
        auto sDevice = servicePathToDevice[cInfo.servicePath];

        if (!devicePath.empty() && sDevice != devicePath) {
            continue;
        }

        if (!serviceUuid.empty()) {
            auto sUuid = servicePathToUuid[cInfo.servicePath];

            if (g_ascii_strcasecmp(sUuid.c_str(), serviceUuid.c_str()) != 0) {
                continue;
            }
        }

        if (g_ascii_strcasecmp(cInfo.uuid.c_str(), rxUuid.c_str()) == 0) {
            rxPath = cPath;
        }
        if (g_ascii_strcasecmp(cInfo.uuid.c_str(), txUuid.c_str()) == 0) {
            txPath = cPath;
        }
    }

    return !rxPath.empty() && !txPath.empty();
}
