/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * io_config.h
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
#pragma once

#include "stdio.h"
#include "pico/stdlib.h"
#include "hardware/pwm.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Sets port pin configuration
/// @param pin represents GPIO pin number
/// @param mode represents GPIO pin direction (GPIO_IN | GPIO_OUT)
void microhil_gpio_mode(uint pin, uint16_t mode);

////////////////////////////////////////////////////////////////////////////
/// @brief Drives GPIO pin
/// @param pin represents GPIO number
/// @param value represents GPIO value (true - set | false - clear)
void microhil_digital_write(uint pin, bool value);

////////////////////////////////////////////////////////////////////////////
/// @brief Gets GPIO state
/// @param pin represents GPIO pin number
/// @return state of GPIO pin
bool microhil_digital_read(uint pin);

////////////////////////////////////////////////////////////////////////////
/// @brief Sets delay in miliseconds
/// @param ms represents number of miliseconds to sleep
void microhil_delay_ms(uint32_t ms);

////////////////////////////////////////////////////////////////////////////
/// @brief Sets delay in microseconds
/// @param us represents number of microseconds to sleep
void microhil_delay_us(uint64_t us);

////////////////////////////////////////////////////////////////////////////
/// @brief Initialization of PWM channel
/// @param gpio represents GPIO pin
/// @param channel represents channel number
/// @return true for success else false
bool microhil_init_pwm(uint gpio, enum pwm_chan channel);

////////////////////////////////////////////////////////////////////////////
/// @brief Writes value to PWM channel
/// @param channel represents PWM channel (PWM_CHAN_A | PWM_CHAN_B)
/// @param value represents new value for selected output
void microhil_write_pwm(enum pwm_chan channel, uint16_t value);
