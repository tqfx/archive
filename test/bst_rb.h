#ifndef TEST_BST_RB_H
#define TEST_BST_RB_H
#define MAIN_(s, argc, argv) main##s(argc, argv)
#include "test.h"
#include "a/bst_rb.h"

typedef struct
{
    a_bst_rb_s node;
    a_int_t data;
    a_int_t reached;
} int_node;

static A_INLINE int_node *int_entry(a_cptr_t node)
{
    return a_bst_rb_entry(node, int_node, node); // NOLINT
}

static a_int_t int_cmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return int_entry(lhs)->data - int_entry(rhs)->data;
}

static a_int_t intcmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return *A_INT_P(lhs) - *A_INT_P(rhs);
}

static int test(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    const a_uint_t n = 0x1000;

    a_bst_rb_u root = A_BST_RB_ROOT;
    int_node *vec = a_new(int_node, A_NULL, n);
    a_int_t *sorted = a_new(a_int_t, A_NULL, n);
    for (a_uint_t i = 0; i < n; ++i)
    {
        a_char_t buff[32];
        (void)snprintf(buff, 32, "%u", i);
        vec[i].data = a_int_c(a_hash_bkdr(buff, 0));
        sorted[i] = vec[i].data;
        a_bst_rb_insert(&root, &vec[i].node, int_cmp);
#if defined(MAIN_ONCE)
        if (i % 0x100 == 0)
        {
            printf("insert 0x%04X/0x%04X\n", i, n);
        }
#endif /* MAIN_ONCE */
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(a_bst_rb_search(&root, &vec[i].node, int_cmp));
    }

    a_uint_t x;
    qsort(sorted, n, sizeof(int), intcmp);

    x = 0;
    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_bst_rb_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        TEST_BUG(it->data == sorted[x]);
        it->reached = 1;
        ++x;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }
    TEST_BUG(x == n);

    x = n;
    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_bst_rb_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        TEST_BUG(it->data == sorted[--x]);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }
    TEST_BUG(x == 0);

    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_bst_rb_pre_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_bst_rb_pre_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_bst_rb_post_foreach(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].reached = 0;
    }
    a_bst_rb_post_foreach_reverse(cur, &root)
    {
        int_node *it = int_entry(cur);
        it->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        a_bst_rb_remove(&root, &vec[i].node);
#if defined(MAIN_ONCE)
        if (i % 0x100 == 0)
        {
            printf("remove 0x%04X/0x%04X\n", i, n);
        }
#endif /* MAIN_ONCE */
    }

    TEST_BUG(a_bst_rb_search(&root, &vec->node, int_cmp) == A_NULL);

    for (a_uint_t i = 0; i < n; ++i)
    {
        a_bst_rb_insert(&root, &vec[i].node, int_cmp);
        vec[i].reached = 0;
    }
    for (a_bst_rb_s *next = A_NULL, *cur = a_bst_rb_tear(&root, &next); cur; cur = a_bst_rb_tear(&root, &next))
    {
        int_entry(cur)->reached = 1;
    }
    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(vec[i].reached);
    }

    sorted = a_die(a_int_t, sorted);
    vec = a_die(int_node, vec);
    return 0;
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s\n", A_FUNC);
    test(argc, argv);
    return 0;
}

#endif /* TEST_BST_RB_H */
