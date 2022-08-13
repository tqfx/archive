/*!
 @file __vector__.c
 @brief Test __brief__
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "../src/host/__vector__.h"
#include "../test.h"

static void test(void)
{
    {
        __type__ *ctx = __vector___new();

        __vector___foreach(it, ctx);
        __vector___foreach_reverse(it, ctx);

        for (__T__ i = 0; i != 10; ++i)
        {
            __T__ *p = __vector___push(ctx);
            if (p)
            {
                *p = i;
            }
        }

        {
            __T__ *end = __vector___end(ctx);
            __T__ *top = __vector___top(ctx);
            TEST_BUG(end - top == 1);
        }

        __vector___forenum(i, ctx)
        {
            __T__ *it = __vector___at(ctx, i);
            printf("%zu ", *it);
        }
        putchar('\n');

        __vector___forenum_reverse(i, ctx)
        {
            __T__ *it = __vector___at(ctx, i);
            printf("%zu ", *it);
        }
        putchar('\n');

        __type__ obj[1];
        __vector___copy(obj, ctx);
        __vector___dtor(ctx);
        __vector___move(ctx, obj);

        for (__T__ i = 0; i != 10; ++i)
        {
            __vector___pop(ctx);
        }

        __vector___die(ctx);
    }

    {
        __type__ *ctx = __vector___new();

        for (__T__ i = 5; i != 10; ++i)
        {
            __T__ *p = __vector___insert(ctx, i);
            if (p)
            {
                *p = i;
            }
        }
        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vector___insert(ctx, i);
            if (p)
            {
                *p = i;
            }
        }

        __vector___swap(ctx, 0, 0);
        __vector___swap(ctx, 0, ~0U);
        __vector___swap(ctx, ~0U, 0);
        __vector___swap(ctx, 4, 6);
        __vector___swap(ctx, 6, 4);

        __vector___foreach(it, ctx)
        {
            printf("%zu ", *it);
        }
        putchar('\n');

        __vector___foreach_reverse(it, ctx)
        {
            printf("%zu ", *it);
        }
        putchar('\n');

        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vector___remove(ctx, i);
            if (p)
            {
                printf("%zu ", *p);
            }
        }
        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vector___remove(ctx, 0);
            if (p)
            {
                printf("%zu ", *p);
            }
        }
        putchar('\n');

        __vector___die(ctx);
    }

    {
        __type__ *ctx = __vector___new();

        for (__T__ i = 5; i != 10; ++i)
        {
            __T__ *p = __vector___push_back(ctx);
            if (p)
            {
                *p = i;
            }
        }
        for (__T__ i = 5; i != 10; ++i)
        {
            __T__ *p = __vector___pop_back(ctx);
            if (p)
            {
                printf("%zu ", *p);
            }
        }
        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vector___push_fore(ctx);
            if (p)
            {
                *p = i;
            }
        }
        for (__T__ i = 0; i != 5; ++i)
        {
            __T__ *p = __vector___pop_fore(ctx);
            if (p)
            {
                printf("%zu ", *p);
            }
        }
        putchar('\n');

        __vector___die(ctx);
    }
}

int main(void)
{
    test();
    return __success__;
}
