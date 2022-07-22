/*!
 @file slist.c
 @brief Test circular singly linked list.
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/slist.h"

#include <stdlib.h>
#include <stdio.h>

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
typedef struct list_int_s
{
    a_slist_u list[1];
    int data;
} list_int_s;
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

static size_t a_slist_len(const a_slist_s *ctx)
{
    size_t count = 0;
    if (ctx == 0)
    {
        goto done;
    }
    const a_slist_u *ptr;
    if (ctx->head->next != ctx->head)
    {
        a_slist_foreach(ptr, ctx)
        {
            if (a_slist_null(ptr))
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

static void test(void)
{
    a_slist_s *list1 = (a_slist_s *)malloc(sizeof(a_slist_s));
    a_slist_ctor(list1);
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_slist_add_tail(list1, node->list);
    }
    a_slist_s *list2 = (a_slist_s *)malloc(sizeof(a_slist_s));
    a_slist_ctor(list2);
    for (int i = 14; i != 9; --i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_slist_add_head(list2, node->list);
    }
    a_slist_s *list3 = (a_slist_s *)malloc(sizeof(a_slist_s));
    a_slist_ctor(list3);
    for (int i = 15; i != 20; ++i)
    {
        list_int_s *node = (list_int_s *)malloc(sizeof(list_int_s));
        node->data = i;
        a_slist_add(list3, list3->tail, node->list);
    }
    a_slist_rot(list1);
    a_slist_mov(list3, list3->head, list2);
    a_slist_dtor(list2);
    a_slist_mov(list1, list1->tail, list3);
    a_slist_dtor(list3);
    a_slist_u *ptr;
    a_slist_foreach(ptr, list1)
    {
        list_int_s *node = a_slist_entry(ptr, list_int_s, list);
        printf("%i ", node->data);
    }
    printf("%zu", a_slist_len(list1));
    for (int i = 0; i != 10; ++i)
    {
        list_int_s *node = a_slist_entry_next(list1->head, list_int_s, list);
        a_slist_del_head(list1);
        free(node);
    }
    a_slist_u *pre;
    a_slist_forsafe(ptr, pre, list1)
    {
        list_int_s *node = a_slist_entry(ptr, list_int_s, list);
        a_slist_del(list1, pre);
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

static void null(void)
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

int main(void)
{
    test();
    null();
    return 0;
}
