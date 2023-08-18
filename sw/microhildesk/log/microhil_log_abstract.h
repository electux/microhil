/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_log_abstract.h
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

#include <glibmm/ustring.h>

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped enumerator for log levels
enum class LogLevel
{
    INFO = 0,
    WARNING = 1,
    ERROR = 2
};

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILLog class declaration and definition
class AbMicroHILLog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILLog destructor
    virtual ~AbMicroHILLog() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Open storage for collecting log messages
    /// @return boolean status true for success else false
    virtual bool open() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Write log message
    /// @param message log message to be stored
    /// @param level log level
    virtual void write(const Glib::ustring message, LogLevel level) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Close log storage
    /// @return boolean status true for success else false
    virtual bool close() = 0;
};
