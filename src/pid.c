#include "pid.h"

a_pid_s *a_pid_off(a_pid_s *ctx)
{
    a_pid_set_mode(ctx, A_PID_OFF);
    return ctx;
}

a_pid_s *a_pid_inc(a_pid_s *ctx)
{
    a_pid_set_mode(ctx, A_PID_INC);
    return ctx;
}

a_pid_s *a_pid_pos(a_pid_s *ctx, a_real_t max)
{
    ctx->summax = (max > 0) ? max : -max;
    if (ctx->outmax < ctx->summax)
    {
        ctx->summax = ctx->outmax;
    }
    a_pid_set_mode(ctx, A_PID_POS);
    return ctx;
}

a_pid_s *a_pid_kpid(a_pid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
{
    ctx->kp = kp;
    ctx->ki = ki * ctx->dt;
    ctx->kd = kd / ctx->dt;
    return ctx;
}

a_pid_s *a_pid_setp(a_pid_s *ctx, a_uint_t num, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e)
{
    a_pid_set_num(ctx, num);
    ctx->out.p = out;
    ctx->fdb.p = fdb;
    ctx->sum.p = sum;
    ctx->ec.p = ec;
    ctx->e.p = e;
    return a_pid_zero(ctx);
}

a_pid_s *a_pid_init(a_pid_s *ctx, a_real_t dt, a_real_t min, a_real_t max)
{
    ctx->reg = A_PID_OFF;
    ctx->outmin = min;
    ctx->outmax = max;
    ctx->summax = 0;
    ctx->num = 0;
    ctx->dt = dt;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    return a_pid_zero(ctx);
}

a_pid_s *a_pid_exit(a_pid_s *ctx) { return a_pid_zero(ctx); }

a_pid_s *a_pid_zero(a_pid_s *ctx)
{
    a_uint_t num = a_pid_num(ctx);
    for (a_uint_t i = 0; i != num; ++i)
    {
        ctx->sum.p[i] = 0;
        ctx->out.p[i] = 0;
        ctx->fdb.p[i] = 0;
        ctx->ec.p[i] = 0;
        ctx->e.p[i] = 0;
    }
    if (num == 0)
    {
        ctx->out.v = 0;
        ctx->sum.v = 0;
        ctx->fdb.v = 0;
        ctx->ec.v = 0;
        ctx->e.v = 0;
    }
    return ctx;
}

a_real_t a_pid_outv_(a_pid_s *ctx, a_uint_t mode, a_real_t set, a_real_t fdb, a_real_t ec, a_real_t e)
{
    /* calculation */
    switch (mode)
    {
    case A_PID_INC:
    {
        /* K_p[e(k)-e(k-1)]+K_i e(k)+K_d[ec(k)-ec(k-1)] */
        ctx->sum.v += ctx->kp * ec + ctx->ki * e + ctx->kd * (ec - ctx->ec.v);
        ctx->out.v = ctx->sum.v;
        break;
    }
    case A_PID_POS:
    {
        a_real_t sum = ctx->ki * e;
        /* when the limit of integration is exceeded or */
        /* the direction of integration is the same, the integration stops. */
        if ((-ctx->summax < ctx->sum.v && ctx->sum.v < ctx->summax) || ctx->sum.v * sum < 0)
        {
            /* sum = K_i \sum^k_{i=0} e(i) */
            ctx->sum.v += sum;
        }
        /* avoid derivative kick, fdb[k-1]-fdb[k] */
        /* out = K_p e(k) + sum + K_d [fdb(k-1)-fdb(k)] */
        ctx->out.v = ctx->kp * e + ctx->sum.v + ctx->kd * (ctx->fdb.v - fdb);
        break;
    }
    case A_PID_OFF:
    default:
        ctx->out.v = ctx->sum.v = set;
    }
    /* output limiter */
    if (ctx->outmax < ctx->out.v)
    {
        ctx->out.v = ctx->outmax;
    }
    else if (ctx->out.v < ctx->outmin)
    {
        ctx->out.v = ctx->outmin;
    }
    /* cache data */
    ctx->fdb.v = fdb;
    ctx->ec.v = ec;
    ctx->e.v = e;
    return ctx->out.v;
}

a_real_t a_pid_outp_(a_pid_s *ctx, a_uint_t mode, a_real_t set, a_real_t fdb, a_real_t ec, a_real_t e, a_uint_t i)
{
    /* calculation */
    switch (mode)
    {
    case A_PID_INC:
    {
        /* K_p[e(k)-e(k-1)]+K_i e(k)+K_d[ec(k)-ec(k-1)] */
        ctx->sum.p[i] += ctx->kp * ec + ctx->ki * e + ctx->kd * (ec - ctx->ec.p[i]);
        ctx->out.p[i] = ctx->sum.p[i];
        break;
    }
    case A_PID_POS:
    {
        a_real_t sum = ctx->ki * e;
        /* when the limit of integration is exceeded or */
        /* the direction of integration is the same, the integration stops. */
        if ((-ctx->summax < ctx->sum.p[i] && ctx->sum.p[i] < ctx->summax) || ctx->sum.p[i] * sum < 0)
        {
            /* sum = K_i \sum^k_{i=0} e(i) */
            ctx->sum.p[i] += sum;
        }
        /* avoid derivative kick, fdb[k-1]-fdb[k] */
        /* out = K_p e(k) + sum + K_d [fdb(k-1)-fdb(k)] */
        ctx->out.p[i] = ctx->kp * e + ctx->sum.p[i] + ctx->kd * (ctx->fdb.p[i] - fdb);
        break;
    }
    case A_PID_OFF:
    default:
        ctx->out.p[i] = ctx->sum.p[i] = set;
    }
    /* output limiter */
    if (ctx->outmax < ctx->out.p[i])
    {
        ctx->out.p[i] = ctx->outmax;
    }
    else if (ctx->out.p[i] < ctx->outmin)
    {
        ctx->out.p[i] = ctx->outmin;
    }
    /* cache data */
    ctx->fdb.p[i] = fdb;
    ctx->ec.p[i] = ec;
    ctx->e.p[i] = e;
    return ctx->out.p[i];
}

a_real_t a_pid_outv(a_pid_s *ctx, a_real_t set, a_real_t fdb)
{
    a_real_t e = set - fdb;
    a_real_t ec = e - ctx->e.v;
    return a_pid_outv_(ctx, a_pid_mode(ctx), set, fdb, ec, e);
}

a_real_t *a_pid_outp(a_pid_s *ctx, a_real_t *set, a_real_t *fdb)
{
    a_uint_t num = a_pid_num(ctx);
    a_uint_t reg = a_pid_mode(ctx);
    for (a_uint_t i = 0; i != num; ++i)
    {
        a_real_t e = set[i] - fdb[i];
        a_real_t ec = e - ctx->e.p[i];
        a_pid_outp_(ctx, reg, set[i], fdb[i], ec, e, i);
    }
    return ctx->out.p;
}

#undef a_pid_set_dt
a_void_t a_pid_set_dt(a_pid_s *ctx, a_real_t dt)
{
    a_real_t t = dt / ctx->dt;
    ctx->ki *= t;
    ctx->kd /= t;
    ctx->dt = dt;
}

#undef a_pid_dt
a_real_t a_pid_dt(const a_pid_s *ctx)
{
    return ctx->dt;
}

#undef a_pid_set_kp
a_void_t a_pid_set_kp(a_pid_s *ctx, a_real_t kp)
{
    ctx->kp = kp;
}

#undef a_pid_kp
a_real_t a_pid_kp(const a_pid_s *ctx)
{
    return ctx->kp;
}

#undef a_pid_set_ki
a_void_t a_pid_set_ki(a_pid_s *ctx, a_real_t ki)
{
    ctx->ki = ki * ctx->dt;
}

#undef a_pid_ki
a_real_t a_pid_ki(const a_pid_s *ctx)
{
    return ctx->ki / ctx->dt;
}

#undef a_pid_set_kd
a_void_t a_pid_set_kd(a_pid_s *ctx, a_real_t kd)
{
    ctx->kd = kd / ctx->dt;
}

#undef a_pid_kd
a_real_t a_pid_kd(const a_pid_s *ctx)
{
    return ctx->kd * ctx->dt;
}

#undef a_pid_set_num
a_void_t a_pid_set_num(a_pid_s *ctx, a_uint_t num)
{
    ctx->num &= ~A_PID_NUM_MASK;
    ctx->num |= num & A_PID_NUM_MASK;
}

#undef a_pid_num
a_uint_t a_pid_num(const a_pid_s *ctx)
{
    return ctx->num & A_PID_NUM_MASK;
}

#undef a_pid_set_reg
a_void_t a_pid_set_reg(a_pid_s *ctx, a_uint_t reg)
{
    ctx->reg &= ~A_PID_REG_MASK;
    ctx->reg |= reg & A_PID_REG_MASK;
}

#undef a_pid_reg
a_uint_t a_pid_reg(const a_pid_s *ctx)
{
    return ctx->reg & A_PID_REG_MASK;
}

#undef a_pid_set_mode
a_void_t a_pid_set_mode(a_pid_s *ctx, a_uint_t mode)
{
    ctx->reg &= ~A_PID_MODE_MASK;
    ctx->reg |= mode & A_PID_MODE_MASK;
}

#undef a_pid_mode
a_uint_t a_pid_mode(const a_pid_s *mode)
{
    return mode->reg & A_PID_MODE_MASK;
}
