#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import a

print("version", a.version())

import aa

print("version", aa.version())
