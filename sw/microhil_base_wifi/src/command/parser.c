/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * parser.c
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
#include "parser.h"
#include "pico/stdlib.h"
#include "wifi/wifi_transport.h"
#include <stdint.h>

typedef enum { PARSER_STATE_IDLE, PARSER_STATE_RECEIVING } parser_state_t;

static parser_state_t parser_state = PARSER_STATE_IDLE;
static uint32_t parser_idx = 0;

static bool parser_process_char(char c, char *buf, uint32_t max_len) {
  if (c == '\r' || c == '\n') {
    return false;
  }

  if (c == '<') {
    parser_state = PARSER_STATE_RECEIVING;
    parser_idx = 0;
    return false;
  }

  if (parser_state == PARSER_STATE_RECEIVING) {
    if (c == '>') {
      buf[parser_idx] = '\0';
      parser_state = PARSER_STATE_IDLE;
      parser_idx = 0;
      return true;
    }

    if (parser_idx < (max_len - 1)) {
      buf[parser_idx++] = c;
    } else {
      parser_state = PARSER_STATE_IDLE;
      parser_idx = 0;
    }
  }

  return false;
}

bool parser_get_command(char *buf, uint32_t max_len) {
  if (buf == 0 || max_len == 0) {
    return false;
  }

  // 1. Check Wi-Fi TCP stream
  uint8_t byte = 0;
  while (wifi_transport_read_byte(&byte)) {
    if (parser_process_char((char)byte, buf, max_len)) {
      return true;
    }
  }

  // 2. Check USB-Serial stream for configuration / commands
  int usb_char = getchar_timeout_us(0);
  while (usb_char != PICO_ERROR_TIMEOUT) {
    if (parser_process_char((char)usb_char, buf, max_len)) {
      return true;
    }
    usb_char = getchar_timeout_us(0);
  }

  return false;
}
