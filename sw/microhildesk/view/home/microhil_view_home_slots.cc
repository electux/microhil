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
#include "microhil_view_home.h"

void MHViewHome::onChannelChanged(Channel id)
{
    auto ix = channelToInt(id);
    bool status = m_enableChannels[ix]->get_active();

    if (status)
    {
        enableChannel(id);
    }
    else
    {
        disableChannel(id);
    }

    m_channelEnabled.emit(id, status);
}

void MHViewHome::onTypeSelected(Channel id)
{
    auto ix = channelToInt(id);

    if (m_enableChannels[ix]->get_active())
    {
        int controlType = m_selectControlChannels[ix]->get_active_row_number();

        if (controlTypeToInt(channelControlType::MICROHIL_TOGGLE_BUTTON) == 0)
        {
            toggleModeChannel(id);
        }

        if (controlTypeToInt(channelControlType::MICROHIL_TIMER_BUTTON) == 1)
        {
            timerModeChannel(id);
        }

        m_channelControlType.emit(id, controlType);
    }
}

void MHViewHome::onToggled(Channel id)
{
    auto ix = channelToInt(id);

    if (m_enableChannels[ix]->get_active())
    {
        bool status = m_toggleChannels[ix]->get_active();
        m_channelToggled.emit(id, status);
    }
}

void MHViewHome::onSpinTimerChanged(Channel id)
{
    auto ix = channelToInt(id);

    if (m_enableChannels[ix]->get_active())
    {
        int value = m_spinTimerChannels[ix]->get_value_as_int();
        m_channelSpinTimerChanged.emit(id, value);
    }
}

void MHViewHome::onToggleTimerChanged(Channel id)
{
    auto ix = channelToInt(id);

    if (m_enableChannels[ix]->get_active())
    {
        bool status = m_toggleTimerChannels[ix]->get_active();
        m_channelTimerToggled.emit(id, status);
    }
}

void MHViewHome::onConnectClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_CONNECT);
    m_connect->set_sensitive(false);
    m_disconnect->set_sensitive(true);
    m_serialSettings->set_sensitive(true);
}

void MHViewHome::onDisconnectClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_DISCONNECT);
    m_connect->set_sensitive(true);
    m_disconnect->set_sensitive(false);
    m_serialSettings->set_sensitive(true);
}

void MHViewHome::onQuitClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_QUIT);
}

void MHViewHome::onSerialSettingsClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_SERIAL_SETTINGS);
}

void MHViewHome::onLogSettingsClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_LOG_SETTINGS);
}

void MHViewHome::onAboutClicked()
{
    m_actionViewTriggered.emit(ViewId::MICROHIL_ABOUT);
}
