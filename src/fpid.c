/*!
 @file fpid.c
 @brief fuzzy proportional integral derivative controller
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "pid.h"
#include "fpid.h"
#include <math.h>

a_real_t a_fpid_op_or(a_real_t l, a_real_t r) { return l + r - l * r; }

a_real_t a_fpid_op_and(a_real_t l, a_real_t r) { return l * r; }

a_real_t a_fpid_op_equ(a_real_t l, a_real_t r)
{
    return A_REAL_F(sqrt, l * r) * A_REAL_F(sqrt, 1 - (1 - l) * (1 - r));
}

a_void_t a_fpid_set_op(a_fpid_s *ctx, a_uint_t op)
{
    ctx->pid->reg &= ~A_FPID_FUZZY_MASK;
    op &= A_FPID_FUZZY_MASK;
    ctx->pid->reg |= op;
    switch (op)
    {
    case A_FPID_OR_ALGEBRA:
    {
        ctx->op = a_fpid_op_or;
        break;
    }
    case A_FPID_OR_BOUNDED:
    case A_FPID_AND:
    {
#if A_REAL_BITS > 64
        ctx->op = fminl;
#elif A_REAL_BITS == 64
        ctx->op = fmin;
#elif A_REAL_BITS == 32
        ctx->op = fminf;
#endif /* A_REAL_BITS */
        break;
    }
    case A_FPID_AND_ALGEBRA:
    {
        ctx->op = a_fpid_op_and;
        break;
    }
    case A_FPID_AND_BOUNDED:
    case A_FPID_OR:
    {
#if A_REAL_BITS > 64
        ctx->op = fmaxl;
#elif A_REAL_BITS == 64
        ctx->op = fmax;
#elif A_REAL_BITS == 32
        ctx->op = fmaxf;
#endif /* A_REAL_BITS */
        break;
    }
    case A_FPID_EQU:
    default:
        ctx->op = a_fpid_op_equ;
    }
}

a_uint_t a_fpid_mf(const a_real_t *a, a_real_t x, a_uint_t *idx, a_real_t *mms)
{
    a_uint_t num = 0;
    a_int_t e = A_MF_NUL;
    for (a_uint_t i = 0; (void)(e = (a_int_t)*a++), e != A_MF_NUL; ++i)
    {
        a_real_t y = 0;
        switch (e)
        {
        case A_MF_GAUSS:
        {
            y = a_mf_gauss(x, a[0], a[1]);
            a += 2;
            break;
        }
        case A_MF_GBELL:
        {
            y = a_mf_gbell(x, a[0], a[1], a[2]);
            a += 3;
            break;
        }
        case A_MF_SIG:
        {
            y = a_mf_sig(x, a[0], a[1]);
            a += 2;
            break;
        }
        case A_MF_TRAP:
        {
            y = a_mf_trap(x, a[0], a[1], a[2], a[3]);
            a += 4;
            break;
        }
        case A_MF_TRI:
        {
            y = a_mf_tri(x, a[0], a[1], a[2]);
            a += 3;
            break;
        }
        case A_MF_Z:
        {
            y = a_mf_z(x, a[0], a[1]);
            a += 2;
            break;
        }
        case A_MF_NUL:
        default:
            goto done;
        }
        if (y > 0)
        {
            ++num;
            *idx++ = i;
            *mms++ = y;
        }
    }
done:
    return num;
}

a_fpid_s *a_fpid_off(a_fpid_s *ctx)
{
    a_pid_off(ctx->pid);
    return ctx;
}

a_fpid_s *a_fpid_inc(a_fpid_s *ctx)
{
    a_pid_inc(ctx->pid);
    return ctx;
}

a_fpid_s *a_fpid_pos(a_fpid_s *ctx, a_real_t max)
{
    a_pid_pos(ctx->pid, max);
    return ctx;
}

a_fpid_s *a_fpid_ilim(a_fpid_s *ctx, a_real_t min, a_real_t max)
{
    a_real_t x = (a_real_t)((a_fpid_col(ctx) - 1) >> 1 << 1);
    ctx->sigma = x / (max - min);
    return ctx;
}

a_fpid_s *a_fpid_olim(a_fpid_s *ctx, a_real_t min, a_real_t max)
{
    a_real_t x = (a_real_t)((a_fpid_col(ctx) - 1) >> 1 << 1);
    ctx->alpha = (max - min) / x;
    ctx->pid->outmin = min;
    ctx->pid->outmax = max;
    return ctx;
}

a_fpid_s *a_fpid_buf1(a_fpid_s *ctx, a_vptr_t ptr, a_size_t max)
{
    a_fpid_set_bufnum(ctx, (a_uint_t)max);
    max <<= 1;
    ctx->idx = (a_uint_t *)ptr;
    ptr = (a_byte_t *)ptr + sizeof(a_uint_t) * max;
    ctx->mms = (a_real_t *)ptr;
    ptr = (a_byte_t *)ptr + sizeof(a_real_t) * max;
    ctx->mat = (a_real_t *)ptr;
    return ctx;
}

a_fpid_s *a_fpid_kpid(a_fpid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
{
    a_pid_kpid(ctx->pid, kp, ki, kd);
    ctx->kp = kp;
    ctx->ki = ki;
    ctx->kd = kd;
    return ctx;
}

a_fpid_s *a_fpid_buff(a_fpid_s *ctx, a_uint_t *idx, a_real_t *mms, a_real_t *mat)
{
    ctx->idx = idx;
    ctx->mms = mms;
    ctx->mat = mat;
    return ctx;
}

a_fpid_s *a_fpid_setp(a_fpid_s *ctx, a_uint_t num, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e)
{
    a_pid_setp(ctx->pid, num, out, fdb, sum, ec, e);
    return ctx;
}

a_fpid_s *a_fpid_base(a_fpid_s *ctx, a_uint_t num, const a_real_t *mmp, const a_real_t *mkp, const a_real_t *mki, const a_real_t *mkd)
{
    a_fpid_set_col(ctx, num);
    ctx->mmp = mmp;
    ctx->mkp = mkp;
    ctx->mki = mki;
    ctx->mkd = mkd;
    return ctx;
}

a_fpid_s *a_fpid_init(a_fpid_s *ctx, a_real_t dt, a_uint_t num, const a_real_t *mmp,
                      const a_real_t *mkp, const a_real_t *mki, const a_real_t *mkd,
                      a_real_t imin, a_real_t imax, a_real_t omin, a_real_t omax)
{
    a_real_t x = (a_real_t)((num - 1) >> 1 << 1);
    a_pid_init(ctx->pid, dt, omin, omax);
    a_fpid_base(ctx, num, mmp, mkp, mki, mkd);
    ctx->sigma = x / (imax - imin);
    ctx->alpha = (omax - omin) / x;
    ctx->op = a_fpid_op_equ;
    ctx->idx = 0;
    ctx->mms = 0;
    ctx->mat = 0;
    ctx->kp = 0;
    ctx->ki = 0;
    ctx->kd = 0;
    return ctx;
}

a_fpid_s *a_fpid_exit(a_fpid_s *ctx) { return a_fpid_zero(ctx); }

a_fpid_s *a_fpid_zero(a_fpid_s *ctx)
{
    a_pid_zero(ctx->pid);
    return ctx;
}

A_STATIC void a_fpid_proc_(a_fpid_s *ctx, a_real_t ev[2], a_uint_t num)
{
    /* quantize input */
    ev[0] = ctx->sigma * ev[0] / (1 << 0);
    ev[1] = ctx->sigma * ev[1] / (1 << 1);
    /* calculate membership */
    a_uint_t ne = a_fpid_mf(ctx->mmp, ev[0], ctx->idx + 00, ctx->mms + 00);
    a_uint_t nc = a_fpid_mf(ctx->mmp, ev[1], ctx->idx + ne, ctx->mms + ne);
    if (!ne || !nc)
    {
        return;
    }
    /* joint membership */
    a_real_t inv = 0;
    for (a_uint_t i = 0; i != ne; ++i)
    {
        a_uint_t col = i * nc;
        for (a_uint_t j = 0; j != nc; ++j)
        {
            a_uint_t idx = col + j; /* mat(i,j)=f(e[i],ec[j]) */
            ctx->mat[idx] = ctx->op(ctx->mms[i], ctx->mms[ne + j]);
            inv += ctx->mat[idx];
        }
    }
    inv = ctx->alpha / inv;
    /* mean of centers defuzzifier */
    a_real_t qv[3] = {0, 0, 0};
    if (ctx->mkp == 0)
    {
        goto skip_kp;
    }
    for (a_uint_t i = 0; i != ne; ++i)
    {
        a_uint_t col = i * nc;
        a_uint_t idx = ctx->idx[i] * num;
        for (a_uint_t j = 0; j != nc; ++j)
        {
            qv[0] += ctx->mat[col + j] * ctx->mkp[ctx->idx[ne + j] + idx]; /* mat(i,j)*kp(e[i],ec[j]) */
        }
    }
    qv[0] *= inv;
skip_kp:
    if (ctx->mki == 0)
    {
        goto skip_ki;
    }
    for (a_uint_t i = 0; i != ne; ++i)
    {
        a_uint_t col = i * nc;
        a_uint_t idx = ctx->idx[i] * num;
        for (a_uint_t j = 0; j != nc; ++j)
        {
            qv[1] += ctx->mat[col + j] * ctx->mki[ctx->idx[ne + j] + idx]; /* mat(i,j)*ki(e[i],ec[j]) */
        }
    }
    qv[1] *= inv;
skip_ki:
    if (ctx->mkd == 0)
    {
        goto skip_kd;
    }
    for (a_uint_t i = 0; i != ne; ++i)
    {
        a_uint_t col = i * nc;
        a_uint_t idx = ctx->idx[i] * num;
        for (a_uint_t j = 0; j != nc; ++j)
        {
            qv[2] += ctx->mat[col + j] * ctx->mkd[ctx->idx[ne + j] + idx]; /* mat(i,j)*kd(e[i],ec[j]) */
        }
    }
    qv[2] *= inv;
skip_kd:
    a_pid_kpid(ctx->pid, qv[0] + ctx->kp, qv[1] + ctx->ki, qv[2] + ctx->kd);
}

a_real_t a_fpid_outv(a_fpid_s *ctx, a_real_t set, a_real_t fdb)
{
    a_real_t e = set - fdb;
    a_real_t ec = e - ctx->pid->e.v;
    a_real_t ev[2] = {e, ec};
    a_fpid_proc_(ctx, ev, a_fpid_col(ctx));
    return a_pid_outv_(ctx->pid, a_pid_mode(ctx->pid), set, fdb, ec, e);
}

a_real_t *a_fpid_outp(a_fpid_s *ctx, a_real_t *set, a_real_t *fdb)
{
    a_uint_t col = a_fpid_col(ctx);
    a_uint_t num = a_pid_num(ctx->pid);
    a_uint_t reg = a_pid_mode(ctx->pid);
    for (a_uint_t i = 0; i != num; ++i)
    {
        a_real_t e = set[i] - fdb[i];
        a_real_t ec = e - ctx->pid->e.p[i];
        a_real_t ev[2] = {e, ec};
        a_fpid_proc_(ctx, ev, col);
        a_pid_outp_(ctx->pid, reg, set[i], fdb[i], ec, e, i);
    }
    return ctx->pid->out.p;
}

#undef A_FPID_BUF1
a_size_t A_FPID_BUF1(a_uint_t max)
{
    return sizeof(a_uint_t) * (max << 1) + sizeof(a_real_t) * (max + 2) * max;
}

#undef a_fpid_set_bufnum
a_void_t a_fpid_set_bufnum(a_fpid_s *ctx, a_uint_t num)
{
    ctx->pid->num &= A_PID_NUM_MASK;
    ctx->pid->num |= num << A_PID_NUM_BITS;
}

#undef a_fpid_bufnum
a_uint_t a_fpid_bufnum(const a_fpid_s *ctx)
{
    return ctx->pid->num >> A_PID_NUM_BITS;
}

#undef a_fpid_bufptr
a_vptr_t a_fpid_bufptr(const a_fpid_s *ctx)
{
    return ctx->idx;
}

#undef a_fpid_set_col
a_void_t a_fpid_set_col(a_fpid_s *ctx, a_uint_t reg)
{
    ctx->pid->reg &= A_PID_REG_MASK;
    ctx->pid->reg |= reg << A_PID_REG_BITS;
}

#undef a_fpid_col
a_uint_t a_fpid_col(const a_fpid_s *ctx)
{
    return ctx->pid->reg >> A_PID_REG_BITS;
}

#undef a_fpid_op
a_uint_t a_fpid_op(const a_fpid_s *ctx)
{
    return ctx->pid->reg & A_FPID_FUZZY_MASK;
}
