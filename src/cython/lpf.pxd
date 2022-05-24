'''
 @file lpf.pxd
 @brief cython for Low Pass Filter
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

cdef extern from "a/filter/lpf.h":
    ctypedef struct a_lpf_s "a_lpf_s":
        double o
        double k
        double t
    void   a_lpf_init "a_lpf_init" (a_lpf_s *ctx, double k, double t)
    double a_lpf_proc "a_lpf_proc" (a_lpf_s *ctx, double x)
    void   a_lpf_done "a_lpf_done" (a_lpf_s *ctx)
