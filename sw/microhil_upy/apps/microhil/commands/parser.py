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
        self.state = "idle"
        self.buf = ""
        self.poll = uselect.poll()
        self.poll.register(sys.stdin, uselect.POLLIN)

    def process_char(self, c):
        '''
            Processes a character.

            :param c: Character to process.
            :exceptions: None.
        '''
        if c in ('\r', '\n'):
            return None

        if c == '<':
            self.state = "receiving"
            self.buf = ""
            return None

        if self.state == "receiving":
            if c == '>':
                cmd = self.buf
                self.state = "idle"
                self.buf = ""

                return cmd

            self.buf += c

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
