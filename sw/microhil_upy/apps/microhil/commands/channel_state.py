# -*- coding: UTF-8 -*-

'''
Module
    channel_state.py
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
    Channel state toggle command handler of microhil.
'''


class ChannelStateCommand:
    '''
        Command handler for channel state toggling.
    '''
    def match(self, cmd_str):
        '''
            Checks if the command string matches the Channel State command.
            :param cmd_str: Command string to match.
            :return: True if the command string matches the Channel State command, False otherwise.
            :exceptions: None.
        '''
        return cmd_str.startswith("mh#ch#") and (cmd_str.endswith("#on#end") or cmd_str.endswith("#off#end"))

    def execute(self, board, cmd_str):
        '''
            Executes the Channel State command.
            :param board: Board to execute the command on.
            :param cmd_str: Command string to execute.
            :return: None.
            :exceptions: None.
        '''
        parts = cmd_str.split("#")
        ch_idx = int(parts[2]) - 1
        on = (parts[3] == "on")

        if 0 <= ch_idx < len(board.channels):
            board.channels[ch_idx].set_state(on, board.buzzer)
            print(f"<mh#sys#channel {parts[2]} {'on' if on else 'off'}#end>")
