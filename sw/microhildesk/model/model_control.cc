/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * model_control.cc
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
#include <model/model_control.h>

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief String constants for control configuration keys
    constexpr std::string_view cEnable{"enable"};
    constexpr std::string_view cMode{"mode"};
    constexpr std::string_view cToggle{"toggle"};
    constexpr std::string_view cTimer{"timer"};
    constexpr std::string_view cTimerEnable{"timerEnable"};
    constexpr std::string_view cUnknown{"unknown"};
};

using namespace Electux::App::Model;

Entities ModelControl::getAllEntries() const 
{
    static const std::vector<ModelControlKey> keys = 
    {
        ModelControlKey::Enable,
        ModelControlKey::Mode,
        ModelControlKey::Toggle,
        ModelControlKey::Timer,
        ModelControlKey::TimerEnable
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

std::string_view ModelControl::toString(const ModelControlKey &key) const
{
    switch (key)
    {
    case ModelControlKey::Enable: return cEnable;
    case ModelControlKey::Mode: return cMode;
    case ModelControlKey::Toggle: return cToggle;
    case ModelControlKey::Timer: return cTimer;
    case ModelControlKey::TimerEnable: return cTimerEnable;
    default: return cUnknown;
    }
}

bool ModelControl::validateKey(const std::string_view &key) const
{
    return key ==  cEnable ||
            key == cMode ||
            key == cToggle ||
            key == cTimer ||
            key == cTimerEnable;
}
