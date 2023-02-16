from a cimport *

cdef extern from "a/polytrack.h":
    ctypedef struct a_polytrack3_s:
        a_real_t k[4]
        a_real_t t[2]
        a_real_t q[2]
        a_real_t v[2]
    a_void_t a_polytrack3_init(a_polytrack3_s *ctx, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0, a_real_t v1)
    a_void_t a_polytrack3_init1(a_polytrack3_s *ctx, const a_real_t t[2], const a_real_t q[2], const a_real_t v[2])
    a_void_t a_polytrack3_init2(a_polytrack3_s *ctx, const a_real_t source[3], const a_real_t target[3])
    a_void_t a_polytrack3_out(a_polytrack3_s const *ctx, a_real_t ts, a_real_t out[3])
    a_real_t a_polytrack3_pos(a_polytrack3_s const *ctx, a_real_t ts)
    a_real_t a_polytrack3_vec(a_polytrack3_s const *ctx, a_real_t ts)
    a_real_t a_polytrack3_acc(a_polytrack3_s const *ctx, a_real_t ts)
    a_void_t a_polytrack3_gen(a_polytrack3_s *ctx)
    ctypedef struct a_polytrack5_s:
        a_real_t k[6]
        a_real_t t[2]
        a_real_t q[2]
        a_real_t v[2]
        a_real_t a[2]
    a_void_t a_polytrack5_init(a_polytrack5_s *ctx, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0, a_real_t v1, a_real_t a0, a_real_t a1)
    a_void_t a_polytrack5_init1(a_polytrack5_s *ctx, const a_real_t t[2], const a_real_t q[2], const a_real_t v[2], const a_real_t a[2])
    a_void_t a_polytrack5_init2(a_polytrack5_s *ctx, const a_real_t source[4], const a_real_t target[4])
    a_void_t a_polytrack5_out(a_polytrack5_s const *ctx, a_real_t ts, a_real_t out[3])
    a_real_t a_polytrack5_pos(a_polytrack5_s const *ctx, a_real_t ts)
    a_real_t a_polytrack5_vec(a_polytrack5_s const *ctx, a_real_t ts)
    a_real_t a_polytrack5_acc(a_polytrack5_s const *ctx, a_real_t ts)
    a_void_t a_polytrack5_gen(a_polytrack5_s *ctx)
    ctypedef struct a_polytrack7_s:
        a_real_t k[8]
        a_real_t t[2]
        a_real_t q[2]
        a_real_t v[2]
        a_real_t a[2]
        a_real_t j[2]
    a_void_t a_polytrack7_init(a_polytrack7_s *ctx, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0, a_real_t v1, a_real_t a0, a_real_t a1, a_real_t j0, a_real_t j1)
    a_void_t a_polytrack7_init1(a_polytrack7_s *ctx, const a_real_t t[2], const a_real_t q[2], const a_real_t v[2], const a_real_t a[2], const a_real_t j[2])
    a_void_t a_polytrack7_init2(a_polytrack7_s *ctx, const a_real_t source[5], const a_real_t target[5])
    a_void_t a_polytrack7_out(a_polytrack7_s const *ctx, a_real_t ts, a_real_t out[4])
    a_real_t a_polytrack7_pos(a_polytrack7_s const *ctx, a_real_t ts)
    a_real_t a_polytrack7_vec(a_polytrack7_s const *ctx, a_real_t ts)
    a_real_t a_polytrack7_acc(a_polytrack7_s const *ctx, a_real_t ts)
    a_real_t a_polytrack7_jer(a_polytrack7_s const *ctx, a_real_t ts)
    a_void_t a_polytrack7_gen(a_polytrack7_s *ctx)
