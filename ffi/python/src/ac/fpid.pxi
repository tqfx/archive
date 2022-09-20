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
    def __cinit__(self, a_uint_t num, double ts, mma, mkp, mki, mkd, double imin, double imax, double omin, double omax):
        self.mma = array('d', (i for j in mma for i in j))
        self.mkp = array('d', (i for j in mkp for i in j))
        self.mki = array('d', (i for j in mki for i in j))
        self.mkd = array('d', (i for j in mkd for i in j))
        cdef a_real_t *ma = self.mma.data.as_doubles
        cdef a_real_t *kp = self.mkp.data.as_doubles
        cdef a_real_t *ki = self.mki.data.as_doubles
        cdef a_real_t *kd = self.mkd.data.as_doubles
        a_fpid_init(self.ctx, ts, len(mkp), ma, kp, ki, kd, imin, imax, omin, omax)
        self.ptr = PyMem_Malloc(A_FPID_BUF1(num))
        a_fpid_buf1(self.ctx, self.ptr, num)
    def __dealloc__(self):
        PyMem_Free(self.ptr)
    def __call__(self, set: float, ref: float) -> float:
        '''process function for fuzzy PID controller'''
        return a_fpid_proc(self.ctx, set, ref)
    def done(self):
        '''terminate function for fuzzy PID controller'''
        a_fpid_done(self.ctx)
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
        a_fpid_base(self.ctx, len(mkp), ma, kp, ki, kd)
        return self
    def kpid(self, kp: float, ki: float, kd: float):
        '''set proportional integral derivative constant for fuzzy PID controller'''
        a_fpid_kpid(self.ctx, kp, ki, kd)
        return self
    def olim(self, min: float, max: float):
        '''set output extreme value for fuzzy PID controller'''
        a_fpid_olim(self.ctx, min, max)
        return self
    def ilim(self, min: float, max: float):
        '''set input extreme value for fuzzy PID controller'''
        a_fpid_ilim(self.ctx, min, max)
        return self
    def time(self, ts: float):
        '''set sampling period for fuzzy PID controller'''
        a_fpid_time(self.ctx, ts)
        return self
    def mode(self, mode: int):
        '''set mode for fuzzy PID controller directly'''
        a_fpid_mode(self.ctx, mode)
        return self
    def pos(self, max: float):
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
