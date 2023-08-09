/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_model_abstract.h
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

enum class ChannelState: bool
{
    OFF = false,
    ON  = true
};

class AbMicroHILModel
{
public:
    ////////////////////////////////////////////////////////////////////////
    // AbMicroHILModel destructor
    virtual ~AbMicroHILModel() = default;

    ////////////////////////////////////////////////////////////////////////
    // Set channel 0 state (ON/OFF)
    virtual void setChannel0(ChannelState state) = 0;

    ////////////////////////////////////////////////////////////////////////
    // Get channel 0 state (ON/OFF)
    virtual ChannelState getChannel0() const = 0;

    ////////////////////////////////////////////////////////////////////////
    // Check is channel 0 ON (true) or OFF (false)
    virtual bool isOnChannel0() const = 0;

    ////////////////////////////////////////////////////////////////////////
    // Set channel 1 state (ON/OFF)
    virtual void setChannel1(ChannelState state) = 0;

    ////////////////////////////////////////////////////////////////////////
    // Get channel 1 state (ON/OFF)
    virtual ChannelState getChannel1() const = 0;

    ////////////////////////////////////////////////////////////////////////
    // Check is channel 1 ON (true) or OFF (false)
    virtual bool isOnChannel1() const = 0;

    ////////////////////////////////////////////////////////////////////////
    // Set channel 2 state (ON/OFF)
    virtual void setChannel2(ChannelState state) = 0;

    ////////////////////////////////////////////////////////////////////////
    // Get channel 2 state (ON/OFF)
    virtual ChannelState getChannel2() const = 0;

    ////////////////////////////////////////////////////////////////////////
    // Check is channel 2 ON (true) or OFF (false)
    virtual bool isOnChannel2() const = 0;

    ////////////////////////////////////////////////////////////////////////
    // Set channel 3 state (ON/OFF)
    virtual void setChannel3(ChannelState state) = 0;

    ////////////////////////////////////////////////////////////////////////
    // Get channel 3 state (ON/OFF)
    virtual ChannelState getChannel3() const = 0;

    ////////////////////////////////////////////////////////////////////////
    // Check is channel 3 ON (true) or OFF (false)
    virtual bool isOnChannel3() const = 0;
};
