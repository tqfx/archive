'''
 @file polytrack.pxd
 @brief cython for polynomial trajectory
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

cdef extern from "a/poly/polytrack.h":

    ctypedef struct c_polytrack3_s "a_polytrack3_s":
        double t[2]
        double q[2]
        double v[2]
        double k[4]
    void   c_polytrack3_init "a_polytrack3_init" (c_polytrack3_s *ctx, const double source[3], const double target[3])
    double c_polytrack3_pos  "a_polytrack3_pos"  (const c_polytrack3_s *ctx, double t)
    double c_polytrack3_vec  "a_polytrack3_vec"  (const c_polytrack3_s *ctx, double t)
    double c_polytrack3_acc  "a_polytrack3_acc"  (const c_polytrack3_s *ctx, double t)
    void   c_polytrack3_all  "a_polytrack3_all"  (const c_polytrack3_s *ctx, double t, double o[3])

    ctypedef struct c_polytrack5_s "a_polytrack5_s":
        double t[2]
        double q[2]
        double v[2]
        double a[2]
        double k[6]
    void   c_polytrack5_init "a_polytrack5_init" (c_polytrack5_s *ctx, const double source[4], const double target[4])
    double c_polytrack5_pos  "a_polytrack5_pos"  (const c_polytrack5_s *ctx, double t)
    double c_polytrack5_vec  "a_polytrack5_vec"  (const c_polytrack5_s *ctx, double t)
    double c_polytrack5_acc  "a_polytrack5_acc"  (const c_polytrack5_s *ctx, double t)
    void   c_polytrack5_all  "a_polytrack5_all"  (const c_polytrack5_s *ctx, double t, double o[3])

    ctypedef struct c_polytrack7_s "a_polytrack7_s":
        double t[2]
        double q[2]
        double v[2]
        double a[2]
        double j[2]
        double k[8]
    void   c_polytrack7_init "a_polytrack7_init" (c_polytrack7_s *ctx, const double source[5], const double target[5])
    double c_polytrack7_pos  "a_polytrack7_pos"  (const c_polytrack7_s *ctx, double t)
    double c_polytrack7_vec  "a_polytrack7_vec"  (const c_polytrack7_s *ctx, double t)
    double c_polytrack7_acc  "a_polytrack7_acc"  (const c_polytrack7_s *ctx, double t)
    double c_polytrack7_jer  "a_polytrack7_jer"  (const c_polytrack7_s *ctx, double t)
    void   c_polytrack7_all  "a_polytrack7_all"  (const c_polytrack7_s *ctx, double t, double o[4])
