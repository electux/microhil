/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_log.h
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

#include <iostream>
#include <fstream>
#include "microhil_ilog.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
/// @brief MHLog class is implementation of log mechanism
class MHLog : public IMHLog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHLog constructor
    explicit MHLog();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets file path for logger
    /// @param logFilePath represents file path for storing log messages
    void setFilePath(const MHString &logFilePath) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets file path for logger
    /// @return Log file path
    MHString getFilePath() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log level
    /// @param level represent level for logging
    void setLogLevel(const MHString &level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log level
    /// @param level represent level for logging
    void setLogLevel(const int level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets log level
    /// @param level represents level for logging
    void setLogLevel(const LogLevel level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets log level
    /// @return Scoped enumeration of log level
    LogLevel getLogLevel() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Opens storage for collecting log messages
    /// @return status true for success else false
    bool open() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets current date and time
    /// @return current date time in string format (18-08-2023 22:52:06)
    MHString getCurrentDateTime() const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts log level type to human readable string
    /// @param level represents log level
    /// @return string representation of log level
    MHString toStringLogType(const LogLevel level) const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts log level string to level type
    /// @param level represents level type in string format
    /// @return log level type
    LogLevel toLogType(const MHString &level) const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Writes log message
    /// @param message represents log message to be stored
    /// @param level represents log level
    void write(const MHString &message, const LogLevel level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Closes log storage
    /// @return status true for success else false
    bool close() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Log file path
    MHString m_logFilePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Log file instance
    ofstream m_logFile{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Type of log level
    LogLevel m_logLevel{LogLevel::MICROHIL_INFO};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Flag for checking log file state
    bool m_fileOpened{false};
};
