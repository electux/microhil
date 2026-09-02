/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * main.c
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

#include "command/dispatcher.h"
#include "command/parser.h"
#include "config/nvm_config.h"
#include "device/buzzer.h"
#include "device/relay.h"
#include "device/status_led.h"
#include "pico/stdlib.h"
#include "wifi/wifi_transport.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

enum { MICROHIL_REQ_LEN = 128 };

static bool device_init(void) {
	stdio_init_all();

	nvm_wifi_config_t config;
	nvm_config_init(&config);

	if (!wifi_transport_init(&config)) {
		return false;
	}

	relay_init();
	status_led_init();
	buzzer_init();
	command_init();

	buzzer_beep_start();

	return true;
}

int main(void) {
	if (!device_init()) {
		return 1;
	}

	char request[MICROHIL_REQ_LEN] = {0};

	while (true) {
		wifi_transport_poll();

		relay_tick();
		buzzer_tick();

		if (parser_get_command(request, MICROHIL_REQ_LEN)) {
			command_dispatch(request);
			memset(request, 0, MICROHIL_REQ_LEN * sizeof(char));
		}
	}

	return 0;
}
