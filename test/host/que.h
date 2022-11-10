#ifndef TEST_HOST_QUE_H
#define TEST_HOST_QUE_H
#define MAIN_(s, argc, argv) que##s(argc, argv)
#include "../test.h"
#include "a/host/que.h"
#include <string.h>

static void dtor(a_vptr_t ptr)
{
    a_u32_t *obj = a_u32_p(ptr);
    printf("%" PRIu32 " ", *obj);
}

static void test(void)
{
    a_que_s *ctx = a_que_new(sizeof(a_u64_t));
    for (a_u64_t i = 0; i != 10; ++i)
    {
        a_u64_t *obj = a_que_push_back(a_u64_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    {
        a_u64_t *fore = a_que_fore_(a_u64_t, ctx);
        a_u64_t *back = a_que_back_(a_u64_t, ctx);
        printf("%" PRIu64 " %" PRIu64 " ", *fore, *back);
    }
    {
        a_u64_t *fore = a_que_fore(a_u64_t, ctx);
        a_u64_t *back = a_que_back(a_u64_t, ctx);
        if (fore && back)
        {
            printf("%" PRIu64 " %" PRIu64 " ", *fore, *back);
        }
    }
    {
        a_u64_t *fore = a_que_at(a_u64_t, ctx, 0);
        a_u64_t *back = a_que_at(a_u64_t, ctx, ~0);
        if (fore && back)
        {
            printf("%" PRIu64 " %" PRIu64 "\n", *fore, *back);
        }
    }
    for (a_u64_t i = 0; i != 5; ++i)
    {
        (void)(a_que_pull_fore(a_u64_t, ctx));
    }
    a_que_set(ctx, sizeof(a_u32_t), A_NULL);
    for (a_u32_t i = 5; i--;)
    {
        a_u32_t *obj = a_que_push_fore(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    for (a_u32_t i = 5; i != 10; ++i)
    {
        a_u32_t *obj = a_que_push_back(a_u32_t, ctx);
        if (obj)
        {
            *obj = i;
        }
    }
    {
        a_u32_t *obj = a_que_insert(a_u32_t, ctx, 0);
        if (obj)
        {
            *obj = A_U32_MAX;
        }
    }
    {
        a_u32_t *obj = a_que_insert(a_u32_t, ctx, A_SIZE_MAX);
        if (obj)
        {
            *obj = A_U32_MAX;
        }
    }
    (void)(a_que_remove(a_u32_t, ctx, 0));
    (void)(a_que_remove(a_u32_t, ctx, A_SIZE_MAX));
    a_que_swap(ctx, 0, A_SIZE_MAX);
    {
        a_u32_t *lhs = a_que_fore_(a_u32_t, ctx);
        a_u32_t *rhs = a_que_back_(a_u32_t, ctx);
        a_que_swap_(ctx, lhs, rhs);
    }
    a_que_foreach(a_u32_t, it, ctx)
    {
        A_ASSERT(a_que_get(ctx) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    a_que_foreach_reverse(a_u32_t, it, ctx)
    {
        A_ASSERT(a_que_get(ctx) == sizeof(*it));
        printf("%" PRIu32 " ", *it);
    }
    putchar('\n');
    for (a_u32_t i = 0; i != 5; ++i)
    {
        (void)(a_que_pull_back(a_u32_t, ctx));
    }
    for (a_u32_t i = 0; i != 5; ++i)
    {
        (void)(a_que_pull_fore(a_u32_t, ctx));
    }
    a_que_die(ctx, dtor);
    putchar('\n');
}

#if defined(_MSC_VER)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include <time.h>

static a_int_t cmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return *a_int_P(lhs) - *a_int_P(rhs);
}

static a_int_t cmpr(a_cptr_t lhs, a_cptr_t rhs)
{
    return *a_int_P(rhs) - *a_int_P(lhs);
}

static void test_sort(void)
{
    a_uint_t t = a_uint_c(time(A_NULL));
    a_que_s *ctx = a_que_new(sizeof(a_int_t));

    srand(t);
    a_que_drop(ctx, A_NULL);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_que_push_fore(a_int_t, ctx);
        if (obj)
        {
            *obj = rand() % 10;
            printf("%i ", *obj);
            a_que_sort_fore(ctx, cmp);
        }
    }
    printf("-> ");
    a_que_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    srand(t);
    a_que_drop(ctx, A_NULL);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_int_t *obj = a_que_push_back(a_int_t, ctx);
        if (obj)
        {
            *obj = rand() % 10;
            printf("%i ", *obj);
            a_que_sort_back(ctx, cmpr);
        }
    }
    printf("-> ");
    a_que_foreach(a_int_t, it, ctx)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    a_que_die(ctx, A_NULL);
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", A_FUNC);
    test();
    test_sort();
    return 0;
}

#endif /* TEST_HOST_QUE_H */
