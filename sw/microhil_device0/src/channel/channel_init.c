/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * channel_init.c
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
#include "channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief Initialization of relay channels
unsigned char channels[MICROHIL_NUMBER_OF_CHANNELS] = {1};

////////////////////////////////////////////////////////////////////////////
/// @brief Global initialization of microHIL device
/// @return true for success else false
bool microhil_init()
{
    bool status = false;

    ////////////////////////////////////////////////////////////////////////
    /// Perform initialization for stdio types
    status = stdio_init_all();

    if(!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for stdio types
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Perform initialization for stdio usb
    status = stdio_usb_init();

    if(!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for stdio usb
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Perform initialization for RELAY
    status = microhil_init_relay();

    if(!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for RELAY
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Perform initialization for PIO
    status = microhil_pio_init();

    if(!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for PIO
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Perform initialization for PWM channel
    status = microhil_init_pwm();

    if(!status)
    {
        ////////////////////////////////////////////////////////////////////
        /// Failed to perform initialization for PWM
        return status;
    }

    ////////////////////////////////////////////////////////////////////////
    /// Led notification
    put_pixel(urgb_u32(0, 0, 0));

    return status;
}