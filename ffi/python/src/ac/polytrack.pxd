from ac cimport *

cdef extern from "a/polytrack.h":
    ctypedef struct a_polytrack3_s "a_polytrack3_s":
        a_real_t t[2]
        a_real_t q[2]
        a_real_t v[2]
        a_real_t k[4]
    a_void_t a_polytrack3_init "a_polytrack3_init" (a_polytrack3_s *ctx, const a_real_t source[3], const a_real_t target[3])
    a_real_t a_polytrack3_pos  "a_polytrack3_pos"  (const a_polytrack3_s *ctx, a_real_t ts)
    a_real_t a_polytrack3_vec  "a_polytrack3_vec"  (const a_polytrack3_s *ctx, a_real_t ts)
    a_real_t a_polytrack3_acc  "a_polytrack3_acc"  (const a_polytrack3_s *ctx, a_real_t ts)
    a_void_t a_polytrack3_all  "a_polytrack3_all"  (const a_polytrack3_s *ctx, a_real_t ts, a_real_t out[3])
    ctypedef struct a_polytrack5_s "a_polytrack5_s":
        a_real_t t[2]
        a_real_t q[2]
        a_real_t v[2]
        a_real_t a[2]
        a_real_t k[6]
    a_void_t a_polytrack5_init "a_polytrack5_init" (a_polytrack5_s *ctx, const a_real_t source[4], const a_real_t target[4])
    a_real_t a_polytrack5_pos  "a_polytrack5_pos"  (const a_polytrack5_s *ctx, a_real_t ts)
    a_real_t a_polytrack5_vec  "a_polytrack5_vec"  (const a_polytrack5_s *ctx, a_real_t ts)
    a_real_t a_polytrack5_acc  "a_polytrack5_acc"  (const a_polytrack5_s *ctx, a_real_t ts)
    a_void_t a_polytrack5_all  "a_polytrack5_all"  (const a_polytrack5_s *ctx, a_real_t ts, a_real_t out[3])
    ctypedef struct a_polytrack7_s "a_polytrack7_s":
        a_real_t t[2]
        a_real_t q[2]
        a_real_t v[2]
        a_real_t a[2]
        a_real_t j[2]
        a_real_t k[8]
    a_void_t a_polytrack7_init "a_polytrack7_init" (a_polytrack7_s *ctx, const a_real_t source[5], const a_real_t target[5])
    a_real_t a_polytrack7_pos  "a_polytrack7_pos"  (const a_polytrack7_s *ctx, a_real_t ts)
    a_real_t a_polytrack7_vec  "a_polytrack7_vec"  (const a_polytrack7_s *ctx, a_real_t ts)
    a_real_t a_polytrack7_acc  "a_polytrack7_acc"  (const a_polytrack7_s *ctx, a_real_t ts)
    a_real_t a_polytrack7_jer  "a_polytrack7_jer"  (const a_polytrack7_s *ctx, a_real_t ts)
    a_void_t a_polytrack7_all  "a_polytrack7_all"  (const a_polytrack7_s *ctx, a_real_t ts, a_real_t out[4])
