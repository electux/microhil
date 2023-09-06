/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * infrared.c
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
#include "infrared.h"

int microhil_infrared_pin;

////////////////////////////////////////////////////////////////////////////
/// @brief 
/// @param pin 
void microhil_write_infrared_pin(uint8_t pin)
{
    microhil_infrared_pin = pin;

    microhil_gpio_mode(microhil_infrared_pin, 0);
    gpio_pull_up(microhil_infrared_pin);
}

////////////////////////////////////////////////////////////////////////////
/// @brief
/// @param
/// @return
int microhil_read_infrared_pin()
{
    uint8_t i, idx, cnt;
    uint8_t count;
    uint8_t data[4];
    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;

    if (microhil_digital_read(microhil_infrared_pin) == 0)
    {
        count = 0;

        while (microhil_digital_read(microhil_infrared_pin) == 0 && count++ < 200)
        {
            sleep_us(60);
        }

        count = 0;

        while (microhil_digital_read(microhil_infrared_pin) == 1 && count++ < 80)
        {
            sleep_us(60);
        }

        idx = 0;
        cnt = 0;
        data[0] = 0;
        data[1] = 0;
        data[2] = 0;
        data[3] = 0;

        for (i = 0; i < 32; i++)
        {
            count = 0;

            while (microhil_digital_read(microhil_infrared_pin) == 0 && count++ < 15)
            {
                sleep_us(60);
            }

            count = 0;

            while (microhil_digital_read(microhil_infrared_pin) == 1 && count++ < 40)
            {
                sleep_us(60);
            }

            if (count > 25)
            {
                data[idx] |= (1 << cnt);
            }

            if (cnt == 7)
            {
                cnt = 0;
                idx++;
            }
            else
            {
                cnt++;
            }
        }

        if (data[0] + data[1] == 0xFF && data[2] + data[3] == 0xFF)
        {
            printf("Get the key: 0x%02x\n", data[2]);
            return data[2];
        }
        else
        {
            return -1;
        }
    }

    return -2;
}
