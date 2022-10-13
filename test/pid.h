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
    a_real_t num[] = {A_REAL_C(6.59492796e-05), A_REAL_C(6.54019884e-05)};
    a_real_t den[] = {A_REAL_C(-1.97530991), A_REAL_C(0.97530991)};
    a_real_t num1[] = {A_REAL_C(5.59492796e-05), A_REAL_C(5.54019884e-05)};
    a_real_t den1[] = {A_REAL_C(-1.97530991), A_REAL_C(0.97530991)};
    a_real_t num2[] = {A_REAL_C(7.59492796e-05), A_REAL_C(7.54019884e-05)};
    a_real_t den2[] = {A_REAL_C(-1.97530991), A_REAL_C(0.97530991)};
    a_real_t u[a_arrayof(num)] = {0};
    a_real_t v[a_arrayof(den)] = {0};
    a_real_t u0[a_arrayof(num)] = {0};
    a_real_t v0[a_arrayof(den)] = {0};
    a_real_t u1[a_arrayof(num1)] = {0};
    a_real_t v1[a_arrayof(den1)] = {0};
    a_real_t u2[a_arrayof(num2)] = {0};
    a_real_t v2[a_arrayof(den2)] = {0};
    a_tf_s tf[4];
    a_tf_init(tf + 0, a_arrayof(num), num, u, a_arrayof(den), den, v);
    a_tf_init(tf + 1, a_arrayof(num), num, u0, a_arrayof(den), den, v0);
    a_tf_init(tf + 2, a_arrayof(num1), num1, u1, a_arrayof(den1), den1, v1);
    a_tf_init(tf + 3, a_arrayof(num2), num2, u2, a_arrayof(den2), den2, v2);
    a_pid_s ctx[2];
    a_pid_init(ctx + 0, A_REAL_C(0.01), -10, +10);
    a_pid_init(ctx + 1, A_REAL_C(0.01), -10, +10);
    a_pid_off(a_pid_inc(a_pid_pos(ctx + 0, 10)));
    a_pid_off(a_pid_inc(a_pid_pos(ctx + 1, 10)));
    a_pid_kpid(ctx + 0, 10, A_REAL_C(0.01), A_REAL_C(0.1));
    a_pid_kpid(ctx + 1, 10, A_REAL_C(0.01), A_REAL_C(0.1));
    a_pid_set_dt(ctx + 0, A_REAL_C(0.001));
    a_pid_set_dt(ctx + 1, A_REAL_C(0.001));
    a_pid_set_reg(ctx + 0, A_PID_POS);
    a_pid_set_reg(ctx + 1, A_PID_POS);
    a_real_t set[3] = {1, 1, 1};
    a_real_t out[3];
    a_real_t fdb[3];
    a_real_t sum[3];
    a_real_t ec[3];
    a_real_t e[3];
    a_pid_setp(ctx + 1, 3, out, fdb, sum, ec, e);
    for (a_real_t t = 0; t < A_REAL_C(0.4); t += A_REAL_C(0.001))
    {
        a_real_t buf[3] = {v0[0], v1[0], v2[0]};
        a_real_t *ptr = a_pid_outp(ctx + 1, set, buf);
        for (a_uint_t i = 0; i != 3; ++i)
        {
            a_tf_proc(tf + 1 + i, ptr[i]);
        }
        a_tf_proc(tf, a_pid_outv(ctx + 0, 1, v[0]));
#if defined(__cplusplus)
        printf(A_REAL_PRI(".3", "f ") A_REAL_PRI(, "g ") A_REAL_PRI(, "g ") A_REAL_PRI(, "g ") A_REAL_PRI(, "g ") A_REAL_PRI(, "g\n"),
               t, A_REAL_C(1.0), v[0], v0[0], v1[0], v2[0]);
#endif /* __cplusplus */
    }
    a_pid_exit(ctx + 0);
    a_pid_exit(ctx + 1);
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
