/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_slots.cc
 * Copyright (C) 2021 Vladimir Roncevic <elektron.ronca@gmail.com>
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
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "microhil_view.h"

void MicroHILView::onChannel0()
{
    bool status = m_enableChannels[0]->get_active();
    m_channel0Enabled.emit(status);
}

void MicroHILView::onChannel1()
{
    bool status = m_enableChannels[1]->get_active();
    m_channel1Enabled.emit(status);
}

void MicroHILView::onChannel2()
{
    bool status = m_enableChannels[2]->get_active();
    m_channel2Enabled.emit(status);
}

void MicroHILView::onChannel3()
{
    bool status = m_enableChannels[3]->get_active();
    m_channel3Enabled.emit(status);
}

void MicroHILView::onChannel0TypeSelected()
{
    int controlType = m_selectControlChannels[0]->get_active_row_number();

    switch(controlType)
    {
        case static_cast<int>(channelControlType::TOGGLE_BUTTON):
            break;
        case static_cast<int>(channelControlType::TIMER_BUTTON):
            break;
    }

    m_channel0ControlType.emit(controlType);
}

void MicroHILView::onChannel1TypeSelected()
{
    int controlType = m_selectControlChannels[1]->get_active_row_number();

    switch(controlType)
    {
        case static_cast<int>(channelControlType::TOGGLE_BUTTON):
            break;
        case static_cast<int>(channelControlType::TIMER_BUTTON):
            break;
    }

    m_channel1ControlType.emit(controlType);
}

void MicroHILView::onChannel2TypeSelected()
{
    int controlType = m_selectControlChannels[2]->get_active_row_number();

    switch(controlType)
    {
        case static_cast<int>(channelControlType::TOGGLE_BUTTON):
            break;
        case static_cast<int>(channelControlType::TIMER_BUTTON):
            break;
    }

    m_channel2ControlType.emit(controlType);
}

void MicroHILView::onChannel3TypeSelected()
{
    int controlType = m_selectControlChannels[3]->get_active_row_number();

    switch(controlType)
    {
        case static_cast<int>(channelControlType::TOGGLE_BUTTON):
            break;
        case static_cast<int>(channelControlType::TIMER_BUTTON):
            break;
    }

    m_channel3ControlType.emit(controlType);
}

void MicroHILView::onChannel0Toggled()
{
    bool status = m_toggleChannels[0]->get_active();
    m_channel0Toggled.emit(status);
}

void MicroHILView::onChannel1Toggled()
{
    bool status = m_toggleChannels[1]->get_active();
    m_channel1Toggled.emit(status);
}

void MicroHILView::onChannel2Toggled()
{
    bool status = m_toggleChannels[2]->get_active();
    m_channel2Toggled.emit(status);
}

void MicroHILView::onChannel3Toggled()
{
    bool status = m_toggleChannels[3]->get_active();
    m_channel3Toggled.emit(status);
}

void MicroHILView::onChannel0SpinTimerChanged()
{
    int value = m_spinTimerChannels[0]->get_value_as_int();
    m_channel0SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel1SpinTimerChanged()
{
    int value = m_spinTimerChannels[1]->get_value_as_int();
    m_channel1SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel2SpinTimerChanged()
{
    int value = m_spinTimerChannels[2]->get_value_as_int();
    m_channel2SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel3SpinTimerChanged()
{
    int value = m_spinTimerChannels[3]->get_value_as_int();
    m_channel3SpinTimerChanged.emit(value);
}

void MicroHILView::onChannel0TimerChanged()
{
    bool status = m_toggleTimerChannels[0]->get_active();
    m_channel0TimerToggled.emit(status);
}

void MicroHILView::onChannel1TimerChanged()
{
    bool status = m_toggleTimerChannels[1]->get_active();
    m_channel1TimerToggled.emit(status);
}

void MicroHILView::onChannel2TimerChanged()
{
    bool status = m_toggleTimerChannels[2]->get_active();
    m_channel2TimerToggled.emit(status);
}

void MicroHILView::onChannel3TimerChanged()
{
    bool status = m_toggleTimerChannels[3]->get_active();
    m_channel3TimerToggled.emit(status);
}
