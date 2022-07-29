/*!
 @file a.h
 @brief algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_A_H__
#define __A_A_H__

#include "a.config.h"

/* extern "C" */
#if defined(__cplusplus)
#define A_EXTERN_C extern "C"
#define A_EXTERN_C_ENTER extern "C" {
#define A_EXTERN_C_LEAVE }
#else /* !__cplusplus */
#define A_EXTERN_C
#define A_EXTERN_C_ENTER
#define A_EXTERN_C_LEAVE
#endif /* __cplusplus */

/*! @cond */

#if defined(__MINGW32__)
#undef __USE_MINGW_ANSI_STDIO
#define __USE_MINGW_ANSI_STDIO
#endif /* __MINGW32__ */

/* has builtin */
#if defined(__has_builtin)
#define a_has_builtin(...) __has_builtin(__VA_ARGS__)
#define a_likely(...) __builtin_expect((__VA_ARGS__), 1)
#define a_unlikely(...) __builtin_expect((__VA_ARGS__), 0)
#else /* !__has_builtin */
#define a_has_builtin(...) 0
#define a_likely(...) (__VA_ARGS__)
#define a_unlikely(...) (__VA_ARGS__)
#endif /* __has_builtin */

/* has feature */
#if defined(__has_feature)
#define a_has_feature(...) __has_feature(__VA_ARGS__)
#else /* !__has_feature */
#define a_has_feature(...) 0
#endif /* __has_feature */

/* has include */
#if defined(__has_include)
#define a_has_include(...) __has_include(__VA_ARGS__)
#else /* !__has_include */
#define a_has_include(...) 0
#endif /* __has_include */

/* has warning */
#if defined(__has_warning)
#define a_has_warning(...) __has_warning(__VA_ARGS__)
#else /* !__has_warning */
#define a_has_warning(...) 0
#endif /* __has_warning */

/* has attribute */
#if defined(__has_attribute)
#define a_has_attribute(...) __has_attribute(__VA_ARGS__)
#else /* !__has_attribute */
#define a_has_attribute(...) 0
#define __attribute__(...)
#endif /* __has_attribute */

/* attribute deprecated */
#if defined(_WIN32) || defined(__CYGWIN__)
#define A_DEPRECATED __declspec(deprecated)
#elif a_has_attribute(deprecated)
#define A_DEPRECATED __attribute__((deprecated))
#else /* !a_has_attribute(deprecated) */
#define A_DEPRECATED
#endif /* a_has_attribute(deprecated) */

/* attribute inline */
#if defined(_MSC_VER)
#define A_INLINE_FORCE static __forceinline
#elif a_has_attribute(always_inline)
#define A_INLINE_FORCE static __inline __attribute__((always_inline))
#else /* !_MSC_VER */
#define A_INLINE_FORCE static __inline
#endif /* _MSC_VER */
#define A_INLINE static __inline

/* attribute visibility */
#if defined(_WIN32) || defined(__CYGWIN__)
#define A_EXPORT __declspec(dllexport)
#define A_IMPORT __declspec(dllimport)
#define A_HIDDEN
#elif a_has_attribute(visibility)
#define A_EXPORT __attribute__((visibility("default")))
#define A_IMPORT __attribute__((visibility("default")))
#define A_HIDDEN __attribute__((visibility("hidden")))
#else /* !a_has_attribute(visibility) */
#define A_EXPORT
#define A_IMPORT
#define A_HIDDEN
#endif /* a_has_attribute(visibility) */
#if defined(A_EXPORTS)
#define A_PUBLIC A_EXPORT
#elif defined(A_SHARED)
#define A_PUBLIC A_IMPORT
#else /* !A_PUBLIC */
#define A_PUBLIC
#endif /* A_PUBLIC */

/*! @endcond */

/*!
 @addtogroup A algorithm library based on C
 @{
*/

/* keywords */
#if defined(__cplusplus)
#define a_register register
#else /* !__cplusplus */
#define a_register
#endif /* __cplusplus */
#define a_volatile volatile
#define a_restrict restrict

#include <stddef.h>
#include <stdint.h>

typedef int a_bool_t;

#if defined(__cplusplus)
#define a_true true
#define a_false false
#else /* !__cplusplus */
#define a_true (!0)
#define a_false (0)
#endif /* __cplusplus */

typedef void a_void_t;

#define a_zero 0
#if defined(__cplusplus)
#define a_cast(T, ...) static_cast<T>(__VA_ARGS__)
#define a_null nullptr
#define a_noarg_t
#else /* !__cplusplus */
#define a_cast(T, ...) (T)(__VA_ARGS__)
#define a_null NULL
#define a_noarg_t a_void_t
#endif /* __cplusplus */
#define a_noret_t a_void_t

typedef size_t a_size_t;

#define A_SIZE_MAX SIZE_MAX

// clang-format off

typedef  int8_t a_i8_t;
typedef uint8_t a_u8_t;

#define A_I8_C(X)  INT8_C(X)
#define A_U8_C(X) UINT8_C(X)
#define A_I8_MIN   INT8_MIN
#define A_I8_MAX   INT8_MAX
#define A_U8_MAX  UINT8_MAX

typedef  int16_t a_i16_t;
typedef uint16_t a_u16_t;

#define A_I16_C(X)  INT16_C(X)
#define A_U16_C(X) UINT16_C(X)
#define A_I16_MIN   INT16_MIN
#define A_I16_MAX   INT16_MAX
#define A_U16_MAX  UINT16_MAX

typedef  int32_t a_i32_t;
typedef uint32_t a_u32_t;

#define A_I32_C(X)  INT32_C(X)
#define A_U32_C(X) UINT32_C(X)
#define A_I32_MIN   INT32_MIN
#define A_I32_MAX   INT32_MAX
#define A_U32_MAX  UINT32_MAX

typedef  int64_t a_i64_t;
typedef uint64_t a_u64_t;

#define A_I64_C(X)  INT64_C(X)
#define A_U64_C(X) UINT64_C(X)
#define A_I64_MIN   INT64_MIN
#define A_I64_MAX   INT64_MAX
#define A_U64_MAX  UINT64_MAX

typedef  intmax_t a_imax_t;
typedef uintmax_t a_umax_t;

#define A_IMAX_C(X)  INTMAX_C(X)
#define A_UMAX_C(X) UINTMAX_C(X)
#define A_IMAX_MIN   INTMAX_MIN
#define A_IMAX_MAX   INTMAX_MAX
#define A_UMAX_MAX  UINTMAX_MAX

typedef  intptr_t a_iptr_t;
typedef uintptr_t a_uptr_t;

#define A_IPTR_C(X)  INTPTR_C(X)
#define A_UPTR_C(X) UINTPTR_C(X)
#define A_IPTR_MIN   INTPTR_MIN
#define A_IPTR_PTR   INTPTR_PTR
#define A_UPTR_PTR  UINTPTR_PTR

typedef ptrdiff_t a_ptrdiff_t;

#define A_PTRDIFF_MIN PTRDIFF_MIN
#define A_PTRDIFF_MAX PTRDIFF_MAX

typedef          int  a_int_t;
typedef          int a_sint_t;
typedef unsigned int a_uint_t;

typedef unsigned char  a_byte_t;
typedef          char  a_char_t;
typedef   signed char a_schar_t;
typedef unsigned char a_uchar_t;

typedef       char * a_str_t;
typedef const char *a_cstr_t;
typedef       void *a_vptr_t;
typedef const void *a_cptr_t;

typedef       float a_f32_t;
typedef      double a_f64_t;
typedef long double a_f128_t;

// clang-format on

/*!
 @addtogroup A_REAL real number
 @{
*/

#ifndef A_REAL_BITS
#define A_REAL_BITS 64
#endif // real bits
#if A_REAL_BITS == 32

/*! @brief real number stored using `float` */
typedef float a_real_t;

/*!
 @brief expands to a floating-point constant expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_C(X) X##F
/*!
 @brief expands to a floating-point function expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_F(F, ...) F##f(__VA_ARGS__)

/*! @brief Format constants for the fprintf family of functions */
#define A_REAL_PRI(F, ...) "%" F __VA_ARGS__
/*! @brief Format constants for the fscanf family of functions */
#define A_REAL_SCN(F, ...) "%" F __VA_ARGS__

#elif A_REAL_BITS == 64

/*! @brief real number stored using `double` */
typedef double a_real_t;

/*!
 @brief expands to a floating-point constant expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_C(X) X
/*!
 @brief expands to a floating-point function expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_F(F, ...) F(__VA_ARGS__)

/*! @brief Format constants for the fprintf family of functions */
#define A_REAL_PRI(F, ...) "%" F __VA_ARGS__
/*! @brief Format constants for the fscanf family of functions */
#define A_REAL_SCN(F, ...) "%" F "l" __VA_ARGS__

#elif A_REAL_BITS == 128

/*! @brief real number stored using `long double` */
typedef long double a_real_t;

/*!
 @brief expands to a floating-point constant expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_C(X) X##L
/*!
 @brief expands to a floating-point function expression
 having the value specified by its argument and the type @ref a_real_t
*/
#define A_REAL_F(F, ...) F##l(__VA_ARGS__)

/*! @brief Format constants for the fprintf family of functions */
#define A_REAL_PRI(F, ...) "%" F "L" __VA_ARGS__
/*! @brief Format constants for the fscanf family of functions */
#define A_REAL_SCN(F, ...) "%" F "L" __VA_ARGS__

#endif /* A_REAL_BITS */

/*! @} A_REAL */

/*!
 @brief offset of a structure member
 @param type structure type
 @param member member variable
*/
#if defined(offsetof)
#define a_offsetof(type, member) offsetof(type, member)
#else /* !offsetof */
#define a_offsetof(type, member) (size_t)(&(((type *)0)->member))
#endif /* offsetof */

/*!
 @brief container of a structure member
 @param ptr pointer to a member variable
 @param type structure type
 @param member member variable
*/
#define a_container_of(ptr, type, member) ((type *)((size_t)(ptr)-a_offsetof(type, member)))

/*!
 @brief iterate from 0 to n and not include n
 @param I index type of the iteration
 @param i index variable of the iteration
 @param n final value of the iteration
*/
#define a_forenum(I, i, n) for (I i = 0; i != (n); ++i)
/*!
 @brief iterate from n to 0 and not include n
 @param I index type of the iteration
 @param i index variable of the iteration
 @param n final value of the iteration
*/
#define a_forenum_reverse(I, i, n) for (I i = (n); i--;)

/*!
 @brief iterate over an array
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_foreach(T, it, ptr, num)                                        \
    for (T *it = a_cast(T *, ptr),                                        \
           *it##_ = a_likely(it != a_null) ? it + (num) : a_null; \
         it != it##_; ++it)
/*!
 @brief iterate over an array in reverse
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param num number of elements in this array
*/
#define a_foreach_reverse(T, it, ptr, num)                                             \
    for (T *it##_ = a_likely((ptr) != a_null) ? a_cast(T *, ptr) - 1 : a_null, \
           *it = a_likely((ptr) != a_null) ? it##_ + (num) : a_null;           \
         it != it##_; --it)

/*!
 @brief iterate over an array
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param end the end address of this array
*/
#define a_iterate(T, it, ptr, end) \
    for (T *it = a_cast(T *, ptr), *it##_ = a_cast(T *, end); it != it##_; ++it)

/*!
 @brief iterate over an array in reverse
 @param T the element type in this array
 @param it pointer to the current element
 @param ptr starting address of this array
 @param end the end address of this array
*/
#define a_iterate_reverse(T, it, ptr, end)                                             \
    for (T *it##_ = a_likely((ptr) != a_null) ? a_cast(T *, ptr) - 1 : a_null, \
           *it = a_likely((end) != a_null) ? a_cast(T *, end) - 1 : a_null;    \
         it != it##_; --it)

/*!
 @brief enumeration for return values
*/
enum
{
    A_SUCCESS, //!< return success
    A_FAILURE, //!< return failure
    A_INVALID, //!< return invalid
};

/*! @} A */

#endif /* __A_A_H__ */
