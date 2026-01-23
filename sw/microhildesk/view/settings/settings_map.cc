/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * settings_map.cc
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

void AppSettings::mapping()
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Maps signals to slots (widget actions)
    m_entrySerialPath.signal_changed().connect(sigc::mem_fun(*this, &AppSettings::onEntrySerialPathChanged));
    m_comboSerialBaud.signal_changed().connect(sigc::mem_fun(*this, &AppSettings::onEntrySerialBaudChanged));
    m_comboSerialData.signal_changed().connect(sigc::mem_fun(*this, &AppSettings::onEntrySerialDataChanged));
    m_comboSerialParity.signal_changed().connect(sigc::mem_fun(*this, &AppSettings::onEntrySerialParityChanged));
    m_comboSerialStop.signal_changed().connect(sigc::mem_fun(*this, &AppSettings::onEntrySerialStopChanged));
    m_entryLogPath.signal_changed().connect(sigc::mem_fun(*this, &AppSettings::onEntryLogPathChanged));
    m_comboLogLevel.signal_changed().connect(sigc::mem_fun(*this, &AppSettings::onEntryLogLevelChanged));
    m_buttonOk.signal_clicked().connect(sigc::mem_fun(*this, &AppSettings::onButtonOkClicked));
    m_buttonCancel.signal_clicked().connect(sigc::mem_fun(*this, &AppSettings::onButtonCancelClicked));
}
