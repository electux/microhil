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
#include "ws2812.pio.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Return value for success state
#define MICROHIL_SUCCESS 0

////////////////////////////////////////////////////////////////////////////
/// @brief Return value for failed state
#define MICROHIL_FAILED 1

////////////////////////////////////////////////////////////////////////////
/// @brief Total number of supported channels
#define MICROHIL_NUMBER_OF_CHANNELS 8

////////////////////////////////////////////////////////////////////////////
/// @brief GPIO ports and numbers for channels
typedef enum _channel_gpio_num
{
    MICROHIL_ALL_CHANNELS_ON = 300,
    MICROHIL_ALL_CHANNELS_OFF = 200,
    MICROHIL_CHANNELS_ERROR = 127,
    MICROHIL_CHANNEL_0 = 21,
    MICROHIL_CHANNEL_1 = 20,
    MICROHIL_CHANNEL_2 = 19,
    MICROHIL_CHANNEL_3 = 18,
    MICROHIL_CHANNEL_4 = 17,
    MICROHIL_CHANNEL_5 = 16,
    MICROHIL_CHANNEL_6 = 15,
    MICROHIL_CHANNEL_7 = 14
} channel_gpio_num;

////////////////////////////////////////////////////////////////////////////
/// @brief GPIO port pin number for buzzer
#define MICROHIL_BUZZER 6

////////////////////////////////////////////////////////////////////////////
/// @brief Command message length
#define MICROHIL_CMD_LEN 13

////////////////////////////////////////////////////////////////////////////
/// @brief Command message prefix
#define MICROHIL_CMD_PREFIX "mh#ch#"

////////////////////////////////////////////////////////////////////////////
/// @brief Prpperty channel ON length
#define MICROHIL_PROP_ON_RESERVE 4

////////////////////////////////////////////////////////////////////////////
/// @brief Prpperty channel OFF length
#define MICROHIL_PROP_OFF_RESERVE 5

////////////////////////////////////////////////////////////////////////////
/// @brief Command message propery all ON
#define MICROHIL_CMD_PROP_ALL_ON "all#on"

////////////////////////////////////////////////////////////////////////////
/// @brief Command message propery all OFF
#define MICROHIL_CMD_PROP_ALL_OFF "all#off"

////////////////////////////////////////////////////////////////////////////
/// @brief Global initialization of microHIL device
/// @return true for success else false
bool microhil_init();

////////////////////////////////////////////////////////////////////////////
/// @brief Initialization of PIO state machine
/// @return true for success else false
bool microhil_pio_init();

////////////////////////////////////////////////////////////////////////////
/// @brief Initializatio of relay channels
/// @return true for success else false
bool microhil_init_relay();

////////////////////////////////////////////////////////////////////////////
/// @brief Initializatio of buzzer channel
/// @return true for success else false
bool microhil_init_buzzer();

////////////////////////////////////////////////////////////////////////////
/// @brief Set all channels to ON
void microhil_all_channels_on();

////////////////////////////////////////////////////////////////////////////
/// @brief Set all channels to OFF
void microhil_all_channels_off();

////////////////////////////////////////////////////////////////////////////
/// @brief Switch channel state
/// @param id is GPIO port number
void microhil_channel_switch(channel_gpio_num id);

////////////////////////////////////////////////////////////////////////////
/// @brief Write 32-bit RGB value to PIO state machine
/// @param pixel_rgb is 32-bit RGB value
void microhil_write_pixel(uint32_t pixel_rgb);

////////////////////////////////////////////////////////////////////////////
/// @brief Generate 32-bit RGB value
/// @param red color value
/// @param green color value
/// @param blue color value
/// @return 32-bit RGB value
uint32_t urgb_u32(uint8_t red, uint8_t green, uint8_t blue);

////////////////////////////////////////////////////////////////////////////
/// @brief Fetch microHIL command messages from the serial port
/// @param buffer storage for received message from the serial port
/// @return number of received bytes from the serial port
uint16_t microhil_fetch_command(uint8_t *buffer);

////////////////////////////////////////////////////////////////////////////
/// @brief Extract command property
/// @param cmd is whole command messsage for processing
/// @return command property
unsigned char *microhil_extract_command_property(unsigned char *cmd);

////////////////////////////////////////////////////////////////////////////
/// @brief Process microHIL command messages from uart
/// @param cmd is whole command for processing
/// @return GPIO port number
channel_gpio_num microhil_process_command(unsigned char *cmd);

////////////////////////////////////////////////////////////////////////////
/// @brief Convert index to GPIO port number
/// @param id is index
/// @return GPIO port number
channel_gpio_num index_to_gpio(int id);
