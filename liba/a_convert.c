/*!
 @file           a_convert.c
 @brief          convert library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_convert.h"

char *a_digest(const unsigned char *p, size_t n, char *out)
{
    static const char hexits[] = "0123456789abcdef";

    char *s = out ? out : (out = (char *)a_alloc((n << 1) + 1), out);

    if (s)
    {
        for (size_t i = 0; i != n; ++i)
        {
            *s++ = hexits[p[i] >> 0x4];
            *s++ = hexits[p[i] & 0x0F];
        }
        *s = 0;
    }

    return out;
}

/* END OF FILE */
