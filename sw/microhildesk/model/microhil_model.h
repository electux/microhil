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

#include "microhil_imodel.h"
#include <vector>

////////////////////////////////////////////////////////////////////////////
/// @brief MHModel class is implementation of model mechanism
class MHModel : public IMHModel
{
public:
    ////////////////////////////////////////////////////////////////////////
    /// @brief MHModel constructor
    explicit MHModel();

    ////////////////////////////////////////////////////////////////////////
    /// @brief MHModel destructor
    inline ~MHModel() noexcept = default;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Sets channel #0 state (ON/OFF)
    /// @param id represents request channel by id
    /// @param state represents request for channel #0 (ON | OFF)
    void setChannel(const int id, const ChannelState state) final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Gets channel #0 state (ON/OFF)
    /// @param id represents request channel by id
    /// @return channel state in enumerator format (ON | OFF)
    ChannelState getChannel(const int id) const final;

    ////////////////////////////////////////////////////////////////////////
    /// @brief Checks is channel #0 ON (true) or OFF (false)
    /// @param id represents request channel by id
    /// @return status true for ON channel else false for OFF channel
    bool isOnChannel(const int id) const final;

private:
    ////////////////////////////////////////////////////////////////////////
    /// @brief Channel states
    std::vector<ChannelState> m_channels;
};
