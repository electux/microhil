# -*- coding: UTF-8 -*-

'''
Module
    relay.py
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
    Physical relay driver of microhil.
'''

from machine import Pin


class Relay:
    '''
        Physical driver for a single active-low relay.
    '''
    def __init__(self, pin_num):
        '''
            Initializes the physical relay pin (active-low, default OFF).
        '''
        self.pin = Pin(pin_num, Pin.OUT)
        self.pin.high()  # Active-low OFF
        self.state = False

    def write(self, on, buzzer):
        '''
            Sets the physical state of the relay.
        '''
        if self.state != on:
            self.state = on
            if on:
                self.pin.low()  # Active-low ON
            else:
                self.pin.high()  # Active-low OFF
            buzzer.beep_changed()
