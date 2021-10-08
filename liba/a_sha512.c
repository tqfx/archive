/*!
 @file           a_sha512.c
 @brief          RFC 5754 compliant SHA2 implementation
 @details        https://www.ietf.org/rfc/rfc5754.txt
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha512.h"

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
#define S(x, n)      ROR64c(x, n)
#define R(x, n)      (((x)&0xFFFFFFFFFFFFFFFF) >> (n))
#define Ch(x, y, z)  (z ^ (x & (y ^ z)))
#define Maj(x, y, z) (((x | y) & z) | (x & y))
#define Sigma0(x)    (S(x, 28) ^ S(x, 34) ^ S(x, 39))
#define Sigma1(x)    (S(x, 14) ^ S(x, 18) ^ S(x, 41))
#define Gamma0(x)    (S(x, 1) ^ S(x, 8) ^ R(x, 7))
#define Gamma1(x)    (S(x, 19) ^ S(x, 61) ^ R(x, 6))

void a_sha512_compress(a_sha512_t *ctx, const unsigned char *buf)
{
    /* the k array */
    static const uint64_t k[0x50] = {
        0x428a2f98d728ae22,
        0x7137449123ef65cd,
        0xb5c0fbcfec4d3b2f,
        0xe9b5dba58189dbbc,
        0x3956c25bf348b538,
        0x59f111f1b605d019,
        0x923f82a4af194f9b,
        0xab1c5ed5da6d8118,
        0xd807aa98a3030242,
        0x12835b0145706fbe,
        0x243185be4ee4b28c,
        0x550c7dc3d5ffb4e2,
        0x72be5d74f27b896f,
        0x80deb1fe3b1696b1,
        0x9bdc06a725c71235,
        0xc19bf174cf692694,
        0xe49b69c19ef14ad2,
        0xefbe4786384f25e3,
        0x0fc19dc68b8cd5b5,
        0x240ca1cc77ac9c65,
        0x2de92c6f592b0275,
        0x4a7484aa6ea6e483,
        0x5cb0a9dcbd41fbd4,
        0x76f988da831153b5,
        0x983e5152ee66dfab,
        0xa831c66d2db43210,
        0xb00327c898fb213f,
        0xbf597fc7beef0ee4,
        0xc6e00bf33da88fc2,
        0xd5a79147930aa725,
        0x06ca6351e003826f,
        0x142929670a0e6e70,
        0x27b70a8546d22ffc,
        0x2e1b21385c26c926,
        0x4d2c6dfc5ac42aed,
        0x53380d139d95b3df,
        0x650a73548baf63de,
        0x766a0abb3c77b2a8,
        0x81c2c92e47edaee6,
        0x92722c851482353b,
        0xa2bfe8a14cf10364,
        0xa81a664bbc423001,
        0xc24b8b70d0f89791,
        0xc76c51a30654be30,
        0xd192e819d6ef5218,
        0xd69906245565a910,
        0xf40e35855771202a,
        0x106aa07032bbd1b8,
        0x19a4c116b8d2d0c8,
        0x1e376c085141ab53,
        0x2748774cdf8eeb99,
        0x34b0bcb5e19b48a8,
        0x391c0cb3c5c95a63,
        0x4ed8aa4ae3418acb,
        0x5b9cca4f7763e373,
        0x682e6ff3d6b2b8a3,
        0x748f82ee5defb2fc,
        0x78a5636f43172f60,
        0x84c87814a1f0ab72,
        0x8cc702081a6439ec,
        0x90befffa23631e28,
        0xa4506cebde82bde9,
        0xbef9a3f7b2c67915,
        0xc67178f2e372532b,
        0xca273eceea26619c,
        0xd186b8c721c0c207,
        0xeada7dd6cde0eb1e,
        0xf57d4f7fee6ed178,
        0x06f067aa72176fba,
        0x0a637dc5a2c898a6,
        0x113f9804bef90dae,
        0x1b710b35131c471b,
        0x28db77f523047d84,
        0x32caab7b40c72493,
        0x3c9ebe0a15c9bebc,
        0x431d67c49c100d4c,
        0x4cc5d4becb3e42b6,
        0x597f299cfc657e2a,
        0x5fcb6fab3ad6faec,
        0x6c44198c4a475817,
    };

    uint64_t w[0x50], t0, t1;
    uint64_t s[sizeof(ctx->state) / sizeof(*ctx->state)];

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        s[i] = ctx->state[i];
    }

    /* copy the state into 1024-bits into W[0..15] */
    for (unsigned int i = 0x00; i != 0x10; ++i)
    {
        LOAD64H(w[i], buf + (i << 3));
    }

    /* fill W[16..79] */
    for (unsigned int i = 0x10; i != 0x50; ++i)
    {
        w[i] = Gamma1(w[i - 2]) + w[i - 7] + Gamma0(w[i - 15]) + w[i - 16];
    }

    /* compress */

#define RND(a, b, c, d, e, f, g, h, i)              \
    t0 = h + Sigma1(e) + Ch(e, f, g) + k[i] + w[i]; \
    t1 = Sigma0(a) + Maj(a, b, c);                  \
    d += t0;                                        \
    h = t0 + t1;

    for (unsigned int i = 0; i != 0x50; i += 8)
    {
        RND(s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7], i + 0);
        RND(s[7], s[0], s[1], s[2], s[3], s[4], s[5], s[6], i + 1);
        RND(s[6], s[7], s[0], s[1], s[2], s[3], s[4], s[5], i + 2);
        RND(s[5], s[6], s[7], s[0], s[1], s[2], s[3], s[4], i + 3);
        RND(s[4], s[5], s[6], s[7], s[0], s[1], s[2], s[3], i + 4);
        RND(s[3], s[4], s[5], s[6], s[7], s[0], s[1], s[2], i + 5);
        RND(s[2], s[3], s[4], s[5], s[6], s[7], s[0], s[1], i + 6);
        RND(s[1], s[2], s[3], s[4], s[5], s[6], s[7], s[0], i + 7);
    }

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

void a_sha512_init(a_sha512_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x6a09e667f3bcc908;
    ctx->state[1] = 0xbb67ae8584caa73b;
    ctx->state[2] = 0x3c6ef372fe94f82b;
    ctx->state[3] = 0xa54ff53a5f1d36f1;
    ctx->state[4] = 0x510e527fade682d1;
    ctx->state[5] = 0x9b05688c2b3e6c1f;
    ctx->state[6] = 0x1f83d9abfb41bd6b;
    ctx->state[7] = 0x5be0cd19137e2179;
}

void a_sha384_init(a_sha512_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0xcbbb9d5dc1059ed8;
    ctx->state[1] = 0x629a292a367cd507;
    ctx->state[2] = 0x9159015a3070dd17;
    ctx->state[3] = 0x152fecd8f70e5939;
    ctx->state[4] = 0x67332667ffc00b31;
    ctx->state[5] = 0x8eb44a8768581511;
    ctx->state[6] = 0xdb0c2e0d64f98fa7;
    ctx->state[7] = 0x47b5481dbefa4fa4;
}

void a_sha512_224_init(a_sha512_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x8C3D37C819544DA2;
    ctx->state[1] = 0x73E1996689DCD4D6;
    ctx->state[2] = 0x1DFAB7AE32FF9C82;
    ctx->state[3] = 0x679DD514582F9FCF;
    ctx->state[4] = 0x0F6D2B697BD44DA8;
    ctx->state[5] = 0x77E36F7304C48942;
    ctx->state[6] = 0x3F9D85A86A1D36C8;
    ctx->state[7] = 0x1112E6AD91D692A1;
}

void a_sha512_256_init(a_sha512_t *ctx)
{
    ctx->curlen = 0;
    ctx->length = 0;

    ctx->state[0] = 0x22312194FC2BF72C;
    ctx->state[1] = 0x9F555FA3C84C64C2;
    ctx->state[2] = 0x2393B86B6F53B151;
    ctx->state[3] = 0x963877195940EABD;
    ctx->state[4] = 0x96283EE2A88EFFE3;
    ctx->state[5] = 0xBE5E1E2553863992;
    ctx->state[6] = 0x2B0199FC2C85B8AA;
    ctx->state[7] = 0x0EB72DDC81C52CA2;
}

__A_HASH_PROCESS(a_sha512_t, a_sha512_process, a_sha512_compress)

unsigned char *a_sha512_done(a_sha512_t *ctx, unsigned char *out)
{
    if (sizeof(ctx->buf) - 1 < ctx->curlen)
    {
        return 0;
    }

    /* increase the length of the message */
    ctx->length += (ctx->curlen << 3);

    /* append the '1' bit */
    ctx->buf[ctx->curlen++] = 0x80;

    /* if the length is currently above 112 bytes we append zeros
     * then compress. Then we can fall back to padding zeros and length
     * encoding like normal.
     */
    if (0x70 < ctx->curlen)
    {
        while (ctx->curlen < 0x80)
        {
            ctx->buf[ctx->curlen++] = 0;
        }
        a_sha512_compress(ctx, ctx->buf);
        ctx->curlen = 0;
    }

    /* pad upto 120 bytes of zeroes
     * note: that from 112 to 120 is the 64 MSB of the length.  We assume that you won't hash
     * > 2^64 bits of data... :-)
     */
    while (ctx->curlen < 0x78)
    {
        ctx->buf[ctx->curlen++] = 0;
    }

    /* store length */
    STORE64H(ctx->length, ctx->buf + 0x78);
    a_sha512_compress(ctx, ctx->buf);

    /* copy output */
    for (unsigned int i = 0; i != sizeof(ctx->state) / sizeof(*ctx->state); ++i)
    {
        STORE64H(ctx->state[i], ctx->out + (i << 3));
    }
    if (out && out != ctx->out)
    {
        (void)memcpy(out, ctx->out, sizeof(ctx->state));
    }

    return ctx->out;
}

#define __A_SHA512_DONE(func, size)                          \
    unsigned char *func(a_sha512_t *ctx, unsigned char *out) \
    {                                                        \
        a_sha512_done(ctx, ctx->out);                        \
                                                             \
        if (out && out != ctx->out)                          \
        {                                                    \
            (void)memcpy(out, ctx->out, size);               \
        }                                                    \
                                                             \
        return ctx->out;                                     \
    }
__A_SHA512_DONE(a_sha384_done, A_SHA384_DIGESTSIZE)
__A_SHA512_DONE(a_sha512_224_done, A_SHA512_224_DIGESTSIZE)
__A_SHA512_DONE(a_sha512_256_done, A_SHA512_256_DIGESTSIZE)

#define __A_SHA512(func, size)                                       \
    unsigned char *func(const void *p, size_t n, unsigned char *out) \
    {                                                                \
        a_sha512_t ctx[1];                                           \
                                                                     \
        func##_init(ctx);                                            \
        a_sha512_process(ctx, p, n);                                 \
        func##_done(ctx, out);                                       \
                                                                     \
        if (0 == out && (out = (unsigned char *)a_alloc(size)))      \
        {                                                            \
            (void)memcpy(out, ctx->out, size);                       \
        }                                                            \
                                                                     \
        return out;                                                  \
    }
__A_SHA512(a_sha512, sizeof(ctx->state))
__A_SHA512(a_sha384, A_SHA384_DIGESTSIZE)
__A_SHA512(a_sha512_224, A_SHA512_224_DIGESTSIZE)
__A_SHA512(a_sha512_256, A_SHA512_256_DIGESTSIZE)

/* END OF FILE */
