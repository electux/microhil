# -*- coding: UTF-8 -*-

'''
Module
    led.py
Copyright
    Copyright (C) 2026 Vladimir Roncevic <elektron.ronca@gmail.com>
    microhil is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by the
    Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    microhil is distributed in the hope that it will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along
    with this program. If not, see <http://www.gnu.org/licenses/>.
Info
    Status LED (NeoPixel) driver of microhil.
'''

from machine import Pin
from neopixel import NeoPixel


class StatusLED:
    '''
        Defines control of the status LED (NeoPixel).
    '''
    DEFAULT_PIN = 13
    DEFAULT_NUM_LEDS = 1
    DEFAULT_BRIGHTNESS = 0.8

    def __init__(self, pin_num=DEFAULT_PIN, num_leds=DEFAULT_NUM_LEDS, brightness=DEFAULT_BRIGHTNESS):
        '''
            Initializes the status LED.
            :param pin_num: Pin number for the LED.
            :param num_leds: Number of LEDs.
            :param brightness: Brightness of the LEDs.
            :exceptions: None.
        '''
        self.pin = Pin(pin_num, Pin.OUT)
        self.num = num_leds
        self.brightness = brightness
        self.np = NeoPixel(self.pin, self.num)

    def set_color(self, r, g, b):
        '''
            Writes the RGB state to the first pixel.
            :param r: Red component.
            :param g: Green component.
            :param b: Blue component.
            :exceptions: None.
        '''
        r_val = int(r * self.brightness)
        g_val = int(g * self.brightness)
        b_val = int(b * self.brightness)
        self.np[0] = (r_val, g_val, b_val)
        self.np.write()
