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
#include "model_control.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief String constants for control configuration keys
    constexpr std::string_view enable{"enable"};
    constexpr std::string_view mode{"mode"};
    constexpr std::string_view toggle{"toggle"};
    constexpr std::string_view timer{"timer"};
    constexpr std::string_view timerEnable{"timerEnable"};
    constexpr std::string_view unknown{"unknown"};
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
        std::string keyStr = toString(key);
        entries[keyStr] = getEntity(keyStr); 
    }

    return entries;
}

std::string ModelControl::toString(const ModelControlKey &key) const
{
    switch (key)
    {
    case ModelControlKey::Enable: return enable.data();
    case ModelControlKey::Mode: return mode.data();
    case ModelControlKey::Toggle: return toggle.data();
    case ModelControlKey::Timer: return timer.data();
    case ModelControlKey::TimerEnable: return timerEnable.data();
    default: return unknown.data();
    }
}

bool ModelControl::validateKey(const std::string &key) const
{
    return key == toString(ModelControlKey::Enable) ||
            key == toString(ModelControlKey::Mode) ||
            key == toString(ModelControlKey::Toggle) ||
            key == toString(ModelControlKey::Timer) ||
            key == toString(ModelControlKey::TimerEnable);
}
