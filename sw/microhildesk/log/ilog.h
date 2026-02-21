/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ilog.h
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

#include <string>
#include <cstdint>

namespace Electux::App::Logger
{
    ///////////////////////////////////////////////////////////////////////////
    /// @brief ILog is the interface for logging implementations
    class ILog
    {
    public:
        ///////////////////////////////////////////////////////////////////////
        /// @brief Enum for log levels
        enum class LogLevel : uint8_t
        {
            Error = 0,
            Warning,
            Info
        };

        virtual ~ILog() noexcept = default;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Sets the filtering log level
        /// @param level The log level to set for filtering messages
        virtual void setLevel(LogLevel level) = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Gets the current filtering log level
        /// @return The current log level used for filtering messages
        virtual LogLevel getLevel() const = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Opens the logging sink (file, socket, etc.)
        /// @return true for success, else false
        virtual bool open() = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Closes the logging sink
        /// @return true for success, else false
        virtual bool close() = 0;

        ///////////////////////////////////////////////////////////////////////
        /// @brief Logs a message to the sink
        /// @param message The string content to log
        /// @param level The severity of the message
        virtual void log(const std::string &message, LogLevel level) = 0;
    };
};
