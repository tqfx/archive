from pid cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class pid:
    '''Proportional Integral Derivative Algorithm'''
    OFF = A_PID_OFF
    POS = A_PID_POS
    INC = A_PID_INC
    cdef a_pid_s ctx[1]
    def __cinit__(self, double ts, double min, double max):
        a_pid_init(self.ctx, ts, min, max)
        a_pid_mode(self.ctx, A_PID_INC)
    def __call__(self, set: float, ref: float):
        '''Calculate output'''
        return a_pid_proc(self.ctx, set, ref)
    def mode(self, mode: int):
        '''Set mode'''
        a_pid_mode(self.ctx, mode)
        return self
    def kpid(self, kp: float, ki: float, kd: float):
        '''Set Proportional Integral Derivative'''
        a_pid_kpid(self.ctx, kp, ki, kd)
        return self
    def time(self, ts: float):
        '''Set sampling period'''
        a_pid_time(self.ctx, ts)
        return self
    def done(self):
        '''Terminate'''
        a_pid_done(self.ctx)
        return self
    def pos(self, imx: float):
        '''Positional mode'''
        a_pid_pos(self.ctx, imx)
        return self
    def inc(self):
        '''Incremental mode'''
        a_pid_inc(self.ctx)
        return self
    def off(self):
        '''Turn off mode'''
        a_pid_off(self.ctx)
        return self
