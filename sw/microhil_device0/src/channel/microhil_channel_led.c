/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_channel_led.c
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-device0 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-device0 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "microhil_channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param pixel_rgb
void put_pixel(uint32_t pixel_rgb)
{
    pio_sm_put_blocking(pio0, 0, pixel_rgb << 8u);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param red
/// @param green
/// @param blue
/// @return
uint32_t urgb_u32(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)(red) << 8) |
           ((uint32_t)(green) << 16) |
           (uint32_t)(blue);
}
