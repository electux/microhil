/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ble_ring_buffer.c
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
#include "ble_ring_buffer.h"
#include "hardware/sync.h"

void ble_ring_buffer_init(
    ble_ring_buffer_t *rb, uint8_t *storage, uint32_t capacity
) {
  if (rb == 0) {
    return;
  }

  rb->buffer = storage;
  rb->capacity = capacity;
  rb->head = 0;
  rb->tail = 0;
  rb->count = 0;
}

bool ble_ring_buffer_put(ble_ring_buffer_t *rb, uint8_t byte) {
  if (rb == 0 || rb->buffer == 0) {
    return false;
  }

  uint32_t ints = save_and_disable_interrupts();

  if (rb->count >= rb->capacity) {
    restore_interrupts(ints);
    return false;
  }

  rb->buffer[rb->head] = byte;
  rb->head = (rb->head + 1) % rb->capacity;
  rb->count++;
  restore_interrupts(ints);

  return true;
}

bool ble_ring_buffer_get(ble_ring_buffer_t *rb, uint8_t *byte) {
  if (rb == 0 || rb->buffer == 0 || byte == 0) {
    return false;
  }

  uint32_t ints = save_and_disable_interrupts();

  if (rb->count == 0) {
    restore_interrupts(ints);
    return false;
  }

  *byte = rb->buffer[rb->tail];
  rb->tail = (rb->tail + 1) % rb->capacity;
  rb->count--;
  restore_interrupts(ints);

  return true;
}

uint32_t ble_ring_buffer_available(const ble_ring_buffer_t *rb) {
  if (rb == 0) {
    return 0;
  }

  uint32_t ints = save_and_disable_interrupts();
  uint32_t count = rb->count;
  restore_interrupts(ints);

  return count;
}

bool ble_ring_buffer_is_empty(const ble_ring_buffer_t *rb) {
  if (rb == 0) {
    return true;
  }

  uint32_t ints = save_and_disable_interrupts();
  bool empty = (rb->count == 0);
  restore_interrupts(ints);

  return empty;
}

bool ble_ring_buffer_is_full(const ble_ring_buffer_t *rb) {
  if (rb == 0) {
    return false;
  }

  uint32_t ints = save_and_disable_interrupts();
  bool full = (rb->count >= rb->capacity);
  restore_interrupts(ints);

  return full;
}
