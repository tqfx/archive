cdef extern from "a/poly/polytrack.h":

    ctypedef struct a_polytrack3_s "a_polytrack3_s":
        double t[2]
        double q[2]
        double v[2]
        double k[4]
    void   a_polytrack3_init "a_polytrack3_init" (a_polytrack3_s *ctx, const double source[3], const double target[3])
    double a_polytrack3_pos  "a_polytrack3_pos"  (const a_polytrack3_s *ctx, double t)
    double a_polytrack3_vec  "a_polytrack3_vec"  (const a_polytrack3_s *ctx, double t)
    double a_polytrack3_acc  "a_polytrack3_acc"  (const a_polytrack3_s *ctx, double t)
    void   a_polytrack3_all  "a_polytrack3_all"  (const a_polytrack3_s *ctx, double t, double o[3])

    ctypedef struct a_polytrack5_s "a_polytrack5_s":
        double t[2]
        double q[2]
        double v[2]
        double a[2]
        double k[6]
    void   a_polytrack5_init "a_polytrack5_init" (a_polytrack5_s *ctx, const double source[4], const double target[4])
    double a_polytrack5_pos  "a_polytrack5_pos"  (const a_polytrack5_s *ctx, double t)
    double a_polytrack5_vec  "a_polytrack5_vec"  (const a_polytrack5_s *ctx, double t)
    double a_polytrack5_acc  "a_polytrack5_acc"  (const a_polytrack5_s *ctx, double t)
    void   a_polytrack5_all  "a_polytrack5_all"  (const a_polytrack5_s *ctx, double t, double o[3])

    ctypedef struct a_polytrack7_s "a_polytrack7_s":
        double t[2]
        double q[2]
        double v[2]
        double a[2]
        double j[2]
        double k[8]
    void   a_polytrack7_init "a_polytrack7_init" (a_polytrack7_s *ctx, const double source[5], const double target[5])
    double a_polytrack7_pos  "a_polytrack7_pos"  (const a_polytrack7_s *ctx, double t)
    double a_polytrack7_vec  "a_polytrack7_vec"  (const a_polytrack7_s *ctx, double t)
    double a_polytrack7_acc  "a_polytrack7_acc"  (const a_polytrack7_s *ctx, double t)
    double a_polytrack7_jer  "a_polytrack7_jer"  (const a_polytrack7_s *ctx, double t)
    void   a_polytrack7_all  "a_polytrack7_all"  (const a_polytrack7_s *ctx, double t, double o[4])
