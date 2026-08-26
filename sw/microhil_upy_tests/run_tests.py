# -*- coding: UTF-8 -*-
import os
import sys
import unittest

# Resolve and add microhil apps directory to python search path
current_dir = os.path.dirname(os.path.abspath(__file__))
apps_dir = os.path.join(current_dir, '..', 'microhil_upy', 'apps')
sys.path.insert(0, apps_dir)

# Discover and run all tests under the 'tests' directory
if __name__ == '__main__':
    suite = unittest.defaultTestLoader.discover(os.path.join(current_dir, 'tests'))
    runner = unittest.TextTestRunner()
    result = runner.run(suite)
    sys.exit(not result.wasSuccessful())
