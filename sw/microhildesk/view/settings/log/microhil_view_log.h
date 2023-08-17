/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_log.h
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

#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/dialog.h>
#include "microhil_view_log_abstract.h"

class MicroHILViewLog : public AbMicroHILViewLog, public Gtk::Dialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewLog constructor
    MicroHILViewLog(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    // MicroHILViewLog destructor
    ~MicroHILViewLog() = default;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Log input
    logFilePath logFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing log input 
    void onLogFilePathChange() final;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Log level combobox
    selectLogLevel logLevelChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slot for processing loge level from combobox
    void onLogLevelChange() final;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from Log Cancel and Ok buttons
    cancelLog cancelLogChanged() final;
    okLog okLogChanged() final;

    ////////////////////////////////////////////////////////////////////////
    // Slots for processing Log Cancel and Ok buttons
    void onCancelLogChange() final;
    void onOkLogChange() final;

private:
    ////////////////////////////////////////////////////////////////////////
    // Map all signals and slots for log dialog
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    // UI builder
    Glib::RefPtr<Gtk::Builder> m_ui;

    ////////////////////////////////////////////////////////////////////////
    // Widgets for log view
    Glib::RefPtr<Gtk::Entry> m_device;
    Glib::RefPtr<Gtk::ComboBoxText> m_level;
    Glib::RefPtr<Gtk::Button> m_cancel;
    Glib::RefPtr<Gtk::Button> m_ok;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Log input
    logFilePath m_logFilePath;

    ////////////////////////////////////////////////////////////////////////
    // Signal for emitting from Log level combobox
    selectLogLevel m_logLevel;

    ////////////////////////////////////////////////////////////////////////
    // Signals for emitting from Cancel and Ok button (dismiss and confirm)
    cancelLog m_cancelLog;
    okLog m_okLog;
};
