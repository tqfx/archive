#!/usr/bin/env python
'''
 @file           test_pid.py
 @brief          test Proportional Integral Derivative Algorithm
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
'''
import math
import os
import numpy as np
import matplotlib.pyplot as plt
from sys import argv
from liba import *

data = np.arange(0, 1, 0.01)

prefix = "build"
os.chdir(os.path.dirname(argv[0]))
if not os.path.exists(prefix):
    os.mkdir(prefix)

f = lambda s: 30 / (250 * s + 1) * math.exp(-20 * s)


a = a_pid(0, 1, 0.1, 0, -1000, 1000, 1000).reset()

setpoint = []
faceback = []
x = 0
for i in data:
    x = a.pid(f(x), 100)
    setpoint.append(100)
    faceback.append(x)

plt.figure("Proportional Integral Derivative")
plt.title("Proportional Integral Derivative")
plt.plot(data, setpoint, "r-", data, faceback, "b-")
plt.ylabel("o")
plt.xlabel('i')
plt.grid(True)
plt.savefig(prefix + "/pid.png")
