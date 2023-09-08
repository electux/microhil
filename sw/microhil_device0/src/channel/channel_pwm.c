/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_pwm.c
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
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#include "channel_info.h"
#include "channel_error.h"
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Initialization of PWM channel
/// @return true for success else false
bool microhil_init_pwm()
{
    bool status = false;

    ////////////////////////////////////////////////////////////////////////
    /// Set PWM pin for buzzer
    gpio_set_function(6, GPIO_FUNC_PWM);

    ////////////////////////////////////////////////////////////////////////
    /// Init PWM channel A
    slice_num = pwm_gpio_to_slice_num(6);
    pwm_set_wrap(slice_num, 500);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    pwm_set_clkdiv(slice_num, 50);
    pwm_set_enabled(slice_num, true);

    status = true;

    printf("%s %s\n", MICROHIL_CHANNEL_INFO, MICROHIL_PWM_INIT_OK);

    return status;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Write value to PWM channel
/// @param value for PWM channel
void microhil_write_pwm(uint8_t value)
{
    if (value < 0 || value > 100)
    {
        printf("%s %s\n", MICROHIL_CHANNEL_ERROR, MICROHIL_PWM_WRITE_FAILED);
    }
    else
    {
        pwm_set_chan_level(slice_num, PWM_CHAN_A, value);
    }
}
