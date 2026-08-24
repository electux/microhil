# -*- coding: UTF-8 -*-

'''
Module
    base.py
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
    Base behavior class of microhil.
'''

class BaseBehavior:
    '''
        Base interface for relay channel behaviors.
    '''
    def tick(self, channel, relay, buzzer):
        '''
            Processes non-blocking timing updates.
        '''
        pass

    def get_status_str(self, channel, relay):
        '''
            Returns status string for this behavior state.
        '''
        raise NotImplementedError
