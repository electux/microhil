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

MicroHILModel::MicroHILModel()
{
}

void MicroHILModel::setChannel0(ChannelState state)
{
    if(m_channel0 != state)
    {
        m_channel0 = state;
    }
}

ChannelState MicroHILModel::getChannel0() const
{
    return m_channel0;
}

bool MicroHILModel::isOnChannel0() const
{
    return bool(m_channel0);
}

void MicroHILModel::setChannel1(ChannelState state)
{
    if(m_channel1 != state)
    {
        m_channel1 = state;
    }
}

ChannelState MicroHILModel::getChannel1() const
{
    return m_channel1;
}

bool MicroHILModel::isOnChannel1() const
{
    return bool(m_channel1);
}

void MicroHILModel::setChannel2(ChannelState state)
{
    if(m_channel2 != state)
    {
        m_channel2 = state;
    }
}

ChannelState MicroHILModel::getChannel2() const
{
    return m_channel2;
}

bool MicroHILModel::isOnChannel2() const
{
    return bool(m_channel2);
}

void MicroHILModel::setChannel3(ChannelState state)
{
    if(m_channel3 != state)
    {
        m_channel3 = state;
    }
}

ChannelState MicroHILModel::getChannel3() const
{
    return m_channel3;
}

bool MicroHILModel::isOnChannel3() const
{
    return bool(m_channel3);
}
