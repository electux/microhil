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
/// @brief Setting port pin configuration
/// @param pin is GPIO pin number
/// @param mode is GPIO pin direction (GPIO_IN | GPIO_OUT)
void microhil_gpio_mode(uint16_t pin, uint16_t mode);

////////////////////////////////////////////////////////////////////////////
/// @brief Drive GPIO pin
/// @param pin is GPIO number
/// @param value is GPIO value (true - set | false - clear)
void microhil_digital_write(uint16_t pin, bool value);

////////////////////////////////////////////////////////////////////////////
/// @brief Get GPIO state
/// @param pin is GPIO pin number
/// @return state of GPIO pin
uint8_t microhil_digital_read(uint16_t pin);

////////////////////////////////////////////////////////////////////////////
/// @brief Delay in miliseconds
/// @param ms is number of miliseconds to sleep
void microhil_delay_ms(uint32_t ms);

////////////////////////////////////////////////////////////////////////////
/// @brief Delay in microseconds
/// @param us is number of microseconds to sleep
void microhil_delay_us(uint32_t us);

////////////////////////////////////////////////////////////////////////////
/// @brief Initialization of PWM channel
/// @param gpio
/// @param channel 
/// @return true for success else false
bool microhil_init_pwm(uint gpio, enum pwm_chan channel);

////////////////////////////////////////////////////////////////////////////
/// @brief Write value to PWM channel
/// @param channel is PWM channel (PWM_CHAN_A | PWM_CHAN_B)
/// @param value is new value for selected output
void microhil_write_pwm(enum pwm_chan channel, uint8_t value);
