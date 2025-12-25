/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * log.h
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
#pragma once

#include <fstream>
#include <mutex>

namespace Electux::App::Logger
{
    class Log
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief Model log methods
        ///   Log constructor
        ///   Log destructor with force close log file
        ///   Deleted copy constructor and assignment operator
        inline Log() noexcept = default;
        ~Log();
        Log(const Log &) = delete;
        Log &operator=(const Log &) = delete;

        //////////////////////////////////////////////////////////////////////
        /// @brief Enum for log levels
        enum class LogLevel
        {
            Error = 0,
            Warning,
            Info
        };

        //////////////////////////////////////////////////////////////////////
        /// @brief Sets log level
        /// @param level Represents log level to be set
        void setLevel(LogLevel level);

        //////////////////////////////////////////////////////////////////////
        /// @brief Gets log level
        /// @return current log level
        LogLevel getLevel() const;

        //////////////////////////////////////////////////////////////////////
        /// @brief Sets output log file
        /// @param output Represents output log file to be set
        void setOutputFile(const std::string &output);

        //////////////////////////////////////////////////////////////////////
        /// @brief Opens log file
        /// @return true for success else false
        bool open();

        //////////////////////////////////////////////////////////////////////
        /// @brief Closes log file
        /// @return true for success else false
        bool close();

        //////////////////////////////////////////////////////////////////////
        /// @brief Logs message to log file
        /// @param message Represents message to be logged
        /// @param level Represents log level of the message
        void log(const std::string &message, LogLevel level);
    
    private:
        //////////////////////////////////////////////////////////////////////
        /// @brief Model log properties
        ///   m_level - current log level
        ///   m_outputFile - output log file name
        ///   m_stream - output file stream
        ///   m_mutex - mutex for thread safety
        LogLevel m_level{LogLevel::Info};
        std::string m_outputFile;
        std::ofstream m_stream;
        std::mutex m_mutex;
    };
};

