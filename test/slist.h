/*!
 @file slist.h
 @brief Test circular singly linked list.
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_SLIST_H__
#define __TEST_SLIST_H__

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Winline"
#endif /* __GNUC__ || __clang__ */

#include "a/slist.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct
{
    a_slist_u list[1];
    a_cast_u data[1];
} a_data_s;

A_STATIC a_size_t a_slist_len(const a_slist_s *ctx)
{
    a_size_t count = 0;
    if (ctx == a_null)
    {
        goto done;
    }
    if (a_slist_used(ctx->head))
    {
        a_slist_foreach(it, ctx)
        {
            if (a_slist_null(it))
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

A_STATIC a_noret_t test(a_noarg_t)
{
    a_slist_s *list1 = a_cast_s(a_slist_s *, malloc(sizeof(a_slist_s)));
    a_slist_ctor(list1);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_slist_add_tail(list1, node->list);
    }
    a_slist_s *list2 = a_cast_s(a_slist_s *, malloc(sizeof(a_slist_s)));
    a_slist_ctor(list2);
    for (a_int_t i = 14; i != 9; --i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_slist_add_head(list2, node->list);
    }
    a_slist_s *list3 = a_cast_s(a_slist_s *, malloc(sizeof(a_slist_s)));
    a_slist_ctor(list3);
    for (a_int_t i = 15; i != 20; ++i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_slist_add(list3, list3->tail, node->list);
    }
    a_slist_rot(list1);
    a_slist_mov(list3, list3->head, list2);
    a_slist_dtor(list2);
    a_slist_mov(list1, list1->tail, list3);
    a_slist_dtor(list3);
    a_slist_foreach(it, list1)
    {
        a_data_s *node = a_slist_entry(it, a_data_s, list);
        printf("%i ", node->data->i);
    }
    printf("%zu", a_slist_len(list1));
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_data_s *node = a_slist_entry_next(list1->head, a_data_s, list);
        a_slist_del_head(list1);
        free(node);
    }
    a_slist_forsafe(it, at, list1)
    {
        a_data_s *node = a_slist_entry(it, a_data_s, list);
        a_slist_del(list1, at);
        free(node);
    }
    if (a_slist_none(list1) && a_slist_none(list2) && a_slist_none(list3))
    {
        printf(" ok");
    }
    putchar('\n');
    free(list3);
    free(list2);
    free(list1);
}

A_STATIC a_noret_t null(a_noarg_t)
{
    a_slist_u node1[1] = {{node1}};
    a_slist_u node2[1] = {{node2}};
    a_slist_s list1[1] = {{{{list1->head}}, list1->head}};
    a_slist_s list2[1] = {{{{list2->head}}, list2->head}};

    a_slist_rot(list1);
    a_slist_rot(list1);
    a_slist_mov(list1, list1->head, list2);
    a_slist_mov(list1, list1->tail, list2);
    a_slist_del(list1, list1->head);
    a_slist_del(list1, list1->tail);
    a_slist_del_head(list2);
    a_slist_del_head(list2);

    a_slist_init(list1);
    a_slist_init(list2);
    a_slist_add(list1, list1->head, node1);
    a_slist_add(list1, list1->head, node1);
    a_slist_del(list1, node1);
    a_slist_add(list1, list1->tail, node1);
    a_slist_add(list1, node1, node1);
    a_slist_add_head(list1, node1);
    a_slist_add_tail(list2, node2);
    a_slist_mov(list1, list1->head, list2);
    a_slist_mov(list1, list1->tail, list2);
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t main_c(a_noarg_t);
a_int_t main_cpp(a_noarg_t);
#if defined(__cplusplus)
} /* extern "C" */
#define test_main main_cpp
#else /* !__cplusplus */
#define test_main main_c
#endif /* __cplusplus */
a_int_t test_main(a_noarg_t)
{
    printf("%s\n", __func__);
    test();
    null();
    return A_SUCCESS;
}

#endif /* __TEST_SLIST_H__ */
