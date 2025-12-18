/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings_slots.cc
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
#include "settings.h"

using namespace Electux::App::View::Settings;

void AppSettings::on_button_ok_clicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// Performs action on OK button
    SettingsSetup setup;
    setup.m_serial_device_path = m_entry_serial_path.get_text();
    setup.m_serial_params.push_back(m_combo_serial_baud.get_active_row_number());
    setup.m_serial_params.push_back(m_combo_serial_data.get_active_row_number());
    setup.m_serial_params.push_back(m_combo_serial_parity.get_active_row_number());
    setup.m_serial_params.push_back(m_combo_serial_stop.get_active_row_number());
    setup.m_log_file_path = m_entry_log_path.get_text();
    setup.m_log_level = m_combo_log_level.get_active_row_number();

    //////////////////////////////////////////////////////////////////////////
    /// Emits new serial/log settings setup
    m_setup.emit(setup);

    //////////////////////////////////////////////////////////////////////////
    /// Hide settings window
    hide();
}

void AppSettings::on_button_cancel_clicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// Performs action on Cancel button
    hide();
}

SigSetup AppSettings::setup_changed() { return m_setup; }
