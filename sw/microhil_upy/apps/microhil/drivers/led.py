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
    def __init__(self, pin_num=13, num_leds=1, brightness=0.8):
        '''
            Initializes the status LED.
        '''
        self.pin = Pin(pin_num, Pin.OUT)
        self.num = num_leds
        self.brightness = brightness
        self.np = NeoPixel(self.pin, self.num)

    def set_color(self, r, g, b):
        '''
            Writes the RGB state to the first pixel.
        '''
        r_val = int(r * self.brightness)
        g_val = int(g * self.brightness)
        b_val = int(b * self.brightness)
        self.np[0] = (r_val, g_val, b_val)
        self.np.write()
