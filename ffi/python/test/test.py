#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import a
import aa

if a.version() != aa.version():
    print("version", a.version(), aa.version())
