/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel.c
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
#include <string.h>
#include "io_config.h"
#include "channel.h"

#define VERBOSE

////////////////////////////////////////////////////////////////////////////
/// @brief Marks private functions
#define MICROHIL_PRIVATE

////////////////////////////////////////////////////////////////////////////
/// @brief Total number of supported channels
#define MICROHIL_NUMBER_OF_CHANNELS 8

////////////////////////////////////////////////////////////////////////////
/// @brief microHIL channel switch ON request tail
#define MICROHIL_ON_CHANNEL "on#end"

////////////////////////////////////////////////////////////////////////////
/// @brief microHIL channel switch OFF request tail
#define MICROHIL_OFF_CHANNEL "off#end"

////////////////////////////////////////////////////////////////////////////
/// @brief Prefix verbose message
#define MICROHIL_VERBOSE "[microHIL] INFO"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for all channels switched to ON
#define MICROHIL_ALL_ON "all channels on"

////////////////////////////////////////////////////////////////////////////
/// @brief Info message for all channels switched to OFF
#define MICROHIL_ALL_OFF "all channels off"

////////////////////////////////////////////////////////////////////////////
/// @brief Buffer for storing channel states
static uint8_t channels[MICROHIL_NUMBER_OF_CHANNELS] = {0};

////////////////////////////////////////////////////////////////////////////
/// @brief Performs channel operation (single channel)
/// @param args represents arguments (channel number and state on/off)
MICROHIL_PRIVATE void microhil_channel(uint8_t *args);

////////////////////////////////////////////////////////////////////////////
/// @brief Performs operations over all channels
/// @param args represents argument (state on/off)
MICROHIL_PRIVATE void microhil_all_channels(uint8_t *args);

////////////////////////////////////////////////////////////////////////////
/// @brief Gets unique HW board id
MICROHIL_PRIVATE void microhil_board_id();

////////////////////////////////////////////////////////////////////////////
/// @brief Gets microHIL FW version
MICROHIL_PRIVATE void microhil_version();

////////////////////////////////////////////////////////////////////////////
/// @brief Request table (mapped requests and functions)
static microhil_req request_tbl[] = {
    {"mh#ch#1#on#end", microhil_channel},
    {"mh#ch#1#off#end", microhil_channel},
    {"mh#ch#2#on#end", microhil_channel},
    {"mh#ch#2#off#end", microhil_channel},
    {"mh#ch#3#on#end", microhil_channel},
    {"mh#ch#3#off#end", microhil_channel},
    {"mh#ch#4#on#end", microhil_channel},
    {"mh#ch#4#off#end", microhil_channel},
    {"mh#ch#5#on#end", microhil_channel},
    {"mh#ch#5#off#end", microhil_channel},
    {"mh#ch#6#on#end", microhil_channel},
    {"mh#ch#6#off#end", microhil_channel},
    {"mh#ch#7#on#end", microhil_channel},
    {"mh#ch#7#off#end", microhil_channel},
    {"mh#ch#8#on#end", microhil_channel},
    {"mh#ch#8#off#end", microhil_channel},
    {"mh#ch#all#on#end", microhil_all_channels},
    {"mh#ch#all#off#end", microhil_all_channels},
    {"mh#ch#board#id#end", microhil_board_id},
    {"mh#ch#version#end", microhil_version}
};

////////////////////////////////////////////////////////////////////////////
/// @brief Compare request with candidates from request table
/// @param req1 represents microHIL request
/// @param req2 represents microHIL request
/// @return compare result
MICROHIL_PRIVATE int comapre_request(const void *req1, const void *req2)
{
    const microhil_req *cmd1 = req1, *cmd2 = req2;

    return memcmp(cmd1->name, cmd2->name, 9);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Switches channels by command request
/// @param request represents command request
void microhil_channel_switch(uint8_t *request)
{    
    microhil_req key = {request, NULL};

    microhil_req *channel_target = bsearch(
        &key,
        request_tbl,
        sizeof(request_tbl) / sizeof(request_tbl[0]),
        sizeof(request_tbl[0]),
        comapre_request
    );

    channel_target->req_operation(request);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Converts channel number to GPIO number
/// @param channel_number represents channel number
/// @return GPIO pin number
MICROHIL_PRIVATE microhil_channel_gpio to_gpio(uint8_t channel_number)
{
    switch(channel_number)
    {
        case 1:
            return MICROHIL_CHANNEL_0;
        case 2:
            return MICROHIL_CHANNEL_1;
        case 3:
            return MICROHIL_CHANNEL_2;
        case 4:
            return MICROHIL_CHANNEL_3;
        case 5:
            return MICROHIL_CHANNEL_4;
        case 6:
            return MICROHIL_CHANNEL_5;
        case 7:
            return MICROHIL_CHANNEL_6;
        case 8:
            return MICROHIL_CHANNEL_7;
        }
}

////////////////////////////////////////////////////////////////////////////
/// @brief Performs channel operation (single channel)
/// @param args represents arguments (channel number and state on/off)
MICROHIL_PRIVATE void microhil_channel(uint8_t *args)
{
    uint8_t channel_number = args[6];
    size_t on_len = strlen(MICROHIL_ON_CHANNEL);
    size_t off_len = strlen(MICROHIL_OFF_CHANNEL);
    bool on = (memcmp(args + 8, MICROHIL_ON_CHANNEL, on_len) == 0);
    bool off = (memcmp(args + 8, MICROHIL_OFF_CHANNEL, off_len) == 0);

    if(on)
    {
        microhil_relay(to_gpio(channel_number), on);
#ifdef VERBOSE
        printf("%s channel %c on\n", MICROHIL_VERBOSE, channel_number);
#endif
    }

    if (off)
    {
        microhil_relay(to_gpio(channel_number), off);
#ifdef VERBOSE
        printf("%s channel %c off\n", MICROHIL_VERBOSE, channel_number);
#endif
    }
}

////////////////////////////////////////////////////////////////////////////
/// @brief Performs operations over all channels
/// @param args represents argument (state on/off)
MICROHIL_PRIVATE void microhil_all_channels(uint8_t *args)
{
    size_t on_len = strlen(MICROHIL_ON_CHANNEL);
    size_t off_len = strlen(MICROHIL_OFF_CHANNEL);
    bool on = (memcmp(args + 10, MICROHIL_ON_CHANNEL, on_len) == 0);
    bool off = (memcmp(args + 10, MICROHIL_OFF_CHANNEL, off_len) == 0);

    if (on)
    {
        ////////////////////////////////////////////////////////////////////
        /// Sets relay channels to ON
        microhil_relay_all(true);

        ////////////////////////////////////////////////////////////////////
        /// Store channel states
        memset(channels, 1, MICROHIL_NUMBER_OF_CHANNELS * sizeof(uint8_t));
#ifdef VERBOSE
        printf("%s %s\n", MICROHIL_VERBOSE, MICROHIL_ALL_ON);
#endif
    }

    if (off)
    {
        ////////////////////////////////////////////////////////////////////
        /// Sets relay channels to OFF
        microhil_relay_all(false);

        ////////////////////////////////////////////////////////////////////
        /// Stores channel states
        memset(channels, 0, MICROHIL_NUMBER_OF_CHANNELS * sizeof(uint8_t));
#ifdef VERBOSE
        printf("%s %s\n", MICROHIL_VERBOSE, MICROHIL_ALL_OFF);
#endif
    }

    ////////////////////////////////////////////////////////////////////////
    /// Led notification
    microhil_write_pixel(255, 255, 255);

    ////////////////////////////////////////////////////////////////////////
    /// Buzzer notification
    microhil_write_pwm(PWM_CHAN_A, 80);
    microhil_delay_ms(100);
    microhil_write_pwm(PWM_CHAN_A, 0);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Gets unique HW board id
MICROHIL_PRIVATE void microhil_board_id()
{
    printf("%s", MICROHIL_BOARD_ID);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Gets microHIL FW version
MICROHIL_PRIVATE void microhil_version()
{
    printf("%s", MICROHIL_VERSION);
}
