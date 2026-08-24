# -*- coding: UTF-8 -*-

'''
Module
    engine.py
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
    Main engine of microhil.
'''

# Import local modules
from drivers.buzzer import Buzzer
from drivers.channel import RelayChannel
from drivers.led import StatusLED
from commands.parser import CommandParser
from commands.id import IdCommand
from commands.version import VersionCommand
from commands.reset import ResetCommand
from commands.all_on import AllOnCommand
from commands.all_off import AllOffCommand
from commands.all_stat import AllStatCommand
from commands.channel_state import ChannelStateCommand
from commands.timer import TimerCommand
from commands.pulse import PulseCommand
from commands.blink import BlinkCommand
from commands.channel_stat import ChannelStatCommand
from commands.mask import MaskCommand


class MicroHil:
    '''
        Defines control of the microhil.

        It defines:

            :methods:
                | __init__ - Initializes the microhil.
                | set_led - Writes the status LED.
                | dispatch - Dispatches the command.
                | tick - Ticks the engine and processes incoming commands.
    '''
    def __init__(self, pin=13, num=1, brightness=0.8):
        self.led = StatusLED(pin, num, brightness)
        self.buzzer = Buzzer(6)
        relay_pins = [21, 20, 19, 18, 17, 16, 15, 14]
        self.channels = [RelayChannel(p, i) for i, p in enumerate(relay_pins)]
        self.parser = CommandParser()
        self.commands = [
            IdCommand(),
            VersionCommand(),
            ResetCommand(),
            AllOnCommand(),
            AllOffCommand(),
            AllStatCommand(),
            ChannelStateCommand(),
            TimerCommand(),
            PulseCommand(),
            BlinkCommand(),
            ChannelStatCommand(),
            MaskCommand()
        ]
        self.buzzer.beep_start()

    def set_led(self, r, g, b):
        '''
            Delegates write to the LED driver.
        '''
        self.led.set_color(r, g, b)

    def dispatch(self, cmd):
        '''
            Dispatches a parsed command using the registered command handlers.

            :param cmd: Parsed command string.
            :exceptions: None.
        '''
        for c in self.commands:
            if c.match(cmd):
                c.execute(self, cmd)
                return

    def tick(self):
        '''
            Ticks the engine, updating timers/pulses/blinking on all channels
            and processing incoming command requests non-blockingly.

            :exceptions: None.
        '''
        for ch in self.channels:
            ch.tick(self.buzzer)

        self.buzzer.tick()
        cmd = self.parser.get_command()

        while cmd is not None:
            self.dispatch(cmd)
            cmd = self.parser.get_command()

if __name__=='__main__':
    board = MicroHil()

    while True:
        board.tick()
