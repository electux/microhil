/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel.c
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
/// @brief Set all channels to ON
void microhil_all_channels_on()
{
    ////////////////////////////////////////////////////////////////////////
    /// Set relay channels to ON
    gpio_put(MICROHIL_CHANNEL_8, true);
    gpio_put(MICROHIL_CHANNEL_7, true);
    gpio_put(MICROHIL_CHANNEL_6, true);
    gpio_put(MICROHIL_CHANNEL_5, true);
    gpio_put(MICROHIL_CHANNEL_4, true);
    gpio_put(MICROHIL_CHANNEL_3, true);
    gpio_put(MICROHIL_CHANNEL_2, true);
    gpio_put(MICROHIL_CHANNEL_1, true);

    for(int i = 0; i < MICROHIL_NUMBER_OF_CHANNELS; i++)
    {
        channels[i] = 0x0;
    }

    printf("%s %s\n", MICROHIL_INFO, MICROHIL_ALL_ON);

    ////////////////////////////////////////////////////////////////////////
    /// Led notification
    put_pixel(urgb_u32(255, 255, 255));

    ////////////////////////////////////////////////////////////////////////
    /// Buzzer notification
    microhil_write_pwm(80);
    microhil_delay_ms(100);
    microhil_write_pwm(0);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Set all channels to OFF
void microhil_all_channels_off()
{
    ////////////////////////////////////////////////////////////////////////
    /// Set relay channels to OFF
    gpio_put(MICROHIL_CHANNEL_8, false);
    gpio_put(MICROHIL_CHANNEL_7, false);
    gpio_put(MICROHIL_CHANNEL_6, false);
    gpio_put(MICROHIL_CHANNEL_5, false);
    gpio_put(MICROHIL_CHANNEL_4, false);
    gpio_put(MICROHIL_CHANNEL_3, false);
    gpio_put(MICROHIL_CHANNEL_2, false);
    gpio_put(MICROHIL_CHANNEL_1, false);

    for(int i = 0; i < MICROHIL_NUMBER_OF_CHANNELS; i++)
    {
        channels[i] = 0x1;
    }

    printf("%s %s\n", MICROHIL_INFO, MICROHIL_ALL_OFF);

    ////////////////////////////////////////////////////////////////////////
    /// Led notification
    put_pixel(urgb_u32(0, 0, 0));

    ////////////////////////////////////////////////////////////////////////
    /// Buzzer notification
    microhil_write_pwm(80);
    microhil_delay_ms(100);
    microhil_write_pwm(0);
}

////////////////////////////////////////////////////////////////////////////
/// @brief Switch channel state
/// @param id of channel
void microhil_channel_switch(int id)
{
    unsigned int gpio = id_to_gpio(id);

    switch(gpio)
    {
        case MICROHIL_ALL_CHANNELS_OFF:
            microhil_all_channels_off();
            break;
        case MICROHIL_ALL_CHANNELS_ON:
            microhil_all_channels_on();
            break;
        case MICROHIL_CHANNELS_ERROR:
            printf("%s %s\n", MICROHIL_ERROR, MICROHIL_NO_SUPPORT);
            break;
        default:
            gpio_put(gpio, channels[id - 1]);

            if(channels[id - 1] == 1)
            {
                printf("%s channel %d on\n", MICROHIL_INFO, id - 1);
            }
            else if(channels[id - 1] == 0)
            {
                printf("%s channel %d off\n", MICROHIL_INFO, id - 1);
            }

            channels[id - 1] = !channels[id - 1];

            ////////////////////////////////////////////////////////////////
            /// Led notification
            put_pixel(urgb_u32(255, 0, 0));

            ////////////////////////////////////////////////////////////////
            /// Buzzer notification
            microhil_write_pwm(80);
            microhil_delay_ms(100);
            microhil_write_pwm(0);
            break;
    }
}

////////////////////////////////////////////////////////////////////////////
/// @brief Convert command id to GPIO number or global ON/OFF
/// @param id of command received from serial port
/// @return channel number | all on / all off | error
unsigned int id_to_gpio(int id)
{
    switch(id)
    {
        case 1: return MICROHIL_CHANNEL_1;
        case 2: return MICROHIL_CHANNEL_2;
        case 3: return MICROHIL_CHANNEL_3;
        case 4: return MICROHIL_CHANNEL_4;
        case 5: return MICROHIL_CHANNEL_5;
        case 6: return MICROHIL_CHANNEL_6;
        case 7: return MICROHIL_CHANNEL_7;
        case 8: return MICROHIL_CHANNEL_8;
        case 9: return MICROHIL_ALL_CHANNELS_OFF;
        case 10: return MICROHIL_ALL_CHANNELS_ON;
    }

    return MICROHIL_CHANNELS_ERROR;
}
