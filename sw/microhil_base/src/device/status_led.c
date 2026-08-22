/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * status_led.c
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
#include "status_led.h"
#include "hardware/pio.h"
#include "ws2812.pio.h"

static const uint32_t STATUS_LED_PIN = 13;

bool status_led_init(void) {
  ws2812_init init = {
      .pio = pio0,
      .sm = 0,
      .offset = pio_add_program(pio0, &ws2812_program),
      .pin = STATUS_LED_PIN,
      .freq = 800000,
      .rgbw = false};

  ws2812_program_init(&init);
  return true;
}

void status_led_write(uint8_t red, uint8_t green, uint8_t blue) {
  uint pixel_rgb = ((uint)(red) << 8) | ((uint)(green) << 16) | ((uint)(blue));
  pio_sm_put_blocking(pio0, 0, pixel_rgb << 8u);
}
