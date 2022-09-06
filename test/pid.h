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
a_int_t main_c(a_noarg_t);
a_int_t main_cpp(a_noarg_t);
#if defined(__cplusplus)
} /* extern "C" */
#define test_main main_cpp
#else /* !__cplusplus */
#define test_main main_c
#endif /* __cplusplus */
a_int_t test_main(a_noarg_t)
{
    test();
    return A_SUCCESS;
}

#endif /* __TEST_PID_H__ */
