/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * serial_transport.h
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
#pragma once

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes USB stdio serial interface
/// @return True on success, false on failure
bool serial_transport_init(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Processes pending serial communication / flush tasks
void serial_transport_poll(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Reads one received byte from the serial reception stream
/// @param byte [out] Destination pointer for byte
/// @return True if byte was read, false if no byte available or timeout
bool serial_transport_read_byte(uint8_t *byte);

////////////////////////////////////////////////////////////////////////////
/// @brief Sends data buffer over serial interface
/// @param data [in] Pointer to byte array
/// @param length [in] Number of bytes to send
/// @return True on success, false otherwise
bool serial_transport_send(const uint8_t *data, uint16_t length);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if USB CDC serial host is currently connected
/// @return True if connected, false otherwise
bool serial_transport_is_connected(void);

#ifdef __cplusplus
}
#endif
