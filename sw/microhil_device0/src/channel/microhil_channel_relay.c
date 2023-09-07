/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_channel_relay.c
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
/// @return true for success else false
bool microhil_init_relay()
{
    bool status = false;

    ////////////////////////////////////////////////////////////////////////
    /// Initialize channels
    gpio_init(MICROHIL_CHANNEL_1);
    gpio_init(MICROHIL_CHANNEL_2);
    gpio_init(MICROHIL_CHANNEL_3);
    gpio_init(MICROHIL_CHANNEL_4);
    gpio_init(MICROHIL_CHANNEL_5);
    gpio_init(MICROHIL_CHANNEL_6);
    gpio_init(MICROHIL_CHANNEL_7);
    gpio_init(MICROHIL_CHANNEL_8);

    ////////////////////////////////////////////////////////////////////////
    /// Set channels as outputs
    gpio_set_dir(MICROHIL_CHANNEL_1, GPIO_OUT);
    gpio_set_dir(MICROHIL_CHANNEL_2, GPIO_OUT);
    gpio_set_dir(MICROHIL_CHANNEL_3, GPIO_OUT);
    gpio_set_dir(MICROHIL_CHANNEL_4, GPIO_OUT);
    gpio_set_dir(MICROHIL_CHANNEL_5, GPIO_OUT);
    gpio_set_dir(MICROHIL_CHANNEL_6, GPIO_OUT);
    gpio_set_dir(MICROHIL_CHANNEL_7, GPIO_OUT);
    gpio_set_dir(MICROHIL_CHANNEL_8, GPIO_OUT);

    ////////////////////////////////////////////////////////////////////////
    /// Relay port pins configuration done
    status = true;

    return status;
}
