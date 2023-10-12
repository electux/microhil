/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_model.cc
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
#include "microhil_model.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// Number of controllable channels
    constexpr const int kNumberOfChannels{8};
} // namespace

MHModel::MHModel()
{
    ////////////////////////////////////////////////////////////////////////
    /// Sets all channels in model to OFF by default
    for (int i = 0; i < kNumberOfChannels; i++)
    {
        m_channels.push_back(ChannelState::MICROHIL_OFF);
    }
}

void MHModel::setChannel(const int id, const ChannelState state)
{
    ////////////////////////////////////////////////////////////////////////
    /// Sets channel state
    m_channels[id] = state;
}

ChannelState MHModel::getChannel(const int id) const
{
    ////////////////////////////////////////////////////////////////////////
    /// Gets channel state
    return m_channels[id];
}

bool MHModel::isOnChannel(const int id) const
{
    ////////////////////////////////////////////////////////////////////////
    /// Checks is channel active
    return m_channels[id] == ChannelState::MICROHIL_ON;
}
