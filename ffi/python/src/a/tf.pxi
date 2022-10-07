from a.tf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class tf:
    '''transfer function'''
    cdef a_tf_s ctx[1]
    cdef array num
    cdef array den
    cdef array u
    cdef array v
    def __cinit__(self, num, den):
        cdef a_uint_t m = <a_uint_t>len(num)
        cdef a_uint_t n = <a_uint_t>len(den)
        self.num = array('d', num)
        self.den = array('d', den)
        self.u = array('d', num)
        self.v = array('d', den)
        a_tf_init(self.ctx, m, self.num.data.as_doubles, self.u.data.as_doubles, n, self.den.data.as_doubles, self.v.data.as_doubles)
    def __call__(self, x: a_real_t) -> a_real_t:
        '''process function for transfer function'''
        return a_tf_proc(self.ctx, x)
    def __dealloc__(self):
        '''terminate function for transfer function'''
        a_tf_exit(self.ctx)
    def zero(self):
        '''zero function for transfer function'''
        a_tf_zero(self.ctx)
        return self
