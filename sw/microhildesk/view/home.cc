/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * home.cc
 * Copyright (C) 2024 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include <string>

using namespace Electux::App::View;

AppHome::AppHome()
{
    set_title("microhildesk");
    set_default_size(600, 250);
    set_resizable(false);
    set_show_menubar(true);
    m_box_root.set_orientation(Gtk::Orientation::HORIZONTAL);
    set_child(m_box_root);

    for(int i = 0; i < 8; i++)
    {
        std::string channel = std::to_string(i);
        m_box_channels.emplace_back(Gtk::Orientation::VERTICAL);
        m_enable_channels.emplace_back("Enable Channel #" + channel);
        m_box_channels[i].append(m_enable_channels[i]);
        m_select_control_channels.emplace_back();
        m_box_channels[i].append(m_select_control_channels[i]);
        m_label_toggle_channels.emplace_back("Toogle Channel #" + channel);
        m_box_channels[i].append(m_label_toggle_channels[i]);
        m_toggle_channels.emplace_back();
        m_toggle_channels[i].set_label("Activate");
        m_box_channels[i].append(m_toggle_channels[i]);
        m_label_timer_channels.emplace_back("Use timer #" + channel);
        m_box_channels[i].append(m_label_timer_channels[i]);
        m_spin_timer_channels.emplace_back();
        m_box_channels[i].append(m_spin_timer_channels[i]);
        m_toggle_timer_channels.emplace_back();
        m_toggle_timer_channels[i].set_label("Start");
        m_box_channels[i].append(m_toggle_timer_channels[i]);
        m_stauts_timer_channels.emplace_back();
        m_box_channels[i].append(m_stauts_timer_channels[i]);
        m_box_channels[i].set_margin(10);
        m_box_channels[i].set_spacing(5);
        m_box_root.append(m_box_channels[i]);
    }
}

