#ifndef TEST_POLYTRACK_H
#define TEST_POLYTRACK_H

#include "a/polytrack.h"

static void test(void)
{
    static a_real_t t[2] = {0, 10};
    static a_real_t q[2] = {0, 10};
    static a_real_t v[2] = {0, 10};
    static a_real_t a[2] = {0, 10};
    static a_real_t j[2] = {0, 10};
    static a_real_t source[5] = {0, 0, 0, 0, 0};
    static a_real_t target[5] = {10, 10, 10, 10, 10};
    static a_real_t out[4];
    {
        a_polytrack3_s ctx[1];
        a_polytrack3_init1(ctx, t, q, v);
        a_polytrack3_init2(ctx, source, target);
        a_polytrack3_init(ctx, 0, 10, 0, 10, 0, 10);
        a_polytrack3_pos(ctx, 0);
        a_polytrack3_vec(ctx, 0);
        a_polytrack3_acc(ctx, 0);
        a_polytrack3_out(ctx, 0, out);
    }
    {
        a_polytrack5_s ctx[1];
        a_polytrack5_init1(ctx, t, q, v, a);
        a_polytrack5_init2(ctx, source, target);
        a_polytrack5_init(ctx, 0, 10, 0, 10, 0, 10, 0, 10);
        a_polytrack5_pos(ctx, 0);
        a_polytrack5_vec(ctx, 0);
        a_polytrack5_acc(ctx, 0);
        a_polytrack5_out(ctx, 0, out);
    }
    {
        a_polytrack7_s ctx[1];
        a_polytrack7_init1(ctx, t, q, v, a, j);
        a_polytrack7_init2(ctx, source, target);
        a_polytrack7_init(ctx, 0, 10, 0, 10, 0, 10, 0, 10, 0, 10);
        a_polytrack7_pos(ctx, 0);
        a_polytrack7_vec(ctx, 0);
        a_polytrack7_acc(ctx, 0);
        a_polytrack7_jer(ctx, 0);
        a_polytrack7_out(ctx, 0, out);
    }
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t polytrack_c(void);
a_int_t polytrack_cpp(void);
#if defined(__cplusplus)
} /* extern "C" */
#define func polytrack_cpp
#else /* !__cplusplus */
#define func polytrack_c
#endif /* __cplusplus */
a_int_t func(void)
{
    test();
    return A_SUCCESS;
}

#endif /* TEST_POLYTRACK_H */
