/*!
 @file a_md5.c
 @brief RFC 1321 compliant MD5 implementation
 @details https://www.ietf.org/rfc/rfc1321.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_md5.h"

#include "a_hash.h"
#include "a_hash_private.h"

#undef F
#undef G
#undef H
#undef I
#undef FF
#undef GG
#undef HH
#undef II
#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-align"
#endif /* _MSC_VER */

static void a_md5_compress(a_md5_s *ctx, const unsigned char *buf)
{
    uint32_t s[sizeof(ctx->state) / sizeof(*ctx->state)];
    uint32_t *w = (uint32_t *)ctx->buf;
    if (ctx->buf != buf)
    {
        /* copy the state into 512-bits into w[0..15] */
        for (unsigned int i = 0; i != 0x10; ++i)
        {
            LOAD32L(w[i], buf + sizeof(*ctx->state) * i);
        }
    }

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        s[i] = ctx->state[i];
    }

    /* compress */

#define F(x, y, z) ((z) ^ ((x) & ((y) ^ (z))))
#define G(x, y, z) ((y) ^ ((z) & ((x) ^ (y))))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | ~(z)))

#define FF(a, b, c, d, M, s, t)   \
    a = (a + F(b, c, d) + M + t); \
    a = ROLc(a, s) + b;
#define GG(a, b, c, d, M, s, t)   \
    a = (a + G(b, c, d) + M + t); \
    a = ROLc(a, s) + b;
#define HH(a, b, c, d, M, s, t)   \
    a = (a + H(b, c, d) + M + t); \
    a = ROLc(a, s) + b;
#define II(a, b, c, d, M, s, t)   \
    a = (a + I(b, c, d) + M + t); \
    a = ROLc(a, s) + b;

    /* round 1 */
    FF(s[0], s[1], s[2], s[3], w[0x0], 0x07, 0xD76AA478)
    FF(s[3], s[0], s[1], s[2], w[0x1], 0x0C, 0xE8C7B756)
    FF(s[2], s[3], s[0], s[1], w[0x2], 0x11, 0x242070DB)
    FF(s[1], s[2], s[3], s[0], w[0x3], 0x16, 0xC1BDCEEE)
    FF(s[0], s[1], s[2], s[3], w[0x4], 0x07, 0xF57C0FAF)
    FF(s[3], s[0], s[1], s[2], w[0x5], 0x0C, 0x4787C62A)
    FF(s[2], s[3], s[0], s[1], w[0x6], 0x11, 0xA8304613)
    FF(s[1], s[2], s[3], s[0], w[0x7], 0x16, 0xFD469501)
    FF(s[0], s[1], s[2], s[3], w[0x8], 0x07, 0x698098D8)
    FF(s[3], s[0], s[1], s[2], w[0x9], 0x0C, 0x8B44F7AF)
    FF(s[2], s[3], s[0], s[1], w[0xA], 0x11, 0xFFFF5BB1)
    FF(s[1], s[2], s[3], s[0], w[0xB], 0x16, 0x895CD7BE)
    FF(s[0], s[1], s[2], s[3], w[0xC], 0x07, 0x6B901122)
    FF(s[3], s[0], s[1], s[2], w[0xD], 0x0C, 0xFD987193)
    FF(s[2], s[3], s[0], s[1], w[0xE], 0x11, 0xA679438E)
    FF(s[1], s[2], s[3], s[0], w[0xF], 0x16, 0x49B40821)
    /* round 2 */
    GG(s[0], s[1], s[2], s[3], w[0x1], 0x05, 0xF61E2562)
    GG(s[3], s[0], s[1], s[2], w[0x6], 0x09, 0xC040B340)
    GG(s[2], s[3], s[0], s[1], w[0xB], 0x0E, 0x265E5A51)
    GG(s[1], s[2], s[3], s[0], w[0x0], 0x14, 0xE9B6C7AA)
    GG(s[0], s[1], s[2], s[3], w[0x5], 0x05, 0xD62F105D)
    GG(s[3], s[0], s[1], s[2], w[0xA], 0x09, 0x02441453)
    GG(s[2], s[3], s[0], s[1], w[0xF], 0x0E, 0xD8A1E681)
    GG(s[1], s[2], s[3], s[0], w[0x4], 0x14, 0xE7D3FBC8)
    GG(s[0], s[1], s[2], s[3], w[0x9], 0x05, 0x21E1CDE6)
    GG(s[3], s[0], s[1], s[2], w[0xE], 0x09, 0xC33707D6)
    GG(s[2], s[3], s[0], s[1], w[0x3], 0x0E, 0xF4D50D87)
    GG(s[1], s[2], s[3], s[0], w[0x8], 0x14, 0x455A14ED)
    GG(s[0], s[1], s[2], s[3], w[0xD], 0x05, 0xA9E3E905)
    GG(s[3], s[0], s[1], s[2], w[0x2], 0x09, 0xFCEFA3F8)
    GG(s[2], s[3], s[0], s[1], w[0x7], 0x0E, 0x676F02D9)
    GG(s[1], s[2], s[3], s[0], w[0xC], 0x14, 0x8D2A4C8A)
    /* round 3 */
    HH(s[0], s[1], s[2], s[3], w[0x5], 0x04, 0xFFFA3942)
    HH(s[3], s[0], s[1], s[2], w[0x8], 0x0B, 0x8771F681)
    HH(s[2], s[3], s[0], s[1], w[0xB], 0x10, 0x6D9D6122)
    HH(s[1], s[2], s[3], s[0], w[0xE], 0x17, 0xFDE5380C)
    HH(s[0], s[1], s[2], s[3], w[0x1], 0x04, 0xA4BEEA44)
    HH(s[3], s[0], s[1], s[2], w[0x4], 0x0B, 0x4BDECFA9)
    HH(s[2], s[3], s[0], s[1], w[0x7], 0x10, 0xF6BB4B60)
    HH(s[1], s[2], s[3], s[0], w[0xA], 0x17, 0xBEBFBC70)
    HH(s[0], s[1], s[2], s[3], w[0xD], 0x04, 0x289B7EC6)
    HH(s[3], s[0], s[1], s[2], w[0x0], 0x0B, 0xEAA127FA)
    HH(s[2], s[3], s[0], s[1], w[0x3], 0x10, 0xD4EF3085)
    HH(s[1], s[2], s[3], s[0], w[0x6], 0x17, 0x04881D05)
    HH(s[0], s[1], s[2], s[3], w[0x9], 0x04, 0xD9D4D039)
    HH(s[3], s[0], s[1], s[2], w[0xC], 0x0B, 0xE6DB99E5)
    HH(s[2], s[3], s[0], s[1], w[0xF], 0x10, 0x1FA27CF8)
    HH(s[1], s[2], s[3], s[0], w[0x2], 0x17, 0xC4AC5665)
    /* round 4 */
    II(s[0], s[1], s[2], s[3], w[0x0], 0x06, 0xF4292244)
    II(s[3], s[0], s[1], s[2], w[0x7], 0x0A, 0x432AFF97)
    II(s[2], s[3], s[0], s[1], w[0xE], 0x0F, 0xAB9423A7)
    II(s[1], s[2], s[3], s[0], w[0x5], 0x15, 0xFC93A039)
    II(s[0], s[1], s[2], s[3], w[0xC], 0x06, 0x655B59C3)
    II(s[3], s[0], s[1], s[2], w[0x3], 0x0A, 0x8F0CCC92)
    II(s[2], s[3], s[0], s[1], w[0xA], 0x0F, 0xFFEFF47D)
    II(s[1], s[2], s[3], s[0], w[0x1], 0x15, 0x85845DD1)
    II(s[0], s[1], s[2], s[3], w[0x8], 0x06, 0x6FA87E4F)
    II(s[3], s[0], s[1], s[2], w[0xF], 0x0A, 0xFE2CE6E0)
    II(s[2], s[3], s[0], s[1], w[0x6], 0x0F, 0xA3014314)
    II(s[1], s[2], s[3], s[0], w[0xD], 0x15, 0x4E0811A1)
    II(s[0], s[1], s[2], s[3], w[0x4], 0x06, 0xF7537E82)
    II(s[3], s[0], s[1], s[2], w[0xB], 0x0A, 0xBD3AF235)
    II(s[2], s[3], s[0], s[1], w[0x2], 0x0F, 0x2AD7D2BB)
    II(s[1], s[2], s[3], s[0], w[0x9], 0x15, 0xEB86D391)

    /* feedback */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] += s[i];
    }
}

#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */
#undef FF
#undef GG
#undef HH
#undef II
#undef F
#undef G
#undef H
#undef I

void a_md5_init(a_md5_s *ctx)
{
    AASSERT(ctx);

    ctx->cursiz = 0;
    ctx->length = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89; // 0x10325476 ^ 0xFFFFFFFF
    ctx->state[2] = 0x98BADCFE; // 0x67452301 ^ 0xFFFFFFFF
    ctx->state[3] = 0x10325476;
}

A_HASH_PROCESS(a_md5_s, a_md5_process, a_md5_compress)

A_HASH_DONE(a_md5_s, a_md5_done, a_md5_compress, STORE64L, STORE32L, 0x80, 0x38, 0x38)
