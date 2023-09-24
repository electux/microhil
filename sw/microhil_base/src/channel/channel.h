/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel.h
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

#include <stdlib.h>
#include "pico/stdlib.h"
#include "ws2812.pio.h"

////////////////////////////////////////////////////////////////////////////
/// @brief microHIL version
#define MICROHIL_VERSION "microHIL v1.0.0"

////////////////////////////////////////////////////////////////////////////
/// @brief microHIL board id
#define MICROHIL_BOARD_ID "mh:333:2023:0"

////////////////////////////////////////////////////////////////////////////
/// @brief Command request length
#define MICROHIL_REQ_LEN 32

////////////////////////////////////////////////////////////////////////////
/// @brief Flag for received new request from the serial port
extern bool new_request;

////////////////////////////////////////////////////////////////////////////
/// @brief Flog for receiving in progress
extern bool receive_in_progress;

////////////////////////////////////////////////////////////////////////////
/// @brief GPIO ports and numbers for channels
typedef enum _microhil_channel_gpio
{
    MICROHIL_CHANNEL_0 = 21,
    MICROHIL_CHANNEL_1 = 20,
    MICROHIL_CHANNEL_2 = 19,
    MICROHIL_CHANNEL_3 = 18,
    MICROHIL_CHANNEL_4 = 17,
    MICROHIL_CHANNEL_5 = 16,
    MICROHIL_CHANNEL_6 = 15,
    MICROHIL_CHANNEL_7 = 14
} microhil_channel_gpio;

////////////////////////////////////////////////////////////////////////////
/// @brief Structure for mapping name and requst operation
typedef struct _microhil_req
{
    uint8_t *name;
    void (*req_operation)(uint8_t *args);
} microhil_req;

////////////////////////////////////////////////////////////////////////////
/// @brief Global device initialization
/// @return true for success else false
bool microhil_init();

////////////////////////////////////////////////////////////////////////////
/// @brief Performs initialization for relay channels
/// @return true for success else false
bool microhil_init_relay();

////////////////////////////////////////////////////////////////////////////
/// @brief Turns relay to ON/OFF
/// @param channel represents channel number (0 .. 7)
/// @param value represents channel value (true - ON | false - OFF)
void microhil_relay(microhil_channel_gpio channel, bool value);

////////////////////////////////////////////////////////////////////////////
/// @brief Turns all relays to ON/OFF
void microhil_relay_all(bool value);

////////////////////////////////////////////////////////////////////////////
/// @brief Performs initialization for PIO state machine
/// @return true for success else false
bool microhil_pio_init();

////////////////////////////////////////////////////////////////////////////
/// @brief Performs initialization for buzzer channel
/// @return true for success else false
bool microhil_init_buzzer();

////////////////////////////////////////////////////////////////////////////
/// @brief Turns buzzer state on/off
/// @param value represents value for buzzer (true - on | false - off)
void microhil_write_buzzer(bool value);

////////////////////////////////////////////////////////////////////////////
/// @brief Writes 32-bit RGB value to PIO state machine
/// @param red represents red color value
/// @param green represents green color value
/// @param blue represents blue color value
void microhil_write_pixel(uint8_t red, uint8_t green, uint8_t blue);

////////////////////////////////////////////////////////////////////////////
/// @brief Fetches microHIL command requests from the serial port
/// @param request storage for received request from the serial port
void microhil_fetch_request(uint8_t *request);

////////////////////////////////////////////////////////////////////////////
/// @brief Switches channels by command request
/// @param request represents command request
void microhil_channel_switch(uint8_t *request);
