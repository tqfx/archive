#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import libaa

print("version", libaa.version())
