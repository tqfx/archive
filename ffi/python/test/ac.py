#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import libac

print("version", libac.version())
print("major:", libac.version_major())
print("minor:", libac.version_minor())
print("patch:", libac.version_patch())

print(libac.inv_sqrt(1))
