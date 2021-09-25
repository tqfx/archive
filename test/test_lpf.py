#!/usr/bin/env python
'''
 @file           test_lpf.py
 @brief          test Low Pass Filter
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
