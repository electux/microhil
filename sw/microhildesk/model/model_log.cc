/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * model_log.cc
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
#include "model_log.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief String constants for log configuration keys
    constexpr std::string_view logLevel{"log_level"};
    constexpr std::string_view filePath{"log_file_path"};
    constexpr std::string_view unknown{"unknown"};
};

using namespace Electux::App::Model;

Entities ModelLog::getAllEntries() const 
{
    static const std::vector<ModelLogKey> keys =
    {
        ModelLogKey::LogLevel, ModelLogKey::FilePath
    };

    Entities entries;
    for (const auto& key : keys)
    {
        std::string keyStr = toString(key);
        entries[keyStr] = getEntity(keyStr); 
    }

    return entries;
}

std::string ModelLog::toString(const ModelLogKey &key) const
{
    switch (key)
    {
    case ModelLogKey::LogLevel: return logLevel.data();
    case ModelLogKey::FilePath: return filePath.data();
    default: return unknown.data();
    }
}

bool ModelLog::validateKey(const std::string &key) const
{
    return key == toString(ModelLogKey::LogLevel) || key == toString(ModelLogKey::FilePath);
}
