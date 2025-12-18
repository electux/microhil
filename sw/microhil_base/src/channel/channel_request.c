/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_request.c
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Start marker of microHIL request
const char start = '<';

////////////////////////////////////////////////////////////////////////////
/// @brief End marker of microHIL request
const char end = '>';

////////////////////////////////////////////////////////////////////////////
/// @brief Fetches microHIL command requests from the serial port
/// @param request storage for received request from the serial port
void microhil_fetch_request(uint8_t *request)
{
    static uint8_t index = 0;
    int16_t rc = getchar_timeout_us(1);

    while ((rc != PICO_ERROR_TIMEOUT) && (new_request == false))
    {
        if (receive_in_progress == true)
        {
            if (rc == start)
            {
                ////////////////////////////////////////////////////////////
                /// Reset index if a new start marker comes in
                receive_in_progress = true;
                index = 0;
            }
            else if (rc == end)
            {
                ////////////////////////////////////////////////////////////
                // End of the microHIL request
                request[index] = '\0';
                receive_in_progress = false;
                index = 0;
                new_request = true;
            }
            else
            {
                ////////////////////////////////////////////////////////////
                // Append any data between start and end markers
                request[index] = (char)rc;
                index++;

                if (index >= MICROHIL_REQ_LEN)
                {
                    index = MICROHIL_REQ_LEN - 1;
                }
            }
        }
        else if (rc == start)
        {
            receive_in_progress = true;
            index = 0;
        }

        rc = getchar_timeout_us(10);
    }
}
