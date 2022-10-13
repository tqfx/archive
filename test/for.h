#ifndef __TEST_FOR_H__
#define __TEST_FOR_H__

#include "a/a.h"
#include <stdio.h>
#include <stdlib.h>

A_STATIC a_void_t test(a_size_t n)
{
    a_int_t *p = a_cast_s(a_int_t *, malloc(sizeof(a_int_t) * n));
    a_int_t *d = p + n;

    a_forenum(a_size_t, i, n)
    {
        p[i] = a_cast_s(a_int_t, i);
        printf("%zu ", i);
    }
    putchar('\n');
    a_foreach(a_int_t, it, p, n)
    {
        printf("%i ", *it);
    }
    putchar('\n');
    a_iterate(a_int_t, it, p, d)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    a_forenum_reverse(a_size_t, i, n)
    {
        p[i] = a_cast_s(a_int_t, i);
        printf("%zu ", i);
    }
    putchar('\n');
    a_foreach_reverse(a_int_t, it, p, n)
    {
        printf("%i ", *it);
    }
    putchar('\n');
    a_iterate_reverse(a_int_t, it, p, d)
    {
        printf("%i ", *it);
    }
    putchar('\n');

    free(p);
}

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */
a_int_t for_c(void);
a_int_t for_cpp(void);
#if defined(__cplusplus)
} /* extern "C" */
#define func for_cpp
#else /* !__cplusplus */
#define func for_c
#endif /* __cplusplus */
a_int_t func(void)
{
    printf("%s\n", __func__);

    test(10);

    a_str_t a = A_NULL;
    a_foreach(a_char_t, it, a, 0);
    a_foreach_reverse(a_char_t, it, a, 0);

    return A_SUCCESS;
}

#endif /* __TEST_FOR_H__ */
