/*!
 @file pid.h
 @brief Test proportional integral derivative controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_PID_H__
#define __TEST_PID_H__

#include "a/tf.h"
#include "a/pid.h"
#include <stdio.h>

static void test(void)
{
    a_real_t num[] = {6.59492796e-05, 6.54019884e-05};
    a_real_t den[] = {-1.97530991, 0.97530991};
    a_real_t u[a_arrayof(num)] = {0};
    a_real_t v[a_arrayof(den)] = {0};
    a_tf_s tf[1];
    a_tf_init(tf, a_arrayof(num), num, u, a_arrayof(den), den, v);
    a_pid_s ctx[1];
    a_pid_init(ctx, A_REAL_C(0.01), -10, +10);
    a_pid_off(a_pid_inc(a_pid_pos(ctx, 1)));
    a_pid_kpid(ctx, 10, A_REAL_C(0.01), A_REAL_C(0.1));
    a_pid_time(ctx, A_REAL_C(0.001));
    a_pid_mode(ctx, A_PID_POS);
    for (a_real_t t = 0; t < A_REAL_C(0.2); t += A_REAL_C(0.001))
    {
        u[0] = a_pid_proc(ctx, 1, v[0]);
        v[0] = a_tf_proc(tf, u[0]);
#if defined(__cplusplus)
        printf(A_REAL_PRI(".3", "f ") A_REAL_PRI(, "g ") A_REAL_PRI(, "g\n"), t, A_REAL_C(1.0), v[0]);
#endif /* __cplusplus */
    }
    a_pid_done(ctx);
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
