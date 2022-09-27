from ac.pid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid:
    '''proportional integral derivative controller'''
    OFF = A_PID_OFF
    POS = A_PID_POS
    INC = A_PID_INC
    cdef a_pid_s ctx[1]
    def __cinit__(self, a_real_t ts, a_real_t min, a_real_t max):
        a_pid_mode(a_pid_init(self.ctx, ts, min, max), A_PID_INC)
    def __call__(self, set: a_real_t, ref: a_real_t) -> a_real_t:
        '''process function for PID controller'''
        return a_pid_proc(self.ctx, set, ref)
    def __dealloc__(self):
        '''terminate function for PID controller'''
        a_pid_exit(self.ctx)
    def zero(self):
        '''zero function for PID controller'''
        a_pid_zero(self.ctx)
        return self
    def kpid(self, kp: a_real_t, ki: a_real_t, kd: a_real_t):
        '''set proportional integral derivative constant for PID controller'''
        a_pid_kpid(self.ctx, kp, ki, kd)
        return self
    def time(self, ts: a_real_t):
        '''set sampling period for PID controller'''
        a_pid_time(self.ctx, ts)
        return self
    def mode(self, mode: a_uint_t):
        '''set mode for PID controller directly'''
        a_pid_mode(self.ctx, mode)
        return self
    def pos(self, max: a_real_t):
        '''set positional mode'''
        a_pid_pos(self.ctx, max)
        return self
    def inc(self):
        '''set incremental mode'''
        a_pid_inc(self.ctx)
        return self
    def off(self):
        '''set turn off mode'''
        a_pid_off(self.ctx)
        return self
