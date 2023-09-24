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
#include "pico/stdio_usb.h"
#include "channel.h"
#include <tusb.h>

////////////////////////////////////////////////////////////////////////////
/// @brief Flag for received new request from the serial port
bool new_request = false;

////////////////////////////////////////////////////////////////////////////
/// @brief Flog for receiving in progress
bool receive_in_progress = false;

////////////////////////////////////////////////////////////////////////////
/// @brief Main entry point
/// @return 0 for success else 1
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

    ////////////////////////////////////////////////////////////////////
    /// Command buffer for receiving requests
    uint8_t request[MICROHIL_REQ_LEN] = {0};

    while (status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Fetches channel command requests
        microhil_fetch_request(request);

        if (!receive_in_progress && new_request)
        {
            ////////////////////////////////////////////////////////
            /// Clean up command buffer and flag for new request
            microhil_channel_switch(request);
            memset(request, 0, MICROHIL_REQ_LEN * sizeof(uint8_t));
            new_request = false;
        }
    }

    return 0;
}
