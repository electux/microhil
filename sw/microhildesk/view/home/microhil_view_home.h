/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home.h
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
#pragma once

#include <vector>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <giomm/resource.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/progressbar.h>
#include "microhil_view_home_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILViewHome class declaration and definition
class MicroHILViewHome: public AbMicroHILViewHome, public Gtk::ApplicationWindow
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewHome constructor
    /// @param object base object instance
    /// @param ui builder parser
    MicroHILViewHome(
        BaseObjectType* object, Glib::RefPtr<Gtk::Builder> const& ui
    );

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILViewHome destructor
    ~MicroHILViewHome() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for check buttons (enable/disable channel)
    /// @return Signal for perfomed action
    channelChanged channelIsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing check buttons (enable/disable channel)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void onChannelChanged(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for comboboxes (control type)
    /// @return Signal for perfomed action
    selectChanged channelIsSelected() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing comboboxes (control type)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void onTypeSelected(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toggling buttons (turn on/turn off channel)
    /// @return Signal for perfomed action
    channelToggled channelIsToggled() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing toggle buttons (turn on/turn off channel)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void onToggled(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for spin buttons (based on timer)
    /// @return Signal for perfomed action
    channelSpinTimerChanged channelIsSpinTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing spin buttons (based on timer)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void onSpinTimerChanged(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toggle buttons (based on timer)
    /// @return Signal for perfomed action
    channelTimerToggled channelIsTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing toggle buttons (turn on/turn off timer)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void onToggleTimerChanged(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Connect meni-item
    void onConnectClicked();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Disconnect meni-item
    void onDisconnectClicked();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Quit meni-item
    void onQuitClicked();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Serial Settings meni-item
    void onSerialSettingsClicked();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing Log Settings meni-item
    void onLogSettingsClicked();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing About meni-item
    void onAboutClicked();

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Map channels (signals and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enable complete channel
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void enableChannel(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Disable complete channel
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void disableChannel(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup channel in toggle mode
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void toggleModeChannel(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Setup channel timer mode
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    void timerModeChannel(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    Glib::RefPtr<Gtk::Builder> m_ui;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Connect menu-item
    Glib::RefPtr<Gtk::MenuItem> m_connect;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Disconnect menu-item
    Glib::RefPtr<Gtk::MenuItem> m_disconnect;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Quit menu-item
    Glib::RefPtr<Gtk::MenuItem> m_quit;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Serial Port Settings menu-item
    Glib::RefPtr<Gtk::MenuItem> m_serialSettings;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Log Settings menu-item
    Glib::RefPtr<Gtk::MenuItem> m_logSettings;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application About menu-item
    Glib::RefPtr<Gtk::MenuItem> m_about;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Check buttons for enable/disable channels
    std::vector<Glib::RefPtr<Gtk::CheckButton>> m_enableChannels;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Comboboxes for selecting channel mode
    std::vector<Glib::RefPtr<Gtk::ComboBoxText>> m_selectControlChannels;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Toggle button for direct channel control
    std::vector<Glib::RefPtr<Gtk::ToggleButton>> m_toggleChannels;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Spin button for setup channel timer
    std::vector<Glib::RefPtr<Gtk::SpinButton>> m_spinTimerChannels;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Toggle button for starting channel timer
    std::vector<Glib::RefPtr<Gtk::ToggleButton>> m_toggleTimerChannels;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Visual status for channels
    std::vector<Glib::RefPtr<Gtk::ProgressBar>> m_stautsTimerChannels; 

    ////////////////////////////////////////////////////////////////////////
    /// @brief Adjustment setup for channel visual status
    Glib::RefPtr<Gtk::Adjustment> m_adjustment_digits;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for check buttons (enable/disable channel)
    channelChanged m_channelEnabled;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for comboboxes (toogle/timer type control)
    selectChanged m_channelControlType;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toogle buttons (turn on/turn off channel)
    channelToggled m_channelToggled;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for spin buttons (based on timer setup)
    channelSpinTimerChanged m_channelSpinTimerChanged;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toogle buttons (based on timer setup)
    channelTimerToggled m_channelTimerToggled;
};
