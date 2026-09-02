/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
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

#include "ble/ble_transport.h"
#include "command/dispatcher.h"
#include "command/parser.h"
#include "device/buzzer.h"
#include "device/relay.h"
#include "device/status_led.h"
#include "pico/stdlib.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

enum { MICROHIL_REQ_LEN = 64 };

////////////////////////////////////////////////////////////////////////////
/// @brief Performs unified initialization of all hardware and BLE transport
/// @return True for success, false otherwise
static bool device_init(void) {
  if (!stdio_init_all()) {
    return false;
  }

  if (!relay_init()) {
    return false;
  }

  if (!status_led_init()) {
    return false;
  }

  if (!buzzer_init()) {
    return false;
  }

  if (!ble_transport_init()) {
    return false;
  }

  command_init();

  buzzer_beep_start();

  return true;
}

////////////////////////////////////////////////////////////////////////////
/// @brief Main entry point for microhil-base-ble
/// @return 0 for success exit else 1 for failed exit
int main(void) {
  //////////////////////////////////////////////////////////////////////////
  /// Performs device and BLE initialization
  if (!device_init()) {
    return 1;
  }

  //////////////////////////////////////////////////////////////////////////
  /// Command buffer for received request
  char request[MICROHIL_REQ_LEN] = {0};

  while (true) {
    ////////////////////////////////////////////////////////////////////////
    /// Run BLE background polling
    ble_transport_poll();

    ////////////////////////////////////////////////////////////////////////
    /// Run non-blocking timings
    relay_tick();
    buzzer_tick();

    ////////////////////////////////////////////////////////////////////////
    /// Fetch and process channel command request from BLE stream
    if (parser_get_command(request, MICROHIL_REQ_LEN)) {
      command_dispatch(request);
      memset(request, 0, MICROHIL_REQ_LEN * sizeof(char));
    }
  }

  return 0;
}
