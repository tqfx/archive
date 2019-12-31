/*!
 @file pid.c
 @brief Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/controller/pid.h"
#include "a/misc/math.h"

#include <assert.h>

void a_pid_time(a_pid_s *ctx, a_real_t ts)
{
    assert(ctx);
    a_real_t t = ts / ctx->ts;
    ctx->ki *= t;
    ctx->kd /= t;
    ctx->ts = ts;
}

void a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
{
    assert(ctx);
    ctx->kp = kp;
    ctx->ki = ki * ctx->ts;
    ctx->kd = kd / ctx->ts;
}

void a_pid_init(a_pid_s *ctx, a_real_t ts, a_real_t min, a_real_t max)
{
    assert(ctx);
    assert(ts > 0);
    assert(min < max);
    ctx->mode = A_PID_OFF;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    ctx->ts = ts;
    ctx->min = min;
    ctx->max = max;
    ctx->imx = 0;
    ctx->out = 0;
    ctx->sum = 0;
    ctx->ref = 0;
    ctx->ec = 0;
    ctx->e = 0;
}

a_real_t a_pid_proc(a_pid_s *ctx, a_real_t set, a_real_t ref)
{
    assert(ctx);

    a_real_t e = set - ref;
    a_real_t ec = e - ctx->e;

    switch (ctx->mode)
    {
    case A_PID_POS:
    {
        a_real_t sum = ctx->ki * e;
        /* When the limit of integration is exceeded or */
        /* the direction of integration is the same, */
        /* the integration stops. */
        if ((-ctx->imx < ctx->sum && ctx->sum < ctx->imx) || ctx->sum * sum < 0)
        {
            /* sum = K_i \sum^k_{i=0} e(i) */
            ctx->sum += sum;
        }
        /* Avoid derivative kick, ref[k-1]-ref[k] */
        /* out = K_p e(k) + sum + K_d [ref(k-1)-ref(k)] */
        ctx->out = ctx->kp * e + ctx->sum + ctx->kd * (ctx->ref - ref);
    }
    break;
    case A_PID_INC:
    {
        /* K_p[e(k)-e(k-1)]+K_i e(k)+K_d[ec(k)-ec(k-1)] */
        ctx->sum += ctx->kp * ec + ctx->ki * e + ctx->kd * (ec - ctx->ec);
        ctx->out = ctx->sum;
    }
    break;
    case A_PID_OFF:
    {
        ctx->out = ctx->sum = set;
    }
    break;
    default:
        break;
    }

    ctx->out = A_LIMIT(ctx->out, ctx->min, ctx->max);
    ctx->ref = ref;
    ctx->ec = ec;
    ctx->e = e;

    return ctx->out;
}

void a_pid_done(a_pid_s *ctx)
{
    assert(ctx);
    ctx->out = 0;
    ctx->sum = 0;
    ctx->ref = 0;
    ctx->ec = 0;
    ctx->e = 0;
}
