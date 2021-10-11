/*!
 @file           a_hash_sha1.c
 @brief          RFC 3174 compliant SHA1 implementation
 @details        https://www.ietf.org/rfc/rfc3174.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_hash.h"

#undef F0
#undef F1
#undef F2
#undef F3
#undef FF0
#undef FF1
#undef FF2
#undef FF3

static void a_sha1_compress(a_sha1_t *ctx, const unsigned char *buf)
{
    uint32_t w[0x50];
    uint32_t s[sizeof(ctx->state) / sizeof(*ctx->state)];

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        s[i] = ctx->state[i];
    }

    /* copy the state into 512-bits into w[0..15] */
    for (unsigned int i = 0x00; i != 0x10; ++i)
    {
        LOAD32H(w[i], buf + sizeof(*ctx->state) * i);
    }

    /* expand it */
    for (unsigned int i = 0x10; i != 0x50; ++i)
    {
        w[i] = ROL(w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16], 1);
    }

    /* compress */

#define F0(x, y, z) (z ^ (x & (y ^ z)))
#define F1(x, y, z) (x ^ y ^ z)
#define F2(x, y, z) ((x & y) | (z & (x | y)))
#define F3(x, y, z) (x ^ y ^ z)

#define FF0(a, b, c, d, e, i)                               \
    e = (ROLc(a, 5) + F0(b, c, d) + e + w[i] + 0x5A827999); \
    b = ROLc(b, 30);
#define FF1(a, b, c, d, e, i)                               \
    e = (ROLc(a, 5) + F1(b, c, d) + e + w[i] + 0x6ED9EBA1); \
    b = ROLc(b, 30);
#define FF2(a, b, c, d, e, i)                               \
    e = (ROLc(a, 5) + F2(b, c, d) + e + w[i] + 0x8F1BBCDC); \
    b = ROLc(b, 30);
#define FF3(a, b, c, d, e, i)                               \
    e = (ROLc(a, 5) + F3(b, c, d) + e + w[i] + 0xCA62C1D6); \
    b = ROLc(b, 30);

    unsigned int i = 0;

    /* round one */
    while (i != 0x14)
    {
        FF0(s[0], s[1], s[2], s[3], s[4], i++);
        FF0(s[4], s[0], s[1], s[2], s[3], i++);
        FF0(s[3], s[4], s[0], s[1], s[2], i++);
        FF0(s[2], s[3], s[4], s[0], s[1], i++);
        FF0(s[1], s[2], s[3], s[4], s[0], i++);
    }

    /* round two */
    while (i != 0x28)
    {
        FF1(s[0], s[1], s[2], s[3], s[4], i++);
        FF1(s[4], s[0], s[1], s[2], s[3], i++);
        FF1(s[3], s[4], s[0], s[1], s[2], i++);
        FF1(s[2], s[3], s[4], s[0], s[1], i++);
        FF1(s[1], s[2], s[3], s[4], s[0], i++);
    }

    /* round three */
    while (i != 0x3c)
    {
        FF2(s[0], s[1], s[2], s[3], s[4], i++);
        FF2(s[4], s[0], s[1], s[2], s[3], i++);
        FF2(s[3], s[4], s[0], s[1], s[2], i++);
        FF2(s[2], s[3], s[4], s[0], s[1], i++);
        FF2(s[1], s[2], s[3], s[4], s[0], i++);
    }

    /* round four */
    while (i != 0x50)
    {
        FF3(s[0], s[1], s[2], s[3], s[4], i++);
        FF3(s[4], s[0], s[1], s[2], s[3], i++);
        FF3(s[3], s[4], s[0], s[1], s[2], i++);
        FF3(s[2], s[3], s[4], s[0], s[1], i++);
        FF3(s[1], s[2], s[3], s[4], s[0], i++);
    }

    /* feedback */
    for (i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] += s[i];
    }
}

#undef FF0
#undef FF1
#undef FF2
#undef FF3
#undef F0
#undef F1
#undef F2
#undef F3

void a_sha1_init(a_sha1_t *ctx)
{
    /* assert(ctx) */
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xC3D2E1F0;
}

__A_HASH_PROCESS(a_sha1_t, a_sha1_process, a_sha1_compress)

__A_HASH_DONE(a_sha1_t, a_sha1_done, a_sha1_compress, STORE64H, STORE32H, 0x80, 0x38, 0x38)

/* END OF FILE */
