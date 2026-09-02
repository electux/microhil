/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * parser.h
 * Copyright (C) 2025 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-base-ble is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-base-ble is distributed in the hope that it will be useful, but
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
/// @brief Fetches and parses a command frame from BLE or USB-Serial stream
/// @param buf [out] Destination buffer to store parsed command
/// @param max_len [in] Maximum capacity of the destination buffer
/// @return True if a complete command frame was successfully parsed, else false
bool parser_get_command(char *buf, uint32_t max_len);

////////////////////////////////////////////////////////////////////////////
/// @brief Fetches and parses a command specifically from BLE stream
/// @param buf [out] Destination buffer to store parsed command
/// @param max_len [in] Maximum capacity of the destination buffer
/// @return True if a command frame was parsed, else false
bool parser_process_ble_stream(char *buf, uint32_t max_len);

////////////////////////////////////////////////////////////////////////////
/// @brief Fetches and parses a command specifically from USB CDC stream
/// @param buf [out] Destination buffer to store parsed command
/// @param max_len [in] Maximum capacity of the destination buffer
/// @return True if a command frame was parsed, else false
bool parser_process_usb_serial_stream(char *buf, uint32_t max_len);

#ifdef __cplusplus
}
#endif
