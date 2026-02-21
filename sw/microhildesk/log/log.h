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
#include <string>
#include <log/ilog.h>

namespace Electux::App::Logger
{
    ///////////////////////////////////////////////////////////////////////////
    /// @brief Log class is a file-based implementation of ILog
    class Log : public ILog
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Model log methods
        ///   Log constructor
        ///   Log destructor with force close log file
        ///   Deleted copy constructor and assignment operator
        inline Log() noexcept = default;
        ~Log() noexcept;
        Log(const Log &) = delete;
        Log &operator=(const Log &) = delete;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Sets the filtering log level
        /// @param level The log level to set for filtering messages
        void setLevel(LogLevel level) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Gets the current filtering log level
        /// @return The current log level used for filtering messages
        LogLevel getLevel() const final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Opens the logging sink (file, socket, etc.)
        /// @return true for success, else false
        bool open() final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Closes the logging sink
        /// @return true for success, else false
        bool close() final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Logs a message to the sink
        /// @param message The string content to log
        /// @param level The severity of the message
        void log(const std::string &message, LogLevel level) final;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Specific to File Logger: Sets the path
        void setOutputFile(const std::string &output);

    private:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Model log properties
        ///   m_level - current log level
        ///   m_outputFile - output log file name
        ///   m_stream - output file stream
        ///   m_mutex - mutex for thread safety
        LogLevel m_level{LogLevel::Info};
        std::string m_outputFile{};
        std::ofstream m_stream{};
        mutable std::mutex m_mutex{};
    };
};

