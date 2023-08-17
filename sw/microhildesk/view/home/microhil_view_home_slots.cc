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

void MicroHILViewHome::onChannel0()
{
    bool status = m_enableChannels[0]->get_active();

    if(status)
    {
        enableChannel0();
    }
    else
    {
        disableChannel0();
    }

    m_channel0Enabled.emit(status);
}

void MicroHILViewHome::onChannel1()
{
    bool status = m_enableChannels[1]->get_active();

    if(status)
    {
        enableChannel1();
    }
    else
    {
        disableChannel1();
    }

    m_channel1Enabled.emit(status);
}

void MicroHILViewHome::onChannel2()
{
    bool status = m_enableChannels[2]->get_active();

    if(status)
    {
        enableChannel2();
    }
    else
    {
        disableChannel2();
    }

    m_channel2Enabled.emit(status);
}

void MicroHILViewHome::onChannel3()
{
    bool status = m_enableChannels[3]->get_active();

    if(status)
    {
        enableChannel3();
    }
    else
    {
        disableChannel3();
    }

    m_channel3Enabled.emit(status);
}

void MicroHILViewHome::onChannel0TypeSelected()
{
    if(m_enableChannels[0]->get_active() == true)
    {
        int controlType = m_selectControlChannels[0]->get_active_row_number();

        switch(controlType)
        {
            case static_cast<int>(channelControlType::TOGGLE_BUTTON):
                toggleModeChannel0();
                break;
            case static_cast<int>(channelControlType::TIMER_BUTTON):
                timerModeChannel0();
                break;
        }

        m_channel0ControlType.emit(controlType);
    }
}

void MicroHILViewHome::onChannel1TypeSelected()
{
    if(m_enableChannels[1]->get_active() == true)
    {
        int controlType = m_selectControlChannels[1]->get_active_row_number();

        switch(controlType)
        {
            case static_cast<int>(channelControlType::TOGGLE_BUTTON):
                toggleModeChannel1();
                break;
            case static_cast<int>(channelControlType::TIMER_BUTTON):
                timerModeChannel1();
                break;
        }

        m_channel1ControlType.emit(controlType);
    }
}

void MicroHILViewHome::onChannel2TypeSelected()
{
    if(m_enableChannels[2]->get_active() == true)
    {
        int controlType = m_selectControlChannels[2]->get_active_row_number();

        switch(controlType)
        {
            case static_cast<int>(channelControlType::TOGGLE_BUTTON):
                toggleModeChannel2();
                break;
            case static_cast<int>(channelControlType::TIMER_BUTTON):
                timerModeChannel2();
                break;
        }

        m_channel2ControlType.emit(controlType);
    }
}

void MicroHILViewHome::onChannel3TypeSelected()
{
    if(m_enableChannels[3]->get_active() == true)
    {
        int controlType = m_selectControlChannels[3]->get_active_row_number();

        switch(controlType)
        {
            case static_cast<int>(channelControlType::TOGGLE_BUTTON):
                toggleModeChannel3();
                break;
            case static_cast<int>(channelControlType::TIMER_BUTTON):
                timerModeChannel3();
                break;
        }

        m_channel3ControlType.emit(controlType);
    }
}

void MicroHILViewHome::onChannel0Toggled()
{
    if(m_enableChannels[0]->get_active() == true)
    {
        bool status = m_toggleChannels[0]->get_active();
        m_channel0Toggled.emit(status);
    }
}

void MicroHILViewHome::onChannel1Toggled()
{
    if(m_enableChannels[1]->get_active() == true)
    {
        bool status = m_toggleChannels[1]->get_active();
        m_channel1Toggled.emit(status);
    }
}

void MicroHILViewHome::onChannel2Toggled()
{
    if(m_enableChannels[2]->get_active() == true)
    {
        bool status = m_toggleChannels[2]->get_active();
        m_channel2Toggled.emit(status);
    }
}

void MicroHILViewHome::onChannel3Toggled()
{
    if(m_enableChannels[3]->get_active() == true)
    {
        bool status = m_toggleChannels[3]->get_active();
        m_channel3Toggled.emit(status);
    }
}

void MicroHILViewHome::onChannel0SpinTimerChanged()
{
    if(m_enableChannels[0]->get_active() == true)
    {
        int value = m_spinTimerChannels[0]->get_value_as_int();
        m_channel0SpinTimerChanged.emit(value);
    }
}

void MicroHILViewHome::onChannel1SpinTimerChanged()
{
    if(m_enableChannels[1]->get_active() == true)
    {
        int value = m_spinTimerChannels[1]->get_value_as_int();
        m_channel1SpinTimerChanged.emit(value);
    }
}

void MicroHILViewHome::onChannel2SpinTimerChanged()
{
    if(m_enableChannels[2]->get_active() == true)
    {
        int value = m_spinTimerChannels[2]->get_value_as_int();
        m_channel2SpinTimerChanged.emit(value);
    }
}

void MicroHILViewHome::onChannel3SpinTimerChanged()
{
    if(m_enableChannels[3]->get_active() == true)
    {
        int value = m_spinTimerChannels[3]->get_value_as_int();
        m_channel3SpinTimerChanged.emit(value);
    }
}

void MicroHILViewHome::onChannel0TimerChanged()
{
    if(m_enableChannels[0]->get_active() == true)
    {
        bool status = m_toggleTimerChannels[0]->get_active();
        m_channel0TimerToggled.emit(status);
    }
}

void MicroHILViewHome::onChannel1TimerChanged()
{
    if(m_enableChannels[1]->get_active() == true)
    {
        bool status = m_toggleTimerChannels[1]->get_active();
        m_channel1TimerToggled.emit(status);
    }
}

void MicroHILViewHome::onChannel2TimerChanged()
{
    if(m_enableChannels[2]->get_active() == true)
    {
        bool status = m_toggleTimerChannels[2]->get_active();
        m_channel2TimerToggled.emit(status);
    }
}

void MicroHILViewHome::onChannel3TimerChanged()
{
    if(m_enableChannels[3]->get_active() == true)
    {
        bool status = m_toggleTimerChannels[3]->get_active();
        m_channel3TimerToggled.emit(status);
    }
}
