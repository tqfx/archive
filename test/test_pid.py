#!/usr/bin/env python
'''
 @file           test_pid.py
 @brief          test Proportional Integral Derivative Algorithm
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Affero General Public License as published
 by the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 \n \n
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Affero General Public License for more details.
 \n \n
 You should have received a copy of the GNU Affero General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
