# -*- coding: UTF-8 -*-

'''
Module
    mask.py
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
    Binary channel mask command handler of microhil.
'''

from commands.base import BaseCommand

class MaskCommand(BaseCommand):
    '''
        Command handler for applying binary channel states mask.
    '''
    def match(self, cmd_str):
        return cmd_str.startswith("mh#all#mask#") and cmd_str.endswith("#end")

    def execute(self, board, cmd_str):
        mask_str = cmd_str[12:20]
        for i, bit in enumerate(mask_str):
            if i < len(board.channels):
                board.channels[i].set_state(bit == "1", board.buzzer)
        print("<mh#sys#channels mask applied: {}#end>".format(mask_str))
