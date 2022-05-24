#!/usr/bin/env python
'''
 @file fpid.py
 @brief test Fuzzy Proportional Integral Derivative Algorithm
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


NB = -3
NM = -2
NS = -1
ZO = 0
PS = +1
PM = +2
PB = +3

rkp = [
    [NB, NB, NM, NM, NS, ZO, ZO],
    [NB, NB, NM, NS, NS, ZO, PS],
    [NM, NM, NM, NS, ZO, PS, PS],
    [NM, NM, NS, ZO, PS, PM, PM],
    [NS, NS, ZO, PS, PS, PM, PM],
    [NS, ZO, PS, PM, PM, PM, PB],
    [ZO, ZO, PM, PM, PM, PB, PB],
]
rki = [
    [PB, PB, PM, PM, PS, ZO, ZO],
    [PB, PB, PM, PS, PS, ZO, ZO],
    [PB, PM, PS, PS, ZO, NS, NS],
    [PM, PM, PS, ZO, NS, NM, NM],
    [PM, PS, ZO, NS, NS, NM, NB],
    [ZO, ZO, NS, NS, NM, NB, NB],
    [ZO, ZO, NS, NM, NM, NB, NB],
]
rkd = [
    [NS, PS, PB, PB, PB, PM, NS],
    [NS, PS, PB, PM, PM, PS, ZO],
    [ZO, PS, PM, PM, PS, PS, ZO],
    [ZO, PS, PS, PS, PS, PS, ZO],
    [ZO, ZO, ZO, ZO, ZO, ZO, ZO],
    [NB, NS, NS, NS, NS, NS, NB],
    [NB, NM, NM, NM, NS, NS, NB],
]
params = [
    [a.mf.TRI, -3, -3, -2],  # NB
    [a.mf.TRI, -3, -2, -1],  # NM
    [a.mf.TRI, -2, -1, +0],  # NS
    [a.mf.TRI, -1, +0, +1],  # ZO
    [a.mf.TRI, +0, +1, +2],  # PS
    [a.mf.TRI, +1, +2, +3],  # PM
    [a.mf.TRI, +2, +3, +3],  # PB
    [a.mf.NONE, 0, 0, 0],
]


IMIN = -3
IMAX = +3
OMIN = -10
OMAX = +10


def fuzzy(e: float, c: float):
    e = 6 / (IMAX - IMIN) * e
    c = 3 / (IMAX - IMIN) * c

    mse = []
    idxe = []
    mf = a.mf()
    for idx, param in enumerate(params[:-1]):
        ms = mf(param[0], e, param[1:])
        if ms > 0:
            idxe.append(idx)
            mse.append(ms)
    msc = []
    idxc = []
    for idx, param in enumerate(params[:-1]):
        ms = mf(param[0], c, param[1:])
        if ms > 0:
            idxc.append(idx)
            msc.append(ms)
    if mse == [] or msc == []:
        return 0, 0, 0

    num = 0.0
    joint = []
    for e in mse:
        row = []
        for c in msc:
            y = pow(e * c, 0.5) * pow(1 - (1 - e) * (1 - c), 0.5)
            row.append(y)
            num += y
        joint.append(row)

    kp = 0.0
    for i in range(len(mse)):
        for j in range(len(msc)):
            kp += joint[i][j] * rkp[idxe[i]][idxc[j]]
    ki = 0.0
    for i in range(len(mse)):
        for j in range(len(msc)):
            ki += joint[i][j] * rki[idxe[i]][idxc[j]]
    kd = 0.0
    for i in range(len(mse)):
        for j in range(len(msc)):
            kd += joint[i][j] * rkd[idxe[i]][idxc[j]]

    alpha = (OMAX - OMIN) / 6.0 / num
    kp *= alpha
    ki *= alpha
    kd *= alpha

    return kp, ki, kd


kp = 400
ki = 200
kd = 0.005
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

fpid = a.fpid(Ts, params, rkp, rki, rkd, IMIN, IMAX, OMIN, OMAX)

r = 1.0
setpoint = [r] * len(data)

title = "Fuzzy Proportional Integral Derivative"

y = 0.0
error1 = []
feedback1 = []
tf = TF(num, den)
fpid.kpid(kp, ki, kd)
for i in data:
    u = fpid(r, y)
    y = tf(u)
    feedback1.append(y)
    error1.append(r - y)

s = 0.0
y = 0.0
e = [0.0, 0.0, 0.0]
x = [0.0, 0.0, 0.0]
error2 = []
feedback2 = []
tf = TF(num, den)
for i in data:
    e = np.roll(e, 1)
    e[0] = r - y
    x[0] = e[0] - e[1]
    x[1] = e[0] * Ts
    x[2] = (e[0] + e[2] - e[1] * 2) / Ts
    dkp, dki, dkd = fuzzy(e[0], e[0] - e[1])
    s += (kp + dkp) * x[0] + (ki + dki) * x[1] + (kd + dkd) * x[2]
    u = s
    if u < OMIN:
        u = OMIN
    elif u > OMAX:
        u = OMAX
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
plt.savefig(os.path.join(prefix, "fpid.png"))
