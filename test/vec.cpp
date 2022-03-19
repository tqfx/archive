/*!
 @file vec.cpp
 @brief test vector library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_vec.h"
#include "a_vec_util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void test(void)
{
    a_vec_s *ctx = a_vec_new();
    if (a_vec_push(ctx))
    {
        printf("error in line %i!\n", __LINE__);
    }
    if (a_vec_mem(ctx))
    {
        printf("error in line %i!\n", __LINE__);
    }
    if (a_vec_len(ctx))
    {
        printf("error in line %i!\n", __LINE__);
    }
    if (a_vec_pop(ctx))
    {
        printf("error in line %i!\n", __LINE__);
    }
    a_vec_delete(ctx);
}

#undef TEST
#define TEST(name, type)                              \
    static void test_##name(size_t n)                 \
    {                                                 \
        a_vec_##name##_s *ctx = a_vec_##name##_new(); \
        for (size_t i = 0; i != n; ++i)               \
        {                                             \
            type *p = (type *)a_vec_push(ctx);        \
            if (p == 0)                               \
            {                                         \
                printf("%s ", __FUNCTION__);          \
                perror("allocation failure!\n");      \
                exit(EXIT_FAILURE);                   \
            }                                         \
            *(type *)a_vec_ptr(ctx, i) = (type)i;     \
        }                                             \
        for (size_t i = 0; i != n; ++i)               \
        {                                             \
            a_vec_##name##_at(ctx, n - 1 - i);        \
            a_vec_pop(ctx);                           \
        }                                             \
        if (a_vec_len(ctx))                           \
        {                                             \
            printf("error in push or pop!\n");        \
        }                                             \
        a_vec_##name##_delete(ctx);                   \
    }
TEST(i8, int8_t)
TEST(u8, uint8_t)
TEST(i16, int16_t)
TEST(u16, uint16_t)
TEST(i32, int32_t)
TEST(u32, uint32_t)
TEST(i64, int64_t)
TEST(u64, uint64_t)
TEST(f32, float)
TEST(f64, double)
#undef TEST

static void test_str(size_t n)
{
    a_vec_str_s *ctx = a_vec_str_new();
    for (size_t i = 0; i != n; ++i)
    {
        char **str = (char **)a_vec_push(ctx);
        if (str == 0)
        {
            printf("%s ", __FUNCTION__);
            perror("allocation failure!\n");
            exit(EXIT_FAILURE);
        }
        char buf[(sizeof(size_t) << 1) + 3];
        sprintf(buf, "0x%zX", i);
        *str = (char *)malloc(strlen(buf) + 1);
        strcpy(*str, buf);
    }
    for (size_t i = 0; i != (n >> 1); ++i)
    {
        free(*(char **)a_vec_pop(ctx));
    }
    a_vec_str_delete(ctx);
}

int main(void)
{
    test();
#define N 0xFFFF
    test_i8(N);
    test_u8(N);
    test_i16(N);
    test_u16(N);
    test_i32(N);
    test_u32(N);
    test_i64(N);
    test_u64(N);
    test_f32(N);
    test_f64(N);
    test_str(N);
    return 0;
}
