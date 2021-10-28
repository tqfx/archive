/*!
 @file           a_convert.c
 @brief          convert library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_convert.h"

#include <ctype.h>

int a_xdigit(int _x)
{
    int ret = -1;

    switch (_x)
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
        ret = _x - '0';
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
        ret = _x - 'a' + 10;
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
        ret = _x - 'A' + 10;
    }
    break;

    default:
        break;
    }

    return ret;
}

#undef __A_TO
#define __A_TO(_func, _tofunc)                       \
    void *_func(const void *_p, size_t _n, void *_o) \
    {                                                \
        a_assert(!_n || _p);                         \
        const char *p = (const char *)_p;            \
        if (_o || (_o = a_alloc(_n + 1), _o))        \
        {                                            \
            char *o = (char *)_o;                    \
            _p = (const void *)(p + _n);             \
            while (p != _p)                          \
            {                                        \
                *o++ = (char)_tofunc(*p++);          \
            }                                        \
            *o = 0;                                  \
        }                                            \
        return _o;                                   \
    }
__A_TO(a_lower, tolower)
__A_TO(a_upper, toupper)
#undef __A_TO

void *a_digest(const void *_p, size_t _n, unsigned int _x, void *_o)
{
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

    a_assert(!_n || _p);

    const char *hexit = hexits[_x % 2];
    const unsigned char *p = (const unsigned char *)_p;
    if (_o || (_o = a_alloc((_n << 1) + 1), _o))
    {
        char *o = (char *)_o;
        _p = (const void *)(p + _n);
        while (p != _p)
        {
            *o++ = hexit[*p >> 0x4];
            *o++ = hexit[*p & 0x0F];
            ++p;
        }
        *o = 0;
    }

    return _o;
}

void *a_digest_lower(const void *_p, size_t _n, void *_o)
{
    return a_digest(_p, _n, A_DIGEST_LOWER, _o);
}

void *a_digest_upper(const void *_p, size_t _n, void *_o)
{
    return a_digest(_p, _n, A_DIGEST_UPPER, _o);
}

/* END OF FILE */
