/*!
 @file polytrack.cpp
 @brief Testing polynomial trajectory
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/poly/poly.h"
#include "a/poly/polytrack.h"

static void test(void)
{
    static a_real_t source[5] = {0, 0, 0, 0, 0};
    static a_real_t target[5] = {10, 10, 10, 10, 10};
    static a_real_t out[4];
    a_horner(target, 5, 2);
    a_hornerr(target, 5, 2);
    {
        a_polytrack3_s ctx[1];
        a_polytrack3_init(ctx, source, target);
        a_polytrack3_pos(ctx, 0);
        a_polytrack3_vec(ctx, 0);
        a_polytrack3_acc(ctx, 0);
        a_polytrack3_all(ctx, 0, out);
    }
    {
        a_polytrack5_s ctx[1];
        a_polytrack5_init(ctx, source, target);
        a_polytrack5_pos(ctx, 0);
        a_polytrack5_vec(ctx, 0);
        a_polytrack5_acc(ctx, 0);
        a_polytrack5_all(ctx, 0, out);
    }
    {
        a_polytrack7_s ctx[1];
        a_polytrack7_init(ctx, source, target);
        a_polytrack7_pos(ctx, 0);
        a_polytrack7_vec(ctx, 0);
        a_polytrack7_acc(ctx, 0);
        a_polytrack7_jer(ctx, 0);
        a_polytrack7_all(ctx, 0, out);
    }
}

int main(void)
{
    test();
    return 0;
}
