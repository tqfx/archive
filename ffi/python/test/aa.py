#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import libaa

print("version", libaa.version())
print("major:", libaa.version_major())
print("minor:", libaa.version_minor())
print("patch:", libaa.version_patch())
