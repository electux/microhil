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
#include <iostream>
#include "settings.h"
#include "../../params/serial_com_params.h"

using namespace Electux::App::View::Settings;
using namespace Electux::App::Params::SerialComConstants;

void AppSettings::onEntrySerialPathChanged()
{
    m_setup.m_serialDevicePath = m_entrySerialPath.get_text();
}

void AppSettings::onEntrySerialBaudChanged()
{
    m_setup.m_serialParams[comParamBaudIndex] = m_comboSerialBaud.get_active_row_number();
}

void AppSettings::onEntrySerialDataChanged()
{
    m_setup.m_serialParams[comParamDataIndex] = m_comboSerialData.get_active_row_number();
}

void AppSettings::onEntrySerialParityChanged()
{
    m_setup.m_serialParams[comParamParityIndex] = m_comboSerialParity.get_active_row_number();
}

void AppSettings::onEntrySerialStopChanged()
{
    m_setup.m_serialParams[comParamStopIndex] = m_comboSerialStop.get_active_row_number();
}

void AppSettings::onEntryLogPathChanged()
{
    m_setup.m_logFilePath = m_entryLogPath.get_text();
}

void AppSettings::onEntryLogLevelChanged()
{
    m_setup.m_logLevel = m_comboLogLevel.get_active_row_number();
}

void AppSettings::onButtonOkClicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Performs action on OK button emit signal for changed settings
    m_previusSetup = m_setup;
    m_setupSignal.emit(m_setup);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Hide settings window
    hide();
}

void AppSettings::onButtonCancelClicked()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Performs action on Cancel button dissmiss changes
    m_setup = m_previusSetup;
    m_setupSignal.emit(m_setup);

    //////////////////////////////////////////////////////////////////////////
    /// @brief Hide settings window
    hide();
}

SigSetup AppSettings::setupChanged() { return m_setupSignal; }
