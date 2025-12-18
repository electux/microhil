/* -*- Mode: H; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * home.h
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
#pragma once

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/togglebutton.h>

namespace Electux::App::View
{
    //////////////////////////////////////////////////////////////////////////
    /// @brief Home view window definition
    class AppHome : public Gtk::ApplicationWindow
    {
    public:
        //////////////////////////////////////////////////////////////////////
        /// @brief AppHome constructor
        explicit AppHome();

    private:
        //////////////////////////////////////////////////////////////////////
        /// @brief Maps home (signals and slots)
        void mapping(int index);

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for enablement channel
        void on_channel_enable_changed();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for setup channel mode
        void on_channel_mode_changed();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for toggle mode
        void on_channel_toggle_changed();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for timer mode
        void on_channel_timer_changed();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for timer mode (start process)
        void on_channel_timer_toogle_changed();

        //////////////////////////////////////////////////////////////////////
        /// @brief Container for packing widgets for home window
        ///   m_box_root - horizontal box for channel widgets
        ///   m_box_channels - channel  container for widgets
        ///   m_enable_channels - checkbox for enabling channel
        ///   m_select_control_channels - combobox for control type
        ///   m_label_toggle_channels - label for toggle channel
        ///   m_toggle_channels - toogle button (activate)
        ///   m_label_timer_channels -  label for timer channel
        ///   m_spin_timer_channels - channel spinner
        ///   m_toggle_timer_channels - channel toogle timer (start)
        ///   m_status_timer_channels - channel status (visual)
        Gtk::Box m_box_root;
        std::vector<Gtk::Box> m_box_channels;
        std::vector<Gtk::CheckButton> m_enable_channels;
        std::vector<Gtk::ComboBoxText> m_select_control_channels;
        std::vector<Gtk::Label> m_label_toggle_channels;
        std::vector<Gtk::ToggleButton> m_toggle_channels;
        std::vector<Gtk::Label> m_label_timer_channels;
        std::vector<Gtk::SpinButton> m_spin_timer_channels;
        std::vector<Gtk::ToggleButton> m_toggle_timer_channels;
        std::vector<Gtk::ProgressBar> m_status_timer_channels;
    };
};

