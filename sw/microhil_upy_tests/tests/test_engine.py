# -*- coding: UTF-8 -*-
import io
import contextlib
import unittest
from tests.mocks import mock_clear_system_states, Pin, mock_np_colors, mock_wdt_fed
from microhil.engine import MicroHil

class TestEngine(unittest.TestCase):
    def setUp(self):
        mock_clear_system_states()
        self.hil = MicroHil()

    def test_sys_commands(self):
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#sys#id#end")
        self.assertEqual(f.getvalue(), "<mh#sys#mh:333:2023:0#end>\n")

        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#sys#version#end")
        self.assertEqual(f.getvalue(), "<mh#sys#microHIL v1.0.0#end>\n")

    def test_sys_reset(self):
        import tests.mocks as mocks
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#sys#reset#end")
        self.assertEqual(f.getvalue(), "<mh#sys#system resetting...#end>\n")
        self.assertTrue(mocks.mock_machine_reset_called)

    def test_channel_control(self):
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#ch#1#on#end")
        self.assertEqual(f.getvalue(), "<mh#sys#channel 1 on#end>\n")
        self.assertEqual(Pin.mock_pins[21].value(), 0)

        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#ch#1#off#end")
        self.assertEqual(f.getvalue(), "<mh#sys#channel 1 off#end>\n")
        self.assertEqual(Pin.mock_pins[21].value(), 1)

    def test_all_channels(self):
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#all#on#end")
        self.assertEqual(f.getvalue(), "<mh#sys#all channels on#end>\n")
        for pin_num in [21, 20, 19, 18, 17, 16, 15, 14]:
            self.assertEqual(Pin.mock_pins[pin_num].value(), 0)
        self.assertEqual(mock_np_colors, [(204, 204, 204)])

        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#all#off#end")
        self.assertEqual(f.getvalue(), "<mh#sys#all channels off#end>\n")
        for pin_num in [21, 20, 19, 18, 17, 16, 15, 14]:
            self.assertEqual(Pin.mock_pins[pin_num].value(), 1)
        self.assertEqual(mock_np_colors, [(0, 0, 0)])

    def test_mask_command(self):
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#all#mask#10101010#end")
        self.assertEqual(f.getvalue(), "<mh#sys#channels mask applied: 10101010#end>\n")
        self.assertEqual(Pin.mock_pins[21].value(), 0)
        self.assertEqual(Pin.mock_pins[20].value(), 1)
        self.assertEqual(Pin.mock_pins[19].value(), 0)
        self.assertEqual(Pin.mock_pins[18].value(), 1)
        self.assertEqual(Pin.mock_pins[17].value(), 0)
        self.assertEqual(Pin.mock_pins[16].value(), 1)
        self.assertEqual(Pin.mock_pins[15].value(), 0)
        self.assertEqual(Pin.mock_pins[14].value(), 1)

    def test_timer_command(self):
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#ch#3#tmr#15#end")
        self.assertEqual(f.getvalue(), "<mh#sys#channel 3 timer started: 15 seconds#end>\n")

    def test_pulse_command(self):
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#ch#5#pulse#250#end")
        self.assertEqual(f.getvalue(), "<mh#sys#channel 5 pulse started: 250 ms#end>\n")

    def test_blink_command(self):
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#ch#2#blink#100#200#5#end")
        self.assertEqual(f.getvalue(), "<mh#sys#channel 2 blink started: on=100 ms, off=200 ms, count=5#end>\n")

    def test_all_status(self):
        f = io.StringIO()
        with contextlib.redirect_stdout(f):
            self.hil.dispatch("mh#all#stat#end")
        self.assertEqual(f.getvalue(), "<mh#sys#channels: 1:OFF 2:OFF 3:OFF 4:OFF 5:OFF 6:OFF 7:OFF 8:OFF#end>\n")
