/*!
 @file list.cpp
 @brief test circular double-linked list.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_list.h"

#include <stdlib.h>
#include <stdio.h>

#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* _MSC_VER */
typedef struct list_int_s
{
    a_list_s list[1];
    int data;
} list_int_s;
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

static size_t a_list_len(const a_list_s *list)
{
    size_t count = 0;
    const a_list_s *p;
    if (list)
    {
        if (list != list->next)
        {
            a_list_for_next(p, list)
            {
                ++count;
            }
        }
        else if (list != list->last)
        {
            a_list_for_last(p, list)
            {
                ++count;
            }
        }
    }
    return count;
}

static void test_next(void)
{
    a_list_s *list = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_last(list, node->list);
    }
    a_list_rot_last(list);
    a_list_s *list2 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list2);
    for (int i = 10; i != 20; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_last(list2, node->list);
    }
    a_list_s *p;
    a_list_mov_last(list, list2);
    a_list_for_next(p, list)
    {
        list_int_s *node = a_list_entry(p, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list));
    a_list_s *n;
    a_list_forsafe_next(p, n, list)
    {
        list_int_s *node = a_list_entry(p, list_int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    if (a_list_empty(list) && a_list_empty(list2))
    {
        printf(" ok\n");
    }
    free(list);
    free(list2);
}

static void test_last(void)
{
    a_list_s *list = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_next(list, node->list);
    }
    a_list_rot_next(list);
    a_list_s *list2 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list2);
    for (int i = 10; i != 20; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_next(list2, node->list);
    }
    a_list_s *p;
    a_list_mov_next(list, list2);
    a_list_for_last(p, list)
    {
        list_int_s *node = a_list_entry(p, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list));
    a_list_s *n;
    a_list_forsafe_last(p, n, list)
    {
        list_int_s *node = a_list_entry(p, list_int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    if (a_list_empty(list) && a_list_empty(list2))
    {
        printf(" ok\n");
    }
    free(list);
    free(list2);
}

static void test_func(void)
{
    a_list_s *list1 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_last(list1, node->list);
    }
    a_list_s *list2 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list2);
    for (int i = 10; i != 20; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_last(list2, node->list);
    }
    list_int_s *tmp = (list_int_s *)malloc(sizeof(list_int_s));
    tmp->data = -1;
    a_list_s *p = list2->last;
    a_list_replace_node(list2->last, tmp->list);
    tmp = a_list_entry(p, list_int_s, list);
    a_list_swap_node(list2->last, list2->next);
    a_list_for_next(p, list1)
    {
        list_int_s *node = a_list_entry(p, list_int_s, list);
        printf("%i ", node->data);
    }
    a_list_for_next(p, list2)
    {
        list_int_s *node = a_list_entry(p, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list1) + a_list_len(list2));
    a_list_s *n;
    a_list_forsafe_next(p, n, list1)
    {
        list_int_s *node = a_list_entry(p, list_int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    a_list_forsafe_next(p, n, list2)
    {
        list_int_s *node = a_list_entry(p, list_int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    if (a_list_empty(list1) && a_list_empty(list2))
    {
        printf(" ok\n");
    }
    free(tmp);
    free(list1);
    free(list2);
}

static void test_null(void)
{
    A_LIST_HEAD(list1);
    A_LIST_HEAD(list2);
    size_t len = a_list_len(list1) + a_list_len(list2);

    a_list_add_next(list1, list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_add_last(list1, list1);
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

    a_list_add_last(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_del_node(list1);
    a_list_del_node(list1);
    a_list_ctor(list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(list1);
    a_list_rot_last(list1);
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
    a_list_rot_last(list1);
    a_list_rot_last(list1);
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

    a_list_replace_node(list1, list1);
    a_list_replace_node(list2, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_replace_node(list2, list1);
    a_list_ctor(list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }
}

int main(void)
{
    test_next();
    test_last();
    test_func();
    test_null();
    return 0;
}
