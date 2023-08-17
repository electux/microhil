/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_model.h
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

#include "microhil_model_abstract.h"

class MicroHILModel: public AbMicroHILModel
{
public:
    ////////////////////////////////////////////////////////////////////////
    // MicroHILModel constructor
    MicroHILModel();

    ////////////////////////////////////////////////////////////////////////
    // MicroHILModel destructor
    ~MicroHILModel() = default;

    ////////////////////////////////////////////////////////////////////////
    // Set channel 0 state (ON/OFF)
    void setChannel0(ChannelState state) final;

    ////////////////////////////////////////////////////////////////////////
    // Get channel 0 state (ON/OFF)
    ChannelState getChannel0() const final;

    ////////////////////////////////////////////////////////////////////////
    // Check is channel 0 ON (true) or OFF (false)
    bool isOnChannel0() const final;

    ////////////////////////////////////////////////////////////////////////
    // Set channel 1 state (ON/OFF)
    void setChannel1(ChannelState state) final;

    ////////////////////////////////////////////////////////////////////////
    // Get channel 1 state (ON/OFF)
    ChannelState getChannel1() const final;

    ////////////////////////////////////////////////////////////////////////
    // Check is channel 1 ON (true) or OFF (false)
    bool isOnChannel1() const final;

    ////////////////////////////////////////////////////////////////////////
    // Set channel 2 state (ON/OFF)
    void setChannel2(ChannelState state) final;

    ////////////////////////////////////////////////////////////////////////
    // Get channel 2 state (ON/OFF)
    ChannelState getChannel2() const final;

    ////////////////////////////////////////////////////////////////////////
    // Check is channel 2 ON (true) or OFF (false)
    bool isOnChannel2() const final;

    ////////////////////////////////////////////////////////////////////////
    // Set channel 3 state (ON/OFF)
    void setChannel3(ChannelState state) final;

    ////////////////////////////////////////////////////////////////////////
    // Get channel 3 state (ON/OFF)
    ChannelState getChannel3() const final;

    ////////////////////////////////////////////////////////////////////////
    // Check is channel 3 ON (true) or OFF (false)
    bool isOnChannel3() const final;

private:
    ////////////////////////////////////////////////////////////////////////
    // Channel states
    ChannelState m_channel0 {ChannelState::OFF};
    ChannelState m_channel1 {ChannelState::OFF};
    ChannelState m_channel2 {ChannelState::OFF};
    ChannelState m_channel3 {ChannelState::OFF};
};
