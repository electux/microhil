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
    Blink command handler of microhil.
'''

from commands.base import BaseCommand

class BlinkCommand(BaseCommand):
    '''
        Command handler for blinking execution on a channel.
    '''
    def match(self, cmd_str):
        return cmd_str.startswith("mh#ch#") and "#blink#" in cmd_str

    def execute(self, board, cmd_str):
        parts = cmd_str.split("#")
        ch_idx = int(parts[2]) - 1
        on_time = int(parts[4])
        off_time = int(parts[5])
        count = int(parts[6])
        if 0 <= ch_idx < len(board.channels):
            board.channels[ch_idx].start_blink(on_time, off_time, count, board.buzzer)
            print("<mh#sys#channel {} blink started: on={} ms, off={} ms, count={}#end>".format(
                parts[2], on_time, off_time, count
            ))
