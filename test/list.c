/*!
 @file list.c
 @brief Test circular doubly linked list.
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/list.h"

A_INLINE void a_list_replace_(a_list_s *head1, a_list_s *tail1, a_list_s *head2, a_list_s *tail2)
{
    a_list_add_(tail1->next, head1->prev, head2, tail2);
}
A_INLINE void a_list_replace_node(a_list_s *lold, a_list_s *lnew)
{
    (lold != lnew) ? a_list_replace_(lold, lold, lnew, lnew) : (void)0;
}

A_INLINE void a_list_swap_(a_list_s *head1, a_list_s *tail1, a_list_s *head2, a_list_s *tail2)
{
    a_list_s *head = tail2->next, *tail = head2->prev;
    a_list_add_(tail1->next, head1->prev, head2, tail2);
    a_list_add_(head, tail, head1, tail1);
}
A_INLINE void a_list_swap_node(a_list_s *node1, a_list_s *node2) { a_list_swap_(node1, node1, node2, node2); }

#include <stdlib.h>
#include <stdio.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct list_int_s
{
    a_list_s list[1];
    int data;
} list_int_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

static size_t a_list_len(const a_list_s *ctx)
{
    size_t count = 0;
    if (ctx == 0)
    {
        goto done;
    }
    const a_list_s *ptr;
    if (ctx != ctx->next)
    {
        a_list_foreach_next(ptr, ctx)
        {
            if (ptr == ptr->next)
            {
                printf("\nwarning endless loop!\n");
                break;
            }
            ++count;
        }
    }
    else if (ctx != ctx->prev)
    {
        a_list_foreach_prev(ptr, ctx)
        {
            if (ptr == ptr->prev)
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

static void test_next(void)
{
    a_list_s *list1 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_prev(list1, node->list);
    }
    a_list_rot_prev(list1);
    a_list_s *list2 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list2);
    for (int i = 10; i != 21; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_prev(list2, node->list);
    }
    {
        list_int_s *node = a_list_entry_prev(list2, list_int_s, list);
        a_list_del_prev(list2);
        free(node);
    }
    a_list_mov_prev(list1, list2);
    a_list_init(list2);
    a_list_s *ptr;
    a_list_foreach_next(ptr, list1)
    {
        list_int_s *node = a_list_entry(ptr, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list1));
    a_list_s *pre;
    a_list_forsafe_next(ptr, pre, list1)
    {
        list_int_s *node = a_list_entry(ptr, list_int_s, list);
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

static void test_prev(void)
{
    a_list_s *list1 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_next(list1, node->list);
    }
    a_list_rot_next(list1);
    a_list_s *list2 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list2);
    for (int i = 10; i != 21; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_next(list2, node->list);
    }
    {
        list_int_s *node = a_list_entry_next(list2, list_int_s, list);
        a_list_del_next(list2);
        free(node);
    }
    a_list_mov_next(list1, list2);
    a_list_init(list2);
    a_list_s *ptr;
    a_list_foreach_prev(ptr, list1)
    {
        list_int_s *node = a_list_entry(ptr, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list1));
    a_list_s *pre;
    a_list_forsafe_prev(ptr, pre, list1)
    {
        list_int_s *node = a_list_entry(ptr, list_int_s, list);
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

static void test_func(void)
{
    a_list_s *list1 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_prev(list1, node->list);
    }
    a_list_s *list2 = (a_list_s *)malloc(sizeof(a_list_s));
    a_list_ctor(list2);
    for (int i = 10; i != 20; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_list_add_prev(list2, node->list);
    }
    list_int_s *tmp = (list_int_s *)malloc(sizeof(list_int_s));
    tmp->data = -1;
    a_list_s *ptr = list2->prev;
    a_list_replace_node(list2->prev, tmp->list);
    tmp = a_list_entry(ptr, list_int_s, list);
    a_list_swap_node(list2->prev, list2->next);
    a_list_foreach_next(ptr, list1)
    {
        list_int_s *node = a_list_entry(ptr, list_int_s, list);
        printf("%i ", node->data);
    }
    a_list_foreach_next(ptr, list2)
    {
        list_int_s *node = a_list_entry(ptr, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_list_len(list1) + a_list_len(list2));
    a_list_s *pre;
    a_list_forsafe_next(ptr, pre, list1)
    {
        list_int_s *node = a_list_entry(ptr, list_int_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    a_list_forsafe_next(ptr, pre, list2)
    {
        list_int_s *node = a_list_entry(ptr, list_int_s, list);
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
    free(tmp);
}

static void test_null(void)
{
    a_list_s list1[1] = {{list1, list1}};
    a_list_s list2[1] = {{list2, list2}};
    size_t len = a_list_len(list1) + a_list_len(list2);

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

    a_list_replace_node(list1, list1);
    a_list_replace_node(list2, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }

    a_list_replace_node(list2, list1);
    a_list_init(list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %zu\n", __FILE__, __LINE__, len);
    }
}

int main(void)
{
    test_next();
    test_prev();
    test_func();
    test_null();
    return 0;
}
