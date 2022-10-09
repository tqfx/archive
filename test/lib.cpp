/*!
 @file lib.cpp
 @brief Test algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/a.h"
#include "test.h"
#include <inttypes.h>

A_STATIC a_void_t test_swap(void)
{
    {
        a_i8_t lhs = A_I8_MIN;
        a_i8_t rhs = A_I8_MAX;
        printf("%+" PRIi8 " %+" PRIi8 " -> ", lhs, rhs);
        a_swap1(&lhs, &rhs);
        printf("%+" PRIi8 " %+" PRIi8 "  \n", lhs, rhs);
    }
    {
        a_i16_t lhs = A_I16_MIN;
        a_i16_t rhs = A_I16_MAX;
        printf("%+" PRIi16 " %+" PRIi16 " -> ", lhs, rhs);
        a_swap2(&lhs, &rhs);
        printf("%+" PRIi16 " %+" PRIi16 "  \n", lhs, rhs);
    }
    {
        a_i32_t lhs = A_I32_MIN;
        a_i32_t rhs = A_I32_MAX;
        printf("%+" PRIi32 " %+" PRIi32 " -> ", lhs, rhs);
        a_swap4(&lhs, &rhs);
        printf("%+" PRIi32 " %+" PRIi32 "  \n", lhs, rhs);
    }
    {
        a_i64_t lhs = A_I64_MIN;
        a_i64_t rhs = A_I64_MAX;
        printf("%+" PRIi64 " %+" PRIi64 " -> ", lhs, rhs);
        a_swap8(&lhs, &rhs);
        printf("%+" PRIi64 " %+" PRIi64 "  \n", lhs, rhs);
    }
    {
        a_size_t lhs = 0;
        a_size_t rhs = A_SIZE_MAX;
        printf("%zu %zu -> ", lhs, rhs);
        a_swapz(&lhs, &rhs);
        printf("%zu %zu  \n", lhs, rhs);
    }
}

int main(void)
{
    test_swap();
    return A_SUCCESS;
}
