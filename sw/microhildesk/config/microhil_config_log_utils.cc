/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_config_log_utils.cc
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "microhil_config.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter info
    constexpr const char kConfigLevelInfo[]{"INFO"};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter warning
    constexpr const char kConfigLevelWarning[]{"WARNING"};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter error
    constexpr const char kConfigLevelError[]{"ERROR"};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration info index id
    constexpr const int kConfigLevelInfoId{0};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration warning index id
    constexpr const int kConfigLevelWarningId{1};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration error index id
    constexpr const int kConfigLevelErrorId{2};
} // namespace

UString MHConfig::logLevelToUnicodeString(const int logLevel)
{
    ////////////////////////////////////////////////////////////////////////
    /// Converts integer log level to scopped enumerator class
    auto logLevelType = static_cast<LogLevelConfig>(logLevel);

    switch (logLevelType)
    {
    case LogLevelConfig::MICROHIL_INFO_CONFIG:
        return kConfigLevelInfo;
    case LogLevelConfig::MICROHIL_WARNING_CONFIG:
        return kConfigLevelWarning;
    case LogLevelConfig::MICROHIL_ERROR_CONFIG:
        return kConfigLevelError;
    }

    return kConfigLevelInfo;
}

int MHConfig::logLevelStringToInt(const UString &level)
{
    if (level == kConfigLevelWarning)
    {
        return kConfigLevelWarningId;
    }

    if (level == kConfigLevelError)
    {
        return kConfigLevelErrorId;
    }

    return kConfigLevelInfoId;
}
