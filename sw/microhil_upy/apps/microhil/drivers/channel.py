# -*- coding: UTF-8 -*-

'''
Module
    channel.py
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
    Relay channel controller of microhil.
'''

from drivers.relay import Relay
from drivers.behaviors.toggle import ToggleBehavior
from drivers.behaviors.timer import TimerBehavior
from drivers.behaviors.pulse import PulseBehavior
from drivers.behaviors.blink import BlinkBehavior


class RelayChannel:
    '''
        High-level controller for a relay channel that delegates to behavioral strategies.
    '''
    def __init__(self, pin_num, index):
        '''
            Initializes the relay channel.
        '''
        self.relay = Relay(pin_num)
        self.index = index
        # Expose self.pin for backwards compatibility
        self.pin = self.relay.pin
        self.behavior = ToggleBehavior()

    @property
    def state(self):
        '''
            Exposes current physical relay state.
        '''
        return self.relay.state

    def set_behavior(self, behavior, buzzer, turn_on=False):
        '''
            Changes the active behavior strategy.
        '''
        self.behavior = behavior
        self.relay.write(turn_on, buzzer)

    def set_state(self, on, buzzer):
        '''
            Switches channel state using ToggleBehavior.
        '''
        self.set_behavior(ToggleBehavior(), buzzer, turn_on=on)

    def start_timer(self, seconds, buzzer):
        '''
            Starts the timer behavior.
        '''
        self.set_behavior(TimerBehavior(seconds), buzzer, turn_on=True)

    def start_pulse(self, duration_ms, buzzer):
        '''
            Starts the pulse behavior.
        '''
        self.set_behavior(PulseBehavior(duration_ms), buzzer, turn_on=True)

    def start_blink(self, on_ms, off_ms, count, buzzer):
        '''
            Starts the blink behavior.
        '''
        self.set_behavior(BlinkBehavior(on_ms, off_ms, count), buzzer, turn_on=True)

    def tick(self, buzzer):
        '''
            Delegates non-blocking update to active behavior strategy.
        '''
        self.behavior.tick(self, self.relay, buzzer)

    def get_status_str(self):
        '''
            Delegates status string query to active behavior strategy.
        '''
        return self.behavior.get_status_str(self, self.relay)
