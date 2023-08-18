/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home_signals.cc
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

MicroHILViewHome::channel0Changed
MicroHILViewHome::channel0IsChanged()
{
    return m_channel0Enabled;
}

MicroHILViewHome::channel1Changed
MicroHILViewHome::channel1IsChanged()
{
    return m_channel1Enabled;
}

MicroHILViewHome::channel2Changed
MicroHILViewHome::channel2IsChanged()
{
    return m_channel2Enabled;
}

MicroHILViewHome::channel3Changed
MicroHILViewHome::channel3IsChanged()
{
    return m_channel3Enabled;
}

MicroHILViewHome::channel4Changed
MicroHILViewHome::channel4IsChanged()
{
    return m_channel4Enabled;
}

MicroHILViewHome::channel5Changed
MicroHILViewHome::channel5IsChanged()
{
    return m_channel5Enabled;
}

MicroHILViewHome::channel6Changed
MicroHILViewHome::channel6IsChanged()
{
    return m_channel6Enabled;
}

MicroHILViewHome::channel7Changed
MicroHILViewHome::channel7IsChanged()
{
    return m_channel7Enabled;
}

MicroHILViewHome::select0Changed
MicroHILViewHome::channel0IsSelected()
{
    return m_channel0ControlType;
}

MicroHILViewHome::select1Changed
MicroHILViewHome::channel1IsSelected()
{
    return m_channel1ControlType;
}

MicroHILViewHome::select2Changed
MicroHILViewHome::channel2IsSelected()
{
    return m_channel2ControlType;
}

MicroHILViewHome::select3Changed
MicroHILViewHome::channel3IsSelected()
{
    return m_channel3ControlType;
}

MicroHILViewHome::select4Changed
MicroHILViewHome::channel4IsSelected()
{
    return m_channel4ControlType;
}

MicroHILViewHome::select5Changed
MicroHILViewHome::channel5IsSelected()
{
    return m_channel5ControlType;
}

MicroHILViewHome::select6Changed
MicroHILViewHome::channel6IsSelected()
{
    return m_channel6ControlType;
}

MicroHILViewHome::select7Changed
MicroHILViewHome::channel7IsSelected()
{
    return m_channel7ControlType;
}

MicroHILViewHome::channel0Toggled
MicroHILViewHome::channel0IsToggled()
{
    return m_channel0Toggled;
}

MicroHILViewHome::channel1Toggled
MicroHILViewHome::channel1IsToggled()
{
    return m_channel1Toggled;
}

MicroHILViewHome::channel2Toggled
MicroHILViewHome::channel2IsToggled()
{
    return m_channel2Toggled;
}

MicroHILViewHome::channel3Toggled
MicroHILViewHome::channel3IsToggled()
{
    return m_channel3Toggled;
}

MicroHILViewHome::channel4Toggled
MicroHILViewHome::channel4IsToggled()
{
    return m_channel4Toggled;
}

MicroHILViewHome::channel5Toggled
MicroHILViewHome::channel5IsToggled()
{
    return m_channel5Toggled;
}

MicroHILViewHome::channel6Toggled
MicroHILViewHome::channel6IsToggled()
{
    return m_channel6Toggled;
}

MicroHILViewHome::channel7Toggled
MicroHILViewHome::channel7IsToggled()
{
    return m_channel7Toggled;
}

MicroHILViewHome::channel0SpinTimerChanged
MicroHILViewHome::channel0IsSpinTimerChanged()
{
    return m_channel0SpinTimerChanged;
}

MicroHILViewHome::channel1SpinTimerChanged
MicroHILViewHome::channel1IsSpinTimerChanged()
{
    return m_channel1SpinTimerChanged;
}

MicroHILViewHome::channel2SpinTimerChanged
MicroHILViewHome::channel2IsSpinTimerChanged()
{
    return m_channel2SpinTimerChanged;
}

MicroHILViewHome::channel3SpinTimerChanged
MicroHILViewHome::channel3IsSpinTimerChanged()
{
    return m_channel3SpinTimerChanged;
}

MicroHILViewHome::channel4SpinTimerChanged
MicroHILViewHome::channel4IsSpinTimerChanged()
{
    return m_channel4SpinTimerChanged;
}

MicroHILViewHome::channel5SpinTimerChanged
MicroHILViewHome::channel5IsSpinTimerChanged()
{
    return m_channel5SpinTimerChanged;
}

MicroHILViewHome::channel6SpinTimerChanged
MicroHILViewHome::channel6IsSpinTimerChanged()
{
    return m_channel6SpinTimerChanged;
}

MicroHILViewHome::channel7SpinTimerChanged
MicroHILViewHome::channel7IsSpinTimerChanged()
{
    return m_channel7SpinTimerChanged;
}

MicroHILViewHome::channel0TimerToggled
MicroHILViewHome::channel0IsTimerChanged()
{
    return m_channel0TimerToggled;
}

MicroHILViewHome::channel1TimerToggled
MicroHILViewHome::channel1IsTimerChanged()
{
    return m_channel1TimerToggled;
}

MicroHILViewHome::channel2TimerToggled
MicroHILViewHome::channel2IsTimerChanged()
{
    return m_channel2TimerToggled;
}

MicroHILViewHome::channel3TimerToggled
MicroHILViewHome::channel3IsTimerChanged()
{
    return m_channel3TimerToggled;
}

MicroHILViewHome::channel4TimerToggled
MicroHILViewHome::channel4IsTimerChanged()
{
    return m_channel4TimerToggled;
}

MicroHILViewHome::channel5TimerToggled
MicroHILViewHome::channel5IsTimerChanged()
{
    return m_channel5TimerToggled;
}

MicroHILViewHome::channel6TimerToggled
MicroHILViewHome::channel6IsTimerChanged()
{
    return m_channel6TimerToggled;
}

MicroHILViewHome::channel7TimerToggled
MicroHILViewHome::channel7IsTimerChanged()
{
    return m_channel7TimerToggled;
}
