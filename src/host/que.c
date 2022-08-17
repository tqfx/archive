/*!
 @file que.c
 @brief basic queue library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#if __STDC_HOSTED__

#include "a/host/que.h"

#include <assert.h>
#include <string.h>

#undef a_que_at
#undef a_que_fore
#undef a_que_back
#undef a_que_fore_
#undef a_que_back_
#undef a_que_insert
#undef a_que_remove
#undef a_que_push_fore
#undef a_que_push_back
#undef a_que_pull_fore
#undef a_que_pull_back

#define context_alloc(size) malloc(size)
#define context_free(vptr) free(vptr)

A_INLINE a_noret_t default_dtor(a_vptr_t vptr) { (void)(vptr); }

static a_que_node_s *a_que_node_alloc(a_que_s *ctx)
{
    a_que_node_s *node = 0;
    if (ctx->__cur)
    {
        node = ctx->__ptr[--ctx->__cur];
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
        node->__vptr = context_alloc(ctx->__size);
        if (a_unlikely(node->__vptr == 0))
        {
            free(node);
            return 0;
        }
    }
    ++ctx->__num;
    return node;
}

static int a_que_node_free(a_que_s *ctx, a_que_node_s *obj)
{
    if (obj == 0)
    {
        return A_INVALID;
    }
    if (ctx->__mem <= ctx->__cur)
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
    ctx->__ptr[ctx->__cur++] = obj;
    --ctx->__num;
    return A_SUCCESS;
}

static a_noret_t a_que_drop_(a_que_s *ctx)
{
    while (a_list_used(ctx->__head))
    {
        a_que_node_s *node = a_que_from(ctx->__head->prev);
        if (a_unlikely(a_que_node_free(ctx, node)))
        {
            break;
        }
        a_list_del_node(node->__node);
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
    ctx->__size = size ? size : sizeof(a_cast_u);
    ctx->__ptr = 0;
    ctx->__num = 0;
    ctx->__cur = 0;
    ctx->__mem = 0;
}

a_noret_t a_que_dtor(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    a_que_drop_(ctx);
    a_noret_t (*context_dtor)(a_vptr_t) = dtor ? dtor : default_dtor;
    while (ctx->__cur)
    {
        --ctx->__cur;
        context_dtor(ctx->__ptr[ctx->__cur]->__vptr);
        context_free(ctx->__ptr[ctx->__cur]->__vptr);
        free(ctx->__ptr[ctx->__cur]);
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

a_vptr_t a_que_at(const a_que_s *ctx, a_imax_t idx)
{
    assert(ctx);
    a_imax_t cur = 0;
    a_vptr_t vptr = 0;
    if (idx < 0)
    {
        a_list_foreach_prev(it, ctx->__head)
        {
            if (--cur == idx)
            {
                vptr = a_que_from(it)->__vptr;
                break;
            }
        }
    }
    else
    {
        a_list_foreach_next(it, ctx->__head)
        {
            if (cur++ == idx)
            {
                vptr = a_que_from(it)->__vptr;
                break;
            }
        }
    }
    return vptr;
}

a_noret_t a_que_set(a_que_s *ctx, a_size_t size, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    size = size ? size : sizeof(a_cast_u);
    a_que_drop(ctx, dtor);
    ctx->__size = size;
}

a_noret_t a_que_drop(a_que_s *ctx, a_noret_t (*dtor)(a_vptr_t))
{
    assert(ctx);
    a_que_drop_(ctx);
    a_noret_t (*context_dtor)(a_vptr_t) = dtor ? dtor : default_dtor;
    for (a_size_t cur = ctx->__cur; cur--; ctx->__ptr[cur]->__vptr = 0)
    {
        context_dtor(ctx->__ptr[cur]->__vptr);
        context_free(ctx->__ptr[cur]->__vptr);
    }
}

a_int_t a_que_swap_(const a_que_s *ctx, a_vptr_t lhs, a_vptr_t rhs)
{
    assert(ctx);
    assert(lhs);
    assert(rhs);
    if (lhs == rhs)
    {
        return A_SUCCESS;
    }
    int ok = A_FAILURE;
    a_que_node_s *lobj = 0;
    a_que_node_s *robj = 0;
    a_list_foreach_next(it, ctx->__head)
    {
        a_que_node_s *node = a_que_from(it);
        if (node->__vptr == lhs)
        {
            lobj = node;
        }
        else if (node->__vptr == rhs)
        {
            robj = node;
        }
        if (lobj && robj)
        {
            a_list_swap_node(lobj->__node, robj->__node);
            ok = A_SUCCESS;
            break;
        }
    }
    return ok;
}

a_noret_t a_que_swap(const a_que_s *ctx, a_size_t lhs, a_size_t rhs)
{
    assert(ctx);
    a_size_t cur = 0;
    a_size_t num = ctx->__num - 1;
    lhs = lhs < ctx->__num ? lhs : num;
    rhs = rhs < ctx->__num ? rhs : num;
    if (lhs != rhs)
    {
        a_que_node_s *lobj = 0;
        a_que_node_s *robj = 0;
        a_list_foreach_next(it, ctx->__head)
        {
            if (cur == lhs)
            {
                // because lhs less than num
                // it's never a null pointer
                lobj = a_que_from(it);
            }
            else if (cur == rhs)
            {
                // because rhs less than num
                // it's never a null pointer
                robj = a_que_from(it);
            }
            if (lobj && robj)
            {
                break;
            }
            ++cur;
        }
        a_list_swap_node(lobj->__node, robj->__node);
    }
}

a_noret_t a_que_sort_fore(const a_que_s *ctx, a_int_t (*cmp)(a_cptr_t, a_cptr_t))
{
    assert(ctx);
    if (ctx->__num > 1)
    {
        a_list_s *pt = 0;
        a_list_s *it = ctx->__head->next;
        for (a_list_s *at = it->next; at != ctx->__head; at = at->next)
        {
            a_vptr_t lhs = a_que_from(it)->__vptr;
            a_vptr_t rhs = a_que_from(at)->__vptr;
            if (cmp(lhs, rhs) > 0)
            {
                pt = at;
            }
            else
            {
                break;
            }
        }
        if (pt)
        {
            a_list_del_(it, it);
            a_list_add_(pt->next, pt, it, it);
        }
    }
}

a_noret_t a_que_sort_back(const a_que_s *ctx, a_int_t (*cmp)(a_cptr_t, a_cptr_t))
{
    assert(ctx);
    if (ctx->__num > 1)
    {
        a_list_s *pt = 0;
        a_list_s *it = ctx->__head->prev;
        for (a_list_s *at = it->prev; at != ctx->__head; at = at->prev)
        {
            a_vptr_t lhs = a_que_from(at)->__vptr;
            a_vptr_t rhs = a_que_from(it)->__vptr;
            if (cmp(lhs, rhs) > 0)
            {
                pt = at;
            }
            else
            {
                break;
            }
        }
        if (pt)
        {
            a_list_del_(it, it);
            a_list_add_(pt, pt->prev, it, it);
        }
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
        a_que_node_s *node = a_que_from(ctx->__head->next);
        if (a_unlikely(a_que_node_free(ctx, node)))
        {
            return vptr;
        }
        a_list_del_node(node->__node);
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
        a_que_node_s *node = a_que_from(ctx->__head->prev);
        if (a_unlikely(a_que_node_free(ctx, node)))
        {
            return vptr;
        }
        a_list_del_node(node->__node);
        a_list_dtor(node->__node);
        vptr = node->__vptr;
    }
    return vptr;
}

a_vptr_t a_que_insert(a_que_s *ctx, a_size_t idx)
{
    assert(ctx);
    if (idx < ctx->__num)
    {
        a_size_t cur = 0;
        a_que_node_s *node = a_que_node_alloc(ctx);
        if (a_unlikely(node == 0))
        {
            return node;
        }
        a_list_foreach_next(it, ctx->__head)
        {
            if (cur++ == idx)
            {
                a_list_add_prev(it, node->__node);
                break;
            }
        }
        return node->__vptr;
    }
    return a_que_push_back(ctx);
}

a_vptr_t a_que_remove(a_que_s *ctx, a_size_t idx)
{
    assert(ctx);
    if (idx < ctx->__num)
    {
        a_size_t cur = 0;
        a_que_node_s *node = 0;
        a_list_foreach_next(it, ctx->__head)
        {
            if (cur++ == idx)
            {
                // because idx less than num
                // it's never a null pointer
                node = a_que_from(it);
                break;
            }
        }
        if (a_unlikely(a_que_node_free(ctx, node)))
        {
            return 0;
        }
        a_list_del_node(node->__node);
        a_list_dtor(node->__node);
        return node->__vptr;
    }
    return a_que_pull_back(ctx);
}

#endif /* __STDC_HOSTED__ */
