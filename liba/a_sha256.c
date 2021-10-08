/*!
 @file           a_sha256.c
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha256.h"

#include <string.h> /* memcpy */

#undef Ch
#undef Maj
#undef S
#undef R
#undef Sigma0
#undef Sigma1
#undef Gamma0
#undef Gamma1

/* Various logical functions */
#define S(x, n)      RORc((x), (n))
#define R(x, n)      (((x)&0xFFFFFFFF) >> (n))
#define Ch(x, y, z)  (z ^ (x & (y ^ z)))
#define Maj(x, y, z) (((x | y) & z) | (x & y))
#define Sigma0(x)    (S(x, 2) ^ S(x, 13) ^ S(x, 22))
#define Sigma1(x)    (S(x, 6) ^ S(x, 11) ^ S(x, 25))
#define Gamma0(x)    (S(x, 7) ^ S(x, 18) ^ R(x, 3))
#define Gamma1(x)    (S(x, 17) ^ S(x, 19) ^ R(x, 10))

void a_sha256_compress(a_sha256_t *ctx, const unsigned char *buf)
{
    uint32_t w[0x40], t0, t1;
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

    /* fill w[16..63] */
    for (unsigned int i = 0x10; i != 0x40; ++i)
    {
        w[i] = Gamma1(w[i - 2]) + w[i - 7] + Gamma0(w[i - 15]) + w[i - 16];
    }

    /* compress */

#define RND(a, b, c, d, e, f, g, h, i, ki)        \
    t0 = h + Sigma1(e) + Ch(e, f, g) + ki + w[i]; \
    t1 = Sigma0(a) + Maj(a, b, c);                \
    d += t0;                                      \
    h = t0 + t1;

    RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 0, 0x428a2f98);
    RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], 1, 0x71374491);
    RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], 2, 0xb5c0fbcf);
    RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], 3, 0xe9b5dba5);
    RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], 4, 0x3956c25b);
    RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], 5, 0x59f111f1);
    RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], 6, 0x923f82a4);
    RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], 7, 0xab1c5ed5);
    RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 8, 0xd807aa98);
    RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], 9, 0x12835b01);
    RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], 10, 0x243185be);
    RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], 11, 0x550c7dc3);
    RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], 12, 0x72be5d74);
    RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], 13, 0x80deb1fe);
    RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], 14, 0x9bdc06a7);
    RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], 15, 0xc19bf174);
    RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 16, 0xe49b69c1);
    RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], 17, 0xefbe4786);
    RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], 18, 0x0fc19dc6);
    RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], 19, 0x240ca1cc);
    RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], 20, 0x2de92c6f);
    RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], 21, 0x4a7484aa);
    RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], 22, 0x5cb0a9dc);
    RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], 23, 0x76f988da);
    RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 24, 0x983e5152);
    RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], 25, 0xa831c66d);
    RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], 26, 0xb00327c8);
    RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], 27, 0xbf597fc7);
    RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], 28, 0xc6e00bf3);
    RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], 29, 0xd5a79147);
    RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], 30, 0x06ca6351);
    RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], 31, 0x14292967);
    RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 32, 0x27b70a85);
    RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], 33, 0x2e1b2138);
    RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], 34, 0x4d2c6dfc);
    RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], 35, 0x53380d13);
    RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], 36, 0x650a7354);
    RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], 37, 0x766a0abb);
    RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], 38, 0x81c2c92e);
    RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], 39, 0x92722c85);
    RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 40, 0xa2bfe8a1);
    RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], 41, 0xa81a664b);
    RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], 42, 0xc24b8b70);
    RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], 43, 0xc76c51a3);
    RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], 44, 0xd192e819);
    RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], 45, 0xd6990624);
    RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], 46, 0xf40e3585);
    RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], 47, 0x106aa070);
    RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 48, 0x19a4c116);
    RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], 49, 0x1e376c08);
    RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], 50, 0x2748774c);
    RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], 51, 0x34b0bcb5);
    RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], 52, 0x391c0cb3);
    RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], 53, 0x4ed8aa4a);
    RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], 54, 0x5b9cca4f);
    RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], 55, 0x682e6ff3);
    RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], 56, 0x748f82ee);
    RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], 57, 0x78a5636f);
    RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], 58, 0x84c87814);
    RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], 59, 0x8cc70208);
    RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], 60, 0x90befffa);
    RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], 61, 0xa4506ceb);
    RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], 62, 0xbef9a3f7);
    RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], 63, 0xc67178f2);

#undef RND

    /* feedback */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        ctx->state[i] += s[i];
    }
}

#undef S
#undef R
#undef Ch
#undef Maj
#undef Sigma0
#undef Sigma1
#undef Gamma0
#undef Gamma1

void a_sha256_init(a_sha256_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x6A09E667;
    ctx->state[1] = 0xBB67AE85;
    ctx->state[2] = 0x3C6EF372;
    ctx->state[3] = 0xA54FF53A;
    ctx->state[4] = 0x510E527F;
    ctx->state[5] = 0x9B05688C;
    ctx->state[6] = 0x1F83D9AB;
    ctx->state[7] = 0x5BE0CD19;
}

void a_sha224_init(a_sha256_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0xc1059ed8;
    ctx->state[1] = 0x367cd507;
    ctx->state[2] = 0x3070dd17;
    ctx->state[3] = 0xf70e5939;
    ctx->state[4] = 0xffc00b31;
    ctx->state[5] = 0x68581511;
    ctx->state[6] = 0x64f98fa7;
    ctx->state[7] = 0xbefa4fa4;
}

__A_HASH_PROCESS(a_sha256_t, a_sha256_process, a_sha256_compress)

unsigned char *a_sha256_done(a_sha256_t *ctx, unsigned char *out)
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
        a_sha256_compress(ctx, ctx->buf);
        ctx->curlen = 0;
    }

    /* pad up to 56 bytes of zeroes */
    while (ctx->curlen < 0x38)
    {
        ctx->buf[ctx->curlen++] = 0;
    }

    /* store length */
    STORE64H(ctx->length, ctx->buf + 0x38);
    a_sha256_compress(ctx, ctx->buf);

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

unsigned char *a_sha224_done(a_sha256_t *ctx, unsigned char *out)
{
    a_sha256_done(ctx, ctx->out);

    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, A_SHA224_DIGESTSIZE);
    }

    return ctx->out;
}

#define __A_SHA256(func, size)                                       \
    unsigned char *func(const void *p, size_t n, unsigned char *out) \
    {                                                                \
        a_sha256_t ctx[1];                                           \
                                                                     \
        func##_init(ctx);                                            \
        a_sha256_process(ctx, p, n);                                 \
        func##_done(ctx, out);                                       \
                                                                     \
        if (0 == out && (out = (unsigned char *)a_alloc(size)))      \
        {                                                            \
            (void)memcpy(out, ctx->out, size);                       \
        }                                                            \
                                                                     \
        return out;                                                  \
    }
__A_SHA256(a_sha256, sizeof(ctx->state))
__A_SHA256(a_sha224, A_SHA224_DIGESTSIZE)

/* END OF FILE */
