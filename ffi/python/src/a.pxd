from libc.stdint cimport *

cdef extern from "a/a.h":

    ctypedef int a_bool_t

    ctypedef void a_void_t

    ctypedef size_t a_size_t

    ctypedef  int8_t  a_int8_t
    ctypedef  int8_t a_sint8_t
    ctypedef uint8_t a_uint8_t

    ctypedef  int16_t  a_int16_t
    ctypedef  int16_t a_sint16_t
    ctypedef uint16_t a_uint16_t

    ctypedef  int32_t  a_int32_t
    ctypedef  int32_t a_sint32_t
    ctypedef uint32_t a_uint32_t

    ctypedef  int64_t  a_int64_t
    ctypedef  int64_t a_sint64_t
    ctypedef uint64_t a_uint64_t

    ctypedef  intmax_t  a_intmax_t
    ctypedef  intmax_t a_sintmax_t
    ctypedef uintmax_t a_uintmax_t

    ctypedef  intptr_t  a_intptr_t
    ctypedef  intptr_t a_sintptr_t
    ctypedef uintptr_t a_uintptr_t

    ctypedef ptrdiff_t a_ptrdiff_t

    ctypedef          int  a_int_t
    ctypedef          int a_sint_t
    ctypedef unsigned int a_uint_t

    ctypedef unsigned char  a_byte_t
    ctypedef          char  a_char_t
    ctypedef   signed char a_schar_t
    ctypedef unsigned char a_uchar_t

    ctypedef float  a_float32_t
    ctypedef double a_float64_t

    ctypedef double a_real_t
