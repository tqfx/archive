from ac cimport *

cdef extern from "a/pid.h":
    ctypedef enum a_pid_e "a_pid_e":
        A_PID_OFF "A_PID_OFF"
        A_PID_POS "A_PID_POS"
        A_PID_INC "A_PID_INC"
    ctypedef struct a_pid_s "a_pid_s":
        a_real_t ts
        a_real_t kp
        a_real_t ki
        a_real_t kd
        a_real_t outmin
        a_real_t outmax
        a_real_t summax
        a_real_t sum
        a_real_t ref
        a_real_t out
        a_real_t ec
        a_real_t e
        a_uint_t mode
    a_void_t a_pid_init "a_pid_init" (a_pid_s *ctx, a_real_t ts, a_real_t min, a_real_t max)
    a_real_t a_pid_proc "a_pid_proc" (a_pid_s *ctx, a_real_t set, a_real_t ref)
    a_void_t a_pid_done "a_pid_done" (a_pid_s *ctx)
    a_void_t a_pid_kpid "a_pid_kpid" (a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
    a_void_t a_pid_time "a_pid_time" (a_pid_s *ctx, a_real_t ts)
    a_void_t a_pid_mode "a_pid_mode" (a_pid_s *ctx, a_uint_t mode)
    a_void_t a_pid_pos  "a_pid_pos"  (a_pid_s *ctx, a_real_t max)
    a_void_t a_pid_inc  "a_pid_inc"  (a_pid_s *ctx)
    a_void_t a_pid_off  "a_pid_off"  (a_pid_s *ctx)
