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

#include <vector>
#include "microhil_model_abstract.h"

using namespace::std;

////////////////////////////////////////////////////////////////////////////
/// @brief MicroHILModel class declaration and definition 
class MicroHILModel: public AbMicroHILModel
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILModel constructor
    MicroHILModel();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MicroHILModel destructor
    ~MicroHILModel() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set channel #0 state (ON/OFF)
    /// @param id request channel by id
    /// @param state request for channel #0 (ON | OFF)
    void setChannel(int id, ChannelState state) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Get channel #0 state (ON/OFF)
    /// @param id request channel by id
    /// @return channel state in enumerator format (ON | OFF)
    ChannelState getChannel(int id) const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Check is channel #0 ON (true) or OFF (false)
    /// @param id request channel by id
    /// @return boolean status true for open else false
    bool isOnChannel(int id) const final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Channel states
    std::vector<ChannelState> m_channels;
};
