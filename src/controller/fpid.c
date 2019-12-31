/*!
 @file fpid.c
 @brief Fuzzy Proportional Integral Derivative Algorithm
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/controller/fpid.h"

#include <assert.h>
#include <math.h>

A_INLINE a_real_t op(a_real_t a, a_real_t b)
{
    return A_REAL_F(sqrt, a * b) * A_REAL_F(sqrt, 1 - (1 - a) * (1 - b));
}

static unsigned int mf(a_fpid_s *ctx, a_real_t x, a_real_t *ms, unsigned int *idx)
{
    int t = A_MF_NONE;
    unsigned int num = 0;
    const a_real_t *p = ctx->tmf;
    for (unsigned int i = 0; ((void)(t = (int)*p++), t) != A_MF_NONE; ++i)
    {
        a_real_t y = 0;
        switch (t)
        {
        case A_MF_GAUSS:
        {
            y = a_mf_gauss(x, p[0], p[1]);
            p += 2;
        }
        break;
        case A_MF_GBELL:
        {
            y = a_mf_gbell(x, p[0], p[1], p[2]);
            p += 3;
        }
        break;
        case A_MF_SIG:
        {
            y = a_mf_sig(x, p[0], p[1]);
            p += 2;
        }
        break;
        case A_MF_TRAP:
        {
            y = a_mf_trap(x, p[0], p[1], p[2], p[3]);
            p += 4;
        }
        break;
        case A_MF_TRI:
        {
            y = a_mf_tri(x, p[0], p[1], p[2]);
            p += 3;
        }
        break;
        case A_MF_Z:
        {
            y = a_mf_z(x, p[0], p[1]);
            p += 2;
        }
        break;
        case A_MF_NONE:
        default:
            goto done;
        }
        if (y > 0)
        {
            ++num;
            *ms++ = y;
            *idx++ = i;
        }
    }
done:
    return num;
}

void a_fpid_init(a_fpid_s *ctx, a_real_t ts, unsigned int num, const a_real_t *tmf,
                 const a_real_t *tkp, const a_real_t *tki, const a_real_t *tkd,
                 a_real_t vmin, a_real_t vmax, a_real_t umin, a_real_t umax)
{
    assert(ctx);
    a_real_t x = (a_real_t)((num - 1) >> 1 << 1);
    a_pid_init(ctx->pid, ts, umin, umax);
    a_pid_mode(ctx->pid, A_PID_INC);
    ctx->sigma = x / (vmax - vmin);
    ctx->alpha = (umax - umin) / x;
    ctx->num = num;
    ctx->tmf = tmf;
    ctx->tkp = tkp;
    ctx->tki = tki;
    ctx->tkd = tkd;
    ctx->opt = op;
}

a_real_t a_fpid_proc(a_fpid_s *ctx, a_real_t set, a_real_t ref)
{
    assert(ctx);
    a_real_t e = set - ref;
    a_real_t ev[2] = {e, e - ctx->pid->e};
    /* quantize input */
    ev[0] = ctx->sigma * ev[0] / (1 << 0);
    ev[1] = ctx->sigma * ev[1] / (1 << 1);
    /* calculate membership */
    unsigned int ne = mf(ctx, ev[0], ctx->ms + 00, ctx->idx + 00);
    unsigned int nc = mf(ctx, ev[1], ctx->ms + ne, ctx->idx + ne);
    if (!ne || !nc)
    {
        goto done;
    }
    /* joint membership */
    a_real_t inv = 0;
    for (unsigned int i = 0; i != ne; ++i)
    {
        for (unsigned int j = 0; j != nc; ++j)
        {
            unsigned int idx = i * nc + j;
            ctx->mat[idx] = ctx->opt(ctx->ms[i], ctx->ms[ne + j]);
            inv += ctx->mat[idx];
        }
    }
    inv = ctx->alpha / inv;
    /* mean of centers defuzzifier */
    a_real_t qv[3] = {0, 0, 0};
    if (ctx->tkp == 0)
    {
        goto skip_kp;
    }
    for (unsigned int i = 0; i != ne; ++i)
    {
        for (unsigned int j = 0; j != nc; ++j)
        {
            qv[0] += ctx->mat[i * nc + j] * ctx->tkp[ctx->idx[ne + j] + ctx->idx[i] * ctx->num];
        }
    }
skip_kp:
    if (ctx->tki == 0)
    {
        goto skip_ki;
    }
    for (unsigned int i = 0; i != ne; ++i)
    {
        for (unsigned int j = 0; j != nc; ++j)
        {
            qv[1] += ctx->mat[i * nc + j] * ctx->tki[ctx->idx[ne + j] + ctx->idx[i] * ctx->num];
        }
    }
skip_ki:
    if (ctx->tkd == 0)
    {
        goto skip_kd;
    }
    for (unsigned int i = 0; i != ne; ++i)
    {
        for (unsigned int j = 0; j != nc; ++j)
        {
            qv[2] += ctx->mat[i * nc + j] * ctx->tkd[ctx->idx[ne + j] + ctx->idx[i] * ctx->num];
        }
    }
skip_kd: /* realize output */
    qv[0] = ctx->kp + qv[0] * inv;
    qv[1] = ctx->ki + qv[1] * inv;
    qv[2] = ctx->kd + qv[2] * inv;
    a_pid_kpid(ctx->pid, qv[0], qv[1], qv[2]);
done:
    return a_pid_proc(ctx->pid, set, ref);
}
