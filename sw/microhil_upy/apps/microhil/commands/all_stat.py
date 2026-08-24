# -*- coding: UTF-8 -*-

'''
Module
    all_stat.py
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
    All channel states command handler of microhil.
'''

from commands.base import BaseCommand

class AllStatCommand(BaseCommand):
    '''
        Command handler for querying all channel states.
    '''
    def match(self, cmd_str):
        return cmd_str == "mh#all#stat#end"

    def execute(self, board, cmd_str):
        status_parts = []
        for i, ch in enumerate(board.channels):
            state_str = "ON" if ch.state else "OFF"
            status_parts.append("{}:{}".format(i + 1, state_str))
        print("<mh#sys#channels: {}#end>".format(" ".join(status_parts)))
