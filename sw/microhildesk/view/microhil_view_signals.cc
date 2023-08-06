/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_signals.cc
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
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */
#include "microhil_view.h"

MicroHILView::channel0Changed MicroHILView::channel0IsChanged()
{
    return m_channel0Enabled;
}

MicroHILView::channel1Changed MicroHILView::channel1IsChanged()
{
    return m_channel1Enabled;
}

MicroHILView::channel2Changed MicroHILView::channel2IsChanged()
{
    return m_channel2Enabled;
}

MicroHILView::channel3Changed MicroHILView::channel3IsChanged()
{
    return m_channel3Enabled;
}

MicroHILView::select0Changed MicroHILView::channel0IsSelected()
{
    return m_channel0ControlType;
}

MicroHILView::select1Changed MicroHILView::channel1IsSelected()
{
    return m_channel1ControlType;
}

MicroHILView::select2Changed MicroHILView::channel2IsSelected()
{
    return m_channel2ControlType;
}

MicroHILView::select3Changed MicroHILView::channel3IsSelected()
{
    return m_channel3ControlType;
}

MicroHILView::channel0Toggled MicroHILView::channel0IsToggled()
{
    return m_channel0Toggled;
}

MicroHILView::channel1Toggled MicroHILView::channel1IsToggled()
{
    return m_channel1Toggled;
}

MicroHILView::channel2Toggled MicroHILView::channel2IsToggled()
{
    return m_channel2Toggled;
}

MicroHILView::channel3Toggled MicroHILView::channel3IsToggled()
{
    return m_channel3Toggled;
}

MicroHILView::channel0SpinTimerChanged
MicroHILView::channel0IsSpinTimerChanged()
{
    return m_channel0SpinTimerChanged;
}

MicroHILView::channel1SpinTimerChanged
MicroHILView::channel1IsSpinTimerChanged()
{
    return m_channel1SpinTimerChanged;
}

MicroHILView::channel2SpinTimerChanged
MicroHILView::channel2IsSpinTimerChanged()
{
    return m_channel2SpinTimerChanged;
}

MicroHILView::channel3SpinTimerChanged
MicroHILView::channel3IsSpinTimerChanged()
{
    return m_channel3SpinTimerChanged;
}

MicroHILView::channel0TimerToggled MicroHILView::channel0IsTimerChanged()
{
    return m_channel0TimerToggled;
}

MicroHILView::channel1TimerToggled MicroHILView::channel1IsTimerChanged()
{
    return m_channel1TimerToggled;
}

MicroHILView::channel2TimerToggled MicroHILView::channel2IsTimerChanged()
{
    return m_channel2TimerToggled;
}

MicroHILView::channel3TimerToggled MicroHILView::channel3IsTimerChanged()
{
    return m_channel3TimerToggled;
}
