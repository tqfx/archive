from a cimport *

cdef extern from "a/poly.h":
    a_real_t *a_poly_inv(a_real_t *a, a_size_t n)
    a_real_t a_poly_eval(a_real_t const *a, a_size_t n, a_real_t x)
    a_real_t *a_poly_evaln(a_real_t const *a, a_size_t n, a_real_t const *ptr, a_size_t num, a_real_t *out)
    a_real_t a_poly_evar(a_real_t const *a, a_size_t n, a_real_t x)
    a_real_t *a_poly_evarn(a_real_t const *a, a_size_t n, a_real_t const *ptr, a_size_t num, a_real_t *out)
