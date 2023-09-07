/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel.h
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
#pragma once

#include <stdio.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/pwm.h"
#include "ws2812.pio.h"

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_NUMBER_OF_CHANNELS 8

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNEL_1 21

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNEL_2 20

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNEL_3 19

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNEL_4 18

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNEL_5 17

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNEL_6 16

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNEL_7 15

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNEL_8 14

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_ALL_CHANNELS_OFF 0

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_ALL_CHANNELS_ON 1

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_CHANNELS_ERROR 127

////////////////////////////////////////////////////////////////////////////
/// @brief
extern unsigned char channels[MICROHIL_NUMBER_OF_CHANNELS];

////////////////////////////////////////////////////////////////////////////
/// @brief Global initialization of microHIL device
/// @return true for success else false
bool microhil_init();

////////////////////////////////////////////////////////////////////////////
/// @brief Initialization of PIO state machine
/// @return true for success else false
bool microhil_pio_init();

////////////////////////////////////////////////////////////////////////////
/// @brief Initialization of PWM channel
/// @return true for success else false
bool microhil_init_pwm();

////////////////////////////////////////////////////////////////////////////
/// @brief Initializatio of relay channels
/// @return true for success else false
bool microhil_init_relay();

////////////////////////////////////////////////////////////////////////////
/// @brief Set all channels to ON
void microhil_all_channels_on();

////////////////////////////////////////////////////////////////////////////
/// @brief Set all channels to OFF
void microhil_all_channels_off();

////////////////////////////////////////////////////////////////////////////
/// @brief Switch channel state
/// @param id of channel
void microhil_channel_switch(int id);

////////////////////////////////////////////////////////////////////////////
/// @brief Convert command id to GPIO number or global ON/OFF
/// @param id of command received from serial port
/// @return channel number | all on / all off | error
unsigned int id_to_gpio(int id);

////////////////////////////////////////////////////////////////////////////
/// @brief Write 32-bit RGB value to PIO state machine
/// @param pixel_rgb is 32-bit RGB value
void put_pixel(uint32_t pixel_rgb);

////////////////////////////////////////////////////////////////////////////
/// @brief Generate 32-bit RGB value
/// @param red color value
/// @param green color value
/// @param blue color value
/// @return 32-bit RGB value
uint32_t urgb_u32(uint8_t red, uint8_t green, uint8_t blue);

////////////////////////////////////////////////////////////////////////////
/// @brief Write value to PWM channel
/// @param value for PWM channel
void microhil_write_pwm(uint8_t value);
