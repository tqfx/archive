/*!
 @file test.h
 @brief Test algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef __TEST_H__
#define __TEST_H__

#include <stdio.h>

#define TEST_IS_TRUE(expression, message)             \
    do                                                \
    {                                                 \
        if (!(expression))                            \
        {                                             \
            fprintf(stderr, "%s: file %s, line %i\n", \
                    message, __FILE__, __LINE__);     \
        }                                             \
    } while (0)

#define TEST_IS_FASLE(expression, message)            \
    do                                                \
    {                                                 \
        if (expression)                               \
        {                                             \
            fprintf(stderr, "%s: file %s, line %i\n", \
                    message, __FILE__, __LINE__);     \
        }                                             \
    } while (0)

#define TEST_BUG(expression) TEST_IS_TRUE(expression, "bug")

#endif /* __TEST_H__ */
