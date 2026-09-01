/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * response.h
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

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Sends a response string over BLE and mirrors to debug console
/// @param msg [in] Null-terminated response string
void response_send(const char *msg);

////////////////////////////////////////////////////////////////////////////
/// @brief Sends a formatted response string over BLE and mirrors to debug console
/// @param format [in] Format string
/// @param ... [in] Variadic arguments
void response_send_formatted(const char *format, ...);

#ifdef __cplusplus
}
#endif
