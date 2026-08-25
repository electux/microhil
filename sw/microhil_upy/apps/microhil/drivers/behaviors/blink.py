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


class BlinkBehavior:
    '''
        Behavior that blinks a relay channel ON and OFF a specific number of times.
    '''
    def __init__(self, on_ms, off_ms, count):
        '''
            Initialize the blink behavior.
            :param on_ms: Time to blink the relay ON
            :param off_ms: Time to blink the relay OFF
            :param count: Number of times to blink the relay
        '''
        self.start_time = ticks_ms()
        self.blink_on_ms = on_ms
        self.blink_off_ms = off_ms
        self.blink_count = count
        self.blink_phase = True

    def tick(self, channel, relay, buzzer):
        '''
            Tick the blink behavior.
            :param channel: Channel to tick the blink behavior for
            :param relay: Relay to tick the blink behavior for
            :param buzzer: Buzzer to tick the blink behavior for
        '''
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
                        print(f"<mh#sys#channel {channel.index + 1} off#end>")
                        return

                relay.write(True, buzzer)
                self.blink_phase = True
                self.start_time = now

    def get_status_str(self, channel, relay):
        '''
            Get the status string for the blink behavior.
            :param channel: Channel to get the status string for
            :param relay: Relay to get the status string for
            :return: Status string for the blink behavior
        '''
        state_str = "ON" if relay.state else "OFF"
        phase_str = "ON" if self.blink_phase else "OFF"
        return f"Channel {channel.index + 1}: {state_str} (Blink, count: {self.blink_count}, phase: {phase_str})"
