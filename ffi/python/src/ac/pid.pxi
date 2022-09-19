from ac.pid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid:
    '''proportional integral derivative controller'''
    OFF = A_PID_OFF
    POS = A_PID_POS
    INC = A_PID_INC
    cdef a_pid_s ctx[1]
    def __cinit__(self, double ts, double min, double max):
        a_pid_mode(a_pid_init(self.ctx, ts, min, max), A_PID_INC)
    def __call__(self, set: float, ref: float) -> float:
        '''process function for PID controller'''
        return a_pid_proc(self.ctx, set, ref)
    def done(self):
        '''terminate function for PID controller'''
        a_pid_done(self.ctx)
        return self
    def kpid(self, kp: float, ki: float, kd: float):
        '''set proportional integral derivative constant for PID controller'''
        a_pid_kpid(self.ctx, kp, ki, kd)
        return self
    def time(self, ts: float):
        '''set sampling period for PID controller'''
        a_pid_time(self.ctx, ts)
        return self
    def mode(self, mode: int):
        '''set mode for PID controller directly'''
        a_pid_mode(self.ctx, mode)
        return self
    def pos(self, max: float):
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
