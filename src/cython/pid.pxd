'''
 @file pid.pxd
 @brief cython for Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from libc.stdint cimport *

cdef extern from "a/controller/pid.h":
    ctypedef enum c_pid_e "a_pid_e":
        C_PID_OFF "A_PID_OFF"
        C_PID_POS "A_PID_POS"
        C_PID_INC "A_PID_INC"
    ctypedef struct c_pid_s "a_pid_s":
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
    void   c_pid_init "a_pid_init" (c_pid_s *ctx, double ts, double min, double max)
    double c_pid_proc "a_pid_proc" (c_pid_s *ctx, double set, double ref)
    void   c_pid_done "a_pid_done" (c_pid_s *ctx)
    void   c_pid_kpid "a_pid_kpid" (c_pid_s *ctx, double kp, double ki, double kd)
    void   c_pid_time "a_pid_time" (c_pid_s *ctx, double ts)
    void   c_pid_mode "a_pid_mode" (c_pid_s *ctx, unsigned int mode)
    void   c_pid_pos  "a_pid_pos"  (c_pid_s *ctx, double imx)
    void   c_pid_inc  "a_pid_inc"  (c_pid_s *ctx)
    void   c_pid_off  "a_pid_off"  (c_pid_s *ctx)
