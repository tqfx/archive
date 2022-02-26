/*!
 @file a_vec.c
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_vec.h"

#include <stdlib.h> /* alloc */
#include <string.h> /* memcpy */

void a_vec_erase(a_vec_s *ctx, void *ptr)
{
    ctx->vptr->erase(ctx, ptr);
}
__STATIC_INLINE
void hook_erase(a_vec_s *ctx, void *ptr)
{
    (void)ctx, (void)ptr;
}

int a_vec_clone(const a_vec_s *ctx, const void *src, void *dst)
{
    return ctx->vptr->clone(ctx, src, dst);
}
__STATIC_INLINE
int hook_clone(const a_vec_s *ctx, const void *src, void *dst)
{
    memcpy(dst, src, ctx->z);
    return 0;
}

int a_vec_swap(const a_vec_s *ctx, void *a, void *b)
{
    return ctx->vptr->swap(ctx, a, b);
}
static int hook_swap(const a_vec_s *ctx, void *a, void *b)
{
    void *t = malloc(ctx->z);
    if (t == 0)
    {
        return ~0;
    }
    memcpy(t, a, ctx->z);
    memcpy(a, b, ctx->z);
    memcpy(b, t, ctx->z);
    free(t);
    return 0;
}

void a_vec_cleanup(a_vec_s *ctx)
{
    char *p = (char *)ctx->v;
    while (ctx->n)
    {
        ctx->vptr->erase(ctx, p);
        p += ctx->z;
        --ctx->n;
    }
}

void a_vec_ctor(a_vec_s *ctx, size_t siz)
{
    static a_vec_vtbl_s vtbl = {
        hook_erase,
        hook_clone,
        hook_swap,
    };
    ctx->vptr = &vtbl;
    ctx->z = siz;
    ctx->v = 0;
    ctx->m = 0;
    ctx->n = 0;
}

void a_vec_reuse(a_vec_s *ctx, size_t siz)
{
    a_vec_cleanup(ctx);
    ctx->z = siz;
    ctx->n = 0;
}

void a_vec_dtor(a_vec_s *ctx)
{
    a_vec_cleanup(ctx);
    free(ctx->v);
    ctx->v = 0;
    ctx->m = 0;
    ctx->n = 0;
    ctx->z = 0;
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
    size_t z = ctx->n * ctx->z;
    if (ctx->m <= z)
    {
        size_t m = ctx->m ? ctx->m << 1 : sizeof(size_t) * ctx->z;
        void *v = realloc(ctx->v, m);
        if (v == 0)
        {
            return ~0;
        }
        ctx->v = v;
        ctx->m = m;
    }
    void *p = (char *)ctx->v + z;
    memcpy(p, ptr, ctx->z);
    ++ctx->n;
    return 0;
}

int a_vec_pop(a_vec_s *ctx, void *ptr)
{
    if (ctx->n == 0)
    {
        return ~0;
    }
    void *p = (char *)ctx->v + --ctx->n * ctx->z;
    memcpy(ptr, p, ctx->z);
    return 0;
}

int a_vec_copy(const a_vec_s *ctx, a_vec_s *dst)
{
    size_t m = ctx->n * ctx->z;
    void *v = malloc(m);
    if (v == 0)
    {
        return ~0;
    }
    dst->v = v;
    dst->m = m;
    dst->vptr = ctx->vptr;
    char *q = (char *)dst->v;
    char *p = (char *)ctx->v;
    char *d = p + m;
    while (p != d)
    {
        ctx->vptr->clone(ctx, p, q);
        p += ctx->z;
        q += ctx->z;
    }
    dst->n = ctx->n;
    dst->z = ctx->z;
    return 0;
}

void a_vec_move(a_vec_s *ctx, a_vec_s *dst)
{
    memcpy(dst, ctx, sizeof(a_vec_s));
    ctx->v = 0;
    ctx->m = 0;
    ctx->n = 0;
    ctx->z = 0;
}
