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

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief Number of map channels
    constexpr int kNumberOfMapChannels{8};
}

void MicroHILViewHome::mapping()
{
    ////////////////////////////////////////////////////////////////////////
    /// Map Connect menu-item signal slot
    m_connect->signal_activate().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onConnectClicked)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map Disconnect menu-item signal slot
    m_disconnect->signal_activate().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onDisconnectClicked)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map Quit menu-item signal slot
    m_quit->signal_activate().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onQuitClicked)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map Serial Settings menu-item signal slot
    m_serialSettings->signal_activate().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onSerialSettingsClicked)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map Log Settings menu-item signal slot
    m_logSettings->signal_activate().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onLogSettingsClicked)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map About menu-item signal slot
    m_about->signal_activate().connect(
        sigc::mem_fun(*this, &MicroHILViewHome::onAboutClicked)
    );

    ////////////////////////////////////////////////////////////////////////
    /// Map channels (signals and slots)
    for (int i = 0; i < kNumberOfMapChannels; i++)
    {
        m_enableChannels[i]->signal_toggled().connect(
            sigc::bind<Channel>(
                sigc::mem_fun(*this, &MicroHILViewHome::onChannelChanged),
                static_cast<Channel>(i)
            )
        );

        m_selectControlChannels[i]->signal_changed().connect(
            sigc::bind<Channel>(
                sigc::mem_fun(*this, &MicroHILViewHome::onTypeSelected),
                static_cast<Channel>(i)
            )
        );

        m_toggleChannels[i]->signal_toggled().connect(
            sigc::bind<Channel>(
                sigc::mem_fun(*this, &MicroHILViewHome::onToggled),
                static_cast<Channel>(i)
            )
        );

        m_spinTimerChannels[i]->signal_changed().connect(
            sigc::bind<Channel>(
                sigc::mem_fun(*this, &MicroHILViewHome::onSpinTimerChanged),
                static_cast<Channel>(i)
            )
        );

        m_toggleTimerChannels[i]->signal_toggled().connect(
            sigc::bind<Channel>(
                sigc::mem_fun(*this, &MicroHILViewHome::onToggleTimerChanged),
                static_cast<Channel>(i)
            )
        );
    }
}
