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

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILViewLog class declaration and definition 
class MicroHILViewLog: public AbMicroHILViewLog, public Gtk::Dialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewLog constructor
    /// @param object base object instance
    /// @param ui bulder parser
    MicroHILViewLog(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewLog destructor
    ~MicroHILViewLog() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Log input
    /// @return Signal for entry action
    logFilePath logFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log input
    void onLogFilePathChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Log level combobox
    /// @return Signal for changed log level by combobox
    selectLogLevel logLevelChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing loge level from combobox
    void onLogLevelChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Log Cancel button
    /// @return Signal for performed action
    cancelLog cancelLogChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Log Ok button 
    /// @return Signal for performed action
    okLog okLogChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Log Cancel button
    void onCancelLogChange() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Log Ok button
    void onOkLogChange() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Map all signals and slots for log dialog
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_ui;

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI entry for setting file log path
    Glib::RefPtr<Gtk::Entry> m_device;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Combobox for selecting log level type
    Glib::RefPtr<Gtk::ComboBoxText> m_level;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Cancel button
    Glib::RefPtr<Gtk::Button> m_cancel;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Confirm button
    Glib::RefPtr<Gtk::Button> m_ok;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting after type action on input
    logFilePath m_logFilePath;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting after select action on combobox
    selectLogLevel m_logLevel;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Cancel button (dismiss)
    cancelLog m_cancelLog;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for emitting from Ok button (confirm)
    okLog m_okLog;
};
