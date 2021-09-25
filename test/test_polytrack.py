#!/usr/bin/env python
'''
 @file           test_polytrack.py
 @brief          test polynomial trajectory
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

t = (0, 1)
q = (0, 1)
data = np.arange(t[0], t[1], 0.01)
source = (t[0], q[0], 0, 0, 0)
target = (t[1], q[1], 0, 0, 0)

prefix = "build"
os.chdir(os.path.dirname(argv[0]))
if not os.path.exists(prefix):
    os.mkdir(prefix)

a = a_polytrack3(source, target)
label = a.label()

plt.figure("3 polynomial trajectory")
plt.subplot(311)
plt.title("cubic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, tuple(a.pos(data)), "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, tuple(a.vec(data)), "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, tuple(a.acc(data)), "g-", label=label[2])
plt.legend()

plt.xlabel('t')
plt.savefig(prefix + "/trajectory_polynomial_3.png")

a = a_polytrack5(source, target)
label = a.label()

plt.figure("5 polynomial trajectory")
plt.subplot(311)
plt.title("quintic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, tuple(a.pos(data)), "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, tuple(a.vec(data)), "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, tuple(a.acc(data)), "g-", label=label[2])
plt.legend()

plt.xlabel('t')
plt.savefig(prefix + "/trajectory_polynomial_5.png")

a = a_polytrack7(source, target)
label = a.label()

plt.figure("7 polynomial trajectory")
plt.subplot(411)
plt.title("hepta polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, tuple(a.pos(data)), "r-", label=label[0])
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, tuple(a.vec(data)), "b-", label=label[1])
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, tuple(a.acc(data)), "g-", label=label[2])
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, tuple(a.jer(data)), "k-", label=label[3])
plt.legend()

plt.xlabel('t')
plt.savefig(prefix + "/trajectory_polynomial_7.png")
