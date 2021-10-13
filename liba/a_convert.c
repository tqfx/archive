/*!
 @file           a_convert.c
 @brief          convert library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_convert.h"

#include <ctype.h>

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

void *a_lower(const void *p, size_t n, void *out)
{
    /* assert(!n || p) */
    const char *s = (const char *)p;

    if (out || (out = a_alloc(n + 1), out))
    {
        char *o = (char *)out;
        p = (const void *)(s + n);
        while (s != p)
        {
            *o++ = (char)tolower(*s++);
        }
        *o = 0;
    }

    return out;
}

void *a_upper(const void *p, size_t n, void *out)
{
    /* assert(!n || p) */
    const char *s = (const char *)p;

    if (out || (out = a_alloc(n + 1), out))
    {
        char *o = (char *)out;
        p = (const void *)(s + n);
        while (s != p)
        {
            *o++ = (char)toupper(*s++);
        }
        *o = 0;
    }

    return out;
}

/* END OF FILE */
