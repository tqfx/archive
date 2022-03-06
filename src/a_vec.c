/*!
 @file a_vec.c
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_vec.h"

#include <stdlib.h>

a_vec_s *a_vec_new(void)
{
    a_vec_s *ctx = (a_vec_s *)malloc(sizeof(a_vec_s));
    if (ctx)
    {
        a_vec_ctor(ctx);
    }
    return ctx;
}

void a_vec_delete(a_vec_s *ctx)
{
    if (ctx)
    {
        a_vec_dtor(ctx);
        free(ctx);
    }
}

__STATIC_INLINE
void *virtual_address(void *obj, size_t index)
{
    (void)obj, (void)index;
    return 0;
}

__STATIC_INLINE
int virtual_realloc(void *obj, size_t capacity)
{
    (void)obj, (void)capacity;
    return ~0;
}

void a_vec_ctor(a_vec_s *ctx)
{
    AASSERT(ctx);
    static const a_vec_vtbl_s vtbl = {
        virtual_address,
        virtual_realloc,
    };
    ctx->vptr = &vtbl;
    ctx->capacity = ctx->length = 0;
}

void a_vec_dtor(a_vec_s *ctx)
{
    AASSERT(ctx);
    ctx->capacity = ctx->length = 0;
}

void *a_vec_push(void *obj)
{
    AASSERT(obj);
    a_vec_s *ctx = (a_vec_s *)obj;
    if (ctx->capacity <= ctx->length)
    {
        size_t capacity = ctx->capacity + (ctx->capacity >> 1) + 1;
        if (ctx->vptr->realloc(ctx, capacity))
        {
            return 0;
        }
        ctx->capacity = capacity;
    }
    return ctx->vptr->address(ctx, ctx->length++);
}

void *a_vec_pop(void *obj)
{
    AASSERT(obj);
    a_vec_s *ctx = (a_vec_s *)obj;
    if (ctx->length)
    {
        return ctx->vptr->address(ctx, --ctx->length);
    }
    return 0;
}
