/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ble_transport.h
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

#include "config/nvm_config.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes NVM config, CYW43, BTstack, and starts advertising
/// @return True on success, false on failure
bool ble_transport_init(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Processes pending BLE/wireless stack events
void ble_transport_poll(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Reads one received byte from the BLE reception buffer
/// @param byte [out] Destination pointer for byte
/// @return True if byte was read, false if buffer is empty
bool ble_transport_read_byte(uint8_t *byte);

////////////////////////////////////////////////////////////////////////////
/// @brief Sends data buffer over BLE connection
/// @param data [in] Pointer to byte array
/// @param length [in] Number of bytes to send
/// @return True on success, false if not connected or buffer full
bool ble_transport_send(const uint8_t *data, uint16_t length);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if a BLE peer is currently connected
/// @return True if connected, false otherwise
bool ble_transport_is_connected(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Gets active BLE NVM configuration
/// @return Pointer to current nvm_ble_config_t
const nvm_ble_config_t *ble_transport_get_config(void);

#ifdef __cplusplus
}
#endif
