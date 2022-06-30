/*!
 @file vec.c
 @brief Testing vector library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/misc/vec.h"

#include <inttypes.h>
#include <string.h>
#include <stdio.h>

static void func(void *ptr)
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
    a_vec_die(ctx, func);
    putchar('\n');
}

int main(void)
{
    test();
    return 0;
}
