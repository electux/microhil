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

from .relay import Relay
from .behaviors.toggle import ToggleBehavior
from .behaviors.timer import TimerBehavior
from .behaviors.pulse import PulseBehavior
from .behaviors.blink import BlinkBehavior


class RelayChannel:
    '''
        High-level controller for a relay channel that delegates to behavioral strategies.
    '''
    def __init__(self, pin_num, index):
        '''
            Initializes the relay channel.
            :param pin_num: Pin number for the relay.
            :param index: Index of the relay.
            :exceptions: None.
        '''
        self.relay = Relay(pin_num)
        self.index = index
        self.pin = self.relay.pin
        self.behavior = ToggleBehavior()

    @property
    def state(self):
        '''
            Exposes current physical relay state.
            :return: Current physical relay state.
            :exceptions: None.
        '''
        return self.relay.state

    def set_behavior(self, behavior, buzzer, turn_on=False):
        '''
            Changes the active behavior strategy.
            :param behavior: Behavior to set.
            :param buzzer: Buzzer to set.
            :param turn_on: Whether to turn the relay on.
            :exceptions: None.
        '''
        self.behavior = behavior
        self.relay.write(turn_on, buzzer)

    def set_state(self, on, buzzer):
        '''
            Switches channel state using ToggleBehavior.
            :param on: Whether to turn the relay on.
            :param buzzer: Buzzer to set.
            :exceptions: None.
        '''
        self.set_behavior(ToggleBehavior(), buzzer, turn_on=on)

    def start_timer(self, seconds, buzzer):
        '''
            Starts the timer behavior.
            :param seconds: Time to turn the relay OFF.
            :param buzzer: Buzzer to set.
            :exceptions: None.
        '''
        self.set_behavior(TimerBehavior(seconds), buzzer, turn_on=True)

    def start_pulse(self, duration_ms, buzzer):
        '''
            Starts the pulse behavior.
            :param duration_ms: Duration of the pulse in milliseconds.
            :param buzzer: Buzzer to set.
            :exceptions: None.
        '''
        self.set_behavior(PulseBehavior(duration_ms), buzzer, turn_on=True)

    def start_blink(self, on_ms, off_ms, count, buzzer):
        '''
            Starts the blink behavior.
            :param on_ms: Duration of the blink in milliseconds.
            :param off_ms: Duration of the blink in milliseconds.
            :param count: Number of blinks.
            :param buzzer: Buzzer to set.
            :exceptions: None.
        '''
        self.set_behavior(BlinkBehavior(on_ms, off_ms, count), buzzer, turn_on=True)

    def tick(self, buzzer):
        '''
            Delegates non-blocking update to active behavior strategy.
            :param buzzer: Buzzer to set.
            :exceptions: None.
        '''
        self.behavior.tick(self, self.relay, buzzer)

    def get_status_str(self):
        '''
            Delegates status string query to active behavior strategy.
            :return: Status string for the behavior.
            :exceptions: None.
        '''
        return self.behavior.get_status_str(self, self.relay)
