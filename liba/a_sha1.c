/*!
 @file           a_sha1.c
 @brief          RFC 3174 compliant SHA1 implementation
 @details        https://www.ietf.org/rfc/rfc3174.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha1.h"

#include <string.h> /* memcpy */

#undef F0
#undef F1
#undef F2
#undef F3
#undef FF0
#undef FF1
#undef FF2
#undef FF3

void a_sha1_compress(a_sha1_t *ctx, const unsigned char *buf)
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
        LOAD32H(w[i], buf + (i << 2));
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
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x67452301;
    ctx->state[1] = 0xEFCDAB89;
    ctx->state[2] = 0x98BADCFE;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xC3D2E1F0;
}

__A_HASH_PROCESS(a_sha1_t, a_sha1_process, a_sha1_compress)

unsigned char *a_sha1_done(a_sha1_t *ctx, unsigned char *out)
{
    if (sizeof(ctx->buf) - 1 < ctx->curlen)
    {
        return 0;
    }

    /* increase the length of the message */
    ctx->length += (ctx->curlen << 3);

    /* append the '1' bit */
    ctx->buf[ctx->curlen++] = 0x80;

    /* if the length is currently above 56 bytes we append zeros
     * then compress. Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (0x38 < ctx->curlen)
    {
        while (ctx->curlen < 0x40)
        {
            ctx->buf[ctx->curlen++] = 0;
        }
        a_sha1_compress(ctx, ctx->buf);
        ctx->curlen = 0;
    }

    /* pad up to 56 bytes of zeroes */
    while (ctx->curlen < 0x38)
    {
        ctx->buf[ctx->curlen++] = 0;
    }

    /* store length */
    STORE64H(ctx->length, ctx->buf + 0x38);
    a_sha1_compress(ctx, ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        STORE32H(ctx->state[i], ctx->out + (i << 2));
    }
    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, sizeof(ctx->state));
    }

    return ctx->out;
}

unsigned char *a_sha1(const void *p, size_t n, unsigned char *out)
{
    a_sha1_t ctx[1];

    a_sha1_init(ctx);
    a_sha1_process(ctx, p, n);
    a_sha1_done(ctx, out);

    if (0 == out && (out = (unsigned char *)a_alloc(sizeof(ctx->state))))
    {
        (void)memcpy(out, ctx->out, sizeof(ctx->state));
    }

    return out;
}

/* END OF FILE */
