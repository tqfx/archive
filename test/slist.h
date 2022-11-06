#ifndef TEST_SLIST_H
#define TEST_SLIST_H
#define MAIN_(s, argc, argv) slist##s(argc, argv)
#include "test.h"
#if a_prereq_gnuc(2, 95) || __has_warning("-Winline")
#pragma GCC diagnostic ignored "-Winline"
#endif /* -Winline */
#if a_prereq_gnuc(2, 95) || __has_warning("-Wpadded")
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* -Wpadded */
#if defined(_MSC_VER)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include "a/slist.h"
#include <stdlib.h>

typedef struct
{
    a_slist_u list[1];
    a_cast_u data[1];
} a_data_s;

static a_size_t a_slist_len(const a_slist_s *ctx)
{
    a_size_t count = 0;
    if (ctx == A_NULL)
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

static void test(void)
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
        it = A_NULL;
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
    a_slist_u node1[1];
    a_slist_u node2[1];
    a_slist_s list1[1];
    a_slist_s list2[1];
    a_slist_node(node1);
    a_slist_node(node2);
    a_slist_ctor(list1);
    a_slist_ctor(list2);

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

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", __func__);
    test();
    null();
    return 0;
}

#endif /* TEST_SLIST_H */
