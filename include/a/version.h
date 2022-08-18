/*!
 @file version.h
 @brief algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_VERSION_H__
#define __A_VERSION_H__

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
A_PUBLIC const a_char_t *a_version(a_noarg_t);

/*!
 @brief algorithm library version major
*/
A_PUBLIC a_uint_t a_version_major(a_noarg_t);
/*!
 @brief algorithm library version minor
*/
A_PUBLIC a_uint_t a_version_minor(a_noarg_t);
/*!
 @brief algorithm library version patch
*/
A_PUBLIC a_uint_t a_version_patch(a_noarg_t);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

/*! @} A_VERSION */

#endif /* __A_VERSION_H__ */
