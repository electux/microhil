/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_ilog.h
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
#pragma once

#include "../utils/microhil_types.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped class enumerator for log levels
enum class LogLevel : int
{
    /// @brief Log level info
    MICROHIL_INFO = 0,
    /// @brief Log level warning
    MICROHIL_WARNING = 1,
    /// @brief Log level error
    MICROHIL_ERROR = 2
};

////////////////////////////////////////////////////////////////////////////
/// @brief IMHLog class is interface set for log mechanism
class IMHLog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief IMHLog destructor
    inline virtual ~IMHLog() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets file path for logger
    /// @param logFilePath represents file path for storing log messages
    virtual void setFilePath(const MHString &logFilePath) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets file path for logger
    /// @return Log file path
    virtual MHString getFilePath() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log level
    /// @param level represent level for logging
    virtual void setLogLevel(const MHString &level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log level
    /// @param level represent level for logging
    virtual void setLogLevel(const int level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log level
    /// @param level represents level for logging
    virtual void setLogLevel(const LogLevel level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets log level
    /// @return Scoped enumeration of log level
    virtual LogLevel getLogLevel() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Opens storage for collecting log messages
    /// @return status true for success open operation else false
    virtual bool open() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets current date and time
    /// @return current date time in string format (18-08-2023 22:52:06)
    virtual MHString getCurrentDateTime() const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts log level type to human readable string
    /// @param level represents log level
    /// @return string representation of log level
    virtual MHString toStringLogType(const LogLevel level) const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts log level string to level type
    /// @param level represents level type in string format
    /// @return log level type
    virtual LogLevel toLogType(const MHString &level) const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Writes log message
    /// @param message represents log message to be stored
    /// @param level represents log level
    virtual void write(const MHString &message, const LogLevel level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Closes log storage
    /// @return status true for success close operation else false
    virtual bool close() = 0;
};
