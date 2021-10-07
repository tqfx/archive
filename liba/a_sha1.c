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
    uint32_t w[80];
    /* copy state */
    uint32_t a = ctx->state[0];
    uint32_t b = ctx->state[1];
    uint32_t c = ctx->state[2];
    uint32_t d = ctx->state[3];
    uint32_t e = ctx->state[4];

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
    e = (ROLc(a, 5) + F0(b, c, d) + e + w[i] + 0x5a827999); \
    b = ROLc(b, 30);
#define FF1(a, b, c, d, e, i)                               \
    e = (ROLc(a, 5) + F1(b, c, d) + e + w[i] + 0x6ed9eba1); \
    b = ROLc(b, 30);
#define FF2(a, b, c, d, e, i)                               \
    e = (ROLc(a, 5) + F2(b, c, d) + e + w[i] + 0x8f1bbcdc); \
    b = ROLc(b, 30);
#define FF3(a, b, c, d, e, i)                               \
    e = (ROLc(a, 5) + F3(b, c, d) + e + w[i] + 0xca62c1d6); \
    b = ROLc(b, 30);

    unsigned int i = 0;

    /* round one */
    while (i != 0x14)
    {
        FF0(a, b, c, d, e, i++);
        FF0(e, a, b, c, d, i++);
        FF0(d, e, a, b, c, i++);
        FF0(c, d, e, a, b, i++);
        FF0(b, c, d, e, a, i++);
    }

    /* round two */
    while (i != 0x28)
    {
        FF1(a, b, c, d, e, i++);
        FF1(e, a, b, c, d, i++);
        FF1(d, e, a, b, c, i++);
        FF1(c, d, e, a, b, i++);
        FF1(b, c, d, e, a, i++);
    }

    /* round three */
    while (i != 0x3c)
    {
        FF2(a, b, c, d, e, i++);
        FF2(e, a, b, c, d, i++);
        FF2(d, e, a, b, c, i++);
        FF2(c, d, e, a, b, i++);
        FF2(b, c, d, e, a, i++);
    }

    /* round four */
    while (i != 0x50)
    {
        FF3(a, b, c, d, e, i++);
        FF3(e, a, b, c, d, i++);
        FF3(d, e, a, b, c, i++);
        FF3(c, d, e, a, b, i++);
        FF3(b, c, d, e, a, i++);
    }

    /* store */
    ctx->state[0] += a;
    ctx->state[1] += b;
    ctx->state[2] += c;
    ctx->state[3] += d;
    ctx->state[4] += e;
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
    ctx->state[1] = 0xefcdab89;
    ctx->state[2] = 0x98badcfe;
    ctx->state[3] = 0x10325476;
    ctx->state[4] = 0xc3d2e1f0;
}

void a_sha1_process(a_sha1_t *ctx, const void *p, size_t n)
{
    const unsigned char *s = (const unsigned char *)p;

    while (n)
    {
        if ((0 == ctx->curlen) && (A_SHA1_BLOCKSIZE - 1 < n))
        {
            a_sha1_compress(ctx, s);
            ctx->length += (A_SHA1_BLOCKSIZE << 3);
            s += A_SHA1_BLOCKSIZE;
            n -= A_SHA1_BLOCKSIZE;
        }
        else
        {
            uint32_t m = A_SHA1_BLOCKSIZE - ctx->curlen;
            m = n < m ? (uint32_t)n : m;
            (void)memcpy(ctx->buf + ctx->curlen, s, m);
            ctx->curlen += m;
            s += m;
            n -= m;
            if (A_SHA1_BLOCKSIZE == ctx->curlen)
            {
                a_sha1_compress(ctx, ctx->buf);
                ctx->length += (A_SHA1_BLOCKSIZE << 3);
                ctx->curlen = 0;
            }
        }
    }
}

unsigned char *a_sha1_done(a_sha1_t *ctx, unsigned char *out)
{
    if (A_SHA1_BLOCKSIZE - 1 < ctx->curlen)
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
    if (out && ctx->out != out)
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
