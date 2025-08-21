/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * home.cc
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
#include <string>
#include "home.h"

namespace
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Application home window widgets parameters
    ///   home_title - window title
    ///   home_width - window width
    ///   home_height - window height
    ///   home_num_channels - number of channels
    ///   home_en_channel_label - checkbox enable channel label
    ///   home_toggle_channel_label - label for toogle channel
    ///   home_toggle_channel_button_activate - toggle button channel label 
    ///   home_toggle_channel_button_deactivate - toggle button channel label
    ///   home_timer_channel_label - label for timer channel
    ///   home_timer_channel_button_start - spinner channel button label
    ///   home_timer_channel_button_stop - spinner channel button label
    ///   home_status_fraction - status init fraction
    ///   home_box_channel_margin - box channel margin
    ///   home_box_channel_spacing - box channel spacing
    ///   home_channel_mode_options - channel mode options for combobox
    constexpr const char home_title[]{"microhildesk"};
    constexpr int home_width{600};
    constexpr int home_height{250};
    constexpr int home_num_channels{8};
    constexpr const char home_en_channel_label[]{"Enable Channel #"};
    constexpr const char home_toggle_channel_label[]{"Toogle Channel #"};
    constexpr const char home_toggle_channel_button_activate[]{"Activate"};
    constexpr const char home_toggle_channel_button_deactivate[]{"Deactivate"};
    constexpr const char home_timer_channel_label[]{"Use timer #"};
    constexpr const char home_timer_channel_button_start[]{"Start"};
    constexpr const char home_timer_channel_button_stop[]{"Stop"};
    constexpr float home_status_fraction{0.0};
    constexpr int home_box_channel_margin{10};
    constexpr int home_box_channel_spacing{5};
    constexpr const char *home_channel_mode_options[]{"Toogle Active", "Timer Active"};
};

using namespace Electux::App::View;

AppHome::AppHome()
{
    //////////////////////////////////////////////////////////////////////////
    /// Setup application home window
    set_title(home_title);
    set_default_size(home_width, home_height);
    set_resizable(false);
    set_show_menubar(true);
    m_box_root.set_orientation(Gtk::Orientation::HORIZONTAL);
    set_child(m_box_root);

    for(auto i = 0; i < home_num_channels; i++)
    {
        std::string channel = std::to_string(i);
        m_box_channels.emplace_back(Gtk::Orientation::VERTICAL);
        m_enable_channels.emplace_back(home_en_channel_label + channel);
        m_box_channels[i].append(m_enable_channels[i]);
        m_select_control_channels.emplace_back();
        for (const auto& option : home_channel_mode_options)
        {
            m_select_control_channels[i].append(option);
        }
        m_box_channels[i].append(m_select_control_channels[i]);
        m_label_toggle_channels.emplace_back(home_toggle_channel_label + channel);
        m_box_channels[i].append(m_label_toggle_channels[i]);
        m_toggle_channels.emplace_back();
        m_toggle_channels[i].set_label(home_toggle_channel_button_activate);
        m_box_channels[i].append(m_toggle_channels[i]);
        m_label_timer_channels.emplace_back(home_timer_channel_label + channel);
        m_box_channels[i].append(m_label_timer_channels[i]);
        m_spin_timer_channels.emplace_back();
        m_box_channels[i].append(m_spin_timer_channels[i]);
        m_toggle_timer_channels.emplace_back();
        m_toggle_timer_channels[i].set_label(home_timer_channel_button_start);
        m_box_channels[i].append(m_toggle_timer_channels[i]);
        m_stauts_timer_channels.emplace_back();
        m_stauts_timer_channels[i].set_fraction(home_status_fraction);
        m_box_channels[i].append(m_stauts_timer_channels[i]);
        m_box_channels[i].set_margin(home_box_channel_margin);
        m_box_channels[i].set_spacing(home_box_channel_spacing);
        m_box_root.append(m_box_channels[i]);

        //////////////////////////////////////////////////////////////////////
        /// Maps home (signals and slots)
        mapping(i);
    }
}
