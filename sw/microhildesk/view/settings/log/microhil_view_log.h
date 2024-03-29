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

#include "microhil_view_log_abstract.h"
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/dialog.h>
#include <gtkmm/entry.h>

////////////////////////////////////////////////////////////////////////////
/// @brief MHViewLog class is implementation of  log settings view
class MHViewLog : public AbMHViewLog, public Gtk::Dialog
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHViewLog constructor
    /// @param object represents base object instance
    /// @param ui represents bulder instance
    MHViewLog(BaseObjectType *object, RPtr<Gtk::Builder> const &ui);

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHViewLog destructor
    inline ~MHViewLog() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log settings
    /// @return Signal for changed log settings
    SigLogSetup logSetupChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log file path input
    /// @return Signal for changed log file path entry
    SigLogFilePath logFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log level combobox
    /// @return Signal for selected log level combobox
    SigSelectLogLevel logLevelChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button
    /// @return Signal for clicked Cancel button
    SigCancelLog cancelLogTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button
    /// @return Signal for clicked Ok button
    SigOkLog okLogTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set loaded parameters for log settings view
    /// @param filePath represents absolute log file path
    /// @param logLevel represents level for logging
    void logSettingsLoaded(UString &filePath, int logLevel);

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log file path input
    void onLogFilePathChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing log level combobox
    void onLogLevelChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Cancel button
    void onCancelLogTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Ok button
    void onOkLogTriggered() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps all widgets (signals and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    RPtr<Gtk::Builder> m_ui{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI entry for setting file log path
    RPtr<Gtk::Entry> m_device{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Combobox for selecting log level type
    RPtr<Gtk::ComboBoxText> m_level{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Cancel button
    RPtr<Gtk::Button> m_cancel{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Confirm button
    RPtr<Gtk::Button> m_ok{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log settings
    SigLogSetup m_logSetup{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log file path input
    SigLogFilePath m_logFilePath{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for log level combobox
    SigSelectLogLevel m_logLevel{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Cancel button (dismiss)
    SigCancelLog m_cancelLog{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for Ok button (confirm)
    SigOkLog m_okLog{};
};
