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
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#include "pico/stdio_usb.h"
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Main entry point
/// @return MICROHIL_SUCCESS for success else MICROHIL_FAILED
int main()
{
    ////////////////////////////////////////////////////////////////////////
    /// Initialization of microHIL device
    bool status = microhil_init();

    if (!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization of microHIL device
        return MICROHIL_FAILED;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Wait for USB connection
    while (!stdio_usb_connected())
        ;

    while (status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Fetch channel command message
        unsigned char *command = (char *)malloc(MICROHIL_CMD_LEN);
        uint16_t received_bytes = microhil_fetch_command(command);

        if (received_bytes > 0)
        {
            ////////////////////////////////////////////////////////////////
            /// Processing channel command message
            channel_gpio_num cmd_id = microhil_process_command(command);

            if (cmd_id > 0)
            {
                ////////////////////////////////////////////////////////////
                /// Request channel operation
                microhil_channel_switch(cmd_id);
            }
        }

        free(command);
    }

    return MICROHIL_SUCCESS;
}
