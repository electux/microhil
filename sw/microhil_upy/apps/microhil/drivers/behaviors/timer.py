# -*- coding: UTF-8 -*-

'''
Module
    timer.py
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
    Timer behavior class of microhil.
'''

from time import ticks_ms, ticks_diff
from drivers.behaviors.base import BaseBehavior

class TimerBehavior(BaseBehavior):
    '''
        Behavior that turns relay OFF after a duration in seconds.
    '''
    def __init__(self, seconds):
        self.start_time = ticks_ms()
        self.duration_ms = seconds * 1000

    def tick(self, channel, relay, buzzer):
        elapsed = ticks_diff(ticks_ms(), self.start_time)
        if elapsed >= self.duration_ms:
            channel.set_state(False, buzzer)
            print("<mh#sys#channel {} off#end>".format(channel.index + 1))

    def get_status_str(self, channel, relay):
        state_str = "ON" if relay.state else "OFF"
        elapsed = ticks_diff(ticks_ms(), self.start_time)
        rem = max(0, (self.duration_ms - elapsed) // 1000)
        return "Channel {}: {} (Timer, rem: {}s)".format(channel.index + 1, state_str, rem)
