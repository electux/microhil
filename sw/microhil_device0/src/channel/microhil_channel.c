/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_channel_action.c
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
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "microhil_channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief
void microhil_all_channels_on()
{
    gpio_put(MICROHIL_CHANNEL_8, 1);
    gpio_put(MICROHIL_CHANNEL_7, 1);
    gpio_put(MICROHIL_CHANNEL_6, 1);
    gpio_put(MICROHIL_CHANNEL_5, 1);
    gpio_put(MICROHIL_CHANNEL_4, 1);
    gpio_put(MICROHIL_CHANNEL_3, 1);
    gpio_put(MICROHIL_CHANNEL_2, 1);
    gpio_put(MICROHIL_CHANNEL_1, 1);
    printf("***Relay ALL on****\r\n\n");

    for (int i = 0; i < 8; i++)
    {
        channels[i] = 0x0;
    }

    put_pixel(urgb_u32(255, 255, 255));
    microhil_write_pwm(80); // buzzer
    microhil_delay_ms(100);
    microhil_write_pwm(0);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
void microhil_all_channels_off()
{
    gpio_put(MICROHIL_CHANNEL_8, 0);
    gpio_put(MICROHIL_CHANNEL_7, 0);
    gpio_put(MICROHIL_CHANNEL_6, 0);
    gpio_put(MICROHIL_CHANNEL_5, 0);
    gpio_put(MICROHIL_CHANNEL_4, 0);
    gpio_put(MICROHIL_CHANNEL_3, 0);
    gpio_put(MICROHIL_CHANNEL_2, 0);
    gpio_put(MICROHIL_CHANNEL_1, 0);
    printf("***Relay ALL off***\r\n\n");

    for (int i = 0; i < 8; i++)
    {
        channels[i] = 0x1;
    }

    put_pixel(urgb_u32(0, 0, 0));
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param id
void microhil_channel_switch(int id)
{
    unsigned int gpio = id_to_gpio(id);

    switch (gpio)
    {
    case MICROHIL_ALL_CHANNELS_OFF:
        microhil_all_channels_off();
        break;
    case MICROHIL_ALL_CHANNELS_ON:
        microhil_all_channels_on();
        break;
    case MICROHIL_CHANNELS_ERROR:
        printf("****Error*****\r\n\n");
        break;
    default:
        // TODO check gpio value
        gpio_put(gpio, channels[id - 1]);

        if (channels[id - 1] == 1)
        {
            put_pixel(urgb_u32(255, 0, 0));
            microhil_write_pwm(80); // buzzer
            microhil_delay_ms(100);
            microhil_write_pwm(0);
            printf("****Relay 1 on*****\r\n\n");
        }
        else if (channels[id - 1] == 0)
        {
            printf("****Relay 1 off*****\r\n\n");
        }

        channels[id - 1] = !channels[id - 1];
        break;
    }
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param id
/// @return
unsigned int id_to_gpio(int id)
{
    switch (id)
    {
    case 1:
        return MICROHIL_CHANNEL_1;
    case 2:
        return MICROHIL_CHANNEL_2;
    case 3:
        return MICROHIL_CHANNEL_3;
    case 4:
        return MICROHIL_CHANNEL_4;
    case 5:
        return MICROHIL_CHANNEL_5;
    case 6:
        return MICROHIL_CHANNEL_6;
    case 7:
        return MICROHIL_CHANNEL_7;
    case 8:
        return MICROHIL_CHANNEL_8;
    case 9:
        return MICROHIL_ALL_CHANNELS_OFF;
    case 10:
        return MICROHIL_ALL_CHANNELS_ON;
    }

    return MICROHIL_CHANNELS_ERROR;
}
