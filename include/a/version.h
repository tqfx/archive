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
#define A_VERSION_TWEAK 0
#endif /* A_VERSION_TWEAK */

#if defined(__cplusplus)
namespace a
{

/*!
 @brief enumeration for algorithm library version
*/
enum
{
    VERSION_MAJOR = A_VERSION_MAJOR,
    VERSION_MINOR = A_VERSION_MINOR,
    VERSION_PATCH = A_VERSION_PATCH
};

} /* namespace a */
extern "C" {
#endif /* __cplusplus */
#if defined(LIBA_VERSION_C)
#undef A_INTERN
#define A_INTERN A_INLINE
#endif /* LIBA_VERSION_C */

/*!
 @brief algorithm library version string
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_cstr_t a_version(void);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_cstr_t a_version(void)
{
    return A_VERSION;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief algorithm library version major
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_uint_t a_version_major(void);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_uint_t a_version_major(void)
{
    return A_VERSION_MAJOR;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief algorithm library version minor
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_uint_t a_version_minor(void);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_uint_t a_version_minor(void)
{
    return A_VERSION_MINOR;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief algorithm library version patch
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_C)
A_EXTERN a_uint_t a_version_patch(void);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_C)
A_INTERN a_uint_t a_version_patch(void)
{
    return A_VERSION_PATCH;
}
#endif /* A_HAVE_INLINE */

#if defined(LIBA_VERSION_C)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_VERSION_C */
#if defined(__cplusplus)
} /* extern "C" */
#if defined(LIBA_VERSION_CPP)
#undef A_INTERN
#define A_INTERN
#endif /* LIBA_VERSION_CPP */
namespace a
{

/*!
 @brief algorithm library version string
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_CPP)
A_EXTERN cstr_t version(void);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_CPP)
A_INTERN cstr_t version(void)
{
    return A_VERSION;
}
#endif /* A_HAVE_INLINE */

/*!
 @brief algorithm library version major
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_CPP)
A_EXTERN uint_t version_major(void);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_CPP)
A_INTERN uint_t version_major(void)
{
    return VERSION_MAJOR;
}
#endif /* A_HAVE_INLINE */
/*!
 @brief algorithm library version minor
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_CPP)
A_EXTERN uint_t version_minor(void);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_CPP)
A_INTERN uint_t version_minor(void)
{
    return VERSION_MINOR;
}
#endif /* A_HAVE_INLINE */
/*!
 @brief algorithm library version patch
*/
#if !defined A_HAVE_INLINE || defined(LIBA_VERSION_CPP)
A_EXTERN uint_t version_patch(void);
#endif /* A_HAVE_INLINE */
#if defined(A_HAVE_INLINE) || defined(LIBA_VERSION_CPP)
A_INTERN uint_t version_patch(void)
{
    return VERSION_PATCH;
}
#endif /* A_HAVE_INLINE */

} /* namespace a */
#if defined(LIBA_VERSION_CPP)
#undef A_INTERN
#define A_INTERN static A_INLINE
#endif /* LIBA_VERSION_CPP */
#endif /* __cplusplus */

/*! @} A_VERSION */

#endif /* LIBA_VERSION_H */
