/*!
 @file mean.c
 @brief mean calculation
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/mean.h"
#include "a/misc/math.h"

#include <assert.h>
#include <math.h>

void a_mean_init(a_mean_s *ctx, unsigned int mode)
{
    assert(ctx);

    ctx->num = 0;
    ctx->mode = mode;

    switch (ctx->mode)
    {
    case A_MEAN_GEOMETRIC:
    {
        ctx->out = 1;
    }
    break;
    case A_MEAN_ARITHMETIC:
    case A_MEAN_HARMONIC:
    case A_MEAN_SQUARE:
    {
        ctx->out = 0;
    }
    break;
    default:
        break;
    }
}

void a_mean_proc(a_mean_s *ctx, const a_real_t *dat, size_t num)
{
    assert(ctx);
    assert(!num || dat);

    const a_real_t *p = dat + num;

    switch (ctx->mode)
    {
    case A_MEAN_ARITHMETIC:
    {
        for (; dat != p; ++dat)
        {
            ctx->out += *dat;
        }
    }
    break;
    case A_MEAN_GEOMETRIC:
    {
        for (; dat != p; ++dat)
        {
            ctx->out *= *dat;
        }
    }
    break;
    case A_MEAN_HARMONIC:
    {
        for (; dat != p; ++dat)
        {
            ctx->out += 1 / *dat;
        }
    }
    break;
    case A_MEAN_SQUARE:
    {
        for (; dat != p; ++dat)
        {
            ctx->out += A_SQ(*dat);
        }
    }
    break;
    default:
        break;
    }

    ctx->num += num;
}

a_real_t a_mean_done(a_mean_s *ctx)
{
    assert(ctx);

    switch (ctx->mode)
    {
    case A_MEAN_ARITHMETIC:
    {
        ctx->out /= (a_real_t)ctx->num;
    }
    break;
    case A_MEAN_GEOMETRIC:
    {
        a_real_t inv = 1 / (a_real_t)ctx->num;
        ctx->out = A_REAL_F(pow, ctx->out, inv);
    }
    break;
    case A_MEAN_HARMONIC:
    {
        ctx->out = (a_real_t)ctx->num / ctx->out;
    }
    break;
    case A_MEAN_SQUARE:
    {
        ctx->out /= (a_real_t)ctx->num;
        ctx->out = A_REAL_F(sqrt, ctx->out);
    }
    break;
    default:
        break;
    }

    return ctx->out;
}
