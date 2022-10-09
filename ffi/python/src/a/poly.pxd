from a cimport *

cdef extern from "a/poly.h":
    a_real_t *a_poly_inv(a_real_t *a, a_size_t n)
    a_real_t a_poly_x(const a_real_t *a, a_size_t n, a_real_t x)
    a_real_t *a_poly_xs(const a_real_t *a, a_size_t n, const a_real_t *ptr, a_size_t num, a_real_t *out)
    a_real_t a_poly_r(const a_real_t *a, a_size_t n, a_real_t x)
    a_real_t *a_poly_rs(const a_real_t *a, a_size_t n, const a_real_t *ptr, a_size_t num, a_real_t *out)
