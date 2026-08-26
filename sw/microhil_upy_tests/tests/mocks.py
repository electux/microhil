# -*- coding: UTF-8 -*-
'''
Mock MicroPython standard libraries for host python unit tests.
'''

# 1. Ticks and time mocks
_mock_time_ms = 0

def ticks_ms():
    return _mock_time_ms

def ticks_diff(t1, t2):
    return t1 - t2

def sleep_ms(ms):
    global _mock_time_ms
    _mock_time_ms += ms

def sleep(sec):
    sleep_ms(sec * 1000)

def mock_set_time(ms):
    global _mock_time_ms
    _mock_time_ms = ms

# 2. Machine module mock elements
class Pin:
    OUT = 1
    IN = 0
    
    mock_pins = {}  # Global dict to inspect pin states
    
    def __init__(self, pin_num, mode=None):
        self.pin_num = pin_num
        self.mode = mode
        self.val = 1  # Active-low default high (OFF)
        Pin.mock_pins[pin_num] = self
        
    def high(self):
        self.val = 1
        
    def low(self):
        self.val = 0
        
    def value(self, val=None):
        if val is not None:
            self.val = val
        return self.val

class PWM:
    def __init__(self, pin):
        self.pin = pin
        self._freq = 0
        self._duty = 0
        
    def freq(self, val=None):
        if val is not None:
            self._freq = val
        return self._freq
        
    def duty_u16(self, val=None):
        if val is not None:
            self._duty = val
        return self._duty

mock_wdt_fed = False
mock_wdt_initialized = False

class WDT:
    def __init__(self, timeout=5000):
        global mock_wdt_initialized
        mock_wdt_initialized = True
        self.timeout = timeout
        
    def feed(self):
        global mock_wdt_fed
        mock_wdt_fed = True

mock_machine_reset_called = False

def reset():
    global mock_machine_reset_called
    mock_machine_reset_called = True

# 3. NeoPixel module mock elements
mock_np_colors = []

class NeoPixel:
    def __init__(self, pin, n):
        self.pin = pin
        self.n = n
        self.pixels = [(0, 0, 0)] * n
        
    def __setitem__(self, index, val):
        self.pixels[index] = val
        
    def __getitem__(self, index):
        return self.pixels[index]
        
    def write(self):
        global mock_np_colors
        mock_np_colors.clear()
        mock_np_colors.extend(self.pixels)

# 4. uselect module mock elements
mock_input_stream = ""
mock_poll_triggered = False

class Poll:
    def __init__(self):
        self.registered = []
        
    def register(self, obj, flags=None):
        self.registered.append((obj, flags))
        
    def poll(self, timeout=None):
        global mock_input_stream
        if len(mock_input_stream) > 0:
            return [(self.registered[0][0], 1)] # POLLIN
        return []

def poll():
    return Poll()

POLLIN = 1

def mock_push_input(chars):
    global mock_input_stream
    mock_input_stream += chars

def mock_clear_input():
    global mock_input_stream
    mock_input_stream = ""

def mock_read_char():
    global mock_input_stream
    if len(mock_input_stream) > 0:
        c = mock_input_stream[0]
        mock_input_stream = mock_input_stream[1:]
        return c
    return ""

# 5. Clear global state helper
def mock_clear_system_states():
    global _mock_time_ms, mock_wdt_fed, mock_wdt_initialized, mock_np_colors, mock_machine_reset_called
    _mock_time_ms = 0
    mock_wdt_fed = False
    mock_wdt_initialized = False
    mock_machine_reset_called = False
    mock_np_colors.clear()
    Pin.mock_pins.clear()
    mock_clear_input()
