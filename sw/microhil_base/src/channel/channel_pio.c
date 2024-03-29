/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_pio.c
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief WS2812 DIN pin mapped to GPIO pin
const uint microhil_ws2812_din = 13;

////////////////////////////////////////////////////////////////////////////
/// @brief Performs initialization for PIO state machine
/// @return true for success else false
bool microhil_pio_init()
{
    bool status = false;

    ////////////////////////////////////////////////////////////////////////
    /// Add PIO program
    ws2812_init init =
    {
        .pio = pio0,
        .sm = 0,
        .offset = pio_add_program(pio0, &ws2812_program),
        .pin = microhil_ws2812_din,
        .freq = 800000,
        .rgbw = true
    };

    if (init.offset == 0)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to load PIO program
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Performs WS2812 program initialization
    ws2812_program_init(&init);
    status = true;

    return status;
}
