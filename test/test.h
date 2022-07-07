/*!
 @file test.h
 @brief Testing algorithm library
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __A_TEST_H__
#define __A_TEST_H__

#include <stdio.h>

#define TEST_IS_TRUE(expression, message)             \
    do                                                \
    {                                                 \
        if (!(expression))                            \
        {                                             \
            fprintf(stderr, "%s: file %s, line %u\n", \
                    message, __FILE__, __LINE__);     \
        }                                             \
    } while (0)

#define TEST_IS_FASLE(expression, message)            \
    do                                                \
    {                                                 \
        if (expression)                               \
        {                                             \
            fprintf(stderr, "%s: file %s, line %u\n", \
                    message, __FILE__, __LINE__);     \
        }                                             \
    } while (0)

#define TEST_BUG(expression) TEST_IS_TRUE(expression, "bug")

#endif /* __A_TEST_H__ */
