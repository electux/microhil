# -*- coding: UTF-8 -*-
import unittest
from unittest.mock import patch
from tests.mocks import mock_push_input, mock_clear_input, mock_read_char
from microhil.commands.parser import CommandParser

class TestParser(unittest.TestCase):
    def setUp(self):
        mock_clear_input()
        self.parser = CommandParser()

    @patch('sys.stdin.read')
    def test_well_formed_command(self, mock_read):
        mock_push_input("<mh#ch#1#on#end>")
        mock_read.side_effect = lambda n: mock_read_char()
        
        cmd = self.parser.get_command()
        self.assertEqual(cmd, "mh#ch#1#on#end")

    @patch('sys.stdin.read')
    def test_incomplete_command(self, mock_read):
        mock_push_input("<mh#ch#1")
        mock_read.side_effect = lambda n: mock_read_char()
        
        cmd = self.parser.get_command()
        self.assertIsNone(cmd)

    @patch('sys.stdin.read')
    def test_ignore_whitespace(self, mock_read):
        mock_push_input("\r\n<mh#all#on#end>\n")
        mock_read.side_effect = lambda n: mock_read_char()
        
        cmd = self.parser.get_command()
        self.assertEqual(cmd, "mh#all#on#end")

    def test_process_char_overflow(self):
        self.parser.process_char('<')
        for _ in range(70):
            self.parser.process_char('A')
        cmd = self.parser.process_char('>')
        self.assertEqual(cmd, 'A' * 64)
