/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * io_config.c
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
#include "io_config_error.h"
#include "io_config.h"

////////////////////////////////////////////////////////////////////////////
/// @brief PWM slice number
static uint slice_num;

////////////////////////////////////////////////////////////////////////////
/// @brief Setting port pin configuration
/// @param pin is GPIO pin number
/// @param mode is GPIO pin direction (GPIO_IN | GPIO_OUT)
void microhil_gpio_mode(uint pin, uint16_t mode)
{
    gpio_init(pin);

    if (mode == 0 || mode == GPIO_IN)
    {
        gpio_set_dir(pin, GPIO_IN);
    }
    else
    {
        gpio_set_dir(pin, GPIO_OUT);
    }
}

////////////////////////////////////////////////////////////////////////////
/// @brief Drive GPIO pin
/// @param pin is GPIO number
/// @param value is GPIO value (true - set | false - clear)
void microhil_digital_write(uint pin, bool value)
{
    gpio_put(pin, value);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Get GPIO state
/// @param pin is GPIO pin number
/// @return state of GPIO pin (true | false)
bool microhil_digital_read(uint pin)
{
    return gpio_get(pin);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Delay in miliseconds
/// @param ms is number of miliseconds to sleep
void microhil_delay_ms(uint32_t ms)
{
    sleep_ms(ms);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Delay in microseconds
/// @param us is number of microseconds to sleep
void microhil_delay_us(uint64_t us)
{
    sleep_us(us);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Initialization of PWM channel
/// @param gpio pin number
/// @param channel channel
/// @return true for success else false
bool microhil_init_pwm(uint gpio, enum pwm_chan channel)
{
    bool status = false;

    ////////////////////////////////////////////////////////////////////////
    /// Set PWM pin configuration
    gpio_set_function(gpio, GPIO_FUNC_PWM);

    ////////////////////////////////////////////////////////////////////////
    /// Init PWM channel
    slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_set_wrap(slice_num, 500);
    pwm_set_chan_level(slice_num, channel, 1);
    pwm_set_clkdiv(slice_num, 50);
    pwm_set_enabled(slice_num, true);
    status = true;

    return status;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Write value to PWM channel
/// @param channel is PWM channel (PWM_CHAN_A | PWM_CHAN_B)
/// @param value is new value for selected output
void microhil_write_pwm(enum pwm_chan channel, uint16_t value)
{
    if (value < 0 || value > 100)
    {
        printf("%s %s\n", MICROHIL_IO_CONFIG_ERROR, MICROHIL_PWM_SET_ERROR);
    }
    else
    {
        pwm_set_chan_level(slice_num, channel, value);
    }
}
