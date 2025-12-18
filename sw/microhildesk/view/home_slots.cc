/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * home_slots.cc
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
#include <iostream>
#include "home.h"

using namespace Electux::App::View;

void AppHome::on_channel_enable_changed()
{
    for (auto& button : m_enable_channels)
    {
        if (button.get_active())
        {
            std::cout << button.get_label() << " is checked" << std::endl;
        }
        else
        {
            std::cout << button.get_label() << " is unchecked" << std::endl;
        }
    }
}

void AppHome::on_channel_mode_changed()
{
    for (auto& combo : m_select_control_channels)
    {
        std::cout << "Selected: " << combo.get_active_text() << std::endl;
    }
}

void AppHome::on_channel_toggle_changed()
{
    for (auto &toggle : m_toggle_channels)
    {
        std::cout << "Toggled: " << toggle.get_active() << std::endl;
    }   
}

void AppHome::on_channel_timer_changed()
{
    for (auto &timer : m_spin_timer_channels)
    {
        std::cout << "Toggled: " << timer.get_value_as_int() << std::endl;
    }  
}

void AppHome::on_channel_timer_toogle_changed()
{
    for (auto &toggle_timer : m_toggle_timer_channels)
    {
        std::cout << "Toggled: " << toggle_timer.get_active() << std::endl;
    }  
}
