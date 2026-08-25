# -*- coding: UTF-8 -*-

'''
Module
    all_on.py
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
    All ON command handler of microhil.
'''


class AllOnCommand:
    '''
        Command handler for switching all channels ON.
    '''
    def match(self, cmd_str):
        '''
            Checks if the command string matches the All ON command.
            :param cmd_str: Command string to match.
            :return: True if the command string matches the All ON command, False otherwise.
            :exceptions: None.
        '''
        return cmd_str == "mh#all#on#end"

    def execute(self, board, cmd_str):
        '''
            Executes the All ON command.
            :param board: Board to execute the command on.
            :param cmd_str: Command string to execute.
            :return: None.
            :exceptions: None.
        '''
        for ch in board.channels:
            ch.set_state(True, board.buzzer)

        board.set_led(255, 255, 255)
        print("<mh#sys#all channels on#end>")
