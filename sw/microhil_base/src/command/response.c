/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * response.c
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
#include "response.h"
#include "serial/serial_transport.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

enum { RESPONSE_BUFFER_MAX_LEN = 256 };

void response_send(const char *msg) {
  if (msg == NULL) {
    return;
  }
  uint16_t len = (uint16_t)strlen(msg);
  if (len > 0) {
    serial_transport_send((const uint8_t *)msg, len);
  }
}

void response_send_formatted(const char *format, ...) {
  if (format == NULL) {
    return;
  }
  char buffer[RESPONSE_BUFFER_MAX_LEN] = {0};
  va_list args;
  va_start(args, format);
  int written = vsnprintf(buffer, sizeof(buffer), format, args);
  va_end(args);

  if (written > 0) {
    response_send(buffer);
  }
}
