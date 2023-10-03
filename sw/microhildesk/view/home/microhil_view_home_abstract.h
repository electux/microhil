/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home_abstract.h
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

#include <sigc++/sigc++.h>

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped class enumerator for View IDs
enum class ViewId : int
{
    /// @brief Connect view id
    MICROHIL_CONNECT = 0,
    /// @brief Disconnect view id
    MICROHIL_DISCONNECT = 1,
    /// @brief Quit view id
    MICROHIL_QUIT = 2,
    /// @brief Message view id
    MICROHIL_MESSAGE = 3,
    /// @brief Serial settings view id
    MICROHIL_SERIAL_SETTINGS = 4,
    /// @brief Log settings view id
    MICROHIL_LOG_SETTINGS = 5,
    /// @brief About view id
    MICROHIL_ABOUT = 6
};

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped class enumerator for channel IDs
enum class Channel : int
{
    /// @brief Channel 0 id
    MICROHIL_ID0 = 0,
    /// @brief Channel 1 id
    MICROHIL_ID1 = 1,
    /// @brief Channel 2 id
    MICROHIL_ID2 = 2,
    /// @brief Channel 3 id
    MICROHIL_ID3 = 3,
    /// @brief Channel 4 id
    MICROHIL_ID4 = 4,
    /// @brief Channel 5 id
    MICROHIL_ID5 = 5,
    /// @brief Channel 6 id
    MICROHIL_ID6 = 6,
    /// @brief Channel 7 id
    MICROHIL_ID7 = 7
};

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped class enumerator for channel control types
enum class channelControlType : int
{
    /// @brief Toogle button control type
    MICROHIL_TOGGLE_BUTTON = 0,
    /// @brief Timer button control type
    MICROHIL_TIMER_BUTTON = 1
};

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for menu itmes (trigger another view)
using SigActionViewTriggered = sigc::signal<void(ViewId)>;

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for check buttons (enable/disable channel)
using SigChannelChanged = sigc::signal<void(Channel, bool)>;

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for comboboxes (toogle/timer type control)
using SigSelectChanged = sigc::signal<void(Channel, int)>;

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for toogle buttons (turn on/turn off channel)
using SigChannelToggled = sigc::signal<void(Channel, bool)>;

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for spin buttons (based on timer setup)
using SigChannelSpinTimerChanged = sigc::signal<void(Channel, int)>;

////////////////////////////////////////////////////////////////////////
/// @brief Signal type for toogle buttons (based on timer setup)
using SigChannelTimerToggled = sigc::signal<void(Channel, bool)>;

////////////////////////////////////////////////////////////////////////////
/// @brief AbMHViewHome class declaration and definition
class AbMHViewHome
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMHViewHome destructor
    inline virtual ~AbMHViewHome() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for menu items (changed view)
    /// @return Signal for clicked menu item
    virtual SigActionViewTriggered viewChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for check buttons (enable/disable channel)
    /// @return Signal for clicked button
    virtual SigChannelChanged channelIsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing check buttons (enable/disable channel)
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    virtual void onChannelChanged(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for comboboxes (control type)
    /// @return Signal for changed channel state combobox
    virtual SigSelectChanged channelIsSelected() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing comboboxes (control type)
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    virtual void onTypeSelected(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toggling buttons (turn on/turn off channel)
    /// @return Signal for toggled button
    virtual SigChannelToggled channelIsToggled() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing toggle buttons (turn on/turn off channel)
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    virtual void onToggled(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for spin buttons (based on timer)
    /// @return Signal for changed spin button
    virtual SigChannelSpinTimerChanged channelIsSpinTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing spin buttons (based on timer)
    /// @param id repreesnts id for channel (Channel::MICROHIL_ID0 .. 7)
    virtual void onSpinTimerChanged(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toggle buttons (based on timer)
    /// @return Signal for toggled button
    virtual SigChannelTimerToggled channelIsTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing toggle buttons (turn on/turn off timer)
    /// @param id represents id for channel (Channel::MICROHIL_ID0 .. 7)
    virtual void onToggleTimerChanged(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets widgets after confirming changes for the serial port
    /// @param state true for confirmed changes, else false
    virtual void serialSettingsConfirm(bool state) = 0;
};
