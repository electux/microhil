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

void AppSettings::onButtonOkClicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// Performs action on OK button
    SettingsSetup setup;
    setup.m_serialDevicePath = m_entrySerialPath.get_text();
    setup.m_serialParams.push_back(m_comboSerialBaud.get_active_row_number());
    setup.m_serialParams.push_back(m_comboSerialData.get_active_row_number());
    setup.m_serialParams.push_back(m_comboSerialParity.get_active_row_number());
    setup.m_serialParams.push_back(m_comboSerialStop.get_active_row_number());
    setup.m_logFilePath = m_entryLogPath.get_text();
    setup.m_logLevel = m_comboLogLevel.get_active_row_number();

    //////////////////////////////////////////////////////////////////////////
    /// Emits new serial/log settings setup
    m_setup.emit(setup);

    //////////////////////////////////////////////////////////////////////////
    /// Hide settings window
    hide();
}

void AppSettings::onButtonCancelClicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// Performs action on Cancel button
    hide();
}

SigSetup AppSettings::setupChanged() { return m_setup; }
