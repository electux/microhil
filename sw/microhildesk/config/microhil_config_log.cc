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

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter info
    constexpr const char kConfigLogLevelInfo[]{"INFO"};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter warning
    constexpr const char kConfigLogLevelWarning[]{"WARNING"};

    ////////////////////////////////////////////////////////////////////////
    /// Log level configuration parameter error
    constexpr const char kConfigLogLevelError[]{"ERROR"};
}

void MicroHILConfig::setLogLevel(int level)
{
    ////////////////////////////////////////////////////////////////////////
    /// Convert integer log level to string format
    auto logLevel = logLevelToUnicodeString(level);

    m_configuration.set_string(
        kConfigLogSection, kConfigLogLevel, logLevel
    );
}

Glib::ustring MicroHILConfig::getLogLevel() const
{
    return m_configuration.get_string(kConfigLogSection, kConfigLogLevel);
}

void MicroHILConfig::setLogPath(Glib::ustring path)
{
    m_configuration.set_string(
        kConfigLogSection, kConfigLogFile, path
    );
}

Glib::ustring MicroHILConfig::getLogPath() const
{
    return m_configuration.get_string(kConfigLogSection, kConfigLogFile);
}

Glib::ustring MicroHILConfig::logLevelToUnicodeString(int logLevel)
{
    ////////////////////////////////////////////////////////////////////////
    /// Convert integer log level to scopped class 
    auto logLevelType = static_cast<LogLevelConfig>(logLevel);

    switch(logLevelType)
    {
        case LogLevelConfig::MICROHIL_INFO_CONFIG:
            return kConfigLogLevelInfo;
        case LogLevelConfig::MICROHIL_WARNING_CONFIG:
            return kConfigLogLevelWarning;
        case LogLevelConfig::MICROHIL_ERROR_CONFIG:
            return kConfigLogLevelError;

    }

    return kConfigLogLevelInfo;
}

int MicroHILConfig::logLevelStringToInt(Glib::ustring level)
{
    if(level == kConfigLogLevelWarning)
    {
        return 1;
    }

    if(level == kConfigLogLevelError)
    {
        return 2;
    }

    return 0;
}

bool MicroHILConfig::validateLogSettings()
{
    ////////////////////////////////////////////////////////////////////////
    /// Checking log configuration parameters
    auto configCheck = (
        m_configuration.has_key(kConfigLogSection, kConfigLogLevel) &&
        m_configuration.has_key(kConfigLogSection, kConfigLogFile)
    );

    if(!configCheck)
    {
        return false;
    }

    return true;
}
