/* -*- Mode: CC; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_view_home_utils.cc
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
#include "microhil_view_home.h"

namespace
{
    ////////////////////////////////////////////////////////////////////////
    /// @brief invalid parameter for convert processes
    constexpr const int kInvalidConversionParameter = 127;
} // namespace

int MHViewHome::channelToInt(Channel id)
{
    switch (id)
    {
    case Channel::MICROHIL_ID0:
        return 0;
    case Channel::MICROHIL_ID1:
        return 1;
    case Channel::MICROHIL_ID2:
        return 2;
    case Channel::MICROHIL_ID3:
        return 3;
    case Channel::MICROHIL_ID4:
        return 4;
    case Channel::MICROHIL_ID5:
        return 5;
    case Channel::MICROHIL_ID6:
        return 6;
    case Channel::MICROHIL_ID7:
        return 7;
    }

    return kInvalidConversionParameter;
}

int MHViewHome::controlTypeToInt(channelControlType controlType)
{
    switch (controlType)
    {
    case channelControlType::MICROHIL_TOGGLE_BUTTON:
        return 0;
    case channelControlType::MICROHIL_TIMER_BUTTON:
        return 1;
    }

    return kInvalidConversionParameter;
}
