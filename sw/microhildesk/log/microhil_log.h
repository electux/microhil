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
#include "microhil_log_abstract.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////
/// @brief MHLog class declaration and definition
class MHLog : public AbMHLog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHLog constructor
    MHLog();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHLog destructor (needed for closing file)
    ~MHLog();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setting file path for logger
    /// @param logFilePath file path for storing log messages
    void setFilePath(const MHString logFilePath);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting file path for logger
    /// @return Log file path
    MHString getFilePath() const;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup log level
    /// @param level of logging
    void setLogLevel(const MHString level);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup log level
    /// @param level of logging
    void setLogLevel(const int level);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup log level
    /// @param level of logging
    void setLogLevel(const LogLevel level);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting log level
    /// @return Scoped enumeration of log level
    LogLevel getLogLevel() const;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Open storage for collecting log messages
    /// @return boolean status true for success else false
    bool open() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Write log message
    /// @param message log message to be stored
    /// @param level log level
    void write(const MHString message, const LogLevel level) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Close log storage
    /// @return boolean status true for success else false
    bool close() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Getting current date and time
    /// @return current date time in string format (18-08-2023 22:52:06)
    MHString getCurrentDateTime() const;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert log level type to human readable string
    /// @param level log level
    /// @return string representation of log level
    MHString toStringLogType(const LogLevel level) const;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Convert log level string to level type
    /// @param level type in string format
    /// @return log level type
    LogLevel toLogType(const MHString level) const;

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
