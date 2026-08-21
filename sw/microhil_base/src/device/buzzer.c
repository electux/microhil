/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * buzzer.c
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
#include "buzzer.h"
#include "io/io_pwm.h"
#include "pico/stdlib.h"

static const uint32_t BUZZER_PIN = 22;
static const uint32_t BUZZER_PWM_CHAN = 1; // PWM_CHAN_B

bool buzzer_init(void) {
  io_pwm_init(BUZZER_PIN, BUZZER_PWM_CHAN);
  io_pwm_write(BUZZER_PIN, BUZZER_PWM_CHAN, 0);
  return true;
}

void buzzer_write(uint16_t value) {
  io_pwm_write(BUZZER_PIN, BUZZER_PWM_CHAN, value);
}

void buzzer_beep_start(void) {
  buzzer_write(80);
  sleep_ms(100);
  buzzer_write(0);
}
