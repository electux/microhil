# -*- coding: UTF-8 -*-

'''
Module
    parser.py
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
    Command parser of microhil.
'''

import sys
import uselect
from micropython import const

_STATE_IDLE = const(0)
_STATE_RECEIVING = const(1)

class CommandParser:
    '''
        Defines control of a command parser.

        It defines:

            :methods:
                | __init__ - Initializes the command parser.
                | process_char - Processes a character.
                | get_command - Polls stdin and returns parsed command.
    '''
    def __init__(self):
        '''
            Initializes the command parser.

            :exceptions: None.
        '''
        self.state = _STATE_IDLE
        self.buf = bytearray(64)
        self.buf_idx = 0
        self.poll = uselect.poll()
        self.poll.register(sys.stdin, uselect.POLLIN)

    def process_char(self, c):
        '''
            Processes a character.

            :param c: Character to process.
            :exceptions: None.
        '''
        if c == '\r' or c == '\n':
            return None

        if c == '<':
            self.state = _STATE_RECEIVING
            self.buf_idx = 0
            return None

        if self.state == _STATE_RECEIVING:
            if c == '>':
                cmd = self.buf[:self.buf_idx].decode()
                self.state = _STATE_IDLE
                return cmd

            if self.buf_idx < 64:
                self.buf[self.buf_idx] = ord(c)
                self.buf_idx += 1

        return None

    def get_command(self):
        '''
            Polls stdin and reads characters until a command is parsed.

            :exceptions: None.
        '''
        while self.poll.poll(0):
            c = sys.stdin.read(1)
            cmd = self.process_char(c)

            if cmd is not None:
                return cmd

        return None
