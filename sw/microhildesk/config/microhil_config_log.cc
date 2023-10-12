/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_config_log.cc
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
    /// Log configuration section
    constexpr const char kConfigLog[]{"log"};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter
    constexpr const char kConfigLevel[]{"level"};

    ////////////////////////////////////////////////////////////////////////
    /// Log file path configuration parameter
    constexpr const char kConfigFile[]{"file"};
} // namespace

void MHConfig::setLogLevel(int level)
{
    ////////////////////////////////////////////////////////////////////////
    /// Converts integer log level to string format
    auto logLevel = logLevelToUnicodeString(level);

    ////////////////////////////////////////////////////////////////////////
    /// Sets log level to configuration
    m_config.set_string(kConfigLog, kConfigLevel, logLevel);
}

UString MHConfig::getLogLevel() const
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets log level from configuration
    return m_config.get_string(kConfigLog, kConfigLevel);
}

void MHConfig::setLogPath(const UString &path)
{
    ////////////////////////////////////////////////////////////////////////
    /// Sets log file path to configuration
    m_config.set_string(kConfigLog, kConfigFile, path);
}

UString MHConfig::getLogPath() const
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets log file path from configuration
    return m_config.get_string(kConfigLog, kConfigFile);
}

bool MHConfig::validateLogSettings()
{
    ////////////////////////////////////////////////////////////////////////
    /// Checks log configuration parameters from config file
    const auto configCheck =
        (m_config.has_key(kConfigLog, kConfigLevel) &&
         m_config.has_key(kConfigLog, kConfigFile));

    if (!configCheck)
    {
        ////////////////////////////////////////////////////////////////////
        /// Configuration file, log section corrupted
        return false;
    }

    return true;
}
