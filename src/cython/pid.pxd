from libc.stdint cimport *

cdef extern from "a/controller/pid.h":
    ctypedef enum a_pid_e "a_pid_e":
        A_PID_OFF "A_PID_OFF"
        A_PID_POS "A_PID_POS"
        A_PID_INC "A_PID_INC"
    ctypedef struct a_pid_s "a_pid_s":
        double kp
        double ki
        double kd
        double ts
        double min
        double max
        double imx
        double sum
        double ref
        double out
        double ec
        double e
        uint32_t mode
    void   a_pid_init "a_pid_init" (a_pid_s *ctx, double ts, double min, double max)
    double a_pid_proc "a_pid_proc" (a_pid_s *ctx, double set, double ref)
    void   a_pid_done "a_pid_done" (a_pid_s *ctx)
    void   a_pid_kpid "a_pid_kpid" (a_pid_s *ctx, double kp, double ki, double kd)
    void   a_pid_time "a_pid_time" (a_pid_s *ctx, double ts)
    void   a_pid_mode "a_pid_mode" (a_pid_s *ctx, unsigned int mode)
    void   a_pid_pos  "a_pid_pos"  (a_pid_s *ctx, double imx)
    void   a_pid_inc  "a_pid_inc"  (a_pid_s *ctx)
    void   a_pid_off  "a_pid_off"  (a_pid_s *ctx)
