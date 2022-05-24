'''
 @file fpid.pxi
 @brief cython for Fuzzy Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

from fpid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class fpid:
    '''Fuzzy Proportional Integral Derivative Algorithm'''
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
        self.ms = <double *>PyMem_Malloc(sizeof(double) * n)
        self.mat = <double *>PyMem_Malloc(sizeof(double) * n * n)
        self.idx = <unsigned int *>PyMem_Malloc(sizeof(unsigned int) * n)
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
        PyMem_Free(self.ms)
        PyMem_Free(self.mat)
        PyMem_Free(self.idx)
    def __call__(self, set: float, ref: float):
        '''Calculate output'''
        return a_fpid_proc(self.ctx, set, ref)
    def kpid(self, kp: float, ki: float, kd: float):
        '''Set Proportional Integral Derivative'''
        a_fpid_kpid(self.ctx, kp, ki, kd)
        return self
    def time(self, ts: float):
        '''Set sampling period'''
        a_fpid_time(self.ctx, ts)
        return self
    def done(self):
        '''Terminate'''
        a_fpid_done(self.ctx)
        return self
    def pos(self, imx: float):
        '''Positional mode'''
        a_pid_pos(self.ctx[0].pid, imx)
        return self
    def inc(self):
        '''Incremental mode'''
        a_pid_inc(self.ctx[0].pid)
        return self
    def off(self):
        '''Turn off mode'''
        a_pid_off(self.ctx[0].pid)
        return self
