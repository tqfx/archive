'''
 @file fpid.pxi
 @brief cython for Fuzzy Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from fpid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class fpid:
    cdef a_fpid_s ctx[1]
    cdef array.array tmf
    cdef array.array tkp
    cdef array.array tki
    cdef array.array tkd
    cdef unsigned int *idx
    cdef double *mat
    cdef double *ms
    def __cinit__(self, double ts, tmf, tkp, tki, tkd, double vmin, double vmax, double umin, double umax):
        cdef unsigned int n = <unsigned int>len(tmf)
        cdef unsigned int num = <unsigned int>len(tkp)
        self.ms = <double *>malloc(sizeof(double) * n)
        self.mat = <double *>malloc(sizeof(double) * n * n)
        self.idx = <unsigned int *>malloc(sizeof(unsigned int) * n)
        self.tmf = array.array('d', [i for j in tmf for i in j])
        self.tkp = array.array('d', [i for j in tkp for i in j])
        self.tki = array.array('d', [i for j in tki for i in j])
        self.tkd = array.array('d', [i for j in tkd for i in j])
        cdef double *mf = self.tmf.data.as_doubles
        cdef double *kp = self.tkp.data.as_doubles
        cdef double *ki = self.tki.data.as_doubles
        cdef double *kd = self.tkd.data.as_doubles
        a_fpid_init(self.ctx, ts, num, mf, kp, ki, kd, vmin, vmax, umin, umax)
        a_fpid_buff(self.ctx, self.ms, self.idx, self.mat)
    def __dealloc__(self):
        free(self.ms)
        free(self.mat)
        free(self.idx)
        self.ms = NULL
        self.mat = NULL
        self.idx = NULL
    def __call__(self, set: float, ref: float):
        return a_fpid_proc(self.ctx, set, ref)
    def kpid(self, kp: float, ki: float, kd: float):
        a_fpid_kpid(self.ctx, kp, ki, kd)
        return self
    def time(self, ts: float):
        a_fpid_time(self.ctx, ts)
        return self
    def done(self):
        a_fpid_done(self.ctx)
        return self
    def pos(self, imx: float):
        a_pid_pos(self.ctx[0].pid, imx)
        return self
    def inc(self):
        a_pid_inc(self.ctx[0].pid)
        return self
    def off(self):
        a_pid_off(self.ctx[0].pid)
        return self
