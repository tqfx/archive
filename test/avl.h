#ifndef TEST_AVL_H
#define TEST_AVL_H
#define MAIN_(s, argc, argv) main##s(argc, argv)
#include "test.h"
#include "a/avl.h"
#include <time.h>

typedef struct
{
    a_avl_s node;
    a_int_t data;
} intmap;

static a_int_t intcmp(a_cptr_t lhs, a_cptr_t rhs)
{
    return a_container_of(lhs, intmap, node)->data - // NOLINT
           a_container_of(rhs, intmap, node)->data; // NOLINT
}

static int test(int argc, char *argv[])
{
    (void)(argc);
    (void)(argv);

    const a_uint_t n = 0xFFFF;

    a_avl_u root = {A_NULL};
    intmap *vec = a_new(intmap, A_NULL, n);
    srand(a_uint_c(time(A_NULL))); // NOLINT
    for (a_uint_t i = 0; i < n; ++i)
    {
        vec[i].data = rand(); // NOLINT
        a_avl_insert(&root, &vec[i].node, intcmp);
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        TEST_BUG(a_avl_search(&root, &vec[i].node, intcmp));
    }

    for (a_uint_t i = 0; i < n; ++i)
    {
        a_avl_remove(&root, &vec[i].node);
    }

    TEST_BUG(a_avl_search(&root, &vec->node, intcmp) == A_NULL);

    vec = a_die(intmap, vec);
    return 0;
}

int MAIN(int argc, char *argv[]) // NOLINT(misc-definitions-in-headers)
{
    printf("%s\n", A_FUNC);
    test(argc, argv);
    return 0;
}

#endif /* TEST_AVL_H */
