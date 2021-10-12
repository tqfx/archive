/*!
 @file           a_base.c
 @brief          RFC 4648 compliant Base implementation
 @details        https://www.ietf.org/rfc/rfc4648.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_base.h"

int a_base16_encode(const void *p, size_t n, void *out, size_t *siz, unsigned int id)
{
    static const char *alphabets[2] = {
        "0123456789abcdef",
        "0123456789ABCDEF",
    };

    /* check the sizes */
    size_t x = (n << 1) + 1;

    if (x < n)
    {
        return A_BASE_OVERFLOW;
    }

    if (*siz < x)
    {
        *siz = x;
        return A_BASE_OVERFLOW;
    }
    *siz = --x; /* returning the length without terminating NUL */

    char *o = (char *)out;
    const char *map = alphabets[id % 2];
    const unsigned char *s = (const unsigned char *)p;
    for (size_t i = 0; i != x; i += 2)
    {
        size_t t = i >> 1;
        o[i + 0] = map[(s[t] >> 4) & 0x0F];
        o[i + 1] = map[(s[t] >> 0) & 0x0F];
    }
    o[x] = 0;

    return A_BASE_SUCCESS;
}

int a_base16_decode(const void *p, size_t n, void *out, size_t *siz)
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

    if (n % 2)
    {
        return A_BASE_INVALID;
    }

    size_t idx = 0;
    size_t x = *siz << 1;
    const char *s = (const char *)p;
    unsigned char *o = (unsigned char *)out;
    while ((idx + 1 < x) && (idx + 1 < n))
    {
        char c0 = s[idx + 0];
        char c1 = s[idx + 1];

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

        o[idx >> 1] = (unsigned char)(hashmap[idx0] << 4) | hashmap[idx1];
        idx += 2;
    }
    *siz = idx >> 1;

    return A_BASE_SUCCESS;
}

int a_base32_encode(const void *p, size_t n, void *out, size_t *siz, unsigned int id)
{
    static const char *alphabet[A_BASE32_BUFSIZ] = {
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567", /* id = RFC4648   */
        "0123456789ABCDEFGHIJKLMNOPQRSTUV", /* id = BASE32HEX */
        "ybndrfg8ejkmcpqxot1uwisza345h769", /* id = ZBASE32   */
        "0123456789ABCDEFGHJKMNPQRSTVWXYZ"  /* id = CROCKFORD */
    };

    /* check the size of output buffer +1 byte for terminating NUL */
    size_t x = ((n << 3) + 4) / 5 + 1;

    if (*siz < x)
    {
        *siz = x;
        return A_BASE_OVERFLOW;
    }
    *siz = --x; /* returning the length without terminating NUL */
    x = 5 * (n / 5);

    char *o = (char *)out;
    /* no input, nothing to do */
    if (0 == n)
    {
        *o = 0;
        return A_BASE_SUCCESS;
    }

    size_t i = 0;
    const char *codes = alphabet[id % A_BASE32_BUFSIZ];
    const unsigned char *s = (const unsigned char *)p;
    while (i != x)
    {
        *o++ = codes[(s[0] >> 3) & 0x1F];
        *o++ = codes[(((s[0] & 0x7) << 2) + (s[1] >> 6)) & 0x1F];
        *o++ = codes[(s[1] >> 1) & 0x1F];
        *o++ = codes[(((s[1] & 0x1) << 4) + (s[2] >> 4)) & 0x1F];
        *o++ = codes[(((s[2] & 0xF) << 1) + (s[3] >> 7)) & 0x1F];
        *o++ = codes[(s[3] >> 2) & 0x1F];
        *o++ = codes[(((s[3] & 0x3) << 3) + (s[4] >> 5)) & 0x1F];
        *o++ = codes[s[4] & 0x1F];
        s += 5;
        i += 5;
    }
    if (i < n)
    {
        unsigned int a = s[0];
        unsigned int b = (i + 1 < n) ? s[1] : 0;
        unsigned int c = (i + 2 < n) ? s[2] : 0;
        unsigned int d = (i + 3 < n) ? s[3] : 0;
        *o++ = codes[(a >> 3) & 0x1F];
        *o++ = codes[(((a & 0x7) << 2) + (b >> 6)) & 0x1F];
        if (i + 1 < n)
        {
            *o++ = codes[(b >> 1) & 0x1F];
            *o++ = codes[(((b & 0x1) << 4) + (c >> 4)) & 0x1F];
        }
        if (i + 2 < n)
        {
            *o++ = codes[(((c & 0xF) << 1) + (d >> 7)) & 0x1F];
        }
        if (i + 3 < n)
        {
            *o++ = codes[(d >> 2) & 0x1F];
            *o++ = codes[((d & 0x3) << 3) & 0x1F];
        }
    }
    *o = 0;

    return A_BASE_SUCCESS;
}

int a_base32_decode(const void *p, size_t n, void *out, size_t *siz, unsigned int id)
{
    const unsigned char tables[A_BASE32_BUFSIZ][43] = {
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

    const char *s = (const char *)p;

    /* ignore all trailing = */
    while (n && s[n - 1] == '=')
    {
        --n;
    }

    /* no input, nothing to do */
    if (0 == n)
    {
        *siz = 0;
        return A_BASE_SUCCESS;
    }

    /* check the size of output buffer */
    size_t x = (n * 5) >> 3;
    if (*siz < x)
    {
        *siz = x;
        return A_BASE_OVERFLOW;
    }
    *siz = x;

    /* check input data length */
    x = n % 8;
    if (x == 1 || x == 3 || x == 6)
    {
        return A_BASE_INVALID;
    }

    size_t t = 0;
    unsigned int y = 0;
    unsigned char *o = (unsigned char *)out;
    const unsigned char *map = tables[id % A_BASE32_BUFSIZ];
    for (x = 0; x != n; ++x)
    {
        char c = s[x];
        /* convert to upper case */
        if ((c >= 'a') && (c <= 'z'))
        {
            c -= 32;
        }
        if (c < '0' || c > 'Z' || map[c - '0'] > 31)
        {
            return A_BASE_INVALID;
        }
        t = (t << 5) | map[c - '0'];
        if (++y == 8)
        {
            *o++ = (unsigned char)((t >> 0x20) & 0xFF);
            *o++ = (unsigned char)((t >> 0x18) & 0xFF);
            *o++ = (unsigned char)((t >> 0x10) & 0xFF);
            *o++ = (unsigned char)((t >> 0x08) & 0xFF);
            *o++ = (unsigned char)((t >> 0x00) & 0xFF);
            y = 0;
            t = 0;
        }
    }
    if (y)
    {
        t = t << (5 * (8 - y));
        if (y > 1)
        {
            *o++ = (unsigned char)((t >> 0x20) & 0xFF);
        }
        if (y > 3)
        {
            *o++ = (unsigned char)((t >> 0x18) & 0xFF);
        }
        if (y > 4)
        {
            *o++ = (unsigned char)((t >> 0x10) & 0xFF);
        }
        if (y > 6)
        {
            *o++ = (unsigned char)((t >> 0x08) & 0xFF);
        }
    }

    return A_BASE_SUCCESS;
}

enum
{
    insane = 0,
    strict = 1,
    relaxed = 2
};

static const char *const codes_base64 = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static const char *const codes_base64url = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

static int a_base64_encode_internal(const void *p,
                                    size_t n,
                                    void *out,
                                    size_t *siz,
                                    const char *codes,
                                    unsigned int pad)
{
    /* valid output size ? */
    size_t x = ((n + 2) / 3) << 2;
    if (*siz < x + 1)
    {
        *siz = x + 1;
        return A_BASE_OVERFLOW;
    }
    x = 3 * (n / 3);

    size_t i = 0;
    char *o = (char *)out;
    const unsigned char *s = (const unsigned char *)p;
    while (i != x)
    {
        *o++ = codes[(s[0] >> 2) & 0x3F];
        *o++ = codes[(((s[0] & 3) << 4) + (s[1] >> 4)) & 0x3F];
        *o++ = codes[(((s[1] & 0x0F) << 2) + (s[2] >> 6)) & 0x3F];
        *o++ = codes[s[2] & 0x3F];
        s += 3;
        i += 3;
    }
    /* Pad it if necessary...  */
    if (i < n)
    {
        unsigned int a = s[0];
        unsigned int b = (i + 1 < n) ? s[1] : 0;
        *o++ = codes[(a >> 2) & 0x3F];
        *o++ = codes[(((a & 3) << 4) + (b >> 4)) & 0x3F];
        if (pad)
        {
            *o++ = (i + 1 < n) ? codes[(((b & 0x0F) << 2)) & 0x3F] : '=';
            *o++ = '=';
        }
        else
        {
            if (i + 1 < n)
            {
                *o++ = codes[(((b & 0x0F) << 2)) & 0x3F];
            }
        }
    }

    /* the length without terminating NUL */
    *siz = (size_t)(o - (char *)out);
    /* append a NULL byte */
    *o = 0;

    return A_BASE_SUCCESS;
}

int a_base64_encode(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_encode_internal(p, n, out, siz, codes_base64, strict);
}

int a_base64url_encode(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_encode_internal(p, n, out, siz, codes_base64url, insane);
}

int a_base64url_encode_strict(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_encode_internal(p, n, out, siz, codes_base64url, strict);
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

static int a_base64_decode_internal(const void *p,
                                    size_t n,
                                    void *out,
                                    size_t *siz,
                                    const unsigned char *map,
                                    unsigned int mode)
{
    const char *s = (const char *)p;
    unsigned int g = 0; /* '=' counter */
    unsigned char *o = (unsigned char *)out;

    size_t t, x, y, z;
    for (x = y = z = t = 0; x != n; ++x)
    {
        if ((s[x] == 0) && (x == (n - 1)) && (mode != strict))
        {
            continue; /* allow the last byte to be NUL (relaxed+insane) */
        }
        unsigned char c = map[(unsigned char)s[x] & 0xFF];
        if (c == 0xFE)
        {
            ++g;
            continue;
        }
        if (c == 0xFD)
        {
            if (mode == strict)
            {
                return A_BASE_INVALID;
            }
            continue; /* allow to ignore white-spaces (relaxed+insane) */
        }
        if (c == 0xFF)
        {
            if (mode == insane)
            {
                continue; /* allow to ignore invalid garbage (insane) */
            }
            return A_BASE_INVALID;
        }
        if (g && (mode != insane))
        {
            /* we only allow '=' to be at the end (strict+relaxed) */
            return A_BASE_INVALID;
        }
        t = (t << 6) | c;
        if (++y == 4)
        {
            if (z + 3 > *siz)
            {
                return A_BASE_OVERFLOW;
            }
            o[z++] = (unsigned char)((t >> 0x10) & 0xFF);
            o[z++] = (unsigned char)((t >> 0x08) & 0xFF);
            o[z++] = (unsigned char)((t >> 0x00) & 0xFF);
            y = t = 0;
        }
    }

    if (y != 0)
    {
        if (y == 1)
        {
            return A_BASE_INVALID;
        }
        if (((y + g) != 4) && (mode == strict) && (map != map_base64url))
        {
            return A_BASE_INVALID;
        }
        t = t << (6 * (4 - y));
        if (z + y - 1 > *siz)
        {
            return A_BASE_OVERFLOW;
        }
        if (y > 1)
        {
            o[z++] = (unsigned char)((t >> 0x10) & 0xFF);
        }
        if (y == 3)
        {
            o[z++] = (unsigned char)((t >> 0x08) & 0xFF);
        }
    }
    *siz = z;

    return A_BASE_SUCCESS;
}

int a_base64_decode(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_decode_internal(p, n, out, siz, map_base64, insane);
}

int a_base64_decode_strict(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_decode_internal(p, n, out, siz, map_base64, strict);
}

int a_base64_decode_sane(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_decode_internal(p, n, out, siz, map_base64, relaxed);
}

int a_base64url_decode(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_decode_internal(p, n, out, siz, map_base64url, insane);
}

int a_base64url_decode_strict(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_decode_internal(p, n, out, siz, map_base64url, strict);
}

int a_base64url_decode_sane(const void *p, size_t n, void *out, size_t *siz)
{
    return a_base64_decode_internal(p, n, out, siz, map_base64url, relaxed);
}

/* END OF FILE */
