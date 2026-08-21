/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * relay.c
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
#include "relay.h"
#include "io/io_gpio.h"

static const uint32_t relay_pins[RELAY_NUM_CHANNELS] = {
    21, 20, 19, 18, 17, 16, 15, 14,
};

bool relay_init(void) {
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++) {
    io_gpio_init(relay_pins[i], true);
    io_gpio_write(relay_pins[i], false);
  }
  return true;
}

void relay_set(uint32_t channel, bool state) {
  if (channel < RELAY_NUM_CHANNELS) {
    io_gpio_write(relay_pins[channel], state);
  }
}

void relay_set_all(bool state) {
  for (int i = 0; i < RELAY_NUM_CHANNELS; i++) {
    io_gpio_write(relay_pins[i], state);
  }
}
