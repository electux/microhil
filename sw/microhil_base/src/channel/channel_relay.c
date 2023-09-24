/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_relay.c
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
#include "io_config.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Performs initialization for relay channels
/// @return true for success else false
bool microhil_init_relay()
{
    bool status = false;

    ////////////////////////////////////////////////////////////////////////
    /// Initializes all control relay channels as output
    microhil_gpio_mode(MICROHIL_CHANNEL_0, GPIO_OUT);
    microhil_gpio_mode(MICROHIL_CHANNEL_1, GPIO_OUT);
    microhil_gpio_mode(MICROHIL_CHANNEL_2, GPIO_OUT);
    microhil_gpio_mode(MICROHIL_CHANNEL_3, GPIO_OUT);
    microhil_gpio_mode(MICROHIL_CHANNEL_4, GPIO_OUT);
    microhil_gpio_mode(MICROHIL_CHANNEL_5, GPIO_OUT);
    microhil_gpio_mode(MICROHIL_CHANNEL_6, GPIO_OUT);
    microhil_gpio_mode(MICROHIL_CHANNEL_7, GPIO_OUT);

    ////////////////////////////////////////////////////////////////////////
    /// Initializes all control relay channels as closed
    microhil_digital_write(MICROHIL_CHANNEL_0, false);
    microhil_digital_write(MICROHIL_CHANNEL_1, false);
    microhil_digital_write(MICROHIL_CHANNEL_2, false);
    microhil_digital_write(MICROHIL_CHANNEL_3, false);
    microhil_digital_write(MICROHIL_CHANNEL_4, false);
    microhil_digital_write(MICROHIL_CHANNEL_5, false);
    microhil_digital_write(MICROHIL_CHANNEL_6, false);
    microhil_digital_write(MICROHIL_CHANNEL_7, false);

    ////////////////////////////////////////////////////////////////////////
    /// Relay port pins configuration done
    status = true;

    return status;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Turns relay to ON/OFF
/// @param channel represents channel number (0 .. 7)
/// @param value represents channel value (true - ON | false - OFF)
void microhil_relay(microhil_channel_gpio channel, bool value)
{
    microhil_digital_write(channel, value);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Turns all relays to ON/OFF
void microhil_relay_all(bool value)
{
    microhil_digital_write(MICROHIL_CHANNEL_0, value);
    microhil_digital_write(MICROHIL_CHANNEL_1, value);
    microhil_digital_write(MICROHIL_CHANNEL_2, value);
    microhil_digital_write(MICROHIL_CHANNEL_3, value);
    microhil_digital_write(MICROHIL_CHANNEL_4, value);
    microhil_digital_write(MICROHIL_CHANNEL_5, value);
    microhil_digital_write(MICROHIL_CHANNEL_6, value);
    microhil_digital_write(MICROHIL_CHANNEL_7, value);
}
