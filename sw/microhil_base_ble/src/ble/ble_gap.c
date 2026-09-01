/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * ble_gap.c
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
#include "ble_gap.h"
#include "bluetooth.h"
#include "btstack.h"
#include <string.h>

static const uint8_t ADV_DATA[] = {
    // Flags: general discoverable, BR/EDR not supported (3 bytes)
    2, BLUETOOTH_DATA_TYPE_FLAGS, 0x06,
    // Complete Local Name: "microhil-ble" (14 bytes)
    13, BLUETOOTH_DATA_TYPE_COMPLETE_LOCAL_NAME, 'm', 'i', 'c', 'r', 'o', 'h',
    'i', 'l', '-', 'b', 'l', 'e'
};

static const uint8_t SCAN_RESP_DATA[] = {
    // Complete 128-bit Service Class UUID: Nordic SPP (18 bytes)
    // (6E400001-B5A3-F393-E0A9-E50E24DCCA9E)
    17, BLUETOOTH_DATA_TYPE_COMPLETE_LIST_OF_128_BIT_SERVICE_CLASS_UUIDS, 0x9e,
    0xca, 0xdc, 0x24, 0x0e, 0xe5, 0xa9, 0xe0, 0x93, 0xf3, 0xa3, 0xb5, 0x01,
    0x00, 0x40, 0x6e
};

void ble_gap_init(void) {
  uint16_t adv_int_min = 0x0030;
  uint16_t adv_int_max = 0x0060;
  uint8_t adv_type = 0;
  bd_addr_t null_addr;
  memset(null_addr, 0, sizeof(bd_addr_t));

  gap_advertisements_set_params(
      adv_int_min, adv_int_max, adv_type, 0, null_addr, 0x07, 0x00
  );
  gap_advertisements_set_data(sizeof(ADV_DATA), (uint8_t *)ADV_DATA);
  gap_scan_response_set_data(sizeof(SCAN_RESP_DATA), (uint8_t *)SCAN_RESP_DATA);
}

void ble_gap_start_advertising(void) {
  gap_advertisements_enable(1);
}

void ble_gap_stop_advertising(void) {
  gap_advertisements_enable(0);
}
