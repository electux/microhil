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
/// @brief Scoped enumerator for channel IDs
enum class Channel: int
{
    ID0 = 0,
    ID1 = 1,
    ID2 = 2,
    ID3 = 3,
    ID4 = 4,
    ID5 = 5,
    ID6 = 6,
    ID7 = 7
}; 

////////////////////////////////////////////////////////////////////////////
/// @brief  Scoped enumerator for channel control types
enum class channelControlType
{
    TOGGLE_BUTTON = 0,
    TIMER_BUTTON = 1
};

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILViewHome class declaration and definition 
class AbMicroHILViewHome
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for check buttons (enable/disable channel)
    using channelChanged = sigc::signal<void(Channel, bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for comboboxes (toogle/timer type control)
    using selectChanged = sigc::signal<void(Channel, int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for toogle buttons (turn on/turn off channel)
    using channelToggled = sigc::signal<void(Channel, bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for spin buttons (based on timer setup)
    using channelSpinTimerChanged = sigc::signal<void(Channel, int)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal type for toogle buttons (based on timer setup)
    using channelTimerToggled = sigc::signal<void(Channel, bool)>;

    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILViewHome destructor
    virtual ~AbMicroHILViewHome() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for check buttons (enable/disable channel)
    /// @return Signal for perfomed action
    virtual channelChanged channelIsChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing check buttons (enable/disable channel)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    virtual void onChannelChanged(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for comboboxes (control type)
    /// @return Signal for perfomed action
    virtual selectChanged channelIsSelected() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing comboboxes (control type)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    virtual void onTypeSelected(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toggling buttons (turn on/turn off channel)
    /// @return Signal for perfomed action
    virtual channelToggled channelIsToggled() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing toggle buttons (turn on/turn off channel)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    virtual void onToggled(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for spin buttons (based on timer)
    /// @return Signal for perfomed action
    virtual channelSpinTimerChanged channelIsSpinTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing spin buttons (based on timer)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    virtual void onSpinTimerChanged(Channel id) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Signal for toggle buttons (based on timer)
    /// @return Signal for perfomed action
    virtual channelTimerToggled channelIsTimerChanged() = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Slot for processing toggle buttons (turn on/turn off timer)
    /// @param id for channel (Channel::ID0 .. Channel::ID7)
    virtual void onToggleTimerChanged(Channel id) = 0;
};
