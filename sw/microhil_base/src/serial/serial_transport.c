/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * serial_transport.c
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
#include "serial_transport.h"
#include "pico/stdlib.h"
#include "pico/stdio_usb.h"
#include <stddef.h>

static const uint32_t SERIAL_READ_TIMEOUT_US = 0;

////////////////////////////////////////////////////////////////////////////
/// @brief Initializes USB stdio serial interface
/// @return True on success, false on failure
bool serial_transport_init(void) {
  return stdio_init_all();
}

////////////////////////////////////////////////////////////////////////////
/// @brief Processes pending serial communication / flush tasks
void serial_transport_poll(void) {
  stdio_flush();
}

////////////////////////////////////////////////////////////////////////////
/// @brief Reads one received byte from the serial reception stream
/// @param byte [out] Destination pointer for byte
/// @return True if byte was read, false if no byte available or timeout
bool serial_transport_read_byte(uint8_t *byte) {
  if (byte == NULL) {
    return false;
  }

  int16_t rc = getchar_timeout_us(SERIAL_READ_TIMEOUT_US);
  if (rc != PICO_ERROR_TIMEOUT) {
    *byte = (uint8_t)rc;
    return true;
  }

  return false;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Sends data buffer over serial interface
/// @param data [in] Pointer to byte array
/// @param length [in] Number of bytes to send
/// @return True on success, false otherwise
bool serial_transport_send(const uint8_t *data, uint16_t length) {
  if (data == NULL || length == 0) {
    return false;
  }

  for (uint16_t i = 0; i < length; i++) {
    putchar_raw((int)data[i]);
  }
  stdio_flush();

  return true;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Checks if USB CDC serial host is currently connected
/// @return True if connected, false otherwise
bool serial_transport_is_connected(void) {
  return stdio_usb_connected();
}
