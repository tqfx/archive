/*!
 @file lib.c
 @brief algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/a.h"

a_void_t a_swap(a_size_t siz, a_vptr_t lhs, a_vptr_t rhs)
{
    a_byte_t *l = (a_byte_t *)lhs;
    a_byte_t *r = (a_byte_t *)rhs;
    for (a_byte_t *d = r + siz; r != d; ++l, ++r)
    {
        *l ^= *r;
        *r ^= *l;
        *l ^= *r;
    }
}

a_void_t a_swap1(a_vptr_t lhs, a_vptr_t rhs)
{
    *(a_u8_t *)lhs = *(a_u8_t *)lhs ^ *(a_u8_t *)rhs;
    *(a_u8_t *)rhs = *(a_u8_t *)rhs ^ *(a_u8_t *)lhs;
    *(a_u8_t *)lhs = *(a_u8_t *)lhs ^ *(a_u8_t *)rhs;
}

a_void_t a_swap2(a_vptr_t lhs, a_vptr_t rhs)
{
    *(a_u16_t *)lhs = *(a_u16_t *)lhs ^ *(a_u16_t *)rhs;
    *(a_u16_t *)rhs = *(a_u16_t *)rhs ^ *(a_u16_t *)lhs;
    *(a_u16_t *)lhs = *(a_u16_t *)lhs ^ *(a_u16_t *)rhs;
}

a_void_t a_swap4(a_vptr_t lhs, a_vptr_t rhs)
{
    *(a_u32_t *)lhs = *(a_u32_t *)lhs ^ *(a_u32_t *)rhs;
    *(a_u32_t *)rhs = *(a_u32_t *)rhs ^ *(a_u32_t *)lhs;
    *(a_u32_t *)lhs = *(a_u32_t *)lhs ^ *(a_u32_t *)rhs;
}

a_void_t a_swap8(a_vptr_t lhs, a_vptr_t rhs)
{
    *(a_u64_t *)lhs = *(a_u64_t *)lhs ^ *(a_u64_t *)rhs;
    *(a_u64_t *)rhs = *(a_u64_t *)rhs ^ *(a_u64_t *)lhs;
    *(a_u64_t *)lhs = *(a_u64_t *)lhs ^ *(a_u64_t *)rhs;
}

a_void_t a_swapz(a_vptr_t lhs, a_vptr_t rhs)
{
    *(a_size_t *)lhs = *(a_size_t *)lhs ^ *(a_size_t *)rhs;
    *(a_size_t *)rhs = *(a_size_t *)rhs ^ *(a_size_t *)lhs;
    *(a_size_t *)lhs = *(a_size_t *)lhs ^ *(a_size_t *)rhs;
}

a_size_t a_hash_bkdr(a_cptr_t str, a_size_t val)
{
    if (str)
    {
        for (const a_u8_t *p = (const a_u8_t *)str; *p; ++p)
        {
            val = val * 131 + *p;
        }
    }
    return val;
}

a_size_t a_hash_bkdrn(a_cptr_t ptr, a_size_t siz, a_size_t val)
{
    if (ptr && siz)
    {
        for (const a_u8_t *p = (const a_u8_t *)ptr; siz--; ++p)
        {
            val = val * 131 + *p;
        }
    }
    return val;
}
