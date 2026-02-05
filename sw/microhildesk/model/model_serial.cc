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
#include <model/model_serial.h>

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief String constants for serial configuration keys
    constexpr std::string_view cDevice{"device"};
    constexpr std::string_view cBaud{"baud"};
    constexpr std::string_view cData{"data"};
    constexpr std::string_view cParity{"parity"};
    constexpr std::string_view cStop{"stop"};
    constexpr std::string_view cFlow{"flow"};
    constexpr std::string_view cUnknown{"unknown"};
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
        ModelSerialKey::Stop,
        ModelSerialKey::Flow
    };

    Entities entries;
    for (const auto& key : keys)
    {
        std::string_view keyStrView = toString(key);
        std::string keyStr{keyStrView};
        entries.emplace(std::move(keyStr), getEntity(keyStr));
    }

    return entries;
}

std::string_view ModelSerial::toString(const ModelSerialKey &key) const
{
    switch (key)
    {
    case ModelSerialKey::Device: return cDevice;
    case ModelSerialKey::Baud: return cBaud;
    case ModelSerialKey::Data: return cData;
    case ModelSerialKey::Parity: return cParity;
    case ModelSerialKey::Stop: return cStop;
    case ModelSerialKey::Flow: return cFlow;
    default: return cUnknown;
    }
}

bool ModelSerial::validateKey(const std::string_view &key) const
{
    return key == cDevice ||
            key == cBaud ||
            key == cData ||
            key == cParity ||
            key == cStop ||
            key == cFlow;
}
