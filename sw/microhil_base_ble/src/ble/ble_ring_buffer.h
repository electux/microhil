/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ble_ring_buffer.h
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

typedef struct {
  uint8_t *buffer;
  uint32_t capacity;
  uint32_t head;
  uint32_t tail;
  uint32_t count;
} ble_ring_buffer_t;

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes a ring buffer with given backing storage
/// @param rb [out] Pointer to ring buffer instance
/// @param storage [in] Backing memory array
/// @param capacity [in] Capacity in bytes
void ble_ring_buffer_init(
    ble_ring_buffer_t *rb, uint8_t *storage, uint32_t capacity
);

////////////////////////////////////////////////////////////////////////////
/// @brief Pushes a byte into the ring buffer
/// @param rb [in,out] Pointer to ring buffer instance
/// @param byte [in] Byte to store
/// @return True on success, false if full
bool ble_ring_buffer_put(ble_ring_buffer_t *rb, uint8_t byte);

////////////////////////////////////////////////////////////////////////////
/// @brief Pops a byte from the ring buffer
/// @param rb [in,out] Pointer to ring buffer instance
/// @param byte [out] Pointer to store retrieved byte
/// @return True on success, false if empty
bool ble_ring_buffer_get(ble_ring_buffer_t *rb, uint8_t *byte);

////////////////////////////////////////////////////////////////////////////
/// @brief Returns number of available bytes in the ring buffer
/// @param rb [in] Pointer to ring buffer instance
/// @return Number of stored bytes
uint32_t ble_ring_buffer_available(const ble_ring_buffer_t *rb);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if ring buffer is empty
/// @param rb [in] Pointer to ring buffer instance
/// @return True if empty, false otherwise
bool ble_ring_buffer_is_empty(const ble_ring_buffer_t *rb);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if ring buffer is full
/// @param rb [in] Pointer to ring buffer instance
/// @return True if full, false otherwise
bool ble_ring_buffer_is_full(const ble_ring_buffer_t *rb);

#ifdef __cplusplus
}
#endif
