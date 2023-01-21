/*!
 @file version.h
 @brief algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef LIBA_VERSION_H
#define LIBA_VERSION_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_VERSION algorithm library version
 @{
*/

/*! algorithm library version string */
#ifndef A_VERSION
#define A_VERSION "0.0.0"
#endif /* A_VERSION */

/*! algorithm library version major */
#ifndef A_VERSION_MAJOR
#define A_VERSION_MAJOR 0
#endif /* A_VERSION_MAJOR */

/*! algorithm library version minor */
#ifndef A_VERSION_MINOR
#define A_VERSION_MINOR 0
#endif /* A_VERSION_MINOR */

/*! algorithm library version patch */
#ifndef A_VERSION_PATCH
#define A_VERSION_PATCH 0
#endif /* A_VERSION_PATCH */

/*! algorithm library version tweak */
#ifndef A_VERSION_TWEAK
#define A_VERSION_TWEAK A_U64_C(0)
#endif /* A_VERSION_TWEAK */

#if defined(__cplusplus)
#define A_VERSION_C(maj, min, pat) a_version_s(maj, min, pat)
#else /* !__cplusplus */
// clang-format off
#define A_VERSION_C(maj, min, pat) {maj, min, pat}
// clang-format on
#endif /* __cplusplus */

/*!
 @brief instance structure for version
*/
typedef struct a_version_s
{
#if defined(__cplusplus)
    A_PUBLIC a_bool_t operator<(const a_version_s &ver) const;
    A_PUBLIC a_bool_t operator>(const a_version_s &ver) const;
    A_PUBLIC a_bool_t operator<=(const a_version_s &ver) const;
    A_PUBLIC a_bool_t operator>=(const a_version_s &ver) const;
    A_PUBLIC a_bool_t operator==(const a_version_s &ver) const;
    A_PUBLIC a_bool_t operator!=(const a_version_s &ver) const;
    A_PUBLIC a_version_s(a_uint_t maj = 0,
                         a_uint_t min = 0,
                         a_uint_t pat = 0)
        : major(maj)
        , minor(min)
        , patch(pat)
    {
    }
#endif /* __cplusplus */
    a_uint_t major;
    a_uint_t minor;
    a_uint_t patch;
} a_version_s;

#if defined(__cplusplus)
namespace a
{

/*! algorithm library version string */
const cstr_t VERSION = A_VERSION;
/*! algorithm library version major */
const uint_t VERSION_MAJOR = A_VERSION_MAJOR;
/*! algorithm library version minor */
const uint_t VERSION_MINOR = A_VERSION_MINOR;
/*! algorithm library version patch */
const uint_t VERSION_PATCH = A_VERSION_PATCH;
/*! algorithm library version tweak */
const u64_t VERSION_TWEAK = A_VERSION_TWEAK;
/* instance structure for version */
typedef a_version_s version;

} /* namespace a */
extern "C" {
#endif /* __cplusplus */

/*!
 @brief algorithm library version string
*/
A_EXTERN a_cstr_t a_version(void);

/*!
 @brief algorithm library version major
*/
A_EXTERN a_uint_t a_version_major(void);

/*!
 @brief algorithm library version minor
*/
A_EXTERN a_uint_t a_version_minor(void);

/*!
 @brief algorithm library version patch
*/
A_EXTERN a_uint_t a_version_patch(void);

/*!
 @brief compare the version lhs with the version rhs
 @param[in] lhs version structure to be compared
 @param[in] rhs version structure to be compared
 @return relationship between the versions
  @retval <0 version lhs < version rhs
  @retval >0 version lhs > version rhs
  @retval 0 version lhs == version rhs
*/
A_EXTERN a_int_t a_version_cmp(const a_version_s *lhs, const a_version_s *rhs);

/*!
 @brief algorithm library version check
*/
A_EXTERN a_int_t a_version_check(a_uint_t major, a_uint_t minor, a_uint_t patch);
#define a_version_check() a_version_check(A_VERSION_MAJOR, A_VERSION_MINOR, A_VERSION_PATCH)

#if defined(LIBA_VERSION_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_VERSION_C */

/*!
 @brief version lhs less than version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_lt(const a_version_s *lhs, const a_version_s *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_lt(const a_version_s *lhs, const a_version_s *rhs)
{
    if (lhs->major < rhs->major)
    {
        return A_TRUE;
    }
    if (lhs->minor < rhs->minor)
    {
        return A_TRUE;
    }
    if (lhs->patch < rhs->patch)
    {
        return A_TRUE;
    }
    return A_FALSE;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs greater than version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_gt(const a_version_s *lhs, const a_version_s *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_gt(const a_version_s *lhs, const a_version_s *rhs)
{
    if (lhs->major > rhs->major)
    {
        return A_TRUE;
    }
    if (lhs->minor > rhs->minor)
    {
        return A_TRUE;
    }
    if (lhs->patch > rhs->patch)
    {
        return A_TRUE;
    }
    return A_FALSE;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs less than or equal version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_le(const a_version_s *lhs, const a_version_s *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_le(const a_version_s *lhs, const a_version_s *rhs)
{
    return !a_version_lt(rhs, lhs);
}
#endif /* A_HAVE_INLINE */
/*!
 @brief version lhs greater than or equal version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_ge(const a_version_s *lhs, const a_version_s *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_ge(const a_version_s *lhs, const a_version_s *rhs)
{
    return !a_version_gt(rhs, lhs);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs equal version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_eq(const a_version_s *lhs, const a_version_s *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_eq(const a_version_s *lhs, const a_version_s *rhs)
{
    return (lhs->major == rhs->major) && (lhs->minor == rhs->minor) && (lhs->patch == rhs->patch);
}
#endif /* A_HAVE_INLINE */

/*!
 @brief version lhs not equal version rhs
 @param[in] lhs operand on the left
 @param[in] rhs operand on the right
 @return result of comparison
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_bool_t a_version_ne(const a_version_s *lhs, const a_version_s *rhs);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_bool_t a_version_ne(const a_version_s *lhs, const a_version_s *rhs)
{
    return (lhs->major != rhs->major) || (lhs->minor != rhs->minor) || (lhs->patch != rhs->patch);
}
#endif /* A_HAVE_INLINE */

#if defined(LIBA_VERSION_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_VERSION_C */

#if defined(__cplusplus)
} /* extern "C" */
namespace a
{

/*!
 @brief algorithm library version major
*/
A_EXTERN uint_t version_major(void);

/*!
 @brief algorithm library version minor
*/
A_EXTERN uint_t version_minor(void);

/*!
 @brief algorithm library version patch
*/
A_EXTERN uint_t version_patch(void);

} /* namespace a */
#endif /* __cplusplus */

/*! @} A_VERSION */

#endif /* LIBA_VERSION_H */
