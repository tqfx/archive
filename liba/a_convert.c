/*!
 @file           a_convert.c
 @brief          convert library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_convert.h"

#include <ctype.h>

int a_xdigit(int x)
{
    int ret = -1;

    switch (x)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    {
        /* 0 ~ 9 */
        ret = x - '0';
    }
    break;

    case 'a':
    case 'b':
    case 'c':
    case 'd':
    case 'e':
    case 'f':
    {
        /* a ~ f */
        ret = x - 'a' + 10;
    }
    break;

    case 'A':
    case 'B':
    case 'C':
    case 'D':
    case 'E':
    case 'F':
    {
        /* A ~ F */
        ret = x - 'A' + 10;
    }
    break;

    default:
        break;
    }

    return ret;
}

void *a_digest(const void *p, size_t n, unsigned int x, void *out)
{
    /* assert(!n || p) */
    static const char hexits[2][0x10] = {
        /* clang-format off */
        {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'a', 'b', 'c', 'd', 'e', 'f',
        },
        {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
        },
        /* clang-format on */
    };

    const char *hexit = hexits[x % 2];
    const unsigned char *s = (const unsigned char *)p;
    if (out || (out = a_alloc((n << 1) + 1), out))
    {
        char *o = (char *)out;
        p = (const void *)(s + n);
        while (s != p)
        {
            *o++ = hexit[*s >> 0x4];
            *o++ = hexit[*s & 0x0F];
            ++s;
        }
        *o = 0;
    }

    return out;
}

void *a_digest_lower(const void *p, size_t n, void *out)
{
    return a_digest(p, n, A_DIGEST_LOWER, out);
}

void *a_digest_upper(const void *p, size_t n, void *out)
{
    return a_digest(p, n, A_DIGEST_UPPER, out);
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
