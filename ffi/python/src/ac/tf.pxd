from ac cimport *

cdef extern from "a/tf.h":
    ctypedef struct a_tf_s "a_tf_s":
        a_real_t *u;
        a_real_t *v;
        const a_real_t *num;
        const a_real_t *den;
        a_uint_t m;
        a_uint_t n;
    a_tf_s * a_tf_init "a_tf_init" (a_tf_s *ctx, a_uint_t m, const a_real_t *num, a_real_t *u, a_uint_t n, const a_real_t *den, a_real_t *v)
    a_real_t a_tf_proc "a_tf_proc" (a_tf_s *ctx, a_real_t x)
    a_tf_s * a_tf_exit "a_tf_exit" (a_tf_s *ctx)
    a_tf_s * a_tf_zero "a_tf_zero" (a_tf_s *ctx)
