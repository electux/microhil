/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ble_gatt_spp.c
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
#include "ble_gatt_spp.h"
#include "ble/gatt-service/nordic_spp_service_server.h"
#include "ble_gap.h"
#include "btstack.h"

static hci_con_handle_t s_con_handle = HCI_CON_HANDLE_INVALID;
static ble_ring_buffer_t *s_rx_ring_buffer = 0;

static void nordic_spp_packet_handler(
    uint8_t packet_type, uint16_t channel, uint8_t *packet, uint16_t size
) {
  (void)channel;
  switch (packet_type) {
  case HCI_EVENT_PACKET:
    if (hci_event_packet_get_type(packet) != HCI_EVENT_GATTSERVICE_META) {
      break;
    }
    switch (hci_event_gattservice_meta_get_subevent_code(packet)) {
    case GATTSERVICE_SUBEVENT_SPP_SERVICE_CONNECTED:
      s_con_handle =
          gattservice_subevent_spp_service_connected_get_con_handle(packet);
      break;
    case GATTSERVICE_SUBEVENT_SPP_SERVICE_DISCONNECTED:
      s_con_handle = HCI_CON_HANDLE_INVALID;
      ble_gap_start_advertising();
      break;
    default:
      break;
    }
    break;

  case RFCOMM_DATA_PACKET:
    if (s_rx_ring_buffer != 0) {
      for (uint16_t i = 0; i < size; i++) {
        ble_ring_buffer_put(s_rx_ring_buffer, packet[i]);
      }
    }
    break;

  default:
    break;
  }
}

void ble_gatt_spp_init(ble_ring_buffer_t *rx_rb) {
  s_rx_ring_buffer = rx_rb;
  s_con_handle = HCI_CON_HANDLE_INVALID;
  nordic_spp_service_server_init(&nordic_spp_packet_handler);
}

bool ble_gatt_spp_is_connected(void) {
  return (s_con_handle != HCI_CON_HANDLE_INVALID);
}

hci_con_handle_t ble_gatt_spp_get_con_handle(void) {
  return s_con_handle;
}

bool ble_gatt_spp_send(const uint8_t *data, uint16_t length) {
  if (s_con_handle == HCI_CON_HANDLE_INVALID || data == 0 || length == 0) {
    return false;
  }
  return (nordic_spp_service_server_send(s_con_handle, data, length) == 0);
}
