/*!
 @file list.h
 @brief Test circular doubly linked list.
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_LIST_H__
#define __TEST_LIST_H__

#include "a/list.h"

#include <stdlib.h>
#include <stdio.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Winline"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct int_s
{
    a_list_s list[1];
    a_int_t data;
} int_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

static a_size_t a_list_len(const a_list_s *ctx)
{
    a_size_t count = 0;
    if (ctx == a_null)
    {
        goto done;
    }
    if (ctx != ctx->next)
    {
        a_list_foreach_next(it, ctx)
        {
            if (it == it->next)
            {
                printf("\nwarning endless loop!\n");
                break;
            }
            ++count;
        }
    }
    else if (ctx != ctx->prev)
    {
        a_list_foreach_prev(it, ctx)
        {
            if (it == it->prev)
            {
                printf("\nwarning endless loop!\n");
                break;
            }
            ++count;
        }
    }
done:
    return count;
}

static a_noret_t test_next(a_noarg_t)
{
    a_list_s *list1 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list1);
    for (a_int_t i = 0; i != 10; ++i)
    {
        int_s *node = a_cast_s(int_s *, malloc(sizeof(int_s)));
        node->data = i;
        a_list_add_prev(list1, node->list);
    }
    a_list_rot_prev(list1);
    a_list_s *list2 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list2);
    for (a_int_t i = 10; i != 21; ++i)
    {
        int_s *node = a_cast_s(int_s *, malloc(sizeof(int_s)));
        node->data = i;
        a_list_add_prev(list2, node->list);
    }
    {
        int_s *node = a_list_entry_prev(list2, int_s, list);
        a_list_del_prev(list2);
        free(node);
    }
    a_list_mov_prev(list1, list2);
    a_list_init(list2);
    a_list_foreach_next(it, list1)
    {
        int_s *node = a_list_entry(it, int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list1));
    a_list_forsafe_next(it, pre, list1)
    {
        int_s *node = a_list_entry(it, int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    if (a_list_null(list1) && a_list_null(list2))
    {
        printf(" ok");
    }
    putchar('\n');
    free(list1);
    free(list2);
}

static a_noret_t test_prev(a_noarg_t)
{
    a_list_s *list1 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list1);
    for (a_int_t i = 0; i != 10; ++i)
    {
        int_s *node = a_cast_s(int_s *, malloc(sizeof(int_s)));
        node->data = i;
        a_list_add_next(list1, node->list);
    }
    a_list_rot_next(list1);
    a_list_s *list2 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list2);
    for (a_int_t i = 10; i != 21; ++i)
    {
        int_s *node = a_cast_s(int_s *, malloc(sizeof(int_s)));
        node->data = i;
        a_list_add_next(list2, node->list);
    }
    {
        int_s *node = a_list_entry_next(list2, int_s, list);
        a_list_del_next(list2);
        free(node);
    }
    a_list_mov_next(list1, list2);
    a_list_init(list2);
    a_list_foreach_prev(it, list1)
    {
        int_s *node = a_list_entry(it, int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list1));
    a_list_forsafe_prev(it, pre, list1)
    {
        int_s *node = a_list_entry(it, int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    if (a_list_null(list1) && a_list_null(list2))
    {
        printf(" ok");
    }
    putchar('\n');
    free(list1);
    free(list2);
}

static a_noret_t test_func(a_noarg_t)
{
    a_list_s *list1 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list1);
    for (a_int_t i = 0; i != 10; ++i)
    {
        int_s *node = a_cast_s(int_s *, malloc(sizeof(int_s)));
        node->data = i;
        a_list_add_prev(list1, node->list);
    }
    a_list_s *list2 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list2);
    for (a_int_t i = 10; i != 20; ++i)
    {
        int_s *node = a_cast_s(int_s *, malloc(sizeof(int_s)));
        node->data = i;
        a_list_add_prev(list2, node->list);
    }
    int_s *ctx = a_cast_s(int_s *, malloc(sizeof(int_s)));
    ctx->data = -1;
    {
        a_list_s *ptr = list2->prev;
        a_list_shift_node(list2->prev, ctx->list);
        ctx = a_list_entry(ptr, int_s, list);
    }
    a_list_swap_node(list2->prev, list2->next);
    a_list_foreach_next(it, list1)
    {
        int_s *node = a_list_entry(it, int_s, list);
        printf("%i ", node->data);
    }
    a_list_foreach_next(it, list2)
    {
        int_s *node = a_list_entry(it, int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list1) + a_list_len(list2));
    a_list_forsafe_next(it, at, list1)
    {
        int_s *node = a_list_entry(it, int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    a_list_forsafe_next(it, at, list2)
    {
        int_s *node = a_list_entry(it, int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    if (a_list_null(list1) && a_list_null(list2))
    {
        printf(" ok");
    }
    putchar('\n');
    free(list1);
    free(list2);
    free(ctx);
}

static a_noret_t test_null(a_noarg_t)
{
    a_list_s list1[1] = {{list1, list1}};
    a_list_s list2[1] = {{list2, list2}};
    a_size_t len = a_list_len(list1) + a_list_len(list2);

    a_list_add_next(list1, list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_add_prev(list1, list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_add_next(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_add_prev(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_del_node(list1);
    a_list_del_node(list1);
    a_list_del_next(list1);
    a_list_del_prev(list1);
    a_list_ctor(list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(list1);
    a_list_rot_prev(list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_link(list1, list2);
    a_list_loop(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(list1);
    a_list_rot_prev(list1);
    a_list_rot_prev(list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(list1, list1);
    a_list_swap_node(list2, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(list2, list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_shift_node(list1, list1);
    a_list_shift_node(list2, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_shift_node(list2, list1);
    a_list_init(list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t main_c(a_noarg_t);
a_int_t main_cc(a_noarg_t);
#if defined(__cplusplus)
} /* extern "C" */
#define test_main main_cc
#else /* #__cplusplus */
#define test_main main_c
#endif /* __cplusplus */
a_int_t test_main(a_noarg_t)
{
    printf("%s\n", __func__);
    test_next();
    test_prev();
    test_func();
    test_null();
    return A_SUCCESS;
}

#endif /* __TEST_LIST_H__ */
