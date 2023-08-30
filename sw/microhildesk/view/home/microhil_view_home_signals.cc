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

MicroHILViewHome::SigActionViewTriggered
MicroHILViewHome::viewChanged()
{
    return m_actionViewTriggered;
}

MicroHILViewHome::SigChannelChanged
MicroHILViewHome::channelIsChanged()
{
    return m_channelEnabled;
}

MicroHILViewHome::SigSelectChanged
MicroHILViewHome::channelIsSelected()
{
    return m_channelControlType;
}

MicroHILViewHome::SigChannelToggled
MicroHILViewHome::channelIsToggled()
{
    return m_channelToggled;
}

MicroHILViewHome::SigChannelSpinTimerChanged
MicroHILViewHome::channelIsSpinTimerChanged()
{
    return m_channelSpinTimerChanged;
}

MicroHILViewHome::SigChannelTimerToggled
MicroHILViewHome::channelIsTimerChanged()
{
    return m_channelTimerToggled;
}
