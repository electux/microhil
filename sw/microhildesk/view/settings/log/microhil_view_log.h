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
    /// @param ui bulder instance
    MicroHILViewLog(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewLog destructor
    ~MicroHILViewLog() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log file path input
    /// @return Signal for changed log file path entry
    logFilePath logFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log file path input 
    void onLogFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log level combobox
    /// @return Signal for selected log level combobox 
    selectLogLevel logLevelChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log level combobox
    void onLogLevelChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button
    /// @return Signal for clicked Cancel button
    cancelLog cancelLogTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button 
    /// @return Signal for clicked Ok button
    okLog okLogTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Cancel button
    void onCancelLogTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button
    void onOkLogTriggered() final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Map all widgets (signals and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_ui{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI entry for setting file log path
    Glib::RefPtr<Gtk::Entry> m_device{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Combobox for selecting log level type
    Glib::RefPtr<Gtk::ComboBoxText> m_level{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Cancel button
    Glib::RefPtr<Gtk::Button> m_cancel{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Confirm button
    Glib::RefPtr<Gtk::Button> m_ok{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log file path input
    logFilePath m_logFilePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log level combobox
    selectLogLevel m_logLevel{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button (dismiss)
    cancelLog m_cancelLog{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button (confirm)
    okLog m_okLog{};
};
