/*!
 @file           a_hash_sha3.c
 @brief          SHA3 implementation
 @details        https://en.wikipedia.org/wiki/SHA-3
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_hash_sha3.h"
#include "a_hash.h"

#undef SHA3_KECCAK_SPONGE_WORDS
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

static __INLINE void keccakf(uint64_t s[SHA3_KECCAK_SPONGE_WORDS])
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

static unsigned char *a_done(a_sha3_t *ctx, void *out, uint64_t pad)
{
    ctx->s[ctx->word_index] ^= (ctx->saved ^ (pad << (ctx->byte_index << 3)));
    ctx->s[SHA3_KECCAK_SPONGE_WORDS - 1 - ctx->capacity_words] ^= 0x8000000000000000;
    keccakf(ctx->s);

    /* store ctx->s[] as little-endian bytes into ctx->out */
    for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
    {
        STORE64L(ctx->s[i], ctx->out + sizeof(*ctx->s) * i);
    }

    if (out && (out != ctx->out))
    {
        memcpy(out, ctx->out, (unsigned int)ctx->capacity_words << 2);
    }

    return ctx->out;
}

/* ((2 * x) / (8 * 8)) -> ((x << 1) / (8 << 3)) -> (x >> 5) */

void a_sha3_224_init(a_sha3_t *ctx)
{
    /* assert(ctx) */
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = 224 >> 5;
}

void a_sha3_256_init(a_sha3_t *ctx)
{
    /* assert(ctx) */
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = 256 >> 5;
}

void a_sha3_384_init(a_sha3_t *ctx)
{
    /* assert(ctx) */
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = 384 >> 5;
}

void a_sha3_512_init(a_sha3_t *ctx)
{
    /* assert(ctx) */
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = 512 >> 5;
}

int a_sha3_process(a_sha3_t *ctx, const void *p, size_t n)
{
    /* assert(ctx) */
    /* assert(!n || p) */
    if (0 == n) /* nothing to do */
    {
        return A_HASH_SUCCESS;
    }

    /* 0...7 -- how much is needed to have a word */
    unsigned int old_tail = (8 - ctx->byte_index) & 7;
    const unsigned char *s = (const unsigned char *)p;

    if (n < old_tail)
    {
        /* have no complete word or haven't started the word yet */
        while (n--)
        {
            ctx->saved |= (uint64_t)(*(s++)) << ((ctx->byte_index++) << 3);
        }
        return A_HASH_SUCCESS;
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

    return A_HASH_SUCCESS;
}

unsigned char *a_sha3_done(a_sha3_t *ctx, void *out)
{
    /* assert(ctx) */
    return a_done(ctx, out, 0x06);
}

unsigned char *a_keccak_done(a_sha3_t *ctx, void *out)
{
    /* assert(ctx) */
    return a_done(ctx, out, 0x01);
}

void a_shake128_init(a_sha3_t *ctx)
{
    /* assert(ctx) */
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = 128 >> 5;
}

void a_shake256_init(a_sha3_t *ctx)
{
    /* assert(ctx) */
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = 256 >> 5;
}

int a_sha3shake_init(a_sha3_t *ctx, unsigned int num)
{
    /* assert(ctx) */
    if (num != 0x80 && num != 0x100)
    {
        return A_HASH_INVALID;
    }
    memset(ctx, 0, sizeof(*ctx));
    ctx->capacity_words = (unsigned short)(num >> 5);
    return A_HASH_SUCCESS;
}

unsigned char *a_shake128_done(a_sha3_t *ctx, void *out)
{
    /* assert(ctx) */
    a_sha3shake_done(ctx, ctx->out, 128 >> 3);
    if (out && (out != ctx->out))
    {
        memcpy(out, ctx->out, 128 >> 3);
    }
    return ctx->out;
}

unsigned char *a_shake256_done(a_sha3_t *ctx, void *out)
{
    /* assert(ctx) */
    a_sha3shake_done(ctx, ctx->out, 256 >> 3);
    if (out && (out != ctx->out))
    {
        memcpy(out, ctx->out, 256 >> 3);
    }
    return ctx->out;
}

void a_sha3shake_done(a_sha3_t *ctx, unsigned char *out, unsigned int siz)
{
    /* IMPORTANT NOTE: a_sha3shake_done can be called many times */
    /* assert(ctx) */
    /* assert(!siz || out) */
    if (0 == siz) /* nothing to do */
    {
        return;
    }

    if (!ctx->xof_flag)
    {
        /* shake_xof operation must be done only once */
        ctx->s[ctx->word_index] ^= (ctx->saved ^ (0x1FU << (ctx->byte_index << 3)));
        ctx->s[SHA3_KECCAK_SPONGE_WORDS - ctx->capacity_words - 1] ^= 0x8000000000000000;
        keccakf(ctx->s);
        /* store ctx->s[] as little-endian bytes into ctx->out */
        for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
        {
            STORE64L(ctx->s[i], ctx->out + sizeof(*ctx->s) * i);
        }
        ctx->byte_index = 0;
        ctx->xof_flag = 1;
    }

    for (unsigned int idx = 0; idx != siz; ++idx)
    {
        if (ctx->byte_index >= (SHA3_KECCAK_SPONGE_WORDS - ctx->capacity_words) << 3)
        {
            keccakf(ctx->s);
            /* store ctx->s[] as little-endian bytes into ctx->out */
            for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
            {
                STORE64L(ctx->s[i], ctx->out + sizeof(*ctx->s) * i);
            }
            ctx->byte_index = 0;
        }
        out[idx] = ctx->out[ctx->byte_index++];
    }
}

/* END OF FILE */
