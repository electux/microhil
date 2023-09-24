/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_init.c
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
#include "pico/stdio_usb.h"
#include "io_config.h"
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Global device initialization
/// @return true for success else false
bool microhil_init()
{
    bool status = false;

    ////////////////////////////////////////////////////////////////////////
    /// Performs initialization for stdio types
    status = stdio_init_all();

    if (!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for stdio types
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Disables convertion of LF to CR
    stdio_set_translate_crlf(&stdio_usb, false);

    ////////////////////////////////////////////////////////////////////////
    /// Performs initialization for stdio usb
    status = stdio_usb_init();

    if (!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for stdio usb
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Performs initialization for RELAY chanels
    status = microhil_init_relay();

    if (!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for RELAY channels
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Performs initialization for PIO state machine
    status = microhil_pio_init();

    if (!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for PIO
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Performs initialization for BUZZER
    status = microhil_init_buzzer();

    if (!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for BUZZER
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Buzzer notification
    microhil_write_buzzer(true);

    ////////////////////////////////////////////////////////////////////////
    /// Led notification
    microhil_write_pixel(0, 0, 0);

    return status;
}
