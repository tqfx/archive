#ifndef TEST_FPID_H
#define TEST_FPID_H
#define MAIN_(s, argc, argv) fpid##s(argc, argv)
#include "test.h"
#include "a/tf.h"
#include "a/fpid.h"

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
        static const a_real_t mmp[] = {               \
            A_MF_TRI, NB, NB, NM,                     \
            A_MF_TRI, NB, NM, NS,                     \
            A_MF_TRI, NM, NS, ZO,                     \
            A_MF_TRI, NS, ZO, PS,                     \
            A_MF_TRI, ZO, PS, PM,                     \
            A_MF_TRI, PS, PM, PB,                     \
            A_MF_TRI, PM, PB, PB,                     \
            A_MF_NUL};                                \
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
        a_fpid_init(ctx, ts, 7, mmp, mkp, mki, mkd,   \
                    imin, imax, omin, omax);          \
        static a_uint_t idx[A_FPID_IDX(2)];           \
        static a_real_t mms[A_FPID_MMS(2)];           \
        static a_real_t mat[A_FPID_MAT(2)];           \
        a_fpid_buff(ctx, idx, mms, mat);              \
        a_fpid_pos(ctx, omax);                        \
    } while (0)

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
    a_fpid_s ctx[2];
    A_FPID_INIT7(ctx + 0, A_REAL_C(0.01), NB, PB, -10, +10);
    a_fpid_kpid(ctx + 0, 400, 200, A_REAL_C(0.005));
    a_pid_set_dt(ctx[0].pid, A_REAL_C(0.001));
    A_FPID_INIT7(ctx + 1, A_REAL_C(0.01), NB, PB, -10, +10);
    a_fpid_kpid(ctx + 1, 400, 200, A_REAL_C(0.005));
    a_pid_set_dt(ctx[1].pid, A_REAL_C(0.001));
    a_real_t set[3] = {1, 1, 1};
    a_real_t out[3];
    a_real_t fdb[3];
    a_real_t sum[3];
    a_real_t ec[3];
    a_real_t e[3];
    a_fpid_setp(ctx + 1, 3, out, fdb, sum, ec, e);
    for (a_real_t t = 0; t < A_REAL_C(0.2); t += A_REAL_C(0.001))
    {
        a_real_t buf[3];
        buf[0] = *v0;
        buf[1] = *v1;
        buf[2] = *v2;
        a_real_t *ptr = a_fpid_outp(ctx + 1, set, buf);
        for (a_uint_t i = 0; i != 3; ++i)
        {
            a_tf_proc(tf + 1 + i, ptr[i]);
        }
        a_tf_proc(tf, a_fpid_outv(ctx + 0, 1, v[0]));
#if defined(MAIN_ONCE)
        printf(A_REAL_PRI(".3", "f ") A_REAL_PRI("", "g ") A_REAL_PRI("", "g ") A_REAL_PRI("", "g ") A_REAL_PRI("", "g ") A_REAL_PRI("", "g\n"),
               t, A_REAL_C(1.0), v[0], v0[0], v1[0], v2[0]);
#endif /* MAIN_ONCE */
    }
    a_tf_zero(tf);
    a_fpid_zero(ctx);
    char buff[A_FPID_BUF1(2)];
    a_fpid_buf1(ctx, buff, 2);
    for (a_real_t t = 0; t < A_REAL_C(0.2); t += A_REAL_C(0.001))
    {
        u[0] = a_fpid_outv(ctx, 1, v[0]);
        v[0] = a_tf_proc(tf, u[0]);
    }
    TEST_BUG(a_fpid_op(ctx) == A_FPID_EQU);
    a_fpid_set_op(ctx, A_FPID_OR_DEFAULT);
    TEST_BUG(a_fpid_op(ctx) == A_FPID_OR_DEFAULT);
    a_fpid_set_op(ctx, A_FPID_OR_ALGEBRA);
    TEST_BUG(a_fpid_op(ctx) == A_FPID_OR_ALGEBRA);
    a_fpid_set_op(ctx, A_FPID_OR_BOUNDED);
    TEST_BUG(a_fpid_op(ctx) == A_FPID_OR_BOUNDED);
    a_fpid_set_op(ctx, A_FPID_AND_DEFAULT);
    TEST_BUG(a_fpid_op(ctx) == A_FPID_AND_DEFAULT);
    a_fpid_set_op(ctx, A_FPID_AND_ALGEBRA);
    TEST_BUG(a_fpid_op(ctx) == A_FPID_AND_ALGEBRA);
    a_fpid_set_op(ctx, A_FPID_AND_BOUNDED);
    TEST_BUG(a_fpid_op(ctx) == A_FPID_AND_BOUNDED);
    a_fpid_exit(ctx);
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    test();
    return 0;
}

#endif /* TEST_FPID_H */
