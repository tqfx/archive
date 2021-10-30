#!/usr/bin/env python
'''
 @file test_polytrack.py
 @brief test polynomial trajectory
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
'''
import os
from sys import argv

try:
    import numpy as np
    import matplotlib.pyplot as plt
    from liba import *
except Exception as e:
    print(e)
    exit()

t = (0, 1)
q = (0, 1)
data = np.arange(t[0], t[1], 0.01)
source = (t[0], q[0], 0, 0, 0)
target = (t[1], q[1], 1, 1, 1)

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
