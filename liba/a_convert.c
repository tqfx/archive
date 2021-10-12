/*!
 @file           a_convert.c
 @brief          convert library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_convert.h"

void *a_digest(const void *p, size_t n, void *out)
{
    /* assert(!n || p) */
    static const char hexits[] = "0123456789abcdef";
    const unsigned char *s = (const unsigned char *)p;

    if (out || (out = a_alloc((n << 1) + 1), out))
    {
        char *o = (char *)out;
        p = (const void *)(s + n);
        while (s != p)
        {
            *o++ = hexits[*s >> 0x4];
            *o++ = hexits[*s & 0x0F];
            ++s;
        }
        *o = 0;
    }

    return out;
}

/* END OF FILE */
