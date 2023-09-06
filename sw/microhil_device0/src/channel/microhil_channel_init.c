/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * microhil_channel_init.c
 * Copyright (C) 2023 Vladimir Roncevic <elektron.ronca@gmail.com>
 *
 * microhil-device0 is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * microhil-device0 is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program_name.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "microhil_channel.h"

////////////////////////////////////////////////////////////////////////////
/// @brief
unsigned char Relays[8] = {0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1};

////////////////////////////////////////////////////////////////////////////
/// @brief
const int PIN_TX = 13;

////////////////////////////////////////////////////////////////////////////
/// @brief
void microhil_init()
{
    stdio_init_all();
    stdio_usb_init();
    gpio_init(JDQ1);
    gpio_init(JDQ2);
    gpio_init(JDQ3);
    gpio_init(JDQ4);
    gpio_init(JDQ5);
    gpio_init(JDQ6);
    gpio_init(JDQ7);
    gpio_init(JDQ8);
    gpio_set_dir(JDQ1, GPIO_OUT);
    gpio_set_dir(JDQ2, GPIO_OUT);
    gpio_set_dir(JDQ3, GPIO_OUT);
    gpio_set_dir(JDQ4, GPIO_OUT);
    gpio_set_dir(JDQ5, GPIO_OUT);
    gpio_set_dir(JDQ6, GPIO_OUT);
    gpio_set_dir(JDQ7, GPIO_OUT);
    gpio_set_dir(JDQ8, GPIO_OUT);

    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, PIN_TX, 800000, true);
    gpio_set_function(6, GPIO_FUNC_PWM);

    slice_num = pwm_gpio_to_slice_num(6);

    pwm_set_wrap(slice_num, 500);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
    pwm_set_clkdiv(slice_num, 50);
    pwm_set_enabled(slice_num, true);
    put_pixel(urgb_u32(0, 0, 0)); // RGB
    // microhil_write_pwm(80); //buzzer
}
