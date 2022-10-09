#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())

import liba as a

k = [1, 2, 3]
print(k, a.poly(k, *k))
print(k, a.poly(2, *k))
print(k, a.polyr(k, *k))
print(k, a.polyr(2, *k))
