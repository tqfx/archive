/*!
 @file pid.c
 @brief proportional integral derivative controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "pid.h"

a_pid_s *a_pid_off(a_pid_s *ctx) { return a_pid_mode(ctx, A_PID_OFF); }

a_pid_s *a_pid_inc(a_pid_s *ctx) { return a_pid_mode(ctx, A_PID_INC); }

a_pid_s *a_pid_pos(a_pid_s *ctx, a_real_t max)
{
    ctx->summax = (max > 0) ? max : -max;
    if (ctx->outmax < ctx->summax)
    {
        ctx->summax = ctx->outmax;
    }
    return a_pid_mode(ctx, A_PID_POS);
}

a_pid_s *a_pid_mode(a_pid_s *ctx, a_uint_t reg)
{
    ctx->reg = (~((1U << A_PID_REG) - 1) & ctx->reg) | reg;
    return ctx;
}

a_pid_s *a_pid_time(a_pid_s *ctx, a_real_t ts)
{
    a_real_t t = ts / ctx->ts;
    ctx->ki *= t;
    ctx->kd /= t;
    ctx->ts = ts;
    return ctx;
}

a_pid_s *a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
{
    ctx->kp = kp;
    ctx->ki = ki * ctx->ts;
    ctx->kd = kd / ctx->ts;
    return ctx;
}

a_pid_s *a_pid_setv(a_pid_s *ctx, a_uint_t num, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e)
{
    ctx->num = num;
    ctx->out.v = out;
    ctx->fdb.v = fdb;
    ctx->sum.v = sum;
    ctx->ec.v = ec;
    ctx->e.v = e;
    return a_pid_zero(ctx);
}

a_pid_s *a_pid_init(a_pid_s *ctx, a_real_t ts, a_real_t min, a_real_t max)
{
    ctx->reg = A_PID_OFF;
    ctx->outmin = min;
    ctx->outmax = max;
    ctx->summax = 0;
    ctx->num = 0;
    ctx->ts = ts;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    return a_pid_zero(ctx);
}

a_pid_s *a_pid_exit(a_pid_s *ctx) { return a_pid_zero(ctx); }

a_pid_s *a_pid_zero(a_pid_s *ctx)
{
    for (a_uint_t i = 0; i != ctx->num; ++i)
    {
        ctx->sum.v[i] = 0;
        ctx->out.v[i] = 0;
        ctx->fdb.v[i] = 0;
        ctx->ec.v[i] = 0;
        ctx->e.v[i] = 0;
    }
    if (ctx->num == 0)
    {
        ctx->out.x = 0;
        ctx->sum.x = 0;
        ctx->fdb.x = 0;
        ctx->ec.x = 0;
        ctx->e.x = 0;
    }
    return ctx;
}

a_real_t a_pid_cc_x_(a_pid_s *ctx, a_uint_t mode, a_real_t set, a_real_t fdb, a_real_t ec, a_real_t e)
{
    /* calculation */
    switch (mode)
    {
    case A_PID_POS:
    {
        a_real_t sum = ctx->ki * e;
        /* when the limit of integration is exceeded or */
        /* the direction of integration is the same, the integration stops. */
        if ((-ctx->summax < ctx->sum.x && ctx->sum.x < ctx->summax) || ctx->sum.x * sum < 0)
        {
            /* sum = K_i \sum^k_{i=0} e(i) */
            ctx->sum.x += sum;
        }
        /* avoid derivative kick, fdb[k-1]-fdb[k] */
        /* out = K_p e(k) + sum + K_d [fdb(k-1)-fdb(k)] */
        ctx->out.x = ctx->kp * e + ctx->sum.x + ctx->kd * (ctx->fdb.x - fdb);
    }
    break;
    case A_PID_INC:
    {
        /* K_p[e(k)-e(k-1)]+K_i e(k)+K_d[ec(k)-ec(k-1)] */
        ctx->sum.x += ctx->kp * ec + ctx->ki * e + ctx->kd * (ec - ctx->ec.x);
        ctx->out.x = ctx->sum.x;
    }
    break;
    case A_PID_OFF:
    default:
    {
        ctx->out.x = ctx->sum.x = set;
    }
    break;
    }
    /* output limiter */
    if (ctx->outmax < ctx->out.x)
    {
        ctx->out.x = ctx->outmax;
    }
    else if (ctx->out.x < ctx->outmin)
    {
        ctx->out.x = ctx->outmin;
    }
    /* cache data */
    ctx->fdb.x = fdb;
    ctx->ec.x = ec;
    ctx->e.x = e;
    return ctx->out.x;
}

a_real_t a_pid_cc_v_(a_pid_s *ctx, a_uint_t mode, a_real_t set, a_real_t fdb, a_real_t ec, a_real_t e, a_uint_t i)
{
    /* calculation */
    switch (mode)
    {
    case A_PID_POS:
    {
        a_real_t sum = ctx->ki * e;
        /* when the limit of integration is exceeded or */
        /* the direction of integration is the same, the integration stops. */
        if ((-ctx->summax < ctx->sum.v[i] && ctx->sum.v[i] < ctx->summax) || ctx->sum.v[i] * sum < 0)
        {
            /* sum = K_i \sum^k_{i=0} e(i) */
            ctx->sum.v[i] += sum;
        }
        /* avoid derivative kick, fdb[k-1]-fdb[k] */
        /* out = K_p e(k) + sum + K_d [fdb(k-1)-fdb(k)] */
        ctx->out.v[i] = ctx->kp * e + ctx->sum.v[i] + ctx->kd * (ctx->fdb.v[i] - fdb);
    }
    break;
    case A_PID_INC:
    {
        /* K_p[e(k)-e(k-1)]+K_i e(k)+K_d[ec(k)-ec(k-1)] */
        ctx->sum.v[i] += ctx->kp * ec + ctx->ki * e + ctx->kd * (ec - ctx->ec.v[i]);
        ctx->out.v[i] = ctx->sum.v[i];
    }
    break;
    case A_PID_OFF:
    default:
    {
        ctx->out.v[i] = ctx->sum.v[i] = set;
    }
    break;
    }
    /* output limiter */
    if (ctx->outmax < ctx->out.v[i])
    {
        ctx->out.v[i] = ctx->outmax;
    }
    else if (ctx->out.v[i] < ctx->outmin)
    {
        ctx->out.v[i] = ctx->outmin;
    }
    /* cache data */
    ctx->fdb.v[i] = fdb;
    ctx->ec.v[i] = ec;
    ctx->e.v[i] = e;
    return ctx->out.v[i];
}

a_real_t a_pid_cc_x(a_pid_s *ctx, a_real_t set, a_real_t fdb)
{
    a_real_t e = set - fdb;
    a_real_t ec = e - ctx->e.x;
    a_uint_t mode = ctx->reg & ((1U << A_PID_REG) - 1);
    return a_pid_cc_x_(ctx, mode, set, fdb, ec, e);
}

a_real_t *a_pid_cc_v(a_pid_s *ctx, a_real_t *set, a_real_t *fdb)
{
    a_uint_t mode = ctx->reg & ((1U << A_PID_REG) - 1);
    for (a_uint_t i = 0; i != ctx->num; ++i)
    {
        a_real_t e = set[i] - fdb[i];
        a_real_t ec = e - ctx->e.v[i];
        a_pid_cc_v_(ctx, mode, set[i], fdb[i], ec, e, i);
    }
    return ctx->out.v;
}
