from ac.fpid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class fpid:
    '''fuzzy proportional integral derivative controller'''
    cdef a_fpid_s ctx[1]
    cdef a_vptr_t ptr
    cdef array mma
    cdef array mkp
    cdef array mki
    cdef array mkd
    def __cinit__(self, a_uint_t num, a_real_t ts, mma, mkp, mki, mkd, a_real_t imin, a_real_t imax, a_real_t omin, a_real_t omax):
        self.mma = array('d', (i for j in mma for i in j))
        self.mkp = array('d', (i for j in mkp for i in j))
        self.mki = array('d', (i for j in mki for i in j))
        self.mkd = array('d', (i for j in mkd for i in j))
        cdef a_real_t *ma = self.mma.data.as_doubles
        cdef a_real_t *kp = self.mkp.data.as_doubles
        cdef a_real_t *ki = self.mki.data.as_doubles
        cdef a_real_t *kd = self.mkd.data.as_doubles
        a_fpid_init(self.ctx, ts, <a_uint_t>len(mkp), ma, kp, ki, kd, imin, imax, omin, omax)
        self.ptr = PyMem_Malloc(A_FPID_BUF1(num))
        a_fpid_buf1(self.ctx, self.ptr, num)
    def __dealloc__(self):
        PyMem_Free(self.ptr)
    def __call__(self, set: a_real_t, ref: a_real_t) -> a_real_t:
        '''process function for fuzzy PID controller'''
        return a_fpid_proc(self.ctx, set, ref)
    def __dealloc__(self):
        '''terminate function for fuzzy PID controller'''
        a_fpid_exit(self.ctx)
    def zero(self):
        '''zero function for fuzzy PID controller'''
        a_fpid_zero(self.ctx)
        return self
    def buff(self, max: a_uint_t):
        '''set buffer for fuzzy PID controller'''
        self.ptr = PyMem_Realloc(self.ptr, A_FPID_BUF1(max))
        a_fpid_buf1(self.ctx, self.ptr, max)
        return self
    def base(self, mma, mkp, mki, mkd):
        '''set rule base for fuzzy PID controller'''
        self.mma = array('d', (i for j in mma for i in j))
        self.mkp = array('d', (i for j in mkp for i in j))
        self.mki = array('d', (i for j in mki for i in j))
        self.mkd = array('d', (i for j in mkd for i in j))
        cdef a_real_t *ma = self.mma.data.as_doubles
        cdef a_real_t *kp = self.mkp.data.as_doubles
        cdef a_real_t *ki = self.mki.data.as_doubles
        cdef a_real_t *kd = self.mkd.data.as_doubles
        a_fpid_base(self.ctx, <a_uint_t>len(mkp), ma, kp, ki, kd)
        return self
    def kpid(self, kp: a_real_t, ki: a_real_t, kd: a_real_t):
        '''set proportional integral derivative constant for fuzzy PID controller'''
        a_fpid_kpid(self.ctx, kp, ki, kd)
        return self
    def olim(self, min: a_real_t, max: a_real_t):
        '''set output extreme value for fuzzy PID controller'''
        a_fpid_olim(self.ctx, min, max)
        return self
    def ilim(self, min: a_real_t, max: a_real_t):
        '''set input extreme value for fuzzy PID controller'''
        a_fpid_ilim(self.ctx, min, max)
        return self
    def time(self, ts: a_real_t):
        '''set sampling period for fuzzy PID controller'''
        a_fpid_time(self.ctx, ts)
        return self
    def mode(self, mode: a_uint_t):
        '''set mode for fuzzy PID controller directly'''
        a_fpid_mode(self.ctx, mode)
        return self
    def pos(self, max: a_real_t):
        '''set positional mode'''
        a_fpid_pos(self.ctx, max)
        return self
    def inc(self):
        '''set incremental mode'''
        a_fpid_inc(self.ctx)
        return self
    def off(self):
        '''set turn off mode'''
        a_fpid_off(self.ctx)
        return self
