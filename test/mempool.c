/*!
 @file mempool.c
 @brief test memory pool
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_mempool.h"
#include "a_list.h"
#include "a_str.h"

#include <stdio.h>

static void test_show(const a_mempool_s *ctx)
{
    printf("%zu = %zu + %zu = %zu * %zu + %zu * %zu\n",
           sizeof(void *) * a_mempool_capacity(ctx) + a_mempool_size(ctx) * a_mempool_length(ctx),
           sizeof(void *) * a_mempool_capacity(ctx),
           a_mempool_size(ctx) * a_mempool_length(ctx),
           sizeof(void *),
           a_mempool_capacity(ctx),
           a_mempool_size(ctx),
           a_mempool_length(ctx));
}

static void test_str(size_t n)
{
    a_mempool_s *ctx = a_mempool_new(sizeof(a_str_s));
    a_str_s **vec = (a_str_s **)malloc(sizeof(a_str_s *) * n);

    for (size_t i = 0; i != n; ++i)
    {
        vec[i] = (a_str_s *)a_mempool_alloc(ctx);
    }
    test_show(ctx);
    for (size_t i = 0; i != n; ++i)
    {
        a_mempool_free(ctx, vec[i]);
    }
    test_show(ctx);

    for (size_t i = 0; i != n; ++i)
    {
        vec[i] = (a_str_s *)a_mempool_alloc(ctx);
        a_str_ctor(vec[i]);
        a_str_printf(vec[i], "%zu", i);
    }
    test_show(ctx);
    for (size_t i = 0; i != n; ++i)
    {
        a_mempool_free(ctx, vec[i]);
    }
    test_show(ctx);

    a_mempool_delete(ctx, (void (*)(void *))a_str_delete);
    free(vec);
}

static void test_list(size_t n)
{
    a_list_s *next;
    A_LIST_HEAD(list);

    a_mempool_s *ctx = a_mempool_new(sizeof(a_list_s));

    a_list_ctor(list);
    for (size_t i = 0; i != n; ++i)
    {
        next = (a_list_s *)a_mempool_alloc(ctx);
        a_list_add_next(list, next);
    }
    test_show(ctx);

    a_list_for_next(next, list)
    {
        a_mempool_free(ctx, next);
    }
    test_show(ctx);

    a_list_ctor(list);
    for (size_t i = 0; i != n; ++i)
    {
        next = (a_list_s *)a_mempool_alloc(ctx);
        a_list_add_next(list, next);
    }
    test_show(ctx);

    a_list_for_next(next, list)
    {
        a_mempool_free(ctx, next);
    }
    test_show(ctx);

    a_mempool_delete(ctx, 0);
}

int main(void)
{
    test_str(0xFF);
    test_list(0xFF);
    return 0;
}
