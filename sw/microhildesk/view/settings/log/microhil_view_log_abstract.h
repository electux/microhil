/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_log_abstract.h
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
#include <sigc++/sigc++.h>

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILViewLog class declaration and definition 
class AbMicroHILViewLog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for log file path
    using logFilePath = sigc::signal<void(Glib::ustring)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for selectable log level
    using selectLogLevel = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Log Cancel button
    using cancelLog = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for Log Ok button
    using okLog = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILViewLog destructor
    virtual ~AbMicroHILViewLog() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Log input
    /// @return Signal for entry action
    virtual logFilePath logFilePathChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log input 
    virtual void onLogFilePathChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Log level combobox
    /// @return Signal for changed log level by combobox
    virtual selectLogLevel logLevelChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing loge level from combobox
    virtual void onLogLevelChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Log Cancel button
    /// @return Signal for performed action
    virtual cancelLog cancelLogChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Log Ok button 
    /// @return Signal for performed action
    virtual okLog okLogChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Log Cancel button
    virtual void onCancelLogChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Log Ok button
    virtual void onOkLogChange() = 0;
};
