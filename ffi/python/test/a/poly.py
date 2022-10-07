#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import liba as a

b = [1, 2, 3]
print(b, a.poly(2, *b))
