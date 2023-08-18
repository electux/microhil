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

////////////////////////////////////////////////////////////////////////////
/// @brief Scoped enumerator for channel states
enum class ChannelState: bool
{
    OFF = false,
    ON  = true
};

////////////////////////////////////////////////////////////////////////////
/// @brief AbMicroHILModel class declaration and definition
class AbMicroHILModel
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief AbMicroHILModel destructor
    virtual ~AbMicroHILModel() = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Set channel #0 state (ON/OFF)
    /// @param id request channel by id
    /// @param state request for channel #0 (ON | OFF)
    virtual void setChannel(int id, ChannelState state) = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Get channel #0 state (ON/OFF)
    /// @param id request channel by id
    /// @return channel state in enumerator format (ON | OFF)
    virtual ChannelState getChannel(int id) const = 0;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Check is channel #0 ON (true) or OFF (false)
    /// @param id request channel by id
    /// @return boolean status true for open else false
    virtual bool isOnChannel(int id) const = 0;
};
