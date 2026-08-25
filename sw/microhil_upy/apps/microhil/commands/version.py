# -*- coding: UTF-8 -*-

'''
Module
    version.py
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
    Version command handler of microhil.
'''


class VersionCommand:
    '''
        Command handler for 'version' query.
    '''
    def match(self, cmd_str):
        '''
            Checks if the command string matches the Version command.
            :param cmd_str: Command string to match.
            :return: True if the command string matches the Version command, False otherwise.
            :exceptions: None.
        '''
        return cmd_str == "mh#sys#version#end"

    def execute(self, board, cmd_str):
        '''
            Executes the Version command.
            :param board: Board to execute the command on.
            :param cmd_str: Command string to execute.
            :exceptions: None.
        '''
        print("<mh#sys#microHIL v1.0.0#end>")
