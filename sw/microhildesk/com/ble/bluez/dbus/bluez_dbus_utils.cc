////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_dbus_utils.cc
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
#include <cctype>
#include <com/ble/bluez/dbus/bluez_dbus_utils.h>
#include <string_view>

namespace {
    constexpr std::string_view cEmptyString{""};
    constexpr std::string_view cByteArrayType{"ay"};
    constexpr char cColonDelimiter{':'};
    constexpr char cDashDelimiter{'-'};
    constexpr char cUnderscoreDelimiter{'_'};
    constexpr size_t cMacAddressHexLength{12};
    constexpr size_t cMacAddressChunkSize{2};
} // namespace

namespace Electux::App::Com::BluezDbusUtils {
    Glib::ustring getStringFromVariant(const Glib::VariantBase &var) {
        GVariant *gvar = const_cast<GVariant *>(var.gobj());

        if (!gvar) {
            return cEmptyString.data();
        }

        while (g_variant_is_of_type(gvar, G_VARIANT_TYPE_VARIANT)) {
            gvar = g_variant_get_variant(gvar);
        }

        if (g_variant_is_of_type(gvar, G_VARIANT_TYPE_STRING) ||
            g_variant_is_of_type(gvar, G_VARIANT_TYPE_OBJECT_PATH)) {
            const char *str = g_variant_get_string(gvar, nullptr);
            return str ? Glib::ustring(str)
                       : Glib::ustring(cEmptyString.data());
        }

        return cEmptyString.data();
    }

    bool getBoolFromVariant(const Glib::VariantBase &var) {
        GVariant *gvar = const_cast<GVariant *>(var.gobj());

        if (!gvar) {
            return false;
        }

        while (g_variant_is_of_type(gvar, G_VARIANT_TYPE_VARIANT)) {
            gvar = g_variant_get_variant(gvar);
        }

        if (g_variant_is_of_type(gvar, G_VARIANT_TYPE_BOOLEAN)) {
            return g_variant_get_boolean(gvar) != FALSE;
        }

        return false;
    }

    std::vector<uint8_t>
    getByteVectorFromVariant(const Glib::VariantBase &var) {
        std::vector<uint8_t> result;
        GVariant *gvar = const_cast<GVariant *>(var.gobj());

        if (!gvar) {
            return result;
        }

        while (g_variant_is_of_type(gvar, G_VARIANT_TYPE_VARIANT)) {
            gvar = g_variant_get_variant(gvar);
        }

        if (g_variant_is_of_type(gvar, G_VARIANT_TYPE_BYTESTRING) ||
            g_variant_is_of_type(gvar, G_VARIANT_TYPE(cByteArrayType.data()))) {
            gsize n_elements = 0;
            gconstpointer data =
                g_variant_get_fixed_array(gvar, &n_elements, sizeof(guint8));

            if (data && n_elements > 0) {
                const auto *bytes = static_cast<const uint8_t *>(data);
                result.assign(bytes, bytes + n_elements);
            }
        }

        return result;
    }

    std::string normalizeMacAddress(const std::string &address) {
        std::string cleaned;

        for (char c : address) {
            if (c != cColonDelimiter && c != cDashDelimiter &&
                c != cUnderscoreDelimiter) {
                cleaned += static_cast<char>(
                    std::toupper(static_cast<unsigned char>(c))
                );
            }
        }

        if (cleaned.length() == cMacAddressHexLength) {
            std::string formatted;

            for (size_t i = 0; i < cMacAddressHexLength;
                 i += cMacAddressChunkSize) {
                if (i > 0) {
                    formatted += cUnderscoreDelimiter;
                }

                formatted += cleaned.substr(i, cMacAddressChunkSize);
            }

            return formatted;
        }

        return cEmptyString.data();
    }
} // namespace Electux::App::Com::BluezDbusUtils
