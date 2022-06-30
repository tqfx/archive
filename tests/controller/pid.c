/*!
 @file pid.c
 @brief Testing Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/controller/pid.h"

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

int main(void)
{
    test();
    return 0;
}
