#!/usr/bin/env python
'''
 @file lpf.py
 @brief test Low Pass Filter
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
import os
import sys

sys.path.insert(0, os.getcwd())
prefix = os.path.join(sys.path[0], "build")
if not os.path.exists(prefix):
    os.mkdir(prefix)
try:
    import a
    import numpy as np
    import matplotlib.pyplot as plt
except Exception as e:
    print(e)
    exit()

title = "Low Pass Filter"
data = np.arange(0, np.pi * 2, 0.001)
lpf = a.lpf(0.5, 0.001)

plt.figure(title)
plt.title(title)
plt.plot(data, np.sin(data), "r-", data, lpf(np.sin(data)), "b-")
plt.ylabel("o")
plt.xlabel('i')
plt.savefig(os.path.join(prefix, "lpf.png"))
