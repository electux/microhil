/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home_map.cc
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

void MicroHILViewHome::mapping()
{
    ////////////////////////////////////////////////////////////////////////
    // Map channel signals and slots
    m_enableChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel0)
    );

    m_enableChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel1)
    );

    m_enableChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel2)
    );

    m_enableChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel3)
    );

    m_enableChannels[4]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel4)
    );

    m_enableChannels[5]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel5)
    );

    m_enableChannels[6]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel6)
    );

    m_enableChannels[7]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel7)
    );

    m_selectControlChannels[0]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel0TypeSelected)
    );

    m_selectControlChannels[1]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel1TypeSelected)
    );

    m_selectControlChannels[2]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel2TypeSelected)
    );

    m_selectControlChannels[3]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel3TypeSelected)
    );

    m_selectControlChannels[4]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel4TypeSelected)
    );

    m_selectControlChannels[5]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel5TypeSelected)
    );

    m_selectControlChannels[6]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel6TypeSelected)
    );

    m_selectControlChannels[7]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel7TypeSelected)
    );

    m_toggleChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel0Toggled)
    );

    m_toggleChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel1Toggled)
    );

    m_toggleChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel2Toggled)
    );

    m_toggleChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel3Toggled)
    );

    m_toggleChannels[4]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel4Toggled)
    );

    m_toggleChannels[5]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel5Toggled)
    );

    m_toggleChannels[6]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel6Toggled)
    );

    m_toggleChannels[7]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel7Toggled)
    );

    m_spinTimerChannels[0]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel0SpinTimerChanged)
    );

    m_spinTimerChannels[1]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel1SpinTimerChanged)
    );

    m_spinTimerChannels[2]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel2SpinTimerChanged)
    );

    m_spinTimerChannels[3]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel3SpinTimerChanged)
    );

    m_spinTimerChannels[4]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel4SpinTimerChanged)
    );

    m_spinTimerChannels[5]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel5SpinTimerChanged)
    );

    m_spinTimerChannels[6]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel6SpinTimerChanged)
    );

    m_spinTimerChannels[7]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel7SpinTimerChanged)
    );

    m_toggleTimerChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel0TimerChanged)
    );

    m_toggleTimerChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel1TimerChanged)
    );

    m_toggleTimerChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel2TimerChanged)
    );

    m_toggleTimerChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel3TimerChanged)
    );

    m_toggleTimerChannels[4]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel4TimerChanged)
    );

    m_toggleTimerChannels[5]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel5TimerChanged)
    );

    m_toggleTimerChannels[6]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel6TimerChanged)
    );

    m_toggleTimerChannels[7]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onChannel7TimerChanged)
    );
}
