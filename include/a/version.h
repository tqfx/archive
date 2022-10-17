/*!
 @file version.h
 @brief algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef A_VERSION_H
#define A_VERSION_H

#include "a.h"

/*!
 @ingroup A
 @addtogroup A_VERSION algorithm library version based on C
 @{
*/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 @brief algorithm library version string
*/
#if !defined A_INLINE || defined(A_VERSION_I)
A_PUBLIC a_cstr_t a_version(void);
#endif /* A_INLINE */
#if defined(A_INLINE) || defined(A_VERSION_I)
A_INLINE a_cstr_t a_version(void)
{
    return A_VERSION;
}
#endif /* A_INLINE */

/*!
 @brief algorithm library version major
*/
#if !defined A_INLINE || defined(A_VERSION_I)
A_PUBLIC a_uint_t a_version_major(void);
#endif /* A_INLINE */
#if defined(A_INLINE) || defined(A_VERSION_I)
A_INLINE a_uint_t a_version_major(void)
{
    return A_VERSION_MAJOR;
}
#endif /* A_INLINE */

/*!
 @brief algorithm library version minor
*/
#if !defined A_INLINE || defined(A_VERSION_I)
A_PUBLIC a_uint_t a_version_minor(void);
#endif /* A_INLINE */
#if defined(A_INLINE) || defined(A_VERSION_I)
A_INLINE a_uint_t a_version_minor(void)
{
    return A_VERSION_MINOR;
}
#endif /* A_INLINE */

/*!
 @brief algorithm library version patch
*/
#if !defined A_INLINE || defined(A_VERSION_I)
A_PUBLIC a_uint_t a_version_patch(void);
#endif /* A_INLINE */
#if defined(A_INLINE) || defined(A_VERSION_I)
A_INLINE a_uint_t a_version_patch(void)
{
    return A_VERSION_PATCH;
}
#endif /* A_INLINE */

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_VERSION */

#endif /* A_VERSION_H */
