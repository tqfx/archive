/*!
 @file __vec__.cc
 @brief Test __brief__
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "../src/host/__vec__.h"
#include "../test.h"

static void test(void)
{
    {
        __type__ *ctx = __vec___new();

        __vec___foreach(it, ctx);
        __vec___foreach_reverse(it, ctx);

        for (__T__ i = 0; i != 10; ++i)
        {
            __T__ *p = __vec___push(ctx);
            if (p)
            {
                *p = i;
            }
        }

        {
            __T__ *end = __vec___end(ctx);
            __T__ *top = __vec___top(ctx);
            TEST_BUG(end - top == 1);
        }

        __vec___forenum(i, ctx)
        {
            __T__ *it = __vec___at(ctx, i);
            printf("%zu ", *it);
        }
        putchar('\n');

        __vec___forenum_reverse(i, ctx)
        {
            __T__ *it = __vec___at(ctx, i);
            printf("%zu ", *it);
        }
        putchar('\n');

        __type__ obj[1];
        __vec___copy(obj, ctx);
        __vec___dtor(ctx);
        __vec___move(ctx, obj);

        for (__T__ i = 0; i != 10; ++i)
        {
            __vec___pop(ctx);
        }

        __vec___die(ctx);
    }

    {
        __type__ *ctx = __vec___new();

        for (__T__ i = 5; i != 10; ++i)
        {
            __T__ *p = __vec___insert(ctx, i);
            if (p)
            {
                *p = i;
            }
        }
        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vec___insert(ctx, i);
            if (p)
            {
                *p = i;
            }
        }

        __vec___swap(ctx, 0, 0);
        __vec___swap(ctx, 0, ~0U);
        __vec___swap(ctx, ~0U, 0);
        __vec___swap(ctx, 4, 6);
        __vec___swap(ctx, 6, 4);

        __vec___foreach(it, ctx)
        {
            printf("%zu ", *it);
        }
        putchar('\n');

        __vec___foreach_reverse(it, ctx)
        {
            printf("%zu ", *it);
        }
        putchar('\n');

        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vec___remove(ctx, i);
            if (p)
            {
                printf("%zu ", *p);
            }
        }
        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vec___remove(ctx, 0);
            if (p)
            {
                printf("%zu ", *p);
            }
        }
        putchar('\n');

        __vec___die(ctx);
    }

    {
        __type__ *ctx = __vec___new();

        for (__T__ i = 5; i != 10; ++i)
        {
            __T__ *p = __vec___push_back(ctx);
            if (p)
            {
                *p = i;
            }
        }
        for (__T__ i = 5; i != 10; ++i)
        {
            __T__ *p = __vec___pop_back(ctx);
            if (p)
            {
                printf("%zu ", *p);
            }
        }
        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vec___push_front(ctx);
            if (p)
            {
                *p = i;
            }
        }
        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vec___pop_front(ctx);
            if (p)
            {
                printf("%zu ", *p);
            }
        }
        putchar('\n');

        __vec___die(ctx);
    }
}

int main(void)
{
    test();
    return __success__;
}
