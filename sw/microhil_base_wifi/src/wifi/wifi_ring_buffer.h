/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * wifi_ring_buffer.h
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

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

////////////////////////////////////////////////////////////////////////////
/// @brief Thread-safe byte ring buffer structure
typedef struct {
  uint8_t *buffer;
  uint32_t capacity;
  uint32_t head;
  uint32_t tail;
  uint32_t count;
} wifi_ring_buffer_t;

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes a ring buffer with given backing storage
/// @param rb [out] Pointer to ring buffer instance
/// @param storage [in] Backing memory array
/// @param capacity [in] Capacity in bytes
void wifi_ring_buffer_init(
    wifi_ring_buffer_t *rb, uint8_t *storage, uint32_t capacity
);

////////////////////////////////////////////////////////////////////////////
/// @brief Pushes a byte into the ring buffer (interrupt-safe)
/// @param rb [in,out] Pointer to ring buffer instance
/// @param byte [in] Byte to store
/// @return True on success, false if full
bool wifi_ring_buffer_put(wifi_ring_buffer_t *rb, uint8_t byte);

////////////////////////////////////////////////////////////////////////////
/// @brief Pops a byte from the ring buffer (interrupt-safe)
/// @param rb [in,out] Pointer to ring buffer instance
/// @param byte [out] Destination pointer for retrieved byte
/// @return True on success, false if empty
bool wifi_ring_buffer_get(wifi_ring_buffer_t *rb, uint8_t *byte);

////////////////////////////////////////////////////////////////////////////
/// @brief Returns number of available bytes in the ring buffer
/// @param rb [in] Pointer to ring buffer instance
/// @return Available byte count
uint32_t wifi_ring_buffer_available(const wifi_ring_buffer_t *rb);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if the ring buffer is empty
/// @param rb [in] Pointer to ring buffer instance
/// @return True if empty, false otherwise
bool wifi_ring_buffer_is_empty(const wifi_ring_buffer_t *rb);

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if the ring buffer is full
/// @param rb [in] Pointer to ring buffer instance
/// @return True if full, false otherwise
bool wifi_ring_buffer_is_full(const wifi_ring_buffer_t *rb);

#ifdef __cplusplus
}
#endif
