import sys
import time as _original_time
from . import mocks

# Register machine, neopixel, and uselect mocks
sys.modules['machine'] = mocks
sys.modules['neopixel'] = mocks
sys.modules['uselect'] = mocks

# Implement time wrapper to allow MicroPython APIs (ticks_ms, sleep_ms, sleep)
# while falling back to standard library time module for unittest/logging dependencies.
class TimeMockWrapper:
    def ticks_ms(self):
        return mocks.ticks_ms()

    def ticks_diff(self, t1, t2):
        return mocks.ticks_diff(t1, t2)

    def sleep_ms(self, ms):
        mocks.sleep_ms(ms)

    def sleep(self, sec):
        mocks.sleep(sec)

    def __getattr__(self, name):
        return getattr(_original_time, name)

sys.modules['time'] = TimeMockWrapper()

# Register micropython mock
class MockMicroPython:
    @staticmethod
    def const(x):
        return x

sys.modules['micropython'] = MockMicroPython
