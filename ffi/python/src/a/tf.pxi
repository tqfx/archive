from a.tf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class tf:
    '''transfer function'''
    cdef a_tf_s ctx[1]
    cdef array _num
    cdef array _den
    cdef array _u
    cdef array _v
    def __cinit__(self, num, den):
        self.num = num
        self.den = den
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

    @property
    def num(self):
        return self._num
    @num.setter
    def num(self, num):
        cdef a_uint_t m = <a_uint_t>len(num)
        self._num = array('d', num)
        self._u = array('d', num)
        a_tf_set_num(self.ctx, m, self._num.data.as_doubles, self._u.data.as_doubles)

    @property
    def den(self):
        return self._den
    @den.setter
    def den(self, den):
        cdef a_uint_t n = <a_uint_t>len(den)
        self._den = array('d', den)
        self._v = array('d', den)
        a_tf_set_den(self.ctx, n, self._den.data.as_doubles, self._v.data.as_doubles)
