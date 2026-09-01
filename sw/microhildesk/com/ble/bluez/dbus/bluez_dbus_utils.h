////////////////////////////////////////////////////////////////////////////////////////////////////////
///
/// bluez_dbus_utils.h
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

#include <glibmm/ustring.h>
#include <glibmm/variant.h>
#include <string>
#include <vector>
#include <cstdint>

namespace Electux::App::Com::BluezDbusUtils {
    [[nodiscard]] Glib::ustring getStringFromVariant(const Glib::VariantBase &var);
    [[nodiscard]] bool getBoolFromVariant(const Glib::VariantBase &var);
    [[nodiscard]] std::vector<uint8_t> getByteVectorFromVariant(const Glib::VariantBase &var);
    [[nodiscard]] std::string normalizeMacAddress(const std::string &address);
} // namespace Electux::App::Com::BluezDbusUtils
