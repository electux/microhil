# -*- coding: UTF-8 -*-

'''
Module
    pulse.py
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
    Pulse behavior class of microhil.
'''

from time import ticks_ms, ticks_diff


class PulseBehavior:
    '''
        Behavior that turns relay OFF after a duration in milliseconds.
    '''
    def __init__(self, duration_ms):
        '''
            Initialize the pulse behavior.
            :param duration_ms: Time to pulse the relay.
            :exceptions: None.
        '''
        self.start_time = ticks_ms()
        self.duration_ms = duration_ms

    def tick(self, channel, relay, buzzer):
        '''
            Tick the pulse behavior.
            :param channel: Channel to tick the pulse behavior for.
            :param relay: Relay to tick the pulse behavior for.
            :param buzzer: Buzzer to tick the pulse behavior for.
            :exceptions: None.
        '''
        elapsed = ticks_diff(ticks_ms(), self.start_time)

        if elapsed >= self.duration_ms:
            channel.set_state(False, buzzer)
            print(f"<mh#sys#channel {channel.index + 1} off#end>")

    def get_status_str(self, channel, relay):
        '''
            Get the status string for the pulse behavior.
            :param channel: Channel to get the status string for.
            :param relay: Relay to get the status string for.
            :return: Status string for the pulse behavior.
            :exceptions: None.
        '''
        state_str = "ON" if relay.state else "OFF"
        elapsed = ticks_diff(ticks_ms(), self.start_time)
        rem = max(0, self.duration_ms - elapsed)

        return f"Channel {channel.index + 1}: {state_str} (Pulse, rem: {rem}ms)"
