'''
 @file lpf.pxi
 @brief cython for Low Pass Filter
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from lpf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_lpf:
    cdef c_lpf_s ctx[1]
    def __cinit__(self, double k, double t):
        c_lpf_init(self.ctx, k, t)
    def __call__(self, x):
        if not isinstance(x, typing.Iterable):
            return c_lpf_proc(self.ctx, x)
        y = []
        for i in x:
            y.append(c_lpf_proc(self.ctx, i))
        return y
    cpdef done(self):
        c_lpf_done(self.ctx)
        return self
