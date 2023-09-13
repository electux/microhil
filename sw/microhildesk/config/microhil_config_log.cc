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
    constexpr const char kConfigLogSection[]{"log"};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter
    constexpr const char kConfigLogLevel[]{"level"};

    ////////////////////////////////////////////////////////////////////////
    /// Log file path configuration parameter
    constexpr const char kConfigLogFile[]{"file"};
}

void MHConfig::setLogLevel(int level)
{
    ////////////////////////////////////////////////////////////////////////
    /// Convert integer log level to string format
    auto logLevel = logLevelToUnicodeString(level);

    m_config.set_string(kConfigLogSection, kConfigLogLevel, logLevel);
}

MHString MHConfig::getLogLevel()
{
    return m_config.get_string(kConfigLogSection, kConfigLogLevel);
}

void MHConfig::setLogPath(MHString path)
{
    m_config.set_string(kConfigLogSection, kConfigLogFile, path);
}

MHString MHConfig::getLogPath()
{
    return m_config.get_string(kConfigLogSection, kConfigLogFile);
}

bool MHConfig::validateLogSettings()
{
    ////////////////////////////////////////////////////////////////////////
    /// Checking log configuration parameters from config file
    auto configCheck = (m_config.has_key(kConfigLogSection, kConfigLogLevel) &&
                        m_config.has_key(kConfigLogSection, kConfigLogFile));

    if (!configCheck)
    {
        ////////////////////////////////////////////////////////////////////
        /// Configuration file, log section corrupted
        return false;
    }

    return true;
}
