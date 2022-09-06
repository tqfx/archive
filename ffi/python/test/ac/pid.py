#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())
prefix = os.path.join(sys.path[0], "build")
if not os.path.exists(prefix):
    os.mkdir(prefix)
try:
    import libac as a
    import numpy as np
    import matplotlib.pyplot as plt
except Exception as e:
    print(e)
    exit()


class TF:
    def __init__(self, num, den) -> None:
        self.num = np.array(num, dtype=float)
        self.den = np.array(den, dtype=float)[1:]
        self.u = np.array(len(self.num) * [0.0], dtype=float)
        self.y = np.array(len(self.den) * [0.0], dtype=float)

    def __call__(self, u: float) -> float:
        self.u = np.roll(self.u, 1)
        self.u[0] = u
        y = self.num @ self.u - self.den @ self.y  # type: ignore
        self.y = np.roll(self.y, 1)
        self.y[0] = y
        return y


Ts = 0.001
data = np.arange(0, 0.2, Ts)

try:
    import control.matlab as ct

    sysc = ct.tf(133, [1, 25, 0])
    sysd = ct.c2d(sysc, Ts)
    print(sysc, sysd)

    [[num]], [[den]] = ct.tfdata(sysd)
except ModuleNotFoundError:
    num = [6.59492796e-05, 6.54019884e-05]
    den = [1.0, -1.97530991, 0.97530991]
except Exception as e:
    print(e)
    exit()

MIN = -10
MAX = +10

kp = 10.0
ki = 0.01
kd = 0.24

pid = a.pid(Ts, MIN, MAX).kpid(kp, ki, kd)

r = 1.0
setpoint = [r] * len(data)

title = "Proportional Integral Derivative Position"

y = 0.0
error1 = []
feedback1 = []
tf = TF(num, den)
pid.pos(MAX)
for i in data:
    u = pid(r, y)
    y = tf(u)
    feedback1.append(y)
    error1.append(r - y)

y = 0.0
error2 = []
feedback2 = []
tf = TF(num, den)
e = [0.0, 0.0, 0.0]
x = [0.0, 0.0, 0.0]
for i in data:
    e = np.roll(e, 1)
    e[0] = r - y
    x[0] = e[0]
    x[1] += e[0] * ki * Ts
    x[2] = (e[0] - e[1]) / Ts
    u = kp * x[0] + x[1] + kd * x[2]
    if u < MIN:
        u = MIN
    elif u > MAX:
        u = MAX
    y = tf(u)
    feedback2.append(y)
    error2.append(r - y)

plt.figure(title)
plt.subplot(211)
plt.title(title)
plt.plot(data, setpoint, "r-", data, feedback1, "b-", data, feedback2, "g-")
plt.ylabel("r - y")
plt.grid(True)
plt.subplot(212)
plt.plot(data, error1, "b-", data, error2, "g-")
plt.ylabel("error")
plt.xlabel('time(s)')
plt.grid(True)
plt.savefig(os.path.join(prefix, "pid_pos.png"))

title = "Proportional Integral Derivative Increment"

y = 0.0
error1 = []
feedback1 = []
tf = TF(num, den)
pid.inc()
for i in data:
    u = pid(r, y)
    y = tf(u)
    feedback1.append(y)
    error1.append(r - y)

s = 0.0
y = 0.0
error2 = []
feedback2 = []
tf = TF(num, den)
e = [0.0, 0.0, 0.0]
x = [0.0, 0.0, 0.0]
for i in data:
    e = np.roll(e, 1)
    e[0] = r - y
    x[0] = e[0] - e[1]
    x[1] = e[0] * Ts
    x[2] = (e[0] + e[2] - e[1] * 2) / Ts
    s += kp * x[0] + ki * x[1] + kd * x[2]
    u = s
    if u < MIN:
        u = MIN
    elif u > MAX:
        u = MAX
    y = tf(u)
    feedback2.append(y)
    error2.append(r - y)

plt.figure(title)
plt.subplot(211)
plt.title(title)
plt.plot(data, setpoint, "r-", data, feedback1, "b-", data, feedback2, "g-")
plt.ylabel("r - y")
plt.grid(True)
plt.subplot(212)
plt.plot(data, error1, "b-", data, error2, "g-")
plt.ylabel("error")
plt.xlabel('time(s)')
plt.grid(True)
plt.savefig(os.path.join(prefix, "pid_inc.png"))
