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

#include <gtkmm/applicationwindow.h>
#include <gtkmm/builder.h>
#include <giomm/resource.h>
#include <gtkmm/menuitem.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/progressbar.h>
#include "../../utils/microhil_types.h"
#include "microhil_view_home_abstract.h"

////////////////////////////////////////////////////////////////////////////
/// @brief MHViewHome class is implementation of home view
class MHViewHome : public AbMHViewHome, public Gtk::ApplicationWindow
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHViewHome constructor
    /// @param object represents base object instance
    /// @param ui represents builder instance
    MHViewHome(BaseObjectType *object, MHRPtr<Gtk::Builder> const &ui);

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHViewHome destructor
    inline ~MHViewHome() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for menu items (changed view)
    /// @return Signal for clicked menu item
    SigActionViewTriggered viewChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for check buttons (enable/disable channel)
    /// @return Signal for clicked button
    SigChannelChanged channelIsChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing check buttons (enable/disable channel)
    /// @param id represents id for channel (Channel::ID0 .. Channel::ID7)
    void onChannelChanged(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for comboboxes (control type)
    /// @return Signal for changed channel state combobox
    SigSelectChanged channelIsSelected() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing comboboxes (control type)
    /// @param id represents id for channel (Channel::ID0 .. Channel::ID7)
    void onTypeSelected(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toggling buttons (turn on/turn off channel)
    /// @return Signal for toggled button
    SigChannelToggled channelIsToggled() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing toggle buttons (turn on/turn off channel)
    /// @param id represents id for channel (Channel::ID0 .. Channel::ID7)
    void onToggled(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for spin buttons (based on timer)
    /// @return Signal for changed spin button
    SigChannelSpinTimerChanged channelIsSpinTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing spin buttons (based on timer)
    /// @param id represents id for channel (Channel::ID0 .. Channel::ID7)
    void onSpinTimerChanged(Channel id) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toggle buttons (based on timer)
    /// @return Signal for toggled button
    SigChannelTimerToggled channelIsTimerChanged() final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing toggle buttons (turn on/turn off timer)
    /// @param id represents id for channel (Channel::ID0 .. Channel::ID7)
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

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets widgets after confirming changes for the serial port
    /// @param state true for confirmed changes, else false
    void serialSettingsConfirm(bool state) final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Maps channels (signals and slots)
    void mapping();

    ////////////////////////////////////////////////////////////////////////
    /// @brief Enables complete channel
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    void enableChannel(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Disables complete channel
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    void disableChannel(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets channel in toggle mode
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    void toggleModeChannel(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets channel timer mode
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    void timerModeChannel(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts channel id to integer value
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    /// @return integer value of channel id
    int channelToInt(Channel id);

    ////////////////////////////////////////////////////////////////////////
    /// @brief Converts channel control type to integer value
    /// @param controlType represents control type
    /// @return integer value of channel control type
    int controlTypeToInt(channelControlType controlType);

    ////////////////////////////////////////////////////////////////////////
    /// @brief UI builder instance
    MHRPtr<Gtk::Builder> m_ui{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Connect menu-item
    MHRPtr<Gtk::MenuItem> m_connect{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Disconnect menu-item
    MHRPtr<Gtk::MenuItem> m_disconnect{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Quit menu-item
    MHRPtr<Gtk::MenuItem> m_quit{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Serial Port Settings menu-item
    MHRPtr<Gtk::MenuItem> m_serialSettings{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application Log Settings menu-item
    MHRPtr<Gtk::MenuItem> m_logSettings{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Application About menu-item
    MHRPtr<Gtk::MenuItem> m_about{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Check buttons for enable/disable channels
    std::vector<MHRPtr<Gtk::CheckButton>> m_enableChannels{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Comboboxes for selecting channel mode
    std::vector<MHRPtr<Gtk::ComboBoxText>> m_selectControlChannels{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Toggle button for direct channel control
    std::vector<MHRPtr<Gtk::ToggleButton>> m_toggleChannels{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Spin button for setup channel timer
    std::vector<MHRPtr<Gtk::SpinButton>> m_spinTimerChannels{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Toggle button for starting channel timer
    std::vector<MHRPtr<Gtk::ToggleButton>> m_toggleTimerChannels{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Visual status for channels
    std::vector<MHRPtr<Gtk::ProgressBar>> m_stautsTimerChannels{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Adjustment setup for channel visual status
    MHRPtr<Gtk::Adjustment> m_adjustment_digits{nullptr};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for menu items (triggered another view)
    SigActionViewTriggered m_actionViewTriggered{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for check buttons (enable/disable channel)
    SigChannelChanged m_channelEnabled{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for comboboxes (toogle/timer type control)
    SigSelectChanged m_channelControlType{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toogle buttons (turn on/turn off channel)
    SigChannelToggled m_channelToggled{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for spin buttons (based on timer setup)
    SigChannelSpinTimerChanged m_channelSpinTimerChanged{};

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toogle buttons (based on timer setup)
    SigChannelTimerToggled m_channelTimerToggled{};
};
