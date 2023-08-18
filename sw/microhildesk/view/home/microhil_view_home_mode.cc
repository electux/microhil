/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home_mode.cc
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

void MicroHILViewHome::disableChannel0()
{
    m_selectControlChannels[0]->set_sensitive(false);
    m_toggleChannels[0]->set_sensitive(false);
    m_spinTimerChannels[0]->set_sensitive(false);
    m_toggleTimerChannels[0]->set_sensitive(false);
    m_stautsTimerChannels[0]->set_sensitive(false);
}

void MicroHILViewHome::enableChannel0()
{
    m_selectControlChannels[0]->set_sensitive(true);
    m_toggleChannels[0]->set_sensitive(true);
    m_spinTimerChannels[0]->set_sensitive(true);
    m_toggleTimerChannels[0]->set_sensitive(true);
    m_stautsTimerChannels[0]->set_sensitive(true);
}

void MicroHILViewHome::disableChannel1()
{
    m_selectControlChannels[1]->set_sensitive(false);
    m_toggleChannels[1]->set_sensitive(false);
    m_spinTimerChannels[1]->set_sensitive(false);
    m_toggleTimerChannels[1]->set_sensitive(false);
    m_stautsTimerChannels[1]->set_sensitive(false);
}

void MicroHILViewHome::enableChannel1()
{
    m_selectControlChannels[1]->set_sensitive(true);
    m_toggleChannels[1]->set_sensitive(true);
    m_spinTimerChannels[1]->set_sensitive(true);
    m_toggleTimerChannels[1]->set_sensitive(true);
    m_stautsTimerChannels[1]->set_sensitive(true);
}

void MicroHILViewHome::disableChannel2()
{
    m_selectControlChannels[2]->set_sensitive(false);
    m_toggleChannels[2]->set_sensitive(false);
    m_spinTimerChannels[2]->set_sensitive(false);
    m_toggleTimerChannels[2]->set_sensitive(false);
    m_stautsTimerChannels[2]->set_sensitive(false);
}

void MicroHILViewHome::enableChannel2()
{
    m_selectControlChannels[2]->set_sensitive(true);
    m_toggleChannels[2]->set_sensitive(true);
    m_spinTimerChannels[2]->set_sensitive(true);
    m_toggleTimerChannels[2]->set_sensitive(true);
    m_stautsTimerChannels[2]->set_sensitive(true);
}

void MicroHILViewHome::disableChannel3()
{
    m_selectControlChannels[3]->set_sensitive(false);
    m_toggleChannels[3]->set_sensitive(false);
    m_spinTimerChannels[3]->set_sensitive(false);
    m_toggleTimerChannels[3]->set_sensitive(false);
    m_stautsTimerChannels[3]->set_sensitive(false);
}

void MicroHILViewHome::enableChannel3()
{
    m_selectControlChannels[3]->set_sensitive(true);
    m_toggleChannels[3]->set_sensitive(true);
    m_spinTimerChannels[3]->set_sensitive(true);
    m_toggleTimerChannels[3]->set_sensitive(true);
    m_stautsTimerChannels[3]->set_sensitive(true);
}

void MicroHILViewHome::disableChannel4()
{
    m_selectControlChannels[4]->set_sensitive(false);
    m_toggleChannels[4]->set_sensitive(false);
    m_spinTimerChannels[4]->set_sensitive(false);
    m_toggleTimerChannels[4]->set_sensitive(false);
    m_stautsTimerChannels[4]->set_sensitive(false);
}

void MicroHILViewHome::enableChannel4()
{
    m_selectControlChannels[4]->set_sensitive(true);
    m_toggleChannels[4]->set_sensitive(true);
    m_spinTimerChannels[4]->set_sensitive(true);
    m_toggleTimerChannels[4]->set_sensitive(true);
    m_stautsTimerChannels[4]->set_sensitive(true);
}

void MicroHILViewHome::disableChannel5()
{
    m_selectControlChannels[5]->set_sensitive(false);
    m_toggleChannels[5]->set_sensitive(false);
    m_spinTimerChannels[5]->set_sensitive(false);
    m_toggleTimerChannels[5]->set_sensitive(false);
    m_stautsTimerChannels[5]->set_sensitive(false);
}

void MicroHILViewHome::enableChannel5()
{
    m_selectControlChannels[5]->set_sensitive(true);
    m_toggleChannels[5]->set_sensitive(true);
    m_spinTimerChannels[5]->set_sensitive(true);
    m_toggleTimerChannels[5]->set_sensitive(true);
    m_stautsTimerChannels[5]->set_sensitive(true);
}

void MicroHILViewHome::disableChannel6()
{
    m_selectControlChannels[6]->set_sensitive(false);
    m_toggleChannels[6]->set_sensitive(false);
    m_spinTimerChannels[6]->set_sensitive(false);
    m_toggleTimerChannels[6]->set_sensitive(false);
    m_stautsTimerChannels[6]->set_sensitive(false);
}

void MicroHILViewHome::enableChannel6()
{
    m_selectControlChannels[6]->set_sensitive(true);
    m_toggleChannels[6]->set_sensitive(true);
    m_spinTimerChannels[6]->set_sensitive(true);
    m_toggleTimerChannels[6]->set_sensitive(true);
    m_stautsTimerChannels[6]->set_sensitive(true);
}

void MicroHILViewHome::disableChannel7()
{
    m_selectControlChannels[7]->set_sensitive(false);
    m_toggleChannels[7]->set_sensitive(false);
    m_spinTimerChannels[7]->set_sensitive(false);
    m_toggleTimerChannels[7]->set_sensitive(false);
    m_stautsTimerChannels[7]->set_sensitive(false);
}

void MicroHILViewHome::enableChannel7()
{
    m_selectControlChannels[7]->set_sensitive(true);
    m_toggleChannels[7]->set_sensitive(true);
    m_spinTimerChannels[7]->set_sensitive(true);
    m_toggleTimerChannels[7]->set_sensitive(true);
    m_stautsTimerChannels[7]->set_sensitive(true);
}

void MicroHILViewHome::toggleModeChannel0()
{
    m_toggleChannels[0]->set_sensitive(true);
    m_spinTimerChannels[0]->set_sensitive(false);
    m_toggleTimerChannels[0]->set_sensitive(false);
    m_stautsTimerChannels[0]->set_sensitive(true);
}

void MicroHILViewHome::timerModeChannel0()
{
    m_toggleChannels[0]->set_sensitive(false);
    m_spinTimerChannels[0]->set_sensitive(true);
    m_toggleTimerChannels[0]->set_sensitive(true);
    m_stautsTimerChannels[0]->set_sensitive(true);
}

void MicroHILViewHome::toggleModeChannel1()
{
    m_toggleChannels[1]->set_sensitive(true);
    m_spinTimerChannels[1]->set_sensitive(false);
    m_toggleTimerChannels[1]->set_sensitive(false);
    m_stautsTimerChannels[1]->set_sensitive(true);
}

void MicroHILViewHome::timerModeChannel1()
{
    m_toggleChannels[1]->set_sensitive(false);
    m_spinTimerChannels[1]->set_sensitive(true);
    m_toggleTimerChannels[1]->set_sensitive(true);
    m_stautsTimerChannels[1]->set_sensitive(true);
}

void MicroHILViewHome::toggleModeChannel2()
{
    m_toggleChannels[2]->set_sensitive(true);
    m_spinTimerChannels[2]->set_sensitive(false);
    m_toggleTimerChannels[2]->set_sensitive(false);
    m_stautsTimerChannels[2]->set_sensitive(true);
}

void MicroHILViewHome::timerModeChannel2()
{
    m_toggleChannels[2]->set_sensitive(false);
    m_spinTimerChannels[2]->set_sensitive(true);
    m_toggleTimerChannels[2]->set_sensitive(true);
    m_stautsTimerChannels[2]->set_sensitive(true);
}

void MicroHILViewHome::toggleModeChannel3()
{
    m_toggleChannels[3]->set_sensitive(true);
    m_spinTimerChannels[3]->set_sensitive(false);
    m_toggleTimerChannels[3]->set_sensitive(false);
    m_stautsTimerChannels[3]->set_sensitive(true);
}

void MicroHILViewHome::timerModeChannel3()
{
    m_toggleChannels[3]->set_sensitive(false);
    m_spinTimerChannels[3]->set_sensitive(true);
    m_toggleTimerChannels[3]->set_sensitive(true);
    m_stautsTimerChannels[3]->set_sensitive(true);
}

void MicroHILViewHome::toggleModeChannel4()
{
    m_toggleChannels[4]->set_sensitive(true);
    m_spinTimerChannels[4]->set_sensitive(false);
    m_toggleTimerChannels[4]->set_sensitive(false);
    m_stautsTimerChannels[4]->set_sensitive(true);
}

void MicroHILViewHome::timerModeChannel4()
{
    m_toggleChannels[4]->set_sensitive(false);
    m_spinTimerChannels[4]->set_sensitive(true);
    m_toggleTimerChannels[4]->set_sensitive(true);
    m_stautsTimerChannels[4]->set_sensitive(true);
}

void MicroHILViewHome::toggleModeChannel5()
{
    m_toggleChannels[5]->set_sensitive(true);
    m_spinTimerChannels[5]->set_sensitive(false);
    m_toggleTimerChannels[5]->set_sensitive(false);
    m_stautsTimerChannels[5]->set_sensitive(true);
}

void MicroHILViewHome::timerModeChannel5()
{
    m_toggleChannels[5]->set_sensitive(false);
    m_spinTimerChannels[5]->set_sensitive(true);
    m_toggleTimerChannels[5]->set_sensitive(true);
    m_stautsTimerChannels[5]->set_sensitive(true);
}

void MicroHILViewHome::toggleModeChannel6()
{
    m_toggleChannels[6]->set_sensitive(true);
    m_spinTimerChannels[6]->set_sensitive(false);
    m_toggleTimerChannels[6]->set_sensitive(false);
    m_stautsTimerChannels[6]->set_sensitive(true);
}

void MicroHILViewHome::timerModeChannel6()
{
    m_toggleChannels[6]->set_sensitive(false);
    m_spinTimerChannels[6]->set_sensitive(true);
    m_toggleTimerChannels[6]->set_sensitive(true);
    m_stautsTimerChannels[6]->set_sensitive(true);
}

void MicroHILViewHome::toggleModeChannel7()
{
    m_toggleChannels[7]->set_sensitive(true);
    m_spinTimerChannels[7]->set_sensitive(false);
    m_toggleTimerChannels[7]->set_sensitive(false);
    m_stautsTimerChannels[7]->set_sensitive(true);
}

void MicroHILViewHome::timerModeChannel7()
{
    m_toggleChannels[7]->set_sensitive(false);
    m_spinTimerChannels[7]->set_sensitive(true);
    m_toggleTimerChannels[7]->set_sensitive(true);
    m_stautsTimerChannels[7]->set_sensitive(true);
}
