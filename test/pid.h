/*!
 @file pid.h
 @brief Test proportional integral derivative controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_PID_H__
#define __TEST_PID_H__

#include "a/pid.h"

static void test(void)
{
    a_pid_s ctx[1];
    a_pid_init(ctx, A_REAL_C(0.01), -1, 1);
    a_pid_pos(ctx, 1);
    a_pid_inc(ctx);
    a_pid_off(ctx);
    a_pid_mode(ctx, A_PID_OFF);
    a_pid_kpid(ctx, 1, 1, 1);
    a_pid_time(ctx, A_REAL_C(0.001));
    a_pid_done(ctx);
    a_pid_proc(ctx, 1, 0);
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t pid_c(void);
a_int_t pid_cpp(void);
#if defined(__cplusplus)
} /* extern "C" */
#define func pid_cpp
#else /* !__cplusplus */
#define func pid_c
#endif /* __cplusplus */
a_int_t func(void)
{
    test();
    return A_SUCCESS;
}

#endif /* __TEST_PID_H__ */
