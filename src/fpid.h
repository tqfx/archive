/*!
 @file fpid.h
 @brief internal fuzzy proportional integral derivative controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __FPID_H__
#define __FPID_H__

#include "a/fpid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN a_real_t a_fpid_op(a_real_t a, a_real_t b);
A_HIDDEN a_uint_t a_fpid_mf(const a_real_t *a, a_real_t x, a_uint_t *idx, a_real_t *mms);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __FPID_H__ */
