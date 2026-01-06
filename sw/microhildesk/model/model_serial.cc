/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * model_serial.cc
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhildesk is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhildesk is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include <vector>
#include "model_serial.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief String constants for serial configuration keys
    constexpr std::string_view device{"device"};
    constexpr std::string_view baud{"baud"};
    constexpr std::string_view data{"data"};
    constexpr std::string_view parity{"parity"};
    constexpr std::string_view stop{"stop"};
    constexpr std::string_view unknown{"unknown"};
};

using namespace Electux::App::Model;

Entities ModelSerial::getAllEntries() const 
{
    static const std::vector<ModelSerialKey> keys = 
    {
        ModelSerialKey::Device,
        ModelSerialKey::Baud,
        ModelSerialKey::Data,
        ModelSerialKey::Parity,
        ModelSerialKey::Stop
    };

    Entities entries;
    for (const auto& key : keys)
    {
        std::string keyStr = toString(key);
        entries[keyStr] = getEntity(keyStr); 
    }

    return entries;
}

std::string ModelSerial::toString(const ModelSerialKey &key) const
{
    switch (key)
    {
    case ModelSerialKey::Device: return device.data();
    case ModelSerialKey::Baud: return baud.data();
    case ModelSerialKey::Data: return data.data();
    case ModelSerialKey::Parity: return parity.data();
    case ModelSerialKey::Stop: return stop.data();
    default: return unknown.data();
    }
}

bool ModelSerial::validateKey(const std::string &key) const
{
    return key == toString(ModelSerialKey::Device) ||
            key == toString(ModelSerialKey::Baud) ||
            key == toString(ModelSerialKey::Data) ||
            key == toString(ModelSerialKey::Parity) ||
            key == toString(ModelSerialKey::Stop);
}
