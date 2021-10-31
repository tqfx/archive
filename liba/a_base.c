/*!
 @file a_base.c
 @brief RFC 4648 compliant Base implementation
 @details https://www.ietf.org/rfc/rfc4648.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_base.h"

int a_base16_encode(const void *_p, size_t _n, void *_out, size_t *_siz, unsigned int _id)
{
    static const char *alphabets[A_BASE16_ALL] = {
        "0123456789abcdef",
        "0123456789ABCDEF",
    };

    aassert(_out);
    aassert(_siz);
    aassert(!_n || _p);

    /* check the sizes */
    size_t x = (_n << 1) + 1;

    if (x < _n)
    {
        return A_BASE_OVERFLOW;
    }

    if (*_siz < x)
    {
        *_siz = x;
        return A_BASE_OVERFLOW;
    }
    *_siz = --x; /* returning the length without terminating NUL */

    char *out = (char *)_out;
    const char *map = alphabets[_id % A_BASE16_ALL];
    const unsigned char *p = (const unsigned char *)_p;
    for (size_t i = 0; i != x; i += 2)
    {
        size_t t = i >> 1;
        out[i + 0] = map[(p[t] >> 4) & 0x0F];
        out[i + 1] = map[(p[t] >> 0) & 0x0F];
    }
    out[x] = 0;

    return A_BASE_SUCCESS;
}

int a_base16_decode(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    static const unsigned char hashmap[] = {
        /* clang-format off */
         0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, /* 01234567 */
         0x08, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, /* 89:;<=>? */
         0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, /* @ABCDEFG */
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, /* HIJKLMNO */
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, /* PQRSTUVW */
         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, /* XYZ[\]^_ */
         0xFF, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0xFF, /* `abcdefg */
        /* clang-format on */
    };

    aassert(_out);
    aassert(_siz);
    aassert(!_n || _p);

    if (_n % 2)
    {
        return A_BASE_INVALID;
    }

    size_t idx = 0;
    size_t x = *_siz << 1;
    const char *p = (const char *)_p;
    unsigned char *out = (unsigned char *)_out;
    while ((idx + 1 < x) && (idx + 1 < _n))
    {
        char c0 = p[idx + 0];
        char c1 = p[idx + 1];

        if ((c0 < '0') || (c0 > 'g') || (c1 < '0') || (c1 > 'g'))
        {
            return A_BASE_INVALID;
        }

        unsigned char idx0 = (unsigned char)((c0 & 0x1F) ^ 0x10);
        unsigned char idx1 = (unsigned char)((c1 & 0x1F) ^ 0x10);

        if ((hashmap[idx0] == 0xFF) || (hashmap[idx1] == 0xFF))
        {
            return A_BASE_INVALID;
        }

        out[idx >> 1] = (unsigned char)((hashmap[idx0] << 4) | hashmap[idx1]);
        idx += 2;
    }
    *_siz = idx >> 1;

    return A_BASE_SUCCESS;
}

int a_base32_encode(const void *_p, size_t _n, void *_out, size_t *_siz, unsigned int _id)
{
    static const char *alphabet[A_BASE32_ALL] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567", /* id = RFC4648   */
        "0123456789ABCDEFGHIJKLMNOPQRSTUV", /* id = BASE32HEX */
        "ybndrfg8ejkmcpqxot1uwisza345h769", /* id = ZBASE32   */
        "0123456789ABCDEFGHJKMNPQRSTVWXYZ"  /* id = CROCKFORD */
    };

    aassert(_out);
    aassert(_siz);
    aassert(!_n || _p);

    /* check the size of output buffer +1 byte for terminating NUL */
    size_t x = ((_n << 3) + 4) / 5 + 1;

    if (*_siz < x)
    {
        *_siz = x;
        return A_BASE_OVERFLOW;
    }
    *_siz = --x; /* returning the length without terminating NUL */
    x = 5 * (_n / 5);

    char *out = (char *)_out;
    /* no input, nothing to do */
    if (_n == 0)
    {
        *out = 0;
        return A_BASE_SUCCESS;
    }

    size_t i = 0;
    const char *codes = alphabet[_id % A_BASE32_ALL];
    const unsigned char *p = (const unsigned char *)_p;
    while (i != x)
    {
        *out++ = codes[(p[0] >> 3) & 0x1F];
        *out++ = codes[(((p[0] & 0x7) << 2) + (p[1] >> 6)) & 0x1F];
        *out++ = codes[(p[1] >> 1) & 0x1F];
        *out++ = codes[(((p[1] & 0x1) << 4) + (p[2] >> 4)) & 0x1F];
        *out++ = codes[(((p[2] & 0xF) << 1) + (p[3] >> 7)) & 0x1F];
        *out++ = codes[(p[3] >> 2) & 0x1F];
        *out++ = codes[(((p[3] & 0x3) << 3) + (p[4] >> 5)) & 0x1F];
        *out++ = codes[p[4] & 0x1F];
        p += 5;
        i += 5;
    }
    if (i < _n)
    {
        unsigned int a = p[0];
        unsigned int b = (i + 1 < _n) ? p[1] : 0;
        unsigned int c = (i + 2 < _n) ? p[2] : 0;
        unsigned int d = (i + 3 < _n) ? p[3] : 0;
        *out++ = codes[(a >> 3) & 0x1F];
        *out++ = codes[(((a & 0x7) << 2) + (b >> 6)) & 0x1F];
        if (i + 1 < _n)
        {
            *out++ = codes[(b >> 1) & 0x1F];
            *out++ = codes[(((b & 0x1) << 4) + (c >> 4)) & 0x1F];
        }
        if (i + 2 < _n)
        {
            *out++ = codes[(((c & 0xF) << 1) + (d >> 7)) & 0x1F];
        }
        if (i + 3 < _n)
        {
            *out++ = codes[(d >> 2) & 0x1F];
            *out++ = codes[((d & 0x3) << 3) & 0x1F];
        }
    }
    *out = 0;

    return A_BASE_SUCCESS;
}

int a_base32_decode(const void *_p, size_t _n, void *_out, size_t *_siz, unsigned int _id)
{
    const unsigned char tables[A_BASE32_ALL][43] = {
        /* id = RFC4648 : ABCDEFGHIJKLMNOPQRSTUVWXYZ234567 */
        {
            /* clang-format off */
            0x63, 0x63, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, /* 01234567 */
            0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, /* 89:;<=>? */
            0x63, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, /* @ABCDEFG */
            0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, /* HIJKLMNO */
            0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, /* PQRSTUVW */
            0x17, 0x18, 0x19,                               /* XYZ      */
            /* clang-format on */
        },
        /* id = BASE32HEX : 0123456789ABCDEFGHIJKLMNOPQRSTUV */
        {
            /* clang-format off */
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, /* 01234567 */
            0x08, 0x09, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, /* 89:;<=>? */
            0x63, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, /* @ABCDEFG */
            0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, /* HIJKLMNO */
            0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x63, /* PQRSTUVW */
            0x63, 0x63, 0x63,                               /* XYZ      */
            /* clang-format on */
        },
        /* id = ZBASE32 : YBNDRFG8EJKMCPQXOT1UWISZA345H769 */
        {
            /* clang-format off */
            0x63, 0x12, 0x63, 0x19, 0x1A, 0x1B, 0x1E, 0x1D, /* 01234567 */
            0x07, 0x1F, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, /* 89:;<=>? */
            0x63, 0x18, 0x01, 0x0C, 0x03, 0x08, 0x05, 0x06, /* @ABCDEFG */
            0x1C, 0x15, 0x09, 0x0A, 0x63, 0x0B, 0x02, 0x10, /* HIJKLMNO */
            0x0D, 0x0E, 0x04, 0x16, 0x11, 0x13, 0x63, 0x14, /* PQRSTUVW */
            0x0F, 0x00, 0x17,                               /* XYZ      */
            /* clang-format on */
        },
        /* id = CROCKFORD : 0123456789ABCDEFGHJKMNPQRSTVWXYZ + O=>0 + IL=>1 */
        {
            /* clang-format off */
            0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, /* 01234567 */
            0x08, 0x09, 0x63, 0x63, 0x63, 0x63, 0x63, 0x63, /* 89:;<=>? */
            0x63, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, /* @ABCDEFG */
            0x11, 0x01, 0x12, 0x13, 0x01, 0x14, 0x15, 0x00, /* HIJKLMNO */
            0x16, 0x17, 0x18, 0x19, 0x1A, 0x63, 0x1B, 0x1C, /* PQRSTUVW */
            0x1D, 0x1E, 0x1F,                               /* XYZ      */
            /* clang-format on */
        },
    };

    aassert(_out);
    aassert(_siz);
    aassert(!_n || _p);

    const char *p = (const char *)_p;

    /* ignore all trailing = */
    while (_n && p[_n - 1] == '=')
    {
        --_n;
    }

    /* no input, nothing to do */
    if (_n == 0)
    {
        *_siz = 0;
        return A_BASE_SUCCESS;
    }

    /* check the size of output buffer */
    size_t x = (_n * 5) >> 3;
    if (*_siz < x)
    {
        *_siz = x;
        return A_BASE_OVERFLOW;
    }
    *_siz = x;

    /* check input data length */
    x = _n % 8;
    if (x == 1 || x == 3 || x == 6)
    {
        return A_BASE_INVALID;
    }

#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wshift-count-overflow"
#endif /* _MSC_VER */

    size_t t = 0;
    unsigned int y = 0;
    unsigned char *out = (unsigned char *)_out;
    const unsigned char *map = tables[_id % A_BASE32_ALL];
    for (x = 0; x != _n; ++x)
    {
        char c = p[x];
        /* convert to upper case */
        if ((c >= 'a') && (c <= 'z'))
        {
            c = (char)(c - 32);
        }
        if (c < '0' || c > 'Z' || map[c - '0'] > 31)
        {
            return A_BASE_INVALID;
        }
        t = (t << 5) | map[c - '0'];
        if (++y == 8)
        {
            *out++ = (unsigned char)((t >> 0x20) & 0xFF);
            *out++ = (unsigned char)((t >> 0x18) & 0xFF);
            *out++ = (unsigned char)((t >> 0x10) & 0xFF);
            *out++ = (unsigned char)((t >> 0x08) & 0xFF);
            *out++ = (unsigned char)((t >> 0x00) & 0xFF);
            y = 0;
            t = 0;
        }
    }
    if (y)
    {
        t = t << (5 * (8 - y));
        if (y > 1)
        {
            *out++ = (unsigned char)((t >> 0x20) & 0xFF);
        }
        if (y > 3)
        {
            *out++ = (unsigned char)((t >> 0x18) & 0xFF);
        }
        if (y > 4)
        {
            *out++ = (unsigned char)((t >> 0x10) & 0xFF);
        }
        if (y > 6)
        {
            *out++ = (unsigned char)((t >> 0x08) & 0xFF);
        }
    }

#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

    return A_BASE_SUCCESS;
}

enum
{
    insane,
    strict,
    relaxed,
};

static const char *const codes_base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char *const codes_base64url = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static int a_base64_encode_internal(const void *_p,
                                    size_t _n,
                                    void *_out,
                                    size_t *_siz,
                                    const char *_codes,
                                    unsigned int _pad)
{
    aassert(_out);
    aassert(_siz);
    aassert(!_n || _p);

    /* valid output size ? */
    size_t x = ((_n + 2) / 3) << 2;
    if (*_siz < x + 1)
    {
        *_siz = x + 1;
        return A_BASE_OVERFLOW;
    }
    x = 3 * (_n / 3);

    size_t i = 0;
    char *out = (char *)_out;
    const unsigned char *p = (const unsigned char *)_p;
    while (i != x)
    {
        *out++ = _codes[(p[0] >> 2) & 0x3F];
        *out++ = _codes[(((p[0] & 3) << 4) + (p[1] >> 4)) & 0x3F];
        *out++ = _codes[(((p[1] & 0x0F) << 2) + (p[2] >> 6)) & 0x3F];
        *out++ = _codes[p[2] & 0x3F];
        p += 3;
        i += 3;
    }
    /* Pad it if necessary...  */
    if (i < _n)
    {
        unsigned int a = p[0];
        unsigned int b = (i + 1 < _n) ? p[1] : 0;
        *out++ = _codes[(a >> 2) & 0x3F];
        *out++ = _codes[(((a & 3) << 4) + (b >> 4)) & 0x3F];
        if (_pad)
        {
            *out++ = (i + 1 < _n) ? _codes[(((b & 0x0F) << 2)) & 0x3F] : '=';
            *out++ = '=';
        }
        else
        {
            if (i + 1 < _n)
            {
                *out++ = _codes[(((b & 0x0F) << 2)) & 0x3F];
            }
        }
    }

    /* append a NULL byte */
    *out = 0;
    /* the length without terminating NUL */
    *_siz = (size_t)(out - (char *)_out);

    return A_BASE_SUCCESS;
}

int a_base64_encode(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_encode_internal(_p, _n, _out, _siz, codes_base64, strict);
}

int a_base64url_encode(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_encode_internal(_p, _n, _out, _siz, codes_base64url, insane);
}

int a_base64url_encode_strict(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_encode_internal(_p, _n, _out, _siz, codes_base64url, strict);
}

static const unsigned char map_base64[0x100] = {
    /* clang-format off */
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFD, 0xFD, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0x3E, 0xFF, 0xFF, 0xFF, 0x3F,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
    0x3C, 0x3D, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF,
    0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
    0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
    0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    /* clang-format on */
};
static const unsigned char map_base64url[0x100] = {
    /* clang-format off */
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFD, 0xFD, 0xFF, 0xFF, 0xFD, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFD, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x3E, 0xFF, 0xFF,
    0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B,
    0x3C, 0x3D, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF,
    0xFF, 0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
    0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x19, 0xFF, 0xFF, 0xFF, 0xFF, 0x3F,
    0xFF, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20,
    0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28,
    0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30,
    0x31, 0x32, 0x33, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    /* clang-format on */
};

static int a_base64_decode_internal(const void *_p,
                                    size_t _n,
                                    void *_out,
                                    size_t *_siz,
                                    const unsigned char *_map,
                                    unsigned int _mode)
{
    aassert(_out);
    aassert(_siz);
    aassert(!_n || _p);

    /* '=' counter */
    unsigned int g = 0;
    const char *p = (const char *)_p;
    unsigned char *out = (unsigned char *)_out;

    size_t t, x, y, z;
    for (x = y = z = t = 0; x != _n; ++x)
    {
        if ((p[x] == 0) && (x == (_n - 1)) && (_mode != strict))
        {
            continue; /* allow the last byte to be NUL (relaxed+insane) */
        }
        unsigned char c = _map[(unsigned char)p[x] & 0xFF];
        if (c == 0xFE)
        {
            ++g;
            continue;
        }
        if (c == 0xFD)
        {
            if (_mode == strict)
            {
                return A_BASE_INVALID;
            }
            continue; /* allow to ignore white-spaces (relaxed+insane) */
        }
        if (c == 0xFF)
        {
            if (_mode == insane)
            {
                continue; /* allow to ignore invalid garbage (insane) */
            }
            return A_BASE_INVALID;
        }
        if (g && (_mode != insane))
        {
            /* we only allow '=' to be at the end (strict+relaxed) */
            return A_BASE_INVALID;
        }
        t = (t << 6) | c;
        if (++y == 4)
        {
            if (z + 3 > *_siz)
            {
                return A_BASE_OVERFLOW;
            }
            out[z++] = (unsigned char)((t >> 0x10) & 0xFF);
            out[z++] = (unsigned char)((t >> 0x08) & 0xFF);
            out[z++] = (unsigned char)((t >> 0x00) & 0xFF);
            y = t = 0;
        }
    }

    if (y)
    {
        if (y == 1)
        {
            return A_BASE_INVALID;
        }
        if (((y + g) != 4) && (_mode == strict) && (_map != map_base64url))
        {
            return A_BASE_INVALID;
        }
        t = t << (6 * (4 - y));
        if (z + y - 1 > *_siz)
        {
            return A_BASE_OVERFLOW;
        }
        if (y > 1)
        {
            out[z++] = (unsigned char)((t >> 0x10) & 0xFF);
        }
        if (y == 3)
        {
            out[z++] = (unsigned char)((t >> 0x08) & 0xFF);
        }
    }
    *_siz = z;

    return A_BASE_SUCCESS;
}

int a_base64_decode(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_decode_internal(_p, _n, _out, _siz, map_base64, insane);
}

int a_base64_decode_strict(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_decode_internal(_p, _n, _out, _siz, map_base64, strict);
}

int a_base64_decode_sane(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_decode_internal(_p, _n, _out, _siz, map_base64, relaxed);
}

int a_base64url_decode(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_decode_internal(_p, _n, _out, _siz, map_base64url, insane);
}

int a_base64url_decode_strict(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_decode_internal(_p, _n, _out, _siz, map_base64url, strict);
}

int a_base64url_decode_sane(const void *_p, size_t _n, void *_out, size_t *_siz)
{
    return a_base64_decode_internal(_p, _n, _out, _siz, map_base64url, relaxed);
}

/* END OF FILE */
