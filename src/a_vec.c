/*!
 @file a_vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_vec.h"

#include <stdlib.h> /* alloc */
#include <string.h> /* memcpy */

void a_vec_erase(a_vec_s *ctx, void *ptr)
{
    ctx->_vt->erase(ctx, ptr);
}
static void a_vec_vt_erase(a_vec_s *ctx, void *ptr)
{
    (void)ctx, (void)ptr;
}

int a_vec_clone(const a_vec_s *ctx, const void *src, void *dst)
{
    return ctx->_vt->clone(ctx, src, dst);
}
static int a_vec_vt_clone(const a_vec_s *ctx, const void *src, void *dst)
{
    memcpy(dst, src, ctx->_z);
    return 0;
}

int a_vec_swap(const a_vec_s *ctx, void *a, void *b)
{
    return ctx->_vt->swap(ctx, a, b);
}
static int a_vec_vt_swap(const a_vec_s *ctx, void *a, void *b)
{
    void *t = malloc(ctx->_z);
    if (t == 0)
    {
        return ~0;
    }
    memcpy(t, a, ctx->_z);
    memcpy(a, b, ctx->_z);
    memcpy(b, t, ctx->_z);
    free(t);
    return 0;
}

void a_vec_cleanup(a_vec_s *ctx)
{
    unsigned char *p = (unsigned char *)ctx->_v;
    while (ctx->_n)
    {
        ctx->_vt->erase(ctx, p);
        p += ctx->_z;
        --ctx->_n;
    }
}

void a_vec_ctor(a_vec_s *ctx, size_t siz)
{
    static a_vec_vt_s vt = {
        a_vec_vt_erase,
        a_vec_vt_clone,
        a_vec_vt_swap,
    };
    ctx->_vt = &vt;
    ctx->_z = siz;
    ctx->_v = 0;
    ctx->_m = 0;
    ctx->_n = 0;
}

void a_vec_reuse(a_vec_s *ctx, size_t siz)
{
    a_vec_cleanup(ctx);
    ctx->_z = siz;
    ctx->_n = 0;
}

void a_vec_dtor(a_vec_s *ctx)
{
    a_vec_cleanup(ctx);
    free(ctx->_v);
    ctx->_v = 0;
    ctx->_m = 0;
    ctx->_n = 0;
    ctx->_z = 0;
}

a_vec_s *a_vec_new(size_t siz)
{
    a_vec_s *ctx = (a_vec_s *)malloc(sizeof(a_vec_s));
    if (ctx)
    {
        a_vec_ctor(ctx, siz);
    }
    return ctx;
}

void a_vec_delete(a_vec_s *ctx)
{
    if (ctx)
    {
        a_vec_dtor(ctx);
    }
    free(ctx);
}

int a_vec_push(a_vec_s *ctx, void *ptr)
{
    size_t z = ctx->_n * ctx->_z;
    if (ctx->_m <= z)
    {
        size_t m = ctx->_m ? ctx->_m << 1 : sizeof(size_t) * ctx->_z;
        void *v = realloc(ctx->_v, m);
        if (v == 0)
        {
            return ~0;
        }
        ctx->_v = v;
        ctx->_m = m;
    }
    void *p = (unsigned char *)ctx->_v + z;
    memcpy(p, ptr, ctx->_z);
    ++ctx->_n;
    return 0;
}

int a_vec_pop(a_vec_s *ctx, void *ptr)
{
    if (ctx->_n)
    {
        --ctx->_n;
        void *p = (unsigned char *)ctx->_v + ctx->_n * ctx->_z;
        memcpy(ptr, p, ctx->_z);
        return 0;
    }
    return ~0;
}

int a_vec_copy(const a_vec_s *ctx, a_vec_s *dst)
{
    size_t m = ctx->_n * ctx->_z;
    void *v = malloc(m);
    if (v == 0)
    {
        return ~0;
    }
    dst->_v = v;
    dst->_m = m;
    dst->_vt = ctx->_vt;
    unsigned char *q = (unsigned char *)dst->_v;
    unsigned char *p = (unsigned char *)ctx->_v;
    unsigned char *d = p + m;
    while (p != d)
    {
        ctx->_vt->clone(ctx, p, q);
        p += ctx->_z;
        q += ctx->_z;
    }
    dst->_n = ctx->_n;
    dst->_z = ctx->_z;
    return 0;
}

void a_vec_move(a_vec_s *ctx, a_vec_s *dst)
{
    memcpy(dst, ctx, sizeof(a_vec_s));
    ctx->_v = 0;
    ctx->_m = 0;
    ctx->_n = 0;
    ctx->_z = 0;
}
