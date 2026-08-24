# -*- coding: UTF-8 -*-

'''
Module
    blink.py
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
    Blink behavior class of microhil.
'''

from time import ticks_ms, ticks_diff
from drivers.behaviors.base import BaseBehavior

class BlinkBehavior(BaseBehavior):
    '''
        Behavior that blinks a relay channel ON and OFF a specific number of times.
    '''
    def __init__(self, on_ms, off_ms, count):
        self.start_time = ticks_ms()
        self.blink_on_ms = on_ms
        self.blink_off_ms = off_ms
        self.blink_count = count
        self.blink_phase = True  # True for ON phase, False for OFF phase

    def tick(self, channel, relay, buzzer):
        now = ticks_ms()
        elapsed = ticks_diff(now, self.start_time)
        if self.blink_phase:
            if elapsed >= self.blink_on_ms:
                relay.write(False, buzzer)
                self.blink_phase = False
                self.start_time = now
        else:
            if elapsed >= self.blink_off_ms:
                if self.blink_count > 0:
                    self.blink_count -= 1
                    if self.blink_count == 0:
                        channel.set_state(False, buzzer)
                        print("<mh#sys#channel {} off#end>".format(channel.index + 1))
                        return
                relay.write(True, buzzer)
                self.blink_phase = True
                self.start_time = now

    def get_status_str(self, channel, relay):
        state_str = "ON" if relay.state else "OFF"
        phase_str = "ON" if self.blink_phase else "OFF"
        return "Channel {}: {} (Blink, count: {}, phase: {})".format(
            channel.index + 1, state_str, self.blink_count, phase_str
        )
