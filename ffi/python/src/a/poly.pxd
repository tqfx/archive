from a cimport *

cdef extern from "a/poly.h":
    a_real_t *a_poly_inv(a_real_t *a, a_size_t n)
    a_real_t a_poly_c(const a_real_t *a, a_size_t n, a_real_t x)
    a_real_t a_poly_r(const a_real_t *a, a_size_t n, a_real_t x)
