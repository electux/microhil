/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * io_pwm.c
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
#include "io_pwm.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

void io_pwm_init(uint32_t pin, uint32_t channel) {
  gpio_set_function(pin, GPIO_FUNC_PWM);
  uint32_t slice_num = pwm_gpio_to_slice_num(pin);
  pwm_set_wrap(slice_num, 500);
  pwm_set_chan_level(slice_num, channel, 1);
  pwm_set_clkdiv(slice_num, 50);
  pwm_set_enabled(slice_num, true);
}

void io_pwm_write(uint32_t pin, uint32_t channel, uint16_t duty_level) {
  if (duty_level <= 100) {
    uint32_t slice_num = pwm_gpio_to_slice_num(pin);
    pwm_set_chan_level(slice_num, channel, duty_level);
  }
}
