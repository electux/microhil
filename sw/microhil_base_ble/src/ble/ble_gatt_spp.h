/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ble_gatt_spp.h
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

#include "ble_ring_buffer.h"
#include "bluetooth.h"
#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes Nordic SPP service server and registers RX buffer
/// @param rx_rb [in] Pointer to ring buffer where incoming data is stored
void ble_gatt_spp_init(ble_ring_buffer_t *rx_rb);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if a BLE client is connected via Nordic SPP
/// @return True if connected, false otherwise
bool ble_gatt_spp_is_connected(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Returns current active connection handle
/// @return Connection handle or HCI_CON_HANDLE_INVALID
hci_con_handle_t ble_gatt_spp_get_con_handle(void);

////////////////////////////////////////////////////////////////////////////
/// @brief Sends data packet to connected BLE peer
/// @param data [in] Data buffer to transmit
/// @param length [in] Number of bytes to transmit
/// @return True if data was sent, false otherwise
bool ble_gatt_spp_send(const uint8_t *data, uint16_t length);

#ifdef __cplusplus
}
#endif
