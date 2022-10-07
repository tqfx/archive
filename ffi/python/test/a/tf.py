#!/usr/bin/env python
import sys
import os

sys.path.insert(0, os.getcwd())
prefix = os.path.join(sys.path[0], "build")
if not os.path.exists(prefix):
    os.mkdir(prefix)
try:
    import liba as a
    import numpy as np
except Exception as e:
    print(e)
    exit()


class TF:
    def __init__(self, num, den) -> None:
        self.num = np.array(num, dtype=float)
        self.den = np.array(den, dtype=float)[1:]
        self.u = np.array(len(self.num) * [0.0], dtype=float)
        self.v = np.array(len(self.den) * [0.0], dtype=float)

    def __call__(self, u: float) -> float:
        self.u = np.roll(self.u, 1)
        self.u[0] = u
        v = self.num @ self.u - self.den @ self.v  # type: ignore
        self.v = np.roll(self.v, 1)
        self.v[0] = v
        return v


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

tf = a.tf(num, den[1:])
tf_ = TF(num, den)

for t in data:
    t = t * 1000
    tf_(t)
    tf(t)
