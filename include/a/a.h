/*!
 @file a.h
 @brief algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef A_A_H
#define A_A_H

#include "config.h"

/*! @cond */

#if !defined __has_attribute
#define __has_attribute(...) 0
#endif /* __has_attribute */
#if !defined __has_builtin
#define __has_builtin(...) 0
#endif /* __has_builtin */
#if !defined __has_feature
#define __has_feature(...) 0
#endif /* __has_feature */
#if !defined __has_include
#define __has_include(...) 0
#endif /* __has_include */
#if !defined __has_warning
#define __has_warning(...) 0
#endif /* __has_warning */

/* https://en.wikipedia.org/wiki/Microsoft_Visual_C++ */
#if defined(_MSC_VER)
#define a_prereq_msvc(maj, min) (_MSC_VER >= (maj * 100 + min * 10))
#else /* !_MSC_VER */
#define a_prereq_msvc(maj, min) 0
#endif /* _MSC_VER */

/* https://gcc.gnu.org/onlinedocs/gcc-4.9.4/cpp/Common-Predefined-Macros.html */
#if defined(__GNUC__) && defined(__GNUC_MINOR__)
#define a_prereq_gnuc(maj, min) ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else /* !__GNUC__ */
#define a_prereq_gnuc(maj, min) 0
#endif /* __GNUC__ */

/* https://clang.llvm.org/docs/LanguageExtensions.html */
#if defined(__clang_major__) && defined(__clang_minor__)
#define a_prereq_clang(maj, min) ((__clang_major__ << 16) + __clang_minor__ >= ((maj) << 16) + (min))
#else /* !__clang__ */
#define a_prereq_clang(maj, min) 0
#endif /* __clang__ */

#if a_prereq_gnuc(2, 96) || __has_builtin(__builtin_expect)
#define a_unlikely(...) __builtin_expect(!!(__VA_ARGS__), 0)
#define a_likely(...) __builtin_expect(!!(__VA_ARGS__), 1)
#else /* !__GNUC__ */
#define a_unlikely(...) (__VA_ARGS__)
#define a_likely(...) (__VA_ARGS__)
#endif /* __GNUC__ */

#if defined(__GNUC__) || defined(__clang__)
#define A_ATTRIBUTE(...) __attribute__((__VA_ARGS__))
#else /* !__attribute__ */
#define A_ATTRIBUTE(...)
#endif /* __attribute__ */

#if defined(_WIN32) || defined(__CYGWIN__)
#define A_DECLSPEC(...) __declspec(__VA_ARGS__)
#else /* !__declspec */
#define A_DECLSPEC(...)
#endif /* __declspec */

/* attribute fallthrough */
#if a_prereq_gnuc(7, 1) || __has_attribute(fallthrough)
#define A_FALLTHROUGH __attribute__((fallthrough))
#else /* !fallthrough */
#define A_FALLTHROUGH ((void)(0))
#endif /* fallthrough */

/* attribute format */
#if a_prereq_gnuc(2, 4) || __has_attribute(format)
#define A_FORMAT(...) __attribute__((format(__VA_ARGS__)))
#else /* !format */
#define A_FORMAT(...)
#endif /* format */

/* attribute deprecated */
#if a_prereq_gnuc(3, 2) || __has_attribute(deprecated)
#define A_DEPRECATED(...) __attribute__((deprecated(__VA_ARGS__)))
#elif defined(_WIN32) || defined(__CYGWIN__)
#define A_DEPRECATED(...) __declspec(deprecated(__VA_ARGS__))
#else /* !deprecated */
#define A_DEPRECATED(...)
#endif /* deprecated */

/* attribute always inline */
#if a_prereq_gnuc(3, 2) || __has_attribute(always_inline)
#define A_INTERN static __inline __attribute__((always_inline))
#elif defined(_MSC_VER)
#define A_INTERN static __forceinline
#else /* !_MSC_VER */
#define A_INTERN static __inline
#endif /* _MSC_VER */
#if defined(A_HAVE_INLINE)
#if !defined A_INLINE
#define A_INLINE A_INTERN
#endif /* A_INLINE */
#endif /* A_HAVE_INLINE */
#define A_STATIC static

/* attribute visibility */
#if defined(_WIN32) || defined(__CYGWIN__)
#define A_EXPORT __declspec(dllexport)
#define A_IMPORT __declspec(dllimport)
#define A_HIDDEN
#elif a_prereq_gnuc(4, 0) || __has_attribute(visibility)
#define A_EXPORT __attribute__((visibility("default")))
#define A_IMPORT __attribute__((visibility("default")))
#define A_HIDDEN __attribute__((visibility("hidden")))
#else /* !visibility */
#define A_EXPORT
#define A_IMPORT
#define A_HIDDEN
#endif /* visibility */
#if defined(A_EXPORTS)
#define A_PUBLIC A_EXPORT
#elif defined(A_SHARED)
#define A_PUBLIC A_IMPORT
#else /* !A_PUBLIC */
#define A_PUBLIC
#endif /* A_PUBLIC */

#if !defined __cplusplus
#define A_EXTERN_C
#define A_EXTERN_C_ENTER
#define A_EXTERN_C_LEAVE
#else /* !__cplusplus */
#define A_EXTERN_C extern "C"
#define A_EXTERN_C_ENTER extern "C" {
#define A_EXTERN_C_LEAVE }
#endif /* __cplusplus */

#if !defined NDEBUG && defined(__GNUC__)
#define A_ASSERT(E) assert(E)
#else /* !NDEBUG */
#define A_ASSERT(E) ((void)(0))
#endif /* NDEBUG */

/*! @endcond */

/*!
 @addtogroup A algorithm library based on C
 @{
*/

#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>

#if defined(__cplusplus)
#define a_register
#else /* !__cplusplus */
#define a_register __register
#endif /* __cplusplus */
#define a_volatile __volatile
#define a_restrict __restrict

#if !defined __cplusplus
#define a_cast_c(T, ...) ((T)(__VA_ARGS__))
#define a_cast_s(T, ...) ((T)(__VA_ARGS__))
#define a_cast_d(T, ...) ((T)(__VA_ARGS__))
#define a_cast_r(T, ...) ((T)(__VA_ARGS__))
#else /* !__cplusplus */
#define a_cast_c(T, ...) const_cast<T>(__VA_ARGS__)
#define a_cast_s(T, ...) static_cast<T>(__VA_ARGS__)
#define a_cast_d(T, ...) dynamic_cast<T>(__VA_ARGS__)
#define a_cast_r(T, ...) reinterpret_cast<T>(__VA_ARGS__)
#endif /* __cplusplus */

/*! as the declaration of the incomplete type */
#define a_void_t void
#if !defined __cplusplus
#define A_NULL NULL
#else /* !__cplusplus */
#define A_NULL nullptr
#endif /* __cplusplus */
#define A_INIT 0
/*! static cast to \ref a_void_t */
#define a_void_c(x) a_cast_s(a_void_t, x)

/*! type, capable of holding one of the two values: 1 and 0 */
typedef int a_bool_t;
#if !defined __cplusplus
#define A_FALSE 0
#define A_TRUE !A_FALSE
#else /* !__cplusplus */
#define A_FALSE false
#define A_TRUE true
#endif /* __cplusplus */
/*! static cast to \ref a_bool_t */
#define a_bool_c(x) (!!(x))

// clang-format off

/*! signed integer type with width of exactly 8 bits */
typedef  int8_t a_i8_t;
/*! unsigned integer type with width of exactly 8 bits */
typedef uint8_t a_u8_t;
#define A_I8_C(X)  INT8_C(X)
#define A_U8_C(X) UINT8_C(X)
#define A_I8_MIN   INT8_MIN
#define A_I8_MAX   INT8_MAX
#define A_U8_MAX  UINT8_MAX
/*! static cast to \ref a_i8_t */
#define a_i8_c(x) a_cast_s(a_i8_t, x)
/*! static cast to \ref a_u8_t */
#define a_u8_c(x) a_cast_s(a_u8_t, x)

/*! signed integer type with width of exactly 16 bits */
typedef  int16_t a_i16_t;
/*! unsigned integer type with width of exactly 16 bits */
typedef uint16_t a_u16_t;
#define A_I16_C(X)  INT16_C(X)
#define A_U16_C(X) UINT16_C(X)
#define A_I16_MIN   INT16_MIN
#define A_I16_MAX   INT16_MAX
#define A_U16_MAX  UINT16_MAX
/*! static cast to \ref a_i16_t */
#define a_i16_c(x) a_cast_s(a_i16_t, x)
/*! static cast to \ref a_u16_t */
#define a_u16_c(x) a_cast_s(a_u16_t, x)

/*! signed integer type with width of exactly 32 bits */
typedef  int32_t a_i32_t;
/*! unsigned integer type with width of exactly 32 bits */
typedef uint32_t a_u32_t;
#define A_I32_C(X)  INT32_C(X)
#define A_U32_C(X) UINT32_C(X)
#define A_I32_MIN   INT32_MIN
#define A_I32_MAX   INT32_MAX
#define A_U32_MAX  UINT32_MAX
/*! static cast to \ref a_i32_t */
#define a_i32_c(x) a_cast_s(a_i32_t, x)
/*! static cast to \ref a_u32_t */
#define a_u32_c(x) a_cast_s(a_u32_t, x)

/*! signed integer type with width of exactly 64 bits */
typedef  int64_t a_i64_t;
/*! unsigned integer type with width of exactly 64 bits */
typedef uint64_t a_u64_t;
#define A_I64_C(X)  INT64_C(X)
#define A_U64_C(X) UINT64_C(X)
#define A_I64_MIN   INT64_MIN
#define A_I64_MAX   INT64_MAX
#define A_U64_MAX  UINT64_MAX
/*! static cast to \ref a_i64_t */
#define a_i64_c(x) a_cast_s(a_i64_t, x)
/*! static cast to \ref a_u64_t */
#define a_u64_c(x) a_cast_s(a_u64_t, x)

/*! maximum-width signed integer type */
typedef  intmax_t a_imax_t;
/*! maximum-width unsigned integer type */
typedef uintmax_t a_umax_t;
#define A_IMAX_C(X)  INTMAX_C(X)
#define A_UMAX_C(X) UINTMAX_C(X)
#define A_IMAX_MIN   INTMAX_MIN
#define A_IMAX_MAX   INTMAX_MAX
#define A_UMAX_MAX  UINTMAX_MAX
/*! static cast to \ref a_imax_t */
#define a_imax_c(x) a_cast_s(a_imax_t, x)
/*! static cast to \ref a_umax_t */
#define a_umax_c(x) a_cast_s(a_umax_t, x)

/*! signed integer type capable of holding a pointer to void */
typedef  intptr_t a_iptr_t;
/*! unsigned integer type capable of holding a pointer to void */
typedef uintptr_t a_uptr_t;
#define A_IPTR_C(X)  INTPTR_C(X)
#define A_UPTR_C(X) UINTPTR_C(X)
#define A_IPTR_MIN   INTPTR_MIN
#define A_IPTR_MAX   INTPTR_MAX
#define A_UPTR_MAX  UINTPTR_MAX
/*! static cast to \ref a_iptr_t */
#define a_iptr_c(x) a_cast_s(a_iptr_t, x)
/*! static cast to \ref a_uptr_t */
#define a_uptr_c(x) a_cast_s(a_uptr_t, x)

/*! signed integer type returned when subtracting two pointers */
typedef ptrdiff_t a_diff_t;
#define A_DIFF_MIN PTRDIFF_MIN
#define A_DIFF_MAX PTRDIFF_MAX
/*! static cast to \ref a_diff_t */
#define a_diff_c(x) a_cast_s(a_diff_t, x)

/*! unsigned integer type returned by the sizeof operator */
typedef size_t a_size_t;
#define A_SIZE_MAX SIZE_MAX
/*! static cast to \ref a_size_t */
#define a_size_c(x) a_cast_s(a_size_t, x)

/*! signed integer type is guaranteed to be at least 16 bits */
typedef   signed int a_i_t;
/*! unsigned integer type is guaranteed to be at least 16 bits */
typedef unsigned int a_u_t;
#define A_I_MIN  INT_MIN
#define A_I_MAX  INT_MAX
#define A_U_MAX UINT_MAX
/*! static cast to \ref a_i_t */
#define a_i_c(x) a_cast_s(a_i_t, x)
/*! static cast to \ref a_u_t */
#define a_u_c(x) a_cast_s(a_u_t, x)

/*! signed integer type is guaranteed to be at least 32 bits */
typedef   signed long a_il_t;
/*! unsigned integer type is guaranteed to be at least 32 bits */
typedef unsigned long a_ul_t;
#define A_IL_MIN  LONG_MIN
#define A_IL_MAX  LONG_MAX
#define A_UL_MAX ULONG_MAX
/*! static cast to \ref a_il_t */
#define a_il_c(x) a_cast_s(a_il_t, x)
/*! static cast to \ref a_ul_t */
#define a_ul_c(x) a_cast_s(a_ul_t, x)

/*! signed integer type is guaranteed to be at least 16 bits */
typedef   signed short a_is_t;
/*! unsigned integer type is guaranteed to be at least 16 bits */
typedef unsigned short a_us_t;
#define A_IS_MIN  SHRT_MIN
#define A_IS_MAX  SHRT_MAX
#define A_US_MAX USHRT_MAX
/*! static cast to \ref a_is_t */
#define a_is_c(x) a_cast_s(a_is_t, x)
/*! static cast to \ref a_us_t */
#define a_us_c(x) a_cast_s(a_us_t, x)

/*! signed integer type is guaranteed to be at least 64 bits */
typedef   signed long long a_ill_t;
/*! unsigned integer type is guaranteed to be at least 64 bits */
typedef unsigned long long a_ull_t;
#define A_ILL_MIN  LLONG_MIN
#define A_ILL_MAX  LLONG_MAX
#define A_ULL_MAX ULLONG_MAX
/*! static cast to \ref a_ill_t */
#define a_ill_c(x) a_cast_s(a_ill_t, x)
/*! static cast to \ref a_ull_t */
#define a_ull_c(x) a_cast_s(a_ull_t, x)

/*! the most optimal integer type for the platform, and is guaranteed to be at least 16 bits. */
typedef          int  a_int_t;
typedef   signed int a_sint_t;
typedef unsigned int a_uint_t;

typedef unsigned char  a_byte_t;
typedef          char  a_char_t;
typedef   signed char a_schar_t;
typedef unsigned char a_uchar_t;

typedef       char * a_str_t;
typedef const char *a_cstr_t;
typedef       void *a_vptr_t;
typedef const void *a_cptr_t;

// clang-format on

#define A_F16_NNAN A_U16_C(0xFE00)
#define A_F16_PNAN A_U16_C(0x7E00)
#define A_F16_NINF A_U16_C(0xFC00)
#define A_F16_PINF A_U16_C(0x7C00)

/*! single precision floating point type. Matches IEEE-754 binary32 format if supported. */
typedef float a_f32_t;
#define A_F32_C(X) (X##F)
#define A_F32_F(F, ...) F##f(__VA_ARGS__)
#define A_F32_MIN FLT_MIN
#define A_F32_MAX FLT_MAX
#define A_F32_INF a_f32_c(DBL_MAX *DBL_MAX)
#define A_F32_NAN (A_F32_C(0.0) * A_F32_INF)
#define A_F32_NNAN A_U32_C(0xFFC00000)
#define A_F32_PNAN A_U32_C(0x7FC00000)
#define A_F32_NINF A_U32_C(0xFF800000)
#define A_F32_PINF A_U32_C(0x7F800000)
/*! static cast to \ref a_f32_t */
#define a_f32_c(x) a_cast_s(a_f32_t, x)

/*! double precision floating point type. Matches IEEE-754 binary64 format if supported. */
typedef double a_f64_t;
#define A_F64_C(X) (X)
#define A_F64_F(F, ...) F(__VA_ARGS__)
#define A_F64_MIN DBL_MIN
#define A_F64_MAX DBL_MAX
#define A_F64_INF a_f64_c(DBL_MAX *DBL_MAX)
#define A_F64_NAN (A_F64_C(0.0) * A_F64_INF)
#define A_F64_NNAN A_U64_C(0xFFF8000000000000)
#define A_F64_PNAN A_U64_C(0x7FF8000000000000)
#define A_F64_NINF A_U64_C(0xFFF0000000000000)
#define A_F64_PINF A_U64_C(0x7FF0000000000000)
/*! static cast to \ref a_f64_t */
#define a_f64_c(x) a_cast_s(a_f64_t, x)

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif /* diagnostic */

/* from/into */
A_INTERN a_f32_t a_f32_from(a_u32_t x) { return *a_cast_s(a_f32_t *, a_cast_s(a_vptr_t, &x)); }
A_INTERN a_u32_t a_f32_into(a_f32_t x) { return *a_cast_s(a_u32_t *, a_cast_s(a_vptr_t, &x)); }
A_INTERN a_f64_t a_f64_from(a_u64_t x) { return *a_cast_s(a_f64_t *, a_cast_s(a_vptr_t, &x)); }
A_INTERN a_u64_t a_f64_into(a_f64_t x) { return *a_cast_s(a_u64_t *, a_cast_s(a_vptr_t, &x)); }

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */

typedef union a_cast_u
{
    a_i_t i;
    a_u_t u;
    a_is_t is;
    a_us_t us;
    a_il_t il;
    a_ul_t ul;
    a_ill_t ill;
    a_ull_t ull;
    a_i8_t i8;
    a_u8_t u8;
    a_i16_t i16;
    a_u16_t u16;
    a_i32_t i32;
    a_u32_t u32;
    a_i64_t i64;
    a_u64_t u64;
    a_f32_t f32;
    a_f64_t f64;
    a_diff_t diff;
    a_size_t size;
    a_imax_t imax;
    a_umax_t umax;
    a_iptr_t iptr;
    a_uptr_t uptr;
    a_cptr_t cptr;
    a_vptr_t vptr;
    a_cstr_t cstr;
    a_str_t str;
    a_char_t c;
} a_cast_u;

/*!
 @addtogroup A_REAL real number
 @{
*/

#if A_REAL_BITS > 64

/*! real number stored using `long double` */
typedef long double a_real_t;

/*!
 expands to a floating-point constant expression having the value specified by its argument and the type \ref a_real_t
*/
#define A_REAL_C(X) X##L
/*!
 expands to a floating-point function expression having the value specified by its argument and the type \ref a_real_t
*/
#define A_REAL_F(F, ...) F##l(__VA_ARGS__)

/*! Format constants for the fprintf family of functions */
#define A_REAL_PRI(_, ...) "%" _ "L" __VA_ARGS__
/*! Format constants for the fscanf family of functions */
#define A_REAL_SCN(_, ...) "%" _ "L" __VA_ARGS__
#define A_REAL_MIN LDBL_MIN
#define A_REAL_MAX LDBL_MAX

#elif A_REAL_BITS == 64

/*! real number stored using `double` */
typedef double a_real_t;

/*!
 expands to a floating-point constant expression having the value specified by its argument and the type \ref a_real_t
*/
#define A_REAL_C(X) X
/*!
 expands to a floating-point function expression having the value specified by its argument and the type \ref a_real_t
*/
#define A_REAL_F(F, ...) F(__VA_ARGS__)

/*! Format constants for the fprintf family of functions */
#define A_REAL_PRI(_, ...) "%" _ __VA_ARGS__
/*! Format constants for the fscanf family of functions */
#define A_REAL_SCN(_, ...) "%" _ "l" __VA_ARGS__
#define A_REAL_MIN DBL_MIN
#define A_REAL_MAX DBL_MAX

#elif A_REAL_BITS == 32

/*! real number stored using `float` */
typedef float a_real_t;

/*!
 expands to a floating-point constant expression having the value specified by its argument and the type \ref a_real_t
*/
#define A_REAL_C(X) X##F
/*!
 expands to a floating-point function expression having the value specified by its argument and the type \ref a_real_t
*/
#define A_REAL_F(F, ...) F##f(__VA_ARGS__)

/*! Format constants for the fprintf family of functions */
#define A_REAL_PRI(_, ...) "%" _ __VA_ARGS__
/*! Format constants for the fscanf family of functions */
#define A_REAL_SCN(_, ...) "%" _ __VA_ARGS__
#define A_REAL_MIN FLT_MIN
#define A_REAL_MAX FLT_MAX

#endif /* A_REAL_BITS */

#define A_REAL_INF a_cast_s(a_real_t, DBL_MAX *DBL_MAX)
#define A_REAL_NAN (A_REAL_C(0.0) * A_REAL_INF)

/*! static cast to \ref a_real_t */
#define a_real_c(x) a_cast_s(a_real_t, x)

typedef union a_real_u
{
    a_real_t v; //!< a real value
    a_real_t *p; //!< real vector
} a_real_u;

/*! @} A_REAL */

/*!
 @brief size of memory that alignment is specified by alignment
 @param base specifies the alignment that is a power of two
 @param size number of bytes to allocate
*/
#define a_align(base, size) ((a_cast_r(a_size_t, size) + (base)-1) & ~((base)-1))

/*!
 @brief size of an array
 @param a must be an array variable
*/
#define a_arrayof(a) (sizeof(a) / sizeof(*(a)))

/*!
 @brief offset of a structure member
 @param type structure type
 @param member member variable
*/
#if defined(offsetof)
#define a_offsetof(type, member) offsetof(type, member)
#else /* !offsetof */
#define a_offsetof(type, member) a_cast_r(a_size_t, &a_cast_r(type *, 0)->member)
#endif /* offsetof */

/*!
 @brief container of a structure member
 @param ptr pointer to a member variable
 @param type structure type
 @param member member variable
*/
#define a_container_of(ptr, type, member) a_cast_r(type *, a_cast_r(a_uptr_t, ptr) - a_offsetof(type, member))

/*!
 @brief iterate from 0 to n and not include n
 @param I index type of the iteration
 @param i index variable of the iteration
 @param n final value of the iteration
*/
#define a_forenum(I, i, n) for (I i = 0; i < (n); ++i)

/*!
 @brief iterate from n to 0 and not include n
 @param I index type of the iteration
 @param i index variable of the iteration
 @param n final value of the iteration
*/
#define a_forenum_reverse(I, i, n) for (I i = (n); i-- > 0;)

/*!
 @brief iterate over an array
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_foreach(T, it, ptr, num)                      \
    for (T *it = a_cast_s(T *, ptr),                    \
           *it##_ = a_likely(it) ? it + (num) : A_NULL; \
         it < it##_; ++it)

/*!
 @brief iterate over an array in reverse
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_foreach_reverse(T, it, ptr, num)                           \
    for (T *it##_ = a_likely(ptr) ? a_cast_s(T *, ptr) - 1 : A_NULL, \
           *it = a_likely(ptr) ? it##_ + (num) : A_NULL;             \
         it > it##_; --it)

/*!
 @brief iterate over an array
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param end the end address of this array
*/
#define a_iterate(T, it, ptr, end) \
    for (T *it = a_cast_s(T *, ptr), *it##_ = a_cast_s(T *, end); it < it##_; ++it)

/*!
 @brief iterate over an array in reverse
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param end the end address of this array
*/
#define a_iterate_reverse(T, it, ptr, end)                           \
    for (T *it##_ = a_likely(ptr) ? a_cast_s(T *, ptr) - 1 : A_NULL, \
           *it = a_likely(end) ? a_cast_s(T *, end) - 1 : A_NULL;    \
         it > it##_; --it)

/*!
 @brief enumeration for return values
*/
enum
{
    A_SUCCESS, //!< return success
    A_FAILURE, //!< return failure
    A_INVALID, //!< return invalid
};

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief swap two different memory blocks of the same size
 @param[in] siz the size of memory block being swapped
 @param[in,out] lhs points to memory block on the left
 @param[in,out] rhs points to memory block on the right
*/
A_PUBLIC a_void_t a_swap(a_size_t siz, a_vptr_t lhs, a_vptr_t rhs);
A_PUBLIC a_void_t a_swap1(a_vptr_t lhs, a_vptr_t rhs);
A_PUBLIC a_void_t a_swap2(a_vptr_t lhs, a_vptr_t rhs);
A_PUBLIC a_void_t a_swap4(a_vptr_t lhs, a_vptr_t rhs);
A_PUBLIC a_void_t a_swap8(a_vptr_t lhs, a_vptr_t rhs);
A_PUBLIC a_void_t a_swapz(a_vptr_t lhs, a_vptr_t rhs);

/*!
 @brief Brian Kernighan and Dennis Ritchie
 @param[in] str string to be processed
 @param[in] val initial value
 @return hash value
*/
A_PUBLIC a_size_t a_hash_bkdr(a_cptr_t str, a_size_t val);
A_PUBLIC a_size_t a_hash_bkdrn(a_cptr_t ptr, a_size_t siz, a_size_t val);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A */

#endif /* A_A_H */
