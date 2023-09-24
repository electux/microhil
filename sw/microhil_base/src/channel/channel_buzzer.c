/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_buzzer.c
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
#include "io_config.h"
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief GPIO port pin number for buzzer
const uint microhil_buzzer = 6;

////////////////////////////////////////////////////////////////////////////
/// @brief Performs initialization for buzzer channel
/// @return true for success else false
bool microhil_init_buzzer()
{
    ////////////////////////////////////////////////////////////////////////
    /// Performs initialization for buzzer channel to be out
    microhil_gpio_mode(microhil_buzzer, GPIO_OUT);

    ////////////////////////////////////////////////////////////////////////
    /// Performs initialization for buzzer channel to PWM 0
    return microhil_init_pwm(microhil_buzzer, PWM_CHAN_A);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Turns buzzer on/off
/// @param value represents value for buzzer (true - on | false - off)
void microhil_write_buzzer(bool value)
{
    microhil_digital_write(microhil_buzzer, value);
}
