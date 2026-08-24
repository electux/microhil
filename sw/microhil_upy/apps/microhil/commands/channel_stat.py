# -*- coding: UTF-8 -*-

'''
Module
    channel_stat.py
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
    Individual channel status query handler of microhil.
'''

from commands.base import BaseCommand

class ChannelStatCommand(BaseCommand):
    '''
        Command handler for querying individual channel state/timings.
    '''
    def match(self, cmd_str):
        return cmd_str.startswith("mh#ch#") and cmd_str.endswith("#stat#end")

    def execute(self, board, cmd_str):
        parts = cmd_str.split("#")
        ch_idx = int(parts[2]) - 1
        if 0 <= ch_idx < len(board.channels):
            status_str = board.channels[ch_idx].get_status_str()
            print("<mh#sys#{}#end>".format(status_str))
