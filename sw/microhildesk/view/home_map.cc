/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * home_map.cc
 * Copyright (C) 2025 - 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include <view/home.h>

using namespace Electux::App::View;

void AppHome::mapping(int index)
{
    //////////////////////////////////////////////////////////////////////
    /// @brief Connect signals and slots for home window widgets
    m_enableChannels[index].signal_toggled().connect(sigc::mem_fun(*this, &AppHome::onChannelEnableChanged));
    m_selectControlChannels[index].signal_changed().connect(sigc::mem_fun(*this, &AppHome::onChannelModeChanged));
    m_toggleChannels[index].signal_toggled().connect(sigc::mem_fun(*this, &AppHome::onChannelToggleChanged));
    m_spinTimerChannels[index].signal_changed().connect(sigc::mem_fun(*this, &AppHome::onChannelTimerChanged));
    m_toggleTimerChannels[index].signal_toggled().connect(sigc::mem_fun(*this, &AppHome::onChannelTimerToogleChanged));
}
