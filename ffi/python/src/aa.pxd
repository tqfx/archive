from a cimport *

cdef extern from "a/a.hpp" namespace "a":

    ctypedef a_bool_t bool_t

    ctypedef a_void_t void_t

    ctypedef a_size_t size_t

    ctypedef a_sint8_t sint8_t

    ctypedef a_sint16_t sint16_t

    ctypedef a_sint32_t sint32_t

    ctypedef a_sint64_t sint64_t

    ctypedef a_sintmax_t sintmax_t

    ctypedef a_sintptr_t sintptr_t

    ctypedef a_ptrdiff_t ptrdiff_t

    ctypedef  a_int_t  int_t
    ctypedef a_sint_t sint_t
    ctypedef a_uint_t uint_t

    ctypedef  a_byte_t byte_t
    ctypedef  a_char_t char_t
    ctypedef a_schar_t schar_t
    ctypedef a_uchar_t uchar_t

    ctypedef a_float32_t float32_t
    ctypedef a_float64_t float64_t

    ctypedef a_real_t real_t
