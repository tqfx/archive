/*!
 @file test_list.c
 @brief test single-linked list library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_list.h"

#include <stdio.h>

#define test_free(x) printf("%i ", x->data)

#pragma pack(push, 4)
a_list_type(i32, int);
#pragma pack(pop)

void tests(void)
{
    a_list_t(i32) ctx;

    a_list_init(i32, ctx);
    a_list_head(ctx)->data = 0;

    for (int i = -10; i != -4; ++i)
    {
        a_list_push(i32, ctx, i);
    }

    for (int i = -4; i != 0; ++i)
    {
        a_list_ins(i32, ctx, i);
    }

    for (int i = 0; i != 8; ++i)
    {
        *a_list_pushp(i32, ctx) = i;
    }

    for (int i = 8; i != 10; ++i)
    {
        int *pi;
        a_list_insp(i32, ctx, pi);
        *pi = i;
    }

    for (int i = 0; i != 5; ++i)
    {
        int x = 0;
        a_list_pop(i32, ctx, x);
        printf("%i ", x);
    }

    while (a_list_siz(ctx))
    {
        int *px = 0;
        a_list_popp(i32, ctx, px);
        printf("%i ", *px);
    }

    printf("\nalloc = %zu, free = %zu, real = 0x%zX\n", ctx.mem.a, ctx.mem.n, ctx.mem.m);

    printf("done: ");
    a_list_done(i32, ctx, test_free);
    printf("\n");
}

void testt(void)
{
    a_list_t(i32) * ctx;

    a_list_pinit(i32, ctx);
    a_list_phead(ctx)->data = 0;

    for (int i = -10; i != -4; ++i)
    {
        a_list_ppush(i32, ctx, i);
    }

    for (int i = -4; i != 0; ++i)
    {
        a_list_pins(i32, ctx, i);
    }

    for (int i = 0; i != 8; ++i)
    {
        *a_list_ppushp(i32, ctx) = i;
    }

    for (int i = 8; i != 10; ++i)
    {
        int *pi;
        a_list_pinsp(i32, ctx, pi);
        *pi = i;
    }

    for (int i = 0; i != 5; ++i)
    {
        int x = 0;
        a_list_ppop(i32, ctx, x);
        printf("%i ", x);
    }

    while (a_list_psiz(ctx))
    {
        int *px = 0;
        a_list_ppopp(i32, ctx, px);
        printf("%i ", *px);
    }

    printf("\nalloc = %zu, free = %zu, real = 0x%zX\n", ctx->mem.a, ctx->mem.n, ctx->mem.m);

    printf("done: ");
    a_list_pdone(i32, ctx, test_free);
    printf("\n");
}

int main(void)
{
    tests();

    testt();

#define F(x) ++t

#define M 0x1000000
    int t;
    a_list_t(i32) ctx;
    a_list_init(i32, ctx);
    for (size_t i = 0; i != M; ++i)
    {
        a_list_push(i32, ctx, (int)i);
    }
    for (size_t i = 0; i != M; ++i)
    {
        a_list_pop(i32, ctx, t);
    }

    printf("%zu %zu 0x%zX ", ctx.mem.a, ctx.mem.n, ctx.mem.m);

    t = 0;
    a_list_done(i32, ctx, F);
    printf("%i\n", t);

    return 0;
}

/* END OF FILE */
