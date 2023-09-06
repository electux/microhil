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
    gpio_put(JDQ8, 1);
    gpio_put(JDQ7, 1);
    gpio_put(JDQ6, 1);
    gpio_put(JDQ5, 1);
    gpio_put(JDQ4, 1);
    gpio_put(JDQ3, 1);
    gpio_put(JDQ2, 1);
    gpio_put(JDQ1, 1);
    printf("***Relay ALL on****\r\n\n");

    for (int i = 0; i < 8; i++)
    {
        Relays[i] = 0x0;
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
    gpio_put(JDQ8, 0);
    gpio_put(JDQ7, 0);
    gpio_put(JDQ6, 0);
    gpio_put(JDQ5, 0);
    gpio_put(JDQ4, 0);
    gpio_put(JDQ3, 0);
    gpio_put(JDQ2, 0);
    gpio_put(JDQ1, 0);
    printf("***Relay ALL off***\r\n\n");

    for (int i = 0; i < 8; i++)
    {
        Relays[i] = 0x1;
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
    case JDQ_ALL_OFF:
        microhil_all_channels_off();
        break;
    case JDQ_ALL_ON:
        microhil_all_channels_on();
        break;
    case JDQ_ERROR:
        printf("****Error*****\r\n\n");
        break;
    default:
        // TODO check gpio value
        gpio_put(gpio, Relays[id - 1]);

        if (Relays[id - 1] == 1)
        {
            put_pixel(urgb_u32(255, 0, 0));
            microhil_write_pwm(80); // buzzer
            microhil_delay_ms(100);
            microhil_write_pwm(0);
            printf("****Relay 1 on*****\r\n\n");
        }
        else if (Relays[id - 1] == 0)
        {
            printf("****Relay 1 off*****\r\n\n");
        }

        Relays[id - 1] = !Relays[id - 1];
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
        return JDQ1;
    case 2:
        return JDQ2;
    case 3:
        return JDQ3;
    case 4:
        return JDQ4;
    case 5:
        return JDQ5;
    case 6:
        return JDQ6;
    case 7:
        return JDQ7;
    case 8:
        return JDQ8;
    case 9:
        return JDQ_ALL_OFF;
    case 10:
        return JDQ_ALL_ON;
    }

    return JDQ_ERROR;
}
