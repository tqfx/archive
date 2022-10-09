from a cimport *

cdef extern from "a/pid.h":
    ctypedef enum a_pid_e:
        A_PID_OFF
        A_PID_POS
        A_PID_INC
    ctypedef struct a_pid_s:
        pass
    a_pid_s *a_pid_off(a_pid_s *ctx)
    a_pid_s *a_pid_inc(a_pid_s *ctx)
    a_pid_s *a_pid_pos(a_pid_s *ctx, a_real_t max)
    a_pid_s *a_pid_mode(a_pid_s *ctx, a_uint_t reg)
    a_pid_s *a_pid_time(a_pid_s *ctx, a_real_t dt)
    a_pid_s *a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
    a_pid_s *a_pid_setv(a_pid_s *ctx, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e)
    a_pid_s *a_pid_init(a_pid_s *ctx, a_real_t dt, a_real_t min, a_real_t max)
    a_real_t *a_pid_cc_v(a_pid_s *ctx, a_real_t *set, a_real_t *fdb)
    a_real_t a_pid_cc_x(a_pid_s *ctx, a_real_t set, a_real_t fdb)
    a_pid_s *a_pid_exit(a_pid_s *ctx)
    a_pid_s *a_pid_zero(a_pid_s *ctx)
