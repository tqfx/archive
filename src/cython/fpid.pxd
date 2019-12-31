'''
 @file fpid.pxd
 @brief cython for Fuzzy Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from pid cimport *

cdef extern from "a/controller/fpid.h":
    ctypedef struct c_fpid_s "a_fpid_s":
        c_pid_s pid[1]
        uint32_t num
        const double *tkp
        const double *tki
        const double *tkd
        const double *tmf
        unsigned int *idx
        double *ms
        double *mat
        double sigma
        double alpha
        double kp
        double ki
        double kd
        double (*opt)(double, double)
    void   c_fpid_init "a_fpid_init" (c_fpid_s *ctx, double ts, unsigned int num, const double *tmf,
                                      const double *tkp, const double *tki, const double *tkd,
                                      double vmin, double vmax, double umin, double umax)
    void   c_fpid_buff "a_fpid_buff" (c_fpid_s *ctx, double *ms, unsigned int *idx, double *mat)
    void   c_fpid_kpid "a_fpid_kpid" (c_fpid_s *ctx, double kp, double ki, double kd)
    void   c_fpid_time "a_fpid_time" (c_fpid_s *ctx, double ts)
    double c_fpid_proc "a_fpid_proc" (c_fpid_s *ctx, double set, double ref)
    void   c_fpid_done "a_fpid_done" (c_fpid_s *ctx)
