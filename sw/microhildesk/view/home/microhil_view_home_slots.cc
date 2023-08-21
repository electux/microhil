/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home_slots.cc
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
#include <iostream>
#include "microhil_view_home.h"

void MicroHILViewHome::onChannelChanged(Channel id)
{
    auto ix = static_cast<int>(id);
    bool status = m_enableChannels[ix]->get_active();

    if(status)
    {
        enableChannel(id);
    }
    else
    {
        disableChannel(id);
    }

    m_channelEnabled.emit(id, status);
}

void MicroHILViewHome::onTypeSelected(Channel id)
{
    auto ix = static_cast<int>(id);

    if(m_enableChannels[ix]->get_active())
    {
        int controlType = m_selectControlChannels[ix]->get_active_row_number();
        switch(controlType)
        {
            case static_cast<int>(channelControlType::MICROHIL_TOGGLE_BUTTON):
                toggleModeChannel(id);
                break;
            case static_cast<int>(channelControlType::MICROHIL_TIMER_BUTTON):
                timerModeChannel(id);
                break;
        }

        m_channelControlType.emit(id, controlType);
    }
}

void MicroHILViewHome::onToggled(Channel id)
{
    auto ix = static_cast<int>(id);

    if(m_enableChannels[ix]->get_active())
    {
        bool status = m_toggleChannels[ix]->get_active();
        m_channelToggled.emit(id, status);
    }
}

void MicroHILViewHome::onSpinTimerChanged(Channel id)
{
    auto ix = static_cast<int>(id);

    if(m_enableChannels[ix]->get_active())
    {
        int value = m_spinTimerChannels[ix]->get_value_as_int();
        m_channelSpinTimerChanged.emit(id, value);
    }
}

void MicroHILViewHome::onToggleTimerChanged(Channel id)
{
    auto ix = static_cast<int>(id);

    if(m_enableChannels[ix]->get_active())
    {
        bool status = m_toggleTimerChannels[ix]->get_active();
        m_channelTimerToggled.emit(id, status);
    }
}

void MicroHILViewHome::onConnectClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_CONNECT);
}

void MicroHILViewHome::onDisconnectClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_DISCONNECT);
}

void MicroHILViewHome::onQuitClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_QUIT);
}

void MicroHILViewHome::onSerialSettingsClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_SERIAL_SETTINGS);
}

void MicroHILViewHome::onLogSettingsClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_LOG_SETTINGS);
}

void MicroHILViewHome::onAboutClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_ABOUT);
}
