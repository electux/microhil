/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * home_map.cc
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include "home.h"

using namespace Electux::App::View;

void AppHome::mapping(int index)
{
    //////////////////////////////////////////////////////////////////////
    /// 
    m_enable_channels[index].signal_toggled().connect(sigc::mem_fun(*this, &AppHome::on_channel_enable_changed));
    m_select_control_channels[index].signal_changed().connect(sigc::mem_fun(*this, &AppHome::on_channel_mode_changed));
    m_toggle_channels[index].signal_toggled().connect(sigc::mem_fun(*this, &AppHome::on_channel_toggle_changed));
    m_spin_timer_channels[index].signal_changed().connect(sigc::mem_fun(*this, &AppHome::on_channel_timer_changed));
    m_toggle_timer_channels[index].signal_toggled().connect(sigc::mem_fun(*this, &AppHome::on_channel_timer_toogle_changed));
}
