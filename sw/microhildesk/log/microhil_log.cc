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
#include "microhil_log.h"
#include <ctime>

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
} // namespace

MHLog::MHLog()
    : m_fileOpened{false}
{
}

void MHLog::setFilePath(const UString &logFilePath)
{
    ////////////////////////////////////////////////////////////////////////
    /// Sets file path for logger
    m_logFilePath = logFilePath;
}

UString MHLog::getFilePath() const
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets file path for logger
    return m_logFilePath;
}

void MHLog::setLogLevel(const UString &level)
{
    ////////////////////////////////////////////////////////////////////////
    /// Converts log level from string to scoped enum
    auto logLevelPrepared = toLogType(level);

    ////////////////////////////////////////////////////////////////////////
    /// Sets log level for logger
    m_logLevel = logLevelPrepared;
}

void MHLog::setLogLevel(const int level)
{
    ////////////////////////////////////////////////////////////////////////
    /// Sets log level for logger
    m_logLevel = static_cast<LogLevel>(level);
}

void MHLog::setLogLevel(const LogLevel level)
{
    ////////////////////////////////////////////////////////////////////////
    /// Sets log level for logger
    m_logLevel = level;
}

LogLevel MHLog::getLogLevel() const
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets log level for logger
    return m_logLevel;
}

bool MHLog::open()
{
    if (!m_logFile.is_open() && !m_fileOpened)
    {
        m_logFile.open(m_logFilePath, ios::out);
        m_fileOpened = true;
    }

    return m_fileOpened;
}

void MHLog::write(const UString &message, const LogLevel level)
{
    const auto currentTime = getCurrentDateTime();
    const auto prefixLogLevel = toStringLogType(level);
    UString logMessage = currentTime + prefixLogLevel + message;

    if (m_logFile.is_open() && m_fileOpened)
    {
        m_logFile << logMessage;
    }
}

bool MHLog::close()
{
    if (m_logFile.is_open() && m_fileOpened)
    {
        m_logFile.close();
        m_fileOpened = false;
    }

    return !m_fileOpened;
}

UString MHLog::getCurrentDateTime() const
{
    time_t rawTime;
    char buffer[80];

    ////////////////////////////////////////////////////////////////////////
    /// Gets local time in Day-Month-Year Hours:Minutes:Seconds format
    time(&rawTime);
    const struct tm *timeInfo = localtime(&rawTime);
    strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeInfo);

    return UString(buffer);
}

UString MHLog::toStringLogType(const LogLevel level) const
{
    switch (level)
    {
    case LogLevel::MICROHIL_INFO:
        return kInfoLogLevel;
    case LogLevel::MICROHIL_WARNING:
        return kWarningLogLevel;
    case LogLevel::MICROHIL_ERROR:
        return kErrorLogLevel;
    }

    return kInfoLogLevel;
}

LogLevel MHLog::toLogType(const UString &level) const
{
    if (level == kWarningLogLevel)
    {
        return LogLevel::MICROHIL_WARNING;
    }

    if (level == kErrorLogLevel)
    {
        return LogLevel::MICROHIL_ERROR;
    }

    return LogLevel::MICROHIL_INFO;
}
