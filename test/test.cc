/*!
 @file test.c
 @brief Test algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/a.h"
#include "test.h"

#include <inttypes.h>

static a_noret_t test_swap(a_noarg_t)
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
    {
        typedef struct a_16_s
        {
            a_byte_t m0;
            a_byte_t m1;
            a_byte_t m2;
            a_byte_t m3;
            a_byte_t m4;
            a_byte_t m5;
            a_byte_t m6;
            a_byte_t m7;
            a_byte_t m8;
            a_byte_t m9;
            a_byte_t ma;
            a_byte_t mb;
            a_byte_t mc;
            a_byte_t md;
            a_byte_t me;
            a_byte_t mf;
        } a_16_s;
        a_16_s lhs{0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF};
        a_16_s rhs{0xF, 0xE, 0xD, 0xC, 0xB, 0xA, 0x9, 0x8, 0x7, 0x6, 0x5, 0x4, 0x3, 0x2, 0x1, 0x0};
        printf("%X %X %X %X -> ", lhs.m0, rhs.m0, lhs.mf, rhs.mf);
        a_swap(sizeof(a_16_s), &lhs, &rhs);
        printf("%X %X %X %X -> ", lhs.m0, rhs.m0, lhs.mf, rhs.mf);
        a_swap16(&lhs, &rhs);
        printf("%X %X %X %X  \n", lhs.m0, rhs.m0, lhs.mf, rhs.mf);
    }
}

a_int_t main(a_noarg_t)
{
    test_swap();
    return A_SUCCESS;
}
