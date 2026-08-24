# -*- coding: UTF-8 -*-

'''
Module
    buzzer.py
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
    Buzzer of microhil.
'''

from time import sleep, ticks_ms, ticks_diff
from machine import Pin, PWM


class Buzzer:
    '''
        Defines control of the buzzer.

        It defines:

            :methods:
                | __init__ - Initializes the buzzer.
                | write - Writes the duty cycle of the PWM.
                | beep_start - Beeps the buzzer at the start of the application.
                | beep_changed - Beeps the buzzer when a channel is changed.
                | beep_stop - Beeps the buzzer when the application is stopped.
                | tick - Ticks the buzzer.
    '''
    def __init__(self, pin_num):
        '''
            Initializes the buzzer.

            :param pin_num: Pin number of the buzzer.
            :exceptions: None.
        '''
        self.pwm = PWM(Pin(pin_num))
        self.pwm.freq(1000)
        self.pwm.duty_u16(0)
        self.off_time = 0

    def write(self, duty_percent):
        '''
            Writes the duty cycle of the PWM.

            :param duty_percent: Duty cycle of the PWM.
            :exceptions: None.
        '''
        self.pwm.duty_u16(int(duty_percent * 65535 / 100))

    def beep_start(self):
        '''
            Beeps the buzzer at the start of the application.

            :param pin_num: Pin number of the buzzer.
            :exceptions: None.
        '''
        self.write(16)
        sleep(0.1)
        self.write(0)

    def beep_changed(self):
        '''
            Beeps the buzzer when a channel is changed.

            :param pin_num: Pin number of the buzzer.
            :exceptions: None.
        '''
        self.write(16)
        self.off_time = ticks_ms() + 50

    def beep_stop(self):
        '''
            Beeps the buzzer when the application is stopped.

            :param pin_num: Pin number of the buzzer.
            :exceptions: None.
        '''
        self.write(20)
        sleep(0.3)
        self.write(0)

    def tick(self):
        '''
            Ticks the buzzer.

            :param pin_num: Pin number of the buzzer.
            :exceptions: None.
        '''
        if self.off_time > 0:
            if ticks_diff(ticks_ms(), self.off_time) >= 0:
                self.write(0)
                self.off_time = 0
