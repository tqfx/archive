/*!
 @file pid.h
 @brief internal proportional integral derivative controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef PID_H
#define PID_H

#include "a/pid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_HIDDEN a_real_t a_pid_outv_(a_pid_s *ctx, a_uint_t mode, a_real_t set, a_real_t fdb, a_real_t ec, a_real_t e);
A_HIDDEN a_real_t a_pid_outp_(a_pid_s *ctx, a_uint_t mode, a_real_t set, a_real_t fdb, a_real_t ec, a_real_t e, a_uint_t i);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* PID_H */
