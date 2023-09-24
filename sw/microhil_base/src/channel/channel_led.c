/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_led.c
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
/// @brief Writes 32-bit RGB value to PIO state machine
/// @param red represents red color value
/// @param green represents green color value
/// @param blue represents blue color value
void microhil_write_pixel(uint8_t red, uint8_t green, uint8_t blue)
{
    uint pixel_rgb = ((uint)(red) << 8) |
                     ((uint)(green) << 16) |
                     ((uint)(blue));
    pio_sm_put_blocking(pio0, 0, pixel_rgb << 8u);
}
