/*!
 @file a.h
 @brief algorithm library version
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __A_VERSION_H__
#define __A_VERSION_H__

#include "a.h"

A_EXTERN_C_ENTER

/*!
 @ingroup A
 @addtogroup A_VERSION algorithm library version based on C
 @{
*/

/*!
 @brief algorithm library version string
*/
A_PUBLIC const a_char_t *a_version(a_void_t);

A_PUBLIC a_uint_t a_version_major(a_void_t);
A_PUBLIC a_uint_t a_version_minor(a_void_t);
A_PUBLIC a_uint_t a_version_patch(a_void_t);

/*! @} A_VERSION */

A_EXTERN_C_LEAVE

#endif /* __A_VERSION_H__ */
