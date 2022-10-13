/*!
 @file crc.c
 @brief Cyclic Redundancy Check
 @details https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/crc.h"

a_void_t a_crc8l_init(a_u8_t ctx[0x100], a_u8_t poly)
{
    for (a_uint_t i = 0; i != 0x100; ++i)
    {
        a_u8_t val = (a_u8_t)i;
        for (a_uint_t j = 8; j; --j)
        {
            if (val & 1)
            {
                val >>= 1;
                val ^= poly;
            }
            else
            {
                val >>= 1;
            }
        }
        ctx[i] = val;
    }
}

a_void_t a_crc16l_init(a_u16_t ctx[0x100], a_u16_t poly)
{
    for (a_uint_t i = 0; i != 0x100; ++i)
    {
        a_u16_t val = (a_u16_t)i;
        for (a_uint_t j = 8; j; --j)
        {
            if (val & 1)
            {
                val >>= 1;
                val ^= poly;
            }
            else
            {
                val >>= 1;
            }
        }
        ctx[i] = val;
    }
}

a_void_t a_crc32l_init(a_u32_t ctx[0x100], a_u32_t poly)
{
    for (a_uint_t i = 0; i != 0x100; ++i)
    {
        a_u32_t val = i;
        for (a_uint_t j = 8; j; --j)
        {
            if (val & 1)
            {
                val >>= 1;
                val ^= poly;
            }
            else
            {
                val >>= 1;
            }
        }
        ctx[i] = val;
    }
}

a_void_t a_crc64l_init(a_u64_t ctx[0x100], a_u64_t poly)
{
    for (a_uint_t i = 0; i != 0x100; ++i)
    {
        a_u64_t val = i;
        for (a_uint_t j = 8; j; --j)
        {
            if (val & 1)
            {
                val >>= 1;
                val ^= poly;
            }
            else
            {
                val >>= 1;
            }
        }
        ctx[i] = val;
    }
}

a_void_t a_crc8h_init(a_u8_t ctx[0x100], a_u8_t poly)
{
    for (a_uint_t i = 0; i != 0x100; ++i)
    {
        a_uint_t val = i;
        for (a_uint_t j = 8; j; --j)
        {
            if (A_U8_C(0x80) & val)
            {
                val <<= 1;
                val ^= poly;
            }
            else
            {
                val <<= 1;
            }
        }
        ctx[i] = (a_u8_t)val;
    }
}

a_void_t a_crc16h_init(a_u16_t ctx[0x100], a_u16_t poly)
{
    for (a_u16_t i = 0; i != 0x100; ++i)
    {
        a_u16_t val = (a_u16_t)(i << 8);
        for (a_uint_t j = 8; j; --j)
        {
            if (A_U16_C(0x8000) & val)
            {
                val <<= 1;
                val ^= poly;
            }
            else
            {
                val <<= 1;
            }
        }
        ctx[i] = val;
    }
}

a_void_t a_crc32h_init(a_u32_t ctx[0x100], a_u32_t poly)
{
    for (a_u32_t i = 0; i != 0x100; ++i)
    {
        a_u32_t val = i << 24;
        for (a_uint_t j = 8; j; --j)
        {
            if (A_U32_C(0x80000000) & val)
            {
                val <<= 1;
                val ^= poly;
            }
            else
            {
                val <<= 1;
            }
        }
        ctx[i] = val;
    }
}

a_void_t a_crc64h_init(a_u64_t ctx[0x100], a_u64_t poly)
{
    for (a_u64_t i = 0; i != 0x100; ++i)
    {
        a_u64_t val = i << 56;
        for (a_uint_t j = 8; j; --j)
        {
            if (A_U64_C(0x8000000000000000) & val)
            {
                val <<= 1;
                val ^= poly;
            }
            else
            {
                val <<= 1;
            }
        }
        ctx[i] = val;
    }
}

a_u8_t a_crc8(const a_u8_t ctx[0x100], a_cptr_t pdata, a_size_t nbyte, a_u8_t val)
{
    const a_u8_t *p = (const a_u8_t *)pdata;
    const a_u8_t *q = (const a_u8_t *)pdata + nbyte;
    while (p != q)
    {
        val = ctx[val ^ *p++];
    }
    return val;
}

a_u16_t a_crc16l(const a_u16_t ctx[0x100], a_cptr_t pdata, a_size_t nbyte, a_u16_t val)
{
    const a_u8_t *p = (const a_u8_t *)pdata;
    const a_u8_t *q = (const a_u8_t *)pdata + nbyte;
    while (p != q)
    {
        val = (val >> 8) ^ ctx[(val ^ *p++) & 0xFF];
    }
    return val;
}

a_u32_t a_crc32l(const a_u32_t ctx[0x100], a_cptr_t pdata, a_size_t nbyte, a_u32_t val)
{
    const a_u8_t *p = (const a_u8_t *)pdata;
    const a_u8_t *q = (const a_u8_t *)pdata + nbyte;
    while (p != q)
    {
        val = (val >> 8) ^ ctx[(val ^ *p++) & 0xFF];
    }
    return val;
}

a_u64_t a_crc64l(const a_u64_t ctx[0x100], a_cptr_t pdata, a_size_t nbyte, a_u64_t val)
{
    const a_u8_t *p = (const a_u8_t *)pdata;
    const a_u8_t *q = (const a_u8_t *)pdata + nbyte;
    while (p != q)
    {
        val = (val >> 8) ^ ctx[(val ^ *p++) & 0xFF];
    }
    return val;
}

a_u16_t a_crc16h(const a_u16_t ctx[0x100], a_cptr_t pdata, a_size_t nbyte, a_u16_t val)
{
    const a_u8_t *p = (const a_u8_t *)pdata;
    const a_u8_t *q = (const a_u8_t *)pdata + nbyte;
    while (p != q)
    {
        val = (a_u16_t)((val << 8) ^ ctx[((val >> 8) ^ *p++) & 0xFF]);
    }
    return val;
}

a_u32_t a_crc32h(const a_u32_t ctx[0x100], a_cptr_t pdata, a_size_t nbyte, a_u32_t val)
{
    const a_u8_t *p = (const a_u8_t *)pdata;
    const a_u8_t *q = (const a_u8_t *)pdata + nbyte;
    while (p != q)
    {
        val = (val << 8) ^ ctx[((val >> 24) ^ *p++) & 0xFF];
    }
    return val;
}

a_u64_t a_crc64h(const a_u64_t ctx[0x100], a_cptr_t pdata, a_size_t nbyte, a_u64_t val)
{
    const a_u8_t *p = (const a_u8_t *)pdata;
    const a_u8_t *q = (const a_u8_t *)pdata + nbyte;
    while (p != q)
    {
        val = (val << 8) ^ ctx[((val >> 56) ^ *p++) & 0xFF];
    }
    return val;
}
