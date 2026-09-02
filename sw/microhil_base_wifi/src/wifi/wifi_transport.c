/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * wifi_transport.c
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
#include "wifi_transport.h"
#include "pico/cyw43_arch.h"
#include "tcp_server.h"
#include "wifi_manager.h"
#include "wifi_ring_buffer.h"

enum { WIFI_RX_BUFFER_CAPACITY = 256 };

static uint8_t s_rx_storage[WIFI_RX_BUFFER_CAPACITY];
static wifi_ring_buffer_t s_rx_ring_buffer;
static nvm_wifi_config_t s_active_config;

bool wifi_transport_init(const nvm_wifi_config_t *config) {
  if (config == 0) {
    return false;
  }

  s_active_config = *config;

  wifi_ring_buffer_init(
      &s_rx_ring_buffer, s_rx_storage, WIFI_RX_BUFFER_CAPACITY
  );

  if (!wifi_manager_init(config)) {
    return false;
  }

  if (!tcp_server_init(config->port, &s_rx_ring_buffer)) {
    return false;
  }

  return true;
}

void wifi_transport_poll(void) {
  cyw43_arch_poll();
}

bool wifi_transport_read_byte(uint8_t *byte) {
  return wifi_ring_buffer_get(&s_rx_ring_buffer, byte);
}

bool wifi_transport_send(const uint8_t *data, uint16_t length) {
  return tcp_server_send(data, length);
}

bool wifi_transport_is_connected(void) {
  return tcp_server_is_connected();
}

const nvm_wifi_config_t *wifi_transport_get_config(void) {
  return &s_active_config;
}
