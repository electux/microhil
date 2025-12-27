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
        void onChannelEnableChanged();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for setup channel mode
        void onChannelModeChanged();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for toggle mode
        void onChannelToggleChanged();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for timer mode
        void onChannelTimerChanged();

        //////////////////////////////////////////////////////////////////////
        /// @brief Signal handler for timer mode (start process)
        void onChannelTimerToogleChanged();

        //////////////////////////////////////////////////////////////////////
        /// @brief Container for packing widgets for home window
        ///   m_boxRoot - horizontal box for channel widgets
        ///   m_boxChannels - channel  container for widgets
        ///   m_enableChannels - checkbox for enabling channel
        ///   m_selectControlChannels - combobox for control type
        ///   m_labelToggleChannels - label for toggle channel
        ///   m_toggleChannels - toogle button (activate)
        ///   m_labelTimerChannels -  label for timer channel
        ///   m_spinTimerChannels - channel spinner
        ///   m_toggleTimerChannels - channel toogle timer (start)
        ///   m_statusTimerChannels - channel status (visual)
        Gtk::Box m_boxRoot{};
        std::vector<Gtk::Box> m_boxChannels{};
        std::vector<Gtk::CheckButton> m_enableChannels{};
        std::vector<Gtk::ComboBoxText> m_selectControlChannels{};
        std::vector<Gtk::Label> m_labelToggleChannels{};
        std::vector<Gtk::ToggleButton> m_toggleChannels{};
        std::vector<Gtk::Label> m_labelTimerChannels{};
        std::vector<Gtk::SpinButton> m_spinTimerChannels{};
        std::vector<Gtk::ToggleButton> m_toggleTimerChannels{};
        std::vector<Gtk::ProgressBar> m_statusTimerChannels{};
    };
};

