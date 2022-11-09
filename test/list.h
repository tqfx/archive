#ifndef TEST_LIST_H
#define TEST_LIST_H
#define MAIN_(s, argc, argv) list##s(argc, argv)
#include "test.h"
#if a_prereq_gnuc(2, 95) || __has_warning("-Winline")
#pragma GCC diagnostic ignored "-Winline"
#endif /* -Winline */
#include "a/list.h"
#include <stdlib.h>

typedef struct
{
    a_list_s list[1];
    a_cast_u data[1];
} a_data_s;

static a_size_t a_list_len(const a_list_s *ctx)
{
    a_size_t count = 0;
    if (ctx == A_NULL)
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

static void test_next(void)
{
    a_list_s *list1 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list1);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_list_add_prev(list1, node->list);
    }
    a_list_rot_prev(list1);
    a_list_s *list2 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list2);
    for (a_int_t i = 10; i != 21; ++i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_list_add_prev(list2, node->list);
    }
    {
        a_data_s *node = a_list_entry_prev(list2, a_data_s, list);
        a_list_del_prev(list2);
        free(node);
    }
    a_list_mov_prev(list1, list2);
    a_list_init(list2);
    a_list_foreach_next(it, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        printf("%i ", node->data->i);
    }
    printf("%" PRIzu, a_list_len(list1));
    a_list_forsafe_next(it, pre, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
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
    a_list_s *list1 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list1);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_list_add_next(list1, node->list);
    }
    a_list_rot_next(list1);
    a_list_s *list2 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list2);
    for (a_int_t i = 10; i != 21; ++i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_list_add_next(list2, node->list);
    }
    {
        a_data_s *node = a_list_entry_next(list2, a_data_s, list);
        a_list_del_next(list2);
        free(node);
    }
    a_list_mov_next(list1, list2);
    a_list_init(list2);
    a_list_foreach_prev(it, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        printf("%i ", node->data->i);
    }
    printf("%" PRIzu, a_list_len(list1));
    a_list_forsafe_prev(it, pre, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
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
    a_list_s *list1 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list1);
    for (a_int_t i = 0; i != 10; ++i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_list_add_prev(list1, node->list);
    }
    a_list_s *list2 = a_cast_s(a_list_s *, malloc(sizeof(a_list_s)));
    a_list_ctor(list2);
    for (a_int_t i = 10; i != 20; ++i)
    {
        a_data_s *node = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
        node->data->i = i;
        a_list_add_prev(list2, node->list);
    }
    a_data_s *ctx = a_cast_s(a_data_s *, malloc(sizeof(a_data_s)));
    ctx->data->i = -1;
    {
        a_list_s *ptr = list2->prev;
        a_list_shift_node(list2->prev, ctx->list);
        ctx = a_list_entry(ptr, a_data_s, list);
    }
    a_list_swap_node(list2->prev, list2->next);
    a_list_foreach_next(it, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        printf("%i ", node->data->i);
    }
    a_list_foreach_next(it, list2)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        printf("%i ", node->data->i);
    }
    printf("%" PRIzu, a_list_len(list1) + a_list_len(list2));
    a_list_forsafe_next(it, at, list1)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
        a_list_del_node(node->list);
        free(node);
    }
    a_list_forsafe_next(it, at, list2)
    {
        a_data_s *node = a_list_entry(it, a_data_s, list);
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

static void test_null(void)
{
    a_list_s list1[1];
    a_list_s list2[1];
    a_list_ctor(list1);
    a_list_ctor(list2);
    a_size_t len = a_list_len(list1) + a_list_len(list2);

    a_list_add_next(list1, list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_add_prev(list1, list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_add_next(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_add_prev(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_del_node(list1);
    a_list_del_node(list1);
    a_list_del_next(list1);
    a_list_del_prev(list1);
    a_list_ctor(list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(list1);
    a_list_rot_prev(list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_link(list1, list2);
    a_list_loop(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_rot_next(list1);
    a_list_rot_prev(list1);
    a_list_rot_prev(list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(list1, list1);
    a_list_swap_node(list2, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(list1, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_swap_node(list2, list1);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_shift_node(list1, list1);
    a_list_shift_node(list2, list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 2)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }

    a_list_shift_node(list2, list1);
    a_list_init(list2);
    len = a_list_len(list1) + a_list_len(list2);
    if (len != 0)
    {
        printf("failure in %s %i %" PRIzu "\n", __FILE__, __LINE__, len);
    }
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    (void)(argc);
    (void)(argv);
    printf("%s\n", __FUNCTION__);
    test_next();
    test_prev();
    test_func();
    test_null();
    return 0;
}

#endif /* TEST_LIST_H */
