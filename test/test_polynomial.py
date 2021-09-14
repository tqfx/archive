#!/usr/bin/env python
'''
 @file           test.py
 @brief          This is test
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
from liba import *

pos = []
vec = []
acc = []
jer = []

data = np.arange(0, 8, 0.002)
source = (0, 0, 0, 0, 0)
target = (8, 10, 0, 0, 0)
prefix = "build"

if not os.path.exists(prefix):
    os.mkdir(prefix)

ploy = a_polynomial3(source, target)
label = ploy.label()
for i in data:
    pos.append(ploy.pos(i))
for i in data:
    vec.append(ploy.vec(i))
for i in data:
    acc.append(ploy.acc(i))

plt.figure("3 polynomial trajectory")
plt.subplot(311)
plt.title("cubic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, vec, "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.xlabel('t')
plt.savefig(prefix + "/trajectory_polynomial_cubic.png")

ploy = a_polynomial5(source, target)
label = ploy.label()
pos.clear()
for i in data:
    pos.append(ploy.pos(i))
vec.clear()
for i in data:
    vec.append(ploy.vec(i))
acc.clear()
for i in data:
    acc.append(ploy.acc(i))

plt.figure("5 polynomial trajectory")
plt.subplot(311)
plt.title("quintic polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(312)
plt.ylabel("Velocity")
plt.plot(data, vec, "b-", label=label[1])
plt.legend()

plt.subplot(313)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.xlabel('t')
plt.savefig(prefix + "/trajectory_polynomial_quintic.png")

ploy = a_polynomial7(source, target)

label = ploy.label()
pos.clear()
for i in data:
    pos.append(ploy.pos(i))
vec.clear()
for i in data:
    vec.append(ploy.vec(i))
acc.clear()
for i in data:
    acc.append(ploy.acc(i))
jer.clear()
for i in data:
    jer.append(ploy.jer(i))

plt.figure("7 polynomial trajectory")
plt.subplot(411)
plt.title("hepta polynomial trajectory")
plt.ylabel("Position")
plt.plot(data, pos, "r-", label=label[0])
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, vec, "b-", label=label[1])
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, acc, "g-", label=label[2])
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, jer, "k-", label=label[3])
plt.legend()

plt.xlabel('t')
plt.savefig(prefix + "/trajectory_polynomial_hepta.png")

plt.show()
