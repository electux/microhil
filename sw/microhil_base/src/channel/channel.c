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
#include "channel_info.h"
#include "channel_error.h"
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Total number of supported channels
#define MICROHIL_NUMBER_OF_CHANNELS 8

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_ON_CHANNEL "on#end"

////////////////////////////////////////////////////////////////////////////
/// @brief
#define MICROHIL_OFF_CHANNEL "off#end"

////////////////////////////////////////////////////////////////////////////
/// @brief Container for storing channels states
static uint8_t channels[MICROHIL_NUMBER_OF_CHANNELS] = {0};

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param args
void microhil_channel(uint8_t *args);

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param args
void microhil_all_channels(uint8_t *args);

////////////////////////////////////////////////////////////////////////////
/// @brief
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
};

////////////////////////////////////////////////////////////////////////////
/// @brief Compare request with candidates from request table
/// @param c1 
/// @param c2 
/// @return 
static int comapre_request(const void *c1, const void *c2)
{
    const microhil_req *cmd1 = c1, *cmd2 = c2;

    return memcmp(cmd1->name, cmd2->name, 9);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Switches channel by command request
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
/// @brief Convert channel number to GPIO number
/// @param channel_number represents channel number
/// @return GPIO pin number
microhil_channel_gpio to_gpio(uint8_t channel_number)
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

void microhil_channel(uint8_t *args)
{
    uint8_t channel_number = args[6];
    size_t on_len = strlen(MICROHIL_ON_CHANNEL);
    size_t off_len = strlen(MICROHIL_OFF_CHANNEL);
    bool on = (memcmp(args + 8, MICROHIL_ON_CHANNEL, on_len) == 0);
    bool off = (memcmp(args + 8, MICROHIL_OFF_CHANNEL, off_len) == 0);

    if(on)
    {
        microhil_relay(to_gpio(channel_number), on);
        printf("%s channel %c on\n", MICROHIL_CHANNEL_INFO, channel_number);
    }

    if (off)
    {
        microhil_relay(to_gpio(channel_number), off);
        printf("%s channel %c off\n", MICROHIL_CHANNEL_INFO, channel_number);
    }
}

void microhil_all_channels(uint8_t *args)
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
        printf("%s %s\n", MICROHIL_CHANNEL_INFO, MICROHIL_ALL_ON);
    }

    if (off)
    {
        ////////////////////////////////////////////////////////////////////
        /// Sets relay channels to OFF
        microhil_relay_all(false);

        ////////////////////////////////////////////////////////////////////
        /// Store channel states
        memset(channels, 0, MICROHIL_NUMBER_OF_CHANNELS * sizeof(uint8_t));
        printf("%s %s\n", MICROHIL_CHANNEL_INFO, MICROHIL_ALL_OFF);
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
