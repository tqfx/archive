#ifndef TEST_TEST_H
#define TEST_TEST_H

#include <stdio.h>
#include <assert.h>
#include <inttypes.h>

#if !defined static_assert
#if !defined __cplusplus
#define static_assert _Static_assert
#endif /* __cplusplus */
#endif /* static_assert */

#define TEST_IS_TRUE(expression, message)                   \
    do                                                      \
    {                                                       \
        if (!(expression))                                  \
        {                                                   \
            (void)fprintf(stderr, "%s: file %s, line %i\n", \
                          message, __FILE__, __LINE__);     \
        }                                                   \
    } while (0)

#define TEST_IS_FASLE(expression, message)                  \
    do                                                      \
    {                                                       \
        if (expression)                                     \
        {                                                   \
            (void)fprintf(stderr, "%s: file %s, line %i\n", \
                          message, __FILE__, __LINE__);     \
        }                                                   \
    } while (0)

#define TEST_BUG(expression) TEST_IS_TRUE(expression, "bug")

#endif /* TEST_TEST_H */
