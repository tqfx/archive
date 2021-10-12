/*!
 @file           a_convert.c
 @brief          convert library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_convert.h"

char *a_digest(const unsigned char *p, size_t n, void *out)
{
    /* assert(!n || p) */
    static const char hexits[] = "0123456789abcdef";

    if (out || (out = a_alloc((n << 1) + 1), out))
    {
        char *o = (char *)out;
        for (size_t i = 0; i != n; ++i)
        {
            *o++ = hexits[p[i] >> 0x4];
            *o++ = hexits[p[i] & 0x0F];
        }
        *o = 0;
    }

    return (char *)out;
}

/* END OF FILE */
