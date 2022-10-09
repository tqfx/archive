from a.fpid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class fpid:
    '''fuzzy proportional integral derivative controller'''
    cdef a_fpid_s ctx[1]
    cdef a_vptr_t ptr
    cdef array mmp
    cdef array mkp
    cdef array mki
    cdef array mkd
    def __cinit__(self, a_uint_t num, a_real_t dt, mmp, mkp, mki, mkd, a_real_t imin, a_real_t imax, a_real_t omin, a_real_t omax):
        self.mmp = array('d', (i for j in mmp for i in j))
        self.mkp = array('d', (i for j in mkp for i in j))
        self.mki = array('d', (i for j in mki for i in j))
        self.mkd = array('d', (i for j in mkd for i in j))
        cdef a_real_t *ma = self.mmp.data.as_doubles
        cdef a_real_t *kp = self.mkp.data.as_doubles
        cdef a_real_t *ki = self.mki.data.as_doubles
        cdef a_real_t *kd = self.mkd.data.as_doubles
        a_fpid_init(self.ctx, dt, <a_uint_t>len(mkp), ma, kp, ki, kd, imin, imax, omin, omax)
        self.ptr = PyMem_Malloc(A_FPID_BUF1(num))
        a_fpid_buf1(self.ctx, self.ptr, num)
    def __call__(self, set: a_real_t, fdb: a_real_t) -> a_real_t:
        '''process function for fuzzy PID controller'''
        return a_fpid_cc_x(self.ctx, set, fdb)
    def __dealloc__(self):
        '''terminate function for fuzzy PID controller'''
        a_fpid_exit(self.ctx)
        PyMem_Free(self.ptr)
    def zero(self):
        '''zero function for fuzzy PID controller'''
        a_fpid_zero(self.ctx)
        return self
    def buff(self, max: a_uint_t):
        '''set buffer for fuzzy PID controller'''
        self.ptr = PyMem_Realloc(self.ptr, A_FPID_BUF1(max))
        a_fpid_buf1(self.ctx, self.ptr, max)
        return self
    def base(self, mmp, mkp, mki, mkd):
        '''set rule base for fuzzy PID controller'''
        self.mmp = array('d', (i for j in mmp for i in j))
        self.mkp = array('d', (i for j in mkp for i in j))
        self.mki = array('d', (i for j in mki for i in j))
        self.mkd = array('d', (i for j in mkd for i in j))
        cdef a_real_t *ma = self.mmp.data.as_doubles
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
    def time(self, dt: a_real_t):
        '''set sampling period for fuzzy PID controller'''
        a_fpid_time(self.ctx, dt)
        return self
    def mode(self, reg: a_uint_t):
        '''set mode for fuzzy PID controller directly'''
        a_fpid_mode(self.ctx, reg)
        return self
    def pos(self, max: a_real_t):
        '''positional fuzzy PID controller'''
        a_fpid_pos(self.ctx, max)
        return self
    def inc(self):
        '''incremental fuzzy PID controller'''
        a_fpid_inc(self.ctx)
        return self
    def off(self):
        '''turn off fuzzy PID controller'''
        a_fpid_off(self.ctx)
        return self
