# -*- coding: UTF-8 -*-

'''
Module
    id.py
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
    ID command handler of microhil.
'''


class IdCommand:
    '''
        Command handler for 'id' query.
    '''
    def match(self, cmd_str):
        '''
            Checks if the command string matches the ID command.
            :param cmd_str: Command string to match.
            :return: True if the command string matches the ID command, False otherwise.
            :exceptions: None.
        '''
        return cmd_str == "mh#sys#id#end"

    def execute(self, board, cmd_str):
        '''
            Executes the ID command.
            :param board: Board to execute the command on.
            :param cmd_str: Command string to execute.
            :return: None.
            :exceptions: None.
        '''
        print("<mh#sys#mh:333:2023:0#end>")
