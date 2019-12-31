/*!
 @file fpid.c
 @brief Test Fuzzy Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/controller/fpid.h"

#define NB -3
#define NM -2
#define NS -1
#define ZO 0
#define PS +1
#define PM +2
#define PB +3

#define A_FPID_INIT7(ctx, ts, vmin, vmax, umin, umax)  \
    do                                                 \
    {                                                  \
        static const a_real_t rule_kp[] = {            \
            NB, NB, NM, NM, NS, ZO, ZO,                \
            NB, NB, NM, NS, NS, ZO, PS,                \
            NM, NM, NM, NS, ZO, PS, PS,                \
            NM, NM, NS, ZO, PS, PM, PM,                \
            NS, NS, ZO, PS, PS, PM, PM,                \
            NS, ZO, PS, PM, PM, PM, PB,                \
            ZO, ZO, PM, PM, PM, PB, PB};               \
        static const a_real_t rule_ki[] = {            \
            PB, PB, PM, PM, PS, ZO, ZO,                \
            PB, PB, PM, PS, PS, ZO, ZO,                \
            PB, PM, PS, PS, ZO, NS, NS,                \
            PM, PM, PS, ZO, NS, NM, NM,                \
            PM, PS, ZO, NS, NS, NM, NB,                \
            ZO, ZO, NS, NS, NM, NB, NB,                \
            ZO, ZO, NS, NM, NM, NB, NB};               \
        static const a_real_t rule_kd[] = {            \
            NS, PS, PB, PB, PB, PM, NS,                \
            NS, PS, PB, PM, PM, PS, ZO,                \
            ZO, PS, PM, PM, PS, PS, ZO,                \
            ZO, PS, PS, PS, PS, PS, ZO,                \
            ZO, ZO, ZO, ZO, ZO, ZO, ZO,                \
            NB, NS, NS, NS, NS, NS, NB,                \
            NB, NM, NM, NM, NS, NS, NB};               \
        static const a_real_t tmf[] = {                \
            A_MF_TRI, NB, NB, NM,                      \
            A_MF_TRI, NB, NM, NS,                      \
            A_MF_TRI, NM, NS, ZO,                      \
            A_MF_TRI, NS, ZO, PS,                      \
            A_MF_TRI, ZO, PS, PM,                      \
            A_MF_TRI, PS, PM, PB,                      \
            A_MF_TRI, PM, PB, PB,                      \
            A_MF_NONE};                                \
        a_fpid_init(ctx, ts, 7, tmf, rule_kp, rule_ki, \
                    rule_kd, vmin, vmax, umin, umax);  \
        static unsigned int idx[] = {0, 0, 0, 0};      \
        static a_real_t mat[] = {0, 0, 0, 0};          \
        static a_real_t ms[] = {0, 0, 0, 0};           \
        a_fpid_buff(ctx, ms, idx, mat);                \
    } while (0)

static void test(void)
{
    a_fpid_s ctx[1];
    A_FPID_INIT7(ctx, A_REAL_C(0.01), -3, -3, -10, +10);
    a_fpid_kpid(ctx, 1, 0, 0);
    a_fpid_time(ctx, A_REAL_C(0.001));
    for (a_real_t i = -3; i < 3; i += A_REAL_C(0.001))
    {
        a_fpid_proc(ctx, 0, i);
    }
    a_fpid_done(ctx);
}

int main(void)
{
    test();
    return 0;
}
