/*!
 @file vec.cpp
 @brief test vector library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>

#include "a_vec.h"

typedef struct t_vec_s
{
    a_vec_s vec[1];
} t_vec_s;

static void hook_erase(a_vec_s *ctx, void *ptr)
{
    (void)ctx;
    char *s = *(char **)ptr;
    printf("-- erase %s\n", s);
}

static void test_vec_ctor(t_vec_s *ctx, size_t siz)
{
    a_vec_ctor(ctx->vec, siz);
    ctx->vec->vptr->erase = hook_erase;
}

static void test0(size_t n)
{
    a_vec_s *ctx = a_vec_new(sizeof(uint32_t));
    for (size_t i = 0; i != n; ++i)
    {
        uint32_t dat = (uint32_t)i;
        a_vec_push(ctx, &dat);
    }
    printf("%zu %zu %zu\n", a_vec_mem(ctx), a_vec_use(ctx), a_vec_num(ctx));
    for (size_t i = 0; i != n; ++i)
    {
        uint32_t out = 0;
        a_vec_pop(ctx, &out);
    }
    a_vec_reuse(ctx, sizeof(uint64_t));
    for (size_t i = 0; i != n; ++i)
    {
        uint64_t dat = (uint64_t)i;
        a_vec_push(ctx, &dat);
    }
    printf("%zu %zu %zu\n", a_vec_mem(ctx), a_vec_use(ctx), a_vec_num(ctx));
    for (size_t i = 0; i != n; ++i)
    {
        uint64_t out = 0;
        a_vec_pop(ctx, &out);
    }
    a_vec_delete(ctx);
}

static void test1(size_t n)
{
    a_vec_s ctx[1];
    a_vec_ctor(ctx, sizeof(uint32_t));
    for (size_t i = 0; i != n; ++i)
    {
        uint32_t dat = (uint32_t)i;
        a_vec_push(ctx, &dat);
    }
    a_vec_s dst[1];
    a_vec_copy(ctx, dst);
    a_vec_dtor(ctx);
    a_vec_move(dst, ctx);
    for (size_t i = 0; i != 10; ++i)
    {
        uint32_t p = *(uint32_t *)a_vec_at(ctx, i);
        printf("%u ", p);
    }
    putchar('\n');
    a_vec_dtor(ctx);
}

static void test2(void)
{
    static char s1[] = {'1', 0};
    static char s2[] = {'2', 0};
    t_vec_s ctx[1];
    test_vec_ctor(ctx, sizeof(char *));
    a_vec_s *vctx = (a_vec_s *)ctx;
    char *s = s1;
    a_vec_push(vctx, &s);
    s = s2;
    a_vec_push(vctx, &s);
    a_vec_dtor(vctx);
}

int main(void)
{
    size_t n = 1000000;
    test0(n);
    test1(n);
    test2();
    return 0;
}
