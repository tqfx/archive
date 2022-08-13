/*!
 @file que.cc
 @brief Test basic queue library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "que.h"

#include <inttypes.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static a_noret_t dtor(a_vptr_t ptr)
{
    a_u32_t *p = static_cast<a_u32_t *>(ptr);
    printf("%" PRIu32 " ", *p);
}

static a_noret_t test(a_noarg_t)
{
    a_que_s *ctx = a_que_new(sizeof(a_u64_t));
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *p = static_cast<a_u64_t *>(a_que_push_back(ctx));
        if (p)
        {
            *p = i;
        }
    }
    for (a_u64_t i = 0; i != 5; ++i)
    {
        (void)(static_cast<a_u64_t *>(a_que_pull_fore(ctx)));
    }
    a_que_set(ctx, sizeof(a_u32_t), a_null);
    for (a_u32_t i = 5; i--;)
    {
        a_u32_t *p = static_cast<a_u32_t *>(a_que_push_fore(ctx));
        if (p)
        {
            *p = i;
        }
    }
    for (a_u32_t i = 5; i != 10; ++i)
    {
        a_u32_t *p = static_cast<a_u32_t *>(a_que_push_back(ctx));
        if (p)
        {
            *p = i;
        }
    }
    a_que_foreach(a_u32_t, it, ctx)
    {
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_que_foreach_reverse(a_u32_t, it, ctx)
    {
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    for (a_u32_t i = 0; i != 5; ++i)
    {
        (void)(static_cast<a_u32_t *>(a_que_pull_back(ctx)));
    }
    for (a_u32_t i = 0; i != 5; ++i)
    {
        (void)(static_cast<a_u32_t *>(a_que_pull_fore(ctx)));
    }
    a_que_die(ctx, dtor);
    putchar('\n');
}

a_int_t main(a_noarg_t)
{
    test();
    return A_SUCCESS;
}
