'''
 @file lpf.pxd
 @brief cython for Low Pass Filter
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

cdef extern from "a/filter/lpf.h":
    ctypedef struct c_lpf_s "a_lpf_s":
        double o
        double k
        double t
    void   c_lpf_init "a_lpf_init" (c_lpf_s *ctx, double k, double t)
    double c_lpf_proc "a_lpf_proc" (c_lpf_s *ctx, double x)
    void   c_lpf_done "a_lpf_done" (c_lpf_s *ctx)
