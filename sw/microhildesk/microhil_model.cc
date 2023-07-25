#include "microhil_model.h"
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
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "microhil_model.h"

void MicroHILModel::setChannel0(bool channelState)
{
    if(channel0 != channelState)
    {
        channel0 = channelState;
    }
}

bool MicroHILModel::getChannel0() const
{
    return channel0;
}

void MicroHILModel::setChannel1(bool channelState)
{
    if(channel1 != channelState)
    {
        channel1 = channelState;
    }
}

bool MicroHILModel::getChannel1() const
{
    return channel1;
}

void MicroHILModel::setChannel2(bool channelState)
{
    if(channel2 != channelState)
    {
        channel2 = channelState;
    }
}

bool MicroHILModel::getChannel2() const
{
    return channel2;
}

void MicroHILModel::setChannel3(bool channelState)
{
    if(channel3 != channelState)
    {
        channel3 = channelState;
    }
}

bool MicroHILModel::getChannel3() const
{
    return channel3;
}
