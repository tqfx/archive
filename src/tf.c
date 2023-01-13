#include "a/tf.h"
#include <string.h>

static void a_tf_roll(a_real_t *p, a_uint_t n, a_real_t x)
{
    for (a_uint_t i = --n; i; n = i)
    {
        p[n] = p[--i];
    }
    *p = x;
}

a_void_t a_tf_set_num(a_tf_s *ctx, a_uint_t m, const a_real_t *num, a_real_t *u)
{
    memset(u, 0, sizeof(a_real_t) * m);
    ctx->num = num;
    ctx->m = m;
    ctx->u = u;
}

a_void_t a_tf_set_den(a_tf_s *ctx, a_uint_t n, const a_real_t *den, a_real_t *v)
{
    memset(v, 0, sizeof(a_real_t) * n);
    ctx->den = den;
    ctx->n = n;
    ctx->v = v;
}

a_tf_s *a_tf_init(a_tf_s *ctx,
                  a_uint_t m, const a_real_t *num, a_real_t *u,
                  a_uint_t n, const a_real_t *den, a_real_t *v)
{
    a_tf_set_num(ctx, m, num, u);
    a_tf_set_den(ctx, n, den, v);
    return ctx;
}

a_real_t a_tf_proc(a_tf_s *ctx, a_real_t x)
{
    a_real_t y = 0;
    a_tf_roll(ctx->u, ctx->m, x);
    for (a_uint_t i = 0; i != ctx->m; ++i)
    {
        y += ctx->num[i] * ctx->u[i];
    }
    for (a_uint_t i = 0; i != ctx->n; ++i)
    {
        y -= ctx->den[i] * ctx->v[i];
    }
    a_tf_roll(ctx->v, ctx->n, y);
    return y;
}

a_tf_s *a_tf_exit(a_tf_s *ctx) { return a_tf_zero(ctx); }

a_tf_s *a_tf_zero(a_tf_s *ctx)
{
    memset(ctx->u, 0, sizeof(a_real_t) * ctx->m);
    memset(ctx->v, 0, sizeof(a_real_t) * ctx->n);
    return ctx;
}
