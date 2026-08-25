# -*- coding: UTF-8 -*-

'''
Module
    toggle.py
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
    Toggle behavior class of microhil.
'''


class ToggleBehavior:
    '''
        Standard toggle ON/OFF behavior with no timings.
    '''
    def tick(self, channel, relay, buzzer):
        '''
            Tick the toggle behavior.
            :param channel: Channel to tick the toggle behavior for.
            :param relay: Relay to tick the toggle behavior for.
            :param buzzer: Buzzer to tick the toggle behavior for.
            :exceptions: None.
        '''
        pass

    def get_status_str(self, channel, relay):
        '''
            Get the status string for the toggle behavior.
            :param channel: Channel to get the status string for.
            :param relay: Relay to get the status string for.
            :return: Status string for the toggle behavior.
            :exceptions: None.
        '''
        state_str = "ON" if relay.state else "OFF"

        return f"Channel {channel.index + 1}: {state_str} (Toggle)"
