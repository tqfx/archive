'''
 @file pid.pxi
 @brief cython for Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from pid cimport *

A_PID_OFF = C_PID_OFF
A_PID_POS = C_PID_POS
A_PID_INC = C_PID_INC

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_pid:
    cdef c_pid_s ctx[1]
    def __cinit__(self, double ts, double min, double max):
        c_pid_init(self.ctx, ts, min, max)
        c_pid_mode(self.ctx, C_PID_INC)
    def __call__(self, set: float, ref: float):
        return c_pid_proc(self.ctx, set, ref)
    def mode(self, mode: int):
        c_pid_mode(self.ctx, mode)
        return self
    def kpid(self, kp: float, ki: float, kd: float):
        c_pid_kpid(self.ctx, kp, ki, kd)
        return self
    def time(self, ts: float):
        c_pid_time(self.ctx, ts)
        return self
    def done(self):
        c_pid_done(self.ctx)
        return self
    def pos(self, imx: float):
        c_pid_pos(self.ctx, imx)
        return self
    def inc(self):
        c_pid_inc(self.ctx)
        return self
    def off(self):
        c_pid_off(self.ctx)
        return self
