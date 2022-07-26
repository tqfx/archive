#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import liba

print("version", liba.version())
print("major:", liba.version_major())
print("minor:", liba.version_minor())
print("patch:", liba.version_patch())
