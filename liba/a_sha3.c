/*!
 @file           a_sha3.c
 @brief          SHA3 implementation
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_sha3.h"

#include <string.h> /* memset, memcpy*/

#define SHA3_KECCAK_SPONGE_WORDS 25 /* 1600 bits -> 200 bytes -> (25 << 3) */

static const unsigned int keccakf_piln[24] = {
    /* clang-format off */
    0x0A, 0x07, 0x0B, 0x11, 0x12, 0x03, 0x05, 0x10,
    0x08, 0x15, 0x18, 0x04, 0x0F, 0x17, 0x13, 0x0D,
    0x0C, 0x02, 0x14, 0x0E, 0x16, 0x09, 0x06, 0x01,
    /* clang-format on */
};
static const unsigned int keccakf_rotc[24] = {
    /* clang-format off */
    0x01, 0x03, 0x06, 0x0A, 0x0F, 0x15, 0x1C, 0x24,
    0x2D, 0x37, 0x02, 0x0E, 0x1B, 0x29, 0x38, 0x08,
    0x19, 0x2B, 0x3E, 0x12, 0x27, 0x3D, 0x14, 0x2C,
    /* clang-format on */
};
static const uint64_t keccakf_rndc[24] = {
    /* clang-format off */
    0x0000000000000001, 0x0000000000008082, 0x800000000000808A, 0x8000000080008000,
    0x000000000000808B, 0x0000000080000001, 0x8000000080008081, 0x8000000000008009,
    0x000000000000008A, 0x0000000000000088, 0x0000000080008009, 0x000000008000000A,
    0x000000008000808B, 0x800000000000008B, 0x8000000000008089, 0x8000000000008003,
    0x8000000000008002, 0x8000000000000080, 0x000000000000800A, 0x800000008000000A,
    0x8000000080008081, 0x8000000000008080, 0x0000000080000001, 0x8000000080008008,
    /* clang-format on */
};

static inline void keccakf(uint64_t s[SHA3_KECCAK_SPONGE_WORDS])
{
    uint64_t bc[5], t;
    unsigned int i, j;

#undef KECCAK_ROUNDS
#define KECCAK_ROUNDS 24

    for (unsigned int round = 0; round != KECCAK_ROUNDS; ++round)
    {
        /* Theta */
        for (i = 0; i != 5; ++i)
        {
            bc[i] = s[i] ^ s[i + 5] ^ s[i + 10] ^ s[i + 15] ^ s[i + 20];
        }
        for (i = 0; i != 5; ++i)
        {
            t = bc[(i + 4) % 5] ^ ROL64(bc[(i + 1) % 5], 1);
            for (j = 0; j != SHA3_KECCAK_SPONGE_WORDS; j += 5)
            {
                s[j + i] ^= t;
            }
        }
        /* Rho Pi */
        t = s[1];
        for (i = 0; i != KECCAK_ROUNDS; ++i)
        {
            j = keccakf_piln[i];
            bc[0] = s[j];
            s[j] = ROL64(t, keccakf_rotc[i]);
            t = bc[0];
        }
        /* Chi */
        for (j = 0; j != SHA3_KECCAK_SPONGE_WORDS; j += 5)
        {
            for (i = 0; i != 5; ++i)
            {
                bc[i] = s[j + i];
            }
            for (i = 0; i != 5; ++i)
            {
                s[j + i] ^= (~bc[(i + 1) % 5]) & bc[(i + 2) % 5];
            }
        }
        /* Iota */
        s[0] ^= keccakf_rndc[round];
    }

#undef KECCAK_ROUNDS
}

static unsigned char *a_done(a_sha3_t *ctx, unsigned char *out, uint64_t pad)
{
    ctx->s[ctx->word_index] ^= (ctx->saved ^ (pad << (ctx->byte_index << 3)));
    ctx->s[SHA3_KECCAK_SPONGE_WORDS - 1 - ctx->capacity_words] ^= 0x8000000000000000;
    keccakf(ctx->s);

    /* store sha3.s[] as little-endian bytes into sha3.sb */
    for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
    {
        STORE64L(ctx->s[i], ctx->sb + (i << 3));
    }
    if (out && out != ctx->sb)
    {
        memcpy(out, ctx->sb, (unsigned int)ctx->capacity_words << 2);
    }

    return ctx->sb;
}

void a_sha3_224_init(a_sha3_t *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = (224 << 1) / (8 << 3);
}

void a_sha3_256_init(a_sha3_t *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = (256 << 1) / (8 << 3);
}

void a_sha3_384_init(a_sha3_t *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = (384 << 1) / (8 << 3);
}

void a_sha3_512_init(a_sha3_t *ctx)
{
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = (512 << 1) / (8 << 3);
}

int a_sha3_shake_init(a_sha3_t *ctx, unsigned int num)
{
    if (num != 0x80 && num != 0x100)
    {
        return -1;
    }
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = (unsigned short)((num << 1) / (8 << 3));
    return 0;
}

void a_sha3_process(a_sha3_t *ctx, const void *p, size_t n)
{
    const unsigned char *s = (const unsigned char *)p;

    if (0 == n) /* nothing to do */
    {
        return;
    }

    /* 0...7 -- how much is needed to have a word */
    unsigned int old_tail = (8 - ctx->byte_index) & 7;

    if (n < old_tail)
    {
        /* have no complete word or haven't started the word yet */
        while (n--)
        {
            ctx->saved |= (uint64_t)(*(s++)) << ((ctx->byte_index++) << 3);
        }
        return;
    }

    if (old_tail)
    {
        /* will have one word to process */
        n -= old_tail;
        while (old_tail--)
        {
            ctx->saved |= (uint64_t)(*(s++)) << ((ctx->byte_index++) << 3);
        }
        /* now ready to add saved to the sponge */
        ctx->s[ctx->word_index] ^= ctx->saved;
        ctx->byte_index = 0;
        ctx->saved = 0;
        if (++ctx->word_index == (SHA3_KECCAK_SPONGE_WORDS - ctx->capacity_words))
        {
            keccakf(ctx->s);
            ctx->word_index = 0;
        }
    }

    /* now work in full words directly from input */
    size_t words = n >> 3;
    for (size_t i = 0; i != words; ++i, s += 8)
    {
        uint64_t t;
        LOAD64L(t, s);
        ctx->s[ctx->word_index] ^= t;
        if (++ctx->word_index == (SHA3_KECCAK_SPONGE_WORDS - ctx->capacity_words))
        {
            keccakf(ctx->s);
            ctx->word_index = 0;
        }
    }

    /* finally, save the partial word */
    unsigned int tail = (unsigned int)(n % 8);
    while (tail--)
    {
        ctx->saved |= (uint64_t)(*(s++)) << ((ctx->byte_index++) << 3);
    }
}

unsigned char *a_sha3_done(a_sha3_t *ctx, unsigned char *out)
{
    return a_done(ctx, out, 0x06);
}

unsigned char *a_keccak_done(a_sha3_t *ctx, unsigned char *out)
{
    return a_done(ctx, out, 0x01);
}

#undef __A_SHA3
#define __A_SHA3(name, bit)                                                      \
    unsigned char *a_##name##_##bit(const void *p, size_t n, unsigned char *out) \
    {                                                                            \
        a_sha3_t ctx[1];                                                         \
                                                                                 \
        a_##name##_##bit##_init(ctx);                                            \
        a_sha3_process(ctx, p, n);                                               \
        a_##name##_done(ctx, out);                                               \
                                                                                 \
        if (0 == out && (out = (unsigned char *)a_alloc((bit) >> 3)))            \
        {                                                                        \
            memcpy(out, ctx->sb, (bit) >> 3);                                    \
        }                                                                        \
                                                                                 \
        return out;                                                              \
    }
__A_SHA3(sha3, 224)
__A_SHA3(sha3, 256)
__A_SHA3(sha3, 384)
__A_SHA3(sha3, 512)
__A_SHA3(keccak, 224)
__A_SHA3(keccak, 256)
__A_SHA3(keccak, 384)
__A_SHA3(keccak, 512)

void a_sha3_shake_done(a_sha3_t *ctx, unsigned char *out, unsigned int len)
{
    /* IMPORTANT NOTE: sha3_shake_done can be called many times */

    if (0 == len) /* nothing to do */
    {
        return;
    }

    if (!ctx->xof_flag)
    {
        /* shake_xof operation must be done only once */
        ctx->s[ctx->word_index] ^= (ctx->saved ^ (0x1FU << (ctx->byte_index << 3)));
        ctx->s[SHA3_KECCAK_SPONGE_WORDS - ctx->capacity_words - 1] ^= 0x8000000000000000;
        keccakf(ctx->s);
        /* store sha3.s[] as little-endian bytes into sha3.sb */
        for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
        {
            STORE64L(ctx->s[i], ctx->sb + (i << 3));
        }
        ctx->byte_index = 0;
        ctx->xof_flag = 1;
    }

    for (unsigned int idx = 0; idx != len; ++idx)
    {
        if (ctx->byte_index >= (SHA3_KECCAK_SPONGE_WORDS - ctx->capacity_words) << 3)
        {
            keccakf(ctx->s);
            /* store sha3.s[] as little-endian bytes into sha3.sb */
            for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
            {
                STORE64L(ctx->s[i], ctx->sb + (i << 3));
            }
            ctx->byte_index = 0;
        }
        out[idx] = ctx->sb[ctx->byte_index++];
    }
}

int a_sha3_shake(unsigned int num,
                 const void *p,
                 size_t n,
                 unsigned char *out,
                 unsigned int len)
{
    a_sha3_t ctx[1];

    int ret = -1;
    if (a_sha3_shake_init(ctx, num) == 0)
    {
        a_sha3_process(ctx, p, n);
        a_sha3_shake_done(ctx, out, len);
    }

    return ret;
}

/* END OF FILE */
