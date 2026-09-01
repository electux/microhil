/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * parser.c
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
#include "parser.h"
#include "serial/serial_transport.h"
#include <stdint.h>

typedef enum { PARSER_STATE_IDLE, PARSER_STATE_RECEIVING } parser_state_t;

static parser_state_t parser_state = PARSER_STATE_IDLE;
static uint32_t parser_idx = 0;

////////////////////////////////////////////////////////////////////////////
/// @brief Processes a single character inside the parsing state machine
///
/// @param c [in] Character to process
/// @param buf [out] Destination buffer to store parsed command
/// @param max_len [in] Maximum capacity of the destination buffer
/// @return True if a complete command frame was successfully parsed, else false
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

////////////////////////////////////////////////////////////////////////////
/// @brief Reads and parses command requests from the serial input stream
///
/// @param buf [out] Destination buffer to store parsed command
/// @param max_len [in] Maximum capacity of the destination buffer
/// @return True if a command was parsed, else false
bool parser_get_command(char *buf, uint32_t max_len) {
  uint8_t byte = 0;
  while (serial_transport_read_byte(&byte)) {
    if (parser_process_char((char)byte, buf, max_len)) {
      return true;
    }
  }
  return false;
}
