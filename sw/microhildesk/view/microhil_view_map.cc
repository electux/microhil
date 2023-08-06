/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_map.cc
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

void MicroHILView::mapping()
{
    ////////////////////////////////////////////////////////////////////////////
    // Map channel signals and slots
    m_enableChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0)
    );

    m_enableChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1)
    );

    m_enableChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2)
    );

    m_enableChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3)
    );

    m_selectControlChannels[0]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0TypeSelected)
    );

    m_selectControlChannels[1]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1TypeSelected)
    );

    m_selectControlChannels[2]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2TypeSelected)
    );

    m_selectControlChannels[3]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3TypeSelected)
    );

    m_toggleChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0Toggled)
    );

    m_toggleChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1Toggled)
    );

    m_toggleChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2Toggled)
    );

    m_toggleChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3Toggled)
    );

    m_spinTimerChannels[0]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0SpinTimerChanged)
    );

    m_spinTimerChannels[1]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1SpinTimerChanged)
    );

    m_spinTimerChannels[2]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2SpinTimerChanged)
    );

    m_spinTimerChannels[3]->signal_changed().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3SpinTimerChanged)
    );

    m_toggleTimerChannels[0]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel0TimerChanged)
    );

    m_toggleTimerChannels[1]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel1TimerChanged)
    );

    m_toggleTimerChannels[2]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel2TimerChanged)
    );

    m_toggleTimerChannels[3]->signal_toggled().connect(
        sigc::mem_fun(*this, &MicroHILView::onChannel3TimerChanged)
    );
}
