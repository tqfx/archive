/*!
 @file fpid.h
 @brief Test fuzzy proportional integral derivative controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_FPID_H__
#define __TEST_FPID_H__

#include "a/tf.h"
#include "a/fpid.h"
#include <stdio.h>

#define NB -3
#define NM -2
#define NS -1
#define ZO 0
#define PS +1
#define PM +2
#define PB +3

#define A_FPID_INIT7(ctx, ts, imin, imax, omin, omax) \
    do                                                \
    {                                                 \
        static const a_real_t mkp[] = {               \
            NB, NB, NM, NM, NS, ZO, ZO,               \
            NB, NB, NM, NS, NS, ZO, PS,               \
            NM, NM, NM, NS, ZO, PS, PS,               \
            NM, NM, NS, ZO, PS, PM, PM,               \
            NS, NS, ZO, PS, PS, PM, PM,               \
            NS, ZO, PS, PM, PM, PM, PB,               \
            ZO, ZO, PM, PM, PM, PB, PB};              \
        static const a_real_t mki[] = {               \
            PB, PB, PM, PM, PS, ZO, ZO,               \
            PB, PB, PM, PS, PS, ZO, ZO,               \
            PB, PM, PS, PS, ZO, NS, NS,               \
            PM, PM, PS, ZO, NS, NM, NM,               \
            PM, PS, ZO, NS, NS, NM, NB,               \
            ZO, ZO, NS, NS, NM, NB, NB,               \
            ZO, ZO, NS, NM, NM, NB, NB};              \
        static const a_real_t mkd[] = {               \
            NS, PS, PB, PB, PB, PM, NS,               \
            NS, PS, PB, PM, PM, PS, ZO,               \
            ZO, PS, PM, PM, PS, PS, ZO,               \
            ZO, PS, PS, PS, PS, PS, ZO,               \
            ZO, ZO, ZO, ZO, ZO, ZO, ZO,               \
            NB, NS, NS, NS, NS, NS, NB,               \
            NB, NM, NM, NM, NS, NS, NB};              \
        static const a_real_t mma[] = {               \
            A_MF_TRI, NB, NB, NM,                     \
            A_MF_TRI, NB, NM, NS,                     \
            A_MF_TRI, NM, NS, ZO,                     \
            A_MF_TRI, NS, ZO, PS,                     \
            A_MF_TRI, ZO, PS, PM,                     \
            A_MF_TRI, PS, PM, PB,                     \
            A_MF_TRI, PM, PB, PB,                     \
            A_MF_NUL};                                \
        a_fpid_init(ctx, ts, 7, mma, mkp, mki, mkd,   \
                    imin, imax, omin, omax);          \
        static a_uint_t idx[A_FPID_IDX(2)];           \
        static a_real_t mms[A_FPID_MMS(2)];           \
        static a_real_t mat[A_FPID_MAT(2)];           \
        a_fpid_buff(ctx, idx, mms, mat);              \
        a_fpid_pos(ctx, omax);                        \
    } while (0)

static void test(void)
{
    a_real_t num[] = {6.59492796e-05, 6.54019884e-05};
    a_real_t den[] = {-1.97530991, 0.97530991};
    a_real_t u[a_arrayof(num)] = {0};
    a_real_t v[a_arrayof(den)] = {0};
    a_tf_s tf[1];
    a_tf_init(tf, a_arrayof(num), num, u, a_arrayof(den), den, v);
    a_fpid_s ctx[1];
    A_FPID_INIT7(ctx, A_REAL_C(0.01), -3, -3, -10, +10);
    a_fpid_kpid(ctx, 400, 200, A_REAL_C(0.005));
    a_fpid_time(ctx, A_REAL_C(0.001));
    for (a_real_t t = 0; t < A_REAL_C(0.2); t += A_REAL_C(0.001))
    {
        u[0] = a_fpid_proc(ctx, 1, v[0]);
        v[0] = a_tf_proc(tf, u[0]);
#if defined(__cplusplus)
        printf(A_REAL_PRI(".3", "f ") A_REAL_PRI(, "g ") A_REAL_PRI(, "g\n"), t, A_REAL_C(1.0), v[0]);
#endif /* __cplusplus */
    }
    a_tf_zero(tf);
    a_fpid_done(ctx);
    char buff[A_FPID_BUF1(2)];
    a_fpid_buf1(ctx, buff, 2);
    for (a_real_t t = 0; t < A_REAL_C(0.2); t += A_REAL_C(0.001))
    {
        u[0] = a_fpid_proc(ctx, 1, v[0]);
        v[0] = a_tf_proc(tf, u[0]);
    }
    a_fpid_done(ctx);
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t fpid_c(void);
a_int_t fpid_cpp(void);
#if defined(__cplusplus)
} /* extern "C" */
#define func fpid_cpp
#else /* !__cplusplus */
#define func fpid_c
#endif /* __cplusplus */
a_int_t func(void)
{
    test();
    return A_SUCCESS;
}

#endif /* __TEST_FPID_H__ */
