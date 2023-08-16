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

#include <sigc++/sigc++.h>

class AbMicroHILViewLog
{
public:
    ////////////////////////////////////////////////////////////////////////
    // Signal type for log file path
    using logFilePath = sigc::signal<void(Glib::ustring)>;

    ////////////////////////////////////////////////////////////////////////
    // Signal type for selectable log level
    using selectLogLevel = sigc::signal<void(int)>;

    ////////////////////////////////////////////////////////////////////////
    // Signal types for Log Cancel and Ok buttons
    using cancelLog = sigc::signal<void(bool)>;
    using okLog = sigc::signal<void(bool)>;

    ////////////////////////////////////////////////////////////////////////
    // AbMicroHILViewLog destructor
    virtual ~AbMicroHILViewLog() = default;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Log input
    virtual logFilePath logFilePathChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing log input 
    virtual void onLogFilePathChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Log level combobox
    virtual selectLogLevel logLevelChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing loge level from combobox
    virtual void onLogLevelChange() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from Log Cancel and Ok buttons
    virtual cancelLog cancelLogChanged() = 0;
    virtual okLog okLogChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing Log Cancel and Ok buttons
    virtual void onCancelLogChange() = 0;
    virtual void onOkLogChange() = 0;
};
