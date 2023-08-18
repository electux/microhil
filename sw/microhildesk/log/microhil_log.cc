/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_log.cc
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
#include <ctime>
#include "microhil_log.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// String representation of info log level
    constexpr const char kInfoLogLevel[]{" INFO "};
    
    ////////////////////////////////////////////////////////////////////////
    /// String representation of warning log level
    constexpr const char kWarningLogLevel[]{" WARNING "};
    
    ////////////////////////////////////////////////////////////////////////
    /// String representation of error log level
    constexpr const char kErrorLogLevel[]{" ERROR "};
}

MicroHILLog::MicroHILLog(): m_fileOpened{false} {}

MicroHILLog::~MicroHILLog()
{
    if(m_logFile.is_open() && m_fileOpened)
    {
        m_logFile.close();
        m_fileOpened = false;
    }
}

void MicroHILLog::setFilePath(const Glib::ustring logFilePath)
{
    m_logFilePath = logFilePath;
}

Glib::ustring MicroHILLog::getFilePath() const
{
    return m_logFilePath;
}

bool MicroHILLog::open()
{
    if(!m_logFile.is_open() && !m_fileOpened)
    {
        m_logFile.open(m_logFilePath, ios::out);
        m_fileOpened = true;
    }

    return m_fileOpened;
}

void MicroHILLog::write(const Glib::ustring message, LogLevel level)
{
    const auto currentTime = getCurrentDateTime();
    const auto prefixLogLevel = getLogType(level);
    Glib::ustring logMessage = currentTime + prefixLogLevel + message;

    if(m_logFile.is_open() && m_fileOpened)
    {
        m_logFile << logMessage;
    }
}

bool MicroHILLog::close()
{
    if(m_logFile.is_open() && m_fileOpened)
    {
        m_logFile.close();
        m_fileOpened = false;
    }

    return !m_fileOpened;
}

Glib::ustring MicroHILLog::getCurrentDateTime() const
{
    time_t rawTime;
    char buffer[80];

    time(&rawTime);
    const struct tm *timeInfo = localtime(&rawTime);
    strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeInfo);

    return Glib::ustring(buffer);
}

Glib::ustring MicroHILLog::getLogType(LogLevel level) const
{
    switch(level)
    {
        case LogLevel::INFO:
            return kInfoLogLevel;
        case LogLevel::WARNING:
            return kWarningLogLevel;
        case LogLevel::ERROR:
            return kErrorLogLevel;
    }

    return kInfoLogLevel;
}
