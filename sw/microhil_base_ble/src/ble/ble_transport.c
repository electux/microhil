/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ble_transport.c
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
#include "ble_transport.h"
#include "ble_gap.h"
#include "ble_gatt_spp.h"
#include "ble_ring_buffer.h"
#include "btstack.h"
#include "config/nvm_config.h"
#include "microhil_ble.h"
#include "pico/cyw43_arch.h"
#include "pico/stdlib.h"

enum { BLE_RX_BUFFER_CAPACITY = 256 };

static uint8_t s_rx_storage[BLE_RX_BUFFER_CAPACITY];
static ble_ring_buffer_t s_rx_ring_buffer;
static btstack_packet_callback_registration_t s_hci_event_callback_registration;

static void btstack_packet_handler(
    uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size
) {
  (void)channel;
  (void)size;

  if (packet_type != HCI_EVENT_PACKET) {
    return;
  }

  switch (hci_event_packet_get_type(packet)) {
  case BTSTACK_EVENT_STATE:
    if (btstack_event_state_get_state(packet) == HCI_STATE_WORKING) {
      ble_gap_start_advertising();
    }
    break;
  case HCI_EVENT_DISCONNECTION_COMPLETE:
    ble_gap_start_advertising();
    break;
  default:
    break;
  }
}

bool ble_transport_init(void) {
  nvm_config_init();

  if (cyw43_arch_init()) {
    return false;
  }

  ble_ring_buffer_init(&s_rx_ring_buffer, s_rx_storage, BLE_RX_BUFFER_CAPACITY);

  l2cap_init();
  sm_init();
  att_server_init(profile_data, 0, 0);

  ble_gatt_spp_init(&s_rx_ring_buffer);
  ble_gap_init();

  s_hci_event_callback_registration.callback = &btstack_packet_handler;
  hci_add_event_handler(&s_hci_event_callback_registration);

  hci_power_control(HCI_POWER_ON);

  return true;
}

void ble_transport_poll(void) {
  cyw43_arch_poll();
}

bool ble_transport_read_byte(uint8_t *byte) {
  return ble_ring_buffer_get(&s_rx_ring_buffer, byte);
}

bool ble_transport_send(const uint8_t *data, uint16_t length) {
  return ble_gatt_spp_send(data, length);
}

bool ble_transport_is_connected(void) {
  return ble_gatt_spp_is_connected();
}

const nvm_ble_config_t *ble_transport_get_config(void) {
  return nvm_config_get();
}
