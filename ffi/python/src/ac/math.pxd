from ac cimport *

cdef extern from "a/math.h":
    a_f32_t a_inv_sqrt(a_f32_t x)
