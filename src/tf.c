/*!
 @file tf.h
 @brief transfer function
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/tf.h"
#include <string.h>

a_tf_s *a_tf_init(a_tf_s *ctx,
                  a_uint_t m, const a_real_t *num, a_real_t *u,
                  a_uint_t n, const a_real_t *den, a_real_t *v)
{
    ctx->num = num;
    ctx->den = den;
    ctx->u = u;
    ctx->v = v;
    ctx->m = m;
    ctx->n = n;
    return a_tf_zero(ctx);
}

A_STATIC void roll(a_real_t *p, a_uint_t n)
{
    for (a_uint_t i = --n; i--; n = i)
    {
        p[n] = p[i];
    }
}

a_real_t a_tf_proc(a_tf_s *ctx, a_real_t x)
{
    a_real_t y = 0;

    roll(ctx->u, ctx->m);
    ctx->u[0] = x;

    for (a_uint_t i = 0; i != ctx->m; ++i)
    {
        y += ctx->num[i] * ctx->u[i];
    }
    for (a_uint_t i = 0; i != ctx->n; ++i)
    {
        y -= ctx->den[i] * ctx->v[i];
    }

    roll(ctx->v, ctx->n);
    ctx->v[0] = y;

    return y;
}

a_tf_s *a_tf_exit(a_tf_s *ctx) { return a_tf_zero(ctx); }

a_tf_s *a_tf_zero(a_tf_s *ctx)
{
    memset(ctx->u, 0, sizeof(a_real_t) * ctx->m);
    memset(ctx->v, 0, sizeof(a_real_t) * ctx->n);
    return ctx;
}
