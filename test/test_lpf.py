#!/usr/bin/env python
'''
 @file           test_lpf.py
 @brief          test Low Pass Filter
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
'''
import os
import numpy as np
import matplotlib.pyplot as plt
from sys import argv
from liba import *

data = np.arange(0, 64 * np.pi, 0.01)

prefix = "build"
os.chdir(os.path.dirname(argv[0]))
if not os.path.exists(prefix):
    os.mkdir(prefix)

a = a_lpf(1, 0.01).reset()

plt.figure("Low Pass Filter")
plt.title("Low Pass Filter")
plt.plot(data, np.sin(data), "r-", data, tuple(a.lpf(np.sin(data))), "b-")
plt.ylabel("o")
plt.xlabel('i')
plt.savefig(prefix + "/lpf.png")
