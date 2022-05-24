'''
 @file lpf.pxi
 @brief cython for Low Pass Filter
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

from lpf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class lpf:
    '''Low Pass Filter'''
    cdef a_lpf_s ctx[1]
    def __cinit__(self, double k, double t):
        a_lpf_init(self.ctx, k, t)
    def __call__(self, x):
        '''Calculate output'''
        if not isinstance(x, _typing.Iterable):
            return a_lpf_proc(self.ctx, x)
        y = []
        for i in x:
            y.append(a_lpf_proc(self.ctx, i))
        return y
    cpdef done(self):
        '''Terminate'''
        a_lpf_done(self.ctx)
        return self
