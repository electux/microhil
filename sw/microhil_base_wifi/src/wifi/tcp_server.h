/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * tcp_server.h
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base-wifi is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base-wifi is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "wifi_ring_buffer.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes and binds raw lwIP TCP socket server on given port
/// @param port [in] TCP listening port (e.g. 5000)
/// @param rx_rb [in] Pointer to ring buffer where incoming stream bytes are queued
/// @return True on success, false if socket creation or binding fails
bool tcp_server_init(uint16_t port, wifi_ring_buffer_t *rx_rb);

////////////////////////////////////////////////////////////////////////////
/// @brief Sends data buffer over active TCP socket connection
/// @param data [in] Pointer to data byte array
/// @param length [in] Number of bytes to send
/// @return True on successful queueing and transmission, false otherwise
bool tcp_server_send(const uint8_t *data, uint16_t length);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if a TCP client is currently connected
/// @return True if connected, false otherwise
bool tcp_server_is_connected(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Gracefully terminates active client TCP connection
void tcp_server_close_client(void);

#ifdef __cplusplus
}
#endif
