/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * parser.c
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
#include "parser.h"
#include "ble/ble_transport.h"
#include "pico/stdlib.h"
#include <stdint.h>

typedef enum { PARSER_STATE_IDLE, PARSER_STATE_RECEIVING } parser_state_t;

typedef struct {
  parser_state_t state;
  uint32_t idx;
} stream_parser_ctx_t;

static stream_parser_ctx_t ble_ctx = {PARSER_STATE_IDLE, 0};
static stream_parser_ctx_t usb_ctx = {PARSER_STATE_IDLE, 0};

static bool parser_process_char(
    stream_parser_ctx_t *ctx, char c, char *buf, uint32_t max_len
) {
  if (c == '\r' || c == '\n') {
    return false;
  }
  if (c == '<') {
    ctx->state = PARSER_STATE_RECEIVING;
    ctx->idx = 0;
    return false;
  }
  if (ctx->state == PARSER_STATE_RECEIVING) {
    if (c == '>') {
      buf[ctx->idx] = '\0';
      ctx->state = PARSER_STATE_IDLE;
      ctx->idx = 0;
      return true;
    }
    if (ctx->idx < (max_len - 1)) {
      buf[ctx->idx++] = c;
    } else {
      ctx->state = PARSER_STATE_IDLE;
      ctx->idx = 0;
    }
  }
  return false;
}

bool parser_process_ble_stream(char *buf, uint32_t max_len) {
  uint8_t byte = 0;
  while (ble_transport_read_byte(&byte)) {
    if (parser_process_char(&ble_ctx, (char)byte, buf, max_len)) {
      return true;
    }
  }
  return false;
}

bool parser_process_usb_serial_stream(char *buf, uint32_t max_len) {
  int c;
  while ((c = getchar_timeout_us(0)) >= 0) {
    if (parser_process_char(&usb_ctx, (char)c, buf, max_len)) {
      return true;
    }
  }
  return false;
}

bool parser_get_command(char *buf, uint32_t max_len) {
  if (parser_process_ble_stream(buf, max_len)) {
    return true;
  }
  return parser_process_usb_serial_stream(buf, max_len);
}
