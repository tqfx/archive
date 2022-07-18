/*!
 @file vec.c
 @brief Testing basic vector library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/host/vec.h"

#include "../src/host/vec.h"

#include <inttypes.h>
#include <string.h>
#include <stdio.h>

static void dtor(void *ptr)
{
    uint32_t *p = (uint32_t *)ptr;
    printf("%" PRIu32 " ", *p);
}

static void test(void)
{
    a_vec_s *ctx = a_vec_new(sizeof(uint64_t));
    for (uint64_t i = 0; i != 10; ++i)
    {
        uint64_t *p = (uint64_t *)a_vec_push(ctx);
        if (p == 0)
        {
            break;
        }
        *p = i;
    }
    a_vec_resize(ctx, sizeof(uint32_t));
    for (uint32_t i = 0; i != 20; ++i)
    {
        uint32_t *p = (uint32_t *)a_vec_push(ctx);
        if (p == 0)
        {
            break;
        }
        *p = i;
    }
    for (uint32_t i = 0; i != 10; ++i)
    {
        a_vec_pop(ctx);
    }
    uint32_t *p = (uint32_t *)a_vec_ptr(ctx);
    for (uint32_t i = 0; i != 10; ++i)
    {
        printf("%" PRIu32 " ", p[i]);
    }
    putchar('\n');
    a_vec_die(ctx, dtor);
    putchar('\n');
}

VEC_S(int_s, int);
VEC_MEM(int_s, int_mem)
VEC_NUM(int_s, int_num)
VEC_AT(int_s, int_at, int)
VEC_F(static, int, int_s, int)
VEC_CTOR(int_s, int_ctor)
VEC_DTOR(int_s, int_dtor, VEC_DTOR_NO)
VEC_NEW(int_s, int_new, int_ctor)
VEC_DIE(int_s, int_die, int_dtor)
VEC_PUSH(int_s, int_push, int)
VEC_POP(int_s, int_pop, int)

static void test_intern(void)
{
    int_s *ctx = int_new();
    for (int i = 0; i != 0x100; ++i)
    {
        *int_push(ctx) = i;
    }
    for (int i = 0; i != 0x10; ++i)
    {
        int_pop(ctx);
    }
    for (unsigned int i = 0; i != int_num(ctx); ++i)
    {
        *int_at(ctx, i) = 0;
    }
    for (size_t i = int_num(ctx); i != int_mem(ctx); ++i)
    {
        *int_at(ctx, i) = 0;
    }
    int_die(ctx);
}

int main(void)
{
    test();
    test_intern();
    return 0;
}
