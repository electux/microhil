/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
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

int main()
{
    microhil_init();

    char *buf;
    int i = 1, count = -1;

    while (1)
    {
        i = stdio_usb_in_chars(buf, 10);
        microhil_channel_switch(i);

        if (count == 0)
        {
            count = 1;
            printf("****System stability****\r\n\r\n");
        }
        else if (count == -1)
        {
            printf("***System restart...****\r\n\r\n");
            sleep_ms(2000);
            count++;
        }
    }

    return 0;
}
