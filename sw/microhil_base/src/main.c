/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
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
#include "tusb.h"
#include "pico/stdio_usb.h"
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Flag for received new request from the serial port
bool new_request = false;

////////////////////////////////////////////////////////////////////////////
/// @brief Flag for marking receive in progress
bool receive_in_progress = false;

////////////////////////////////////////////////////////////////////////////
/// @brief Main entry point for microhil-base
/// @return 0 for success exit else 1 for failed exit
int main()
{
    ////////////////////////////////////////////////////////////////////////
    /// Performs device initialization
    bool status = microhil_init();

    if (!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform device initialization
        return 1;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Waits for USB connection
    while (!tud_cdc_connected())
    {
        sleep_ms(100);
    }

    ////////////////////////////////////////////////////////////////////////
    /// Command buffer for received request
    uint8_t request[MICROHIL_REQ_LEN] = {0};

    while (status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Fetch channel command request
        microhil_fetch_request(request);

        if (!receive_in_progress && new_request)
        {
            ////////////////////////////////////////////////////////////////
            /// Cleans the command buffer and flag
            microhil_channel_switch(request);
            memset(request, 0, MICROHIL_REQ_LEN * sizeof(uint8_t));
            new_request = false;
        }
    }

    return 0;
}
