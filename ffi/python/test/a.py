#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import liba

print("version", liba.version())
