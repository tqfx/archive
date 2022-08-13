/*!
 @file que.c
 @brief basic queue library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/que.h"

#include <assert.h>
#include <string.h>

A_INLINE a_noret_t no_dtor(a_vptr_t vptr) { (void)(vptr); }

static a_que_node_s *a_que_node_alloc(a_que_s *ctx)
{
    a_que_node_s *node = 0;
    if (ctx->__num)
    {
        node = ctx->__ptr[--ctx->__num];
    }
    else
    {
        node = (a_que_node_s *)malloc(sizeof(a_que_node_s));
        if (a_unlikely(node == 0))
        {
            return node;
        }
        node->__vptr = 0;
    }
    if (node->__vptr == 0)
    {
        node->__vptr = malloc(ctx->__size);
        if (a_unlikely(node->__vptr == 0))
        {
            free(node);
            return 0;
        }
    }
    ++ctx->__cnt;
    return node;
}

static int a_que_node_free(a_que_s *ctx, a_que_node_s *obj)
{
    if (obj == 0)
    {
        return A_INVALID;
    }
    if (ctx->__mem <= ctx->__num)
    {
        a_size_t mem = ctx->__mem + (ctx->__mem >> 1) + 1;
        a_que_node_s **ptr = (a_que_node_s **)realloc(ctx->__ptr, sizeof(a_vptr_t) * mem);
        if (a_unlikely(ptr == 0))
        {
            return A_FAILURE;
        }
        ctx->__ptr = ptr;
        ctx->__mem = mem;
    }
    ctx->__ptr[ctx->__num++] = obj;
    --ctx->__cnt;
    return A_SUCCESS;
}

static a_noret_t a_que_drop_(a_que_s *ctx)
{
    while (a_list_used(ctx->__head))
    {
        a_que_node_s *node = (a_que_node_s *)ctx->__head->prev;
        if (a_unlikely(a_que_node_free(ctx, node)))
        {
            break;
        }
        a_list_del_prev(ctx->__head);
        a_list_dtor(node->__node);
    }
}

a_que_s *a_que_new(a_size_t size)
{
    a_que_s *ctx = (a_que_s *)malloc(sizeof(a_que_s));
    if (ctx)
    {
        a_que_ctor(ctx, size);
    }
    return ctx;
}

a_noret_t a_que_die(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    if (ctx)
    {
        a_que_dtor(ctx, dtor);
        free(ctx);
    }
}

a_noret_t a_que_ctor(a_que_s *ctx, a_size_t size)
{
    assert(ctx);
    a_list_ctor(ctx->__head);
    ctx->__size = size;
    ctx->__ptr = 0;
    ctx->__num = 0;
    ctx->__mem = 0;
    ctx->__cnt = 0;
}

a_noret_t a_que_dtor(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    a_que_drop_(ctx);
    dtor = dtor ? dtor : no_dtor;
    while (ctx->__num)
    {
        --ctx->__num;
        dtor(ctx->__ptr[ctx->__num]->__vptr);
        free(ctx->__ptr[ctx->__num]->__vptr);
        free(ctx->__ptr[ctx->__num]);
    }
    free(ctx->__ptr);
    ctx->__size = 0;
    ctx->__ptr = 0;
    ctx->__mem = 0;
}

a_que_s *a_que_move(a_que_s *ctx, a_que_s *obj)
{
    assert(ctx);
    assert(obj);
    memcpy(ctx, obj, sizeof(*obj));
    memset(obj, 0, sizeof(*obj));
    return ctx;
}

a_int_t a_que_set(a_que_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    if (a_unlikely(size == 0))
    {
        return A_FAILURE;
    }
    a_que_drop(ctx, dtor);
    ctx->__size = size;
    return A_SUCCESS;
}

a_noret_t a_que_drop(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    a_que_drop_(ctx);
    dtor = dtor ? dtor : no_dtor;
    for (a_size_t i = ctx->__num; i--;)
    {
        dtor(ctx->__ptr[i]->__vptr);
        free(ctx->__ptr[i]->__vptr);
        ctx->__ptr[i]->__vptr = 0;
    }
}

a_vptr_t a_que_push_fore(a_que_s *ctx)
{
    assert(ctx);
    a_que_node_s *node = a_que_node_alloc(ctx);
    if (a_unlikely(node == 0))
    {
        return node;
    }
    a_list_add_next(ctx->__head, node->__node);
    return node->__vptr;
}

a_vptr_t a_que_push_back(a_que_s *ctx)
{
    assert(ctx);
    a_que_node_s *node = a_que_node_alloc(ctx);
    if (a_unlikely(node == 0))
    {
        return node;
    }
    a_list_add_prev(ctx->__head, node->__node);
    return node->__vptr;
}

a_vptr_t a_que_pull_fore(a_que_s *ctx)
{
    assert(ctx);
    a_vptr_t vptr = 0;
    if (a_list_used(ctx->__head))
    {
        a_que_node_s *node = (a_que_node_s *)ctx->__head->next;
        if (a_unlikely(a_que_node_free(ctx, node)))
        {
            return vptr;
        }
        a_list_del_next(ctx->__head);
        a_list_dtor(node->__node);
        vptr = node->__vptr;
    }
    return vptr;
}

a_vptr_t a_que_pull_back(a_que_s *ctx)
{
    assert(ctx);
    a_vptr_t vptr = 0;
    if (a_list_used(ctx->__head))
    {
        a_que_node_s *node = (a_que_node_s *)ctx->__head->prev;
        if (a_unlikely(a_que_node_free(ctx, node)))
        {
            return vptr;
        }
        a_list_del_prev(ctx->__head);
        a_list_dtor(node->__node);
        vptr = node->__vptr;
    }
    return vptr;
}

#endif /* __STDC_HOSTED__ */
