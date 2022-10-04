from ac cimport *

cdef extern from "a/a.hpp" namespace "a":

    ctypedef a_bool_t bool_t
    ctypedef a_void_t void_t

    ctypedef a_i8_t i8_t
    ctypedef a_u8_t u8_t
    ctypedef a_i16_t i16_t
    ctypedef a_u16_t u16_t
    ctypedef a_i32_t i32_t
    ctypedef a_u32_t u32_t
    ctypedef a_i64_t i64_t
    ctypedef a_u64_t u64_t
    ctypedef a_imax_t imax_t
    ctypedef a_umax_t umax_t
    ctypedef a_iptr_t iptr_t
    ctypedef a_uptr_t uptr_t
    ctypedef a_diff_t diff_t

    ctypedef a_c_t c_t
    ctypedef a_i_t i_t
    ctypedef a_u_t u_t
    ctypedef a_is_t is_t
    ctypedef a_us_t us_t
    ctypedef a_il_t il_t
    ctypedef a_ul_t ul_t
    ctypedef a_ill_t ill_t
    ctypedef a_ull_t ull_t

    ctypedef  a_int_t  int_t
    ctypedef a_sint_t sint_t
    ctypedef a_uint_t uint_t

    ctypedef  a_byte_t byte_t
    ctypedef  a_char_t char_t
    ctypedef a_schar_t schar_t
    ctypedef a_uchar_t uchar_t

    ctypedef  a_str_t  str_t
    ctypedef a_cstr_t cstr_t
    ctypedef a_vptr_t vptr_t
    ctypedef a_cptr_t cptr_t

    ctypedef a_f32_t  f32_t
    ctypedef a_f64_t  f64_t
    ctypedef a_f128_t f128_t
    ctypedef a_fp64_t fp64_t
    ctypedef a_fp32_t fp32_t
    ctypedef a_real_t real_t
