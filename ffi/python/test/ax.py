#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import libax

print("version", libax.version())
print("major:", libax.version_major())
print("minor:", libax.version_minor())
print("patch:", libax.version_patch())
