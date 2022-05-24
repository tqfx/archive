'''
 @file pid.pxi
 @brief cython for Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from pid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid:
    OFF = A_PID_OFF
    POS = A_PID_POS
    INC = A_PID_INC
    cdef a_pid_s ctx[1]
    def __cinit__(self, double ts, double min, double max):
        a_pid_init(self.ctx, ts, min, max)
        a_pid_mode(self.ctx, A_PID_INC)
    def __call__(self, set: float, ref: float):
        return a_pid_proc(self.ctx, set, ref)
    def mode(self, mode: int):
        a_pid_mode(self.ctx, mode)
        return self
    def kpid(self, kp: float, ki: float, kd: float):
        a_pid_kpid(self.ctx, kp, ki, kd)
        return self
    def time(self, ts: float):
        a_pid_time(self.ctx, ts)
        return self
    def done(self):
        a_pid_done(self.ctx)
        return self
    def pos(self, imx: float):
        a_pid_pos(self.ctx, imx)
        return self
    def inc(self):
        a_pid_inc(self.ctx)
        return self
    def off(self):
        a_pid_off(self.ctx)
        return self
