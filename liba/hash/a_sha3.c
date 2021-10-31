/*!
 @file a_sha3.c
 @brief SHA3 implementation
 @details https://en.wikipedia.org/wiki/SHA-3
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_sha3.h"

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

__STATIC_INLINE
void keccakf(uint64_t _s[SHA3_KECCAK_SPONGE_WORDS])
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
            bc[i] = _s[i] ^ _s[i + 5] ^ _s[i + 10] ^ _s[i + 15] ^ _s[i + 20];
        }
        for (i = 0; i != 5; ++i)
        {
            t = bc[(i + 4) % 5] ^ ROL64(bc[(i + 1) % 5], 1);
            for (j = 0; j != SHA3_KECCAK_SPONGE_WORDS; j += 5)
            {
                _s[j + i] ^= t;
            }
        }
        /* Rho Pi */
        t = _s[1];
        for (i = 0; i != KECCAK_ROUNDS; ++i)
        {
            j = keccakf_piln[i];
            bc[0] = _s[j];
            _s[j] = ROL64(t, keccakf_rotc[i]);
            t = bc[0];
        }
        /* Chi */
        for (j = 0; j != SHA3_KECCAK_SPONGE_WORDS; j += 5)
        {
            for (i = 0; i != 5; ++i)
            {
                bc[i] = _s[j + i];
            }
            for (i = 0; i != 5; ++i)
            {
                _s[j + i] ^= (~bc[(i + 1) % 5]) & bc[(i + 2) % 5];
            }
        }
        /* Iota */
        _s[0] ^= keccakf_rndc[round];
    }

#undef KECCAK_ROUNDS
}

static unsigned char *a_done(a_sha3_t *_ctx, void *_out, uint64_t _pad)
{
    _ctx->s[_ctx->word_index] ^= (_ctx->saved ^ (_pad << (_ctx->byte_index << 3)));
    _ctx->s[SHA3_KECCAK_SPONGE_WORDS - 1 - _ctx->capacity_words] ^= 0x8000000000000000;
    keccakf(_ctx->s);

    /* store _ctx->s[] as little-endian bytes into _ctx->out */
    for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
    {
        STORE64L(_ctx->s[i], _ctx->out + sizeof(*_ctx->s) * i);
    }

    if (_out && (_out != _ctx->out))
    {
        memcpy(_out, _ctx->out, (unsigned int)_ctx->capacity_words << 2);
    }

    return _ctx->out;
}

/* ((2 * x) / (8 * 8)) -> ((x << 1) / (8 << 3)) -> (x >> 5) */

void a_sha3_224_init(a_sha3_t *_ctx)
{
    aassert(_ctx);

    memset(_ctx, 0, sizeof(*_ctx));
    _ctx->capacity_words = 224 >> 5;
}

void a_sha3_256_init(a_sha3_t *_ctx)
{
    aassert(_ctx);

    memset(_ctx, 0, sizeof(*_ctx));
    _ctx->capacity_words = 256 >> 5;
}

void a_sha3_384_init(a_sha3_t *_ctx)
{
    aassert(_ctx);

    memset(_ctx, 0, sizeof(*_ctx));
    _ctx->capacity_words = 384 >> 5;
}

void a_sha3_512_init(a_sha3_t *_ctx)
{
    aassert(_ctx);

    memset(_ctx, 0, sizeof(*_ctx));
    _ctx->capacity_words = 512 >> 5;
}

int a_sha3_process(a_sha3_t *_ctx, const void *_p, size_t _n)
{
    aassert(_ctx);
    aassert(!_n || _p);

    if (_n == 0) /* nothing to do */
    {
        return A_HASH_SUCCESS;
    }

    /* 0...7 -- how much is needed to have a word */
    unsigned int old_tail = (8 - _ctx->byte_index) & 7;
    const unsigned char *p = (const unsigned char *)_p;

    if (_n < old_tail)
    {
        /* have no complete word or haven't started the word yet */
        while (_n--)
        {
            _ctx->saved |= (uint64_t)(*(p++)) << ((_ctx->byte_index++) << 3);
        }
        return A_HASH_SUCCESS;
    }

    if (old_tail)
    {
        /* will have one word to process */
        _n -= old_tail;
        while (old_tail--)
        {
            _ctx->saved |= (uint64_t)(*(p++)) << ((_ctx->byte_index++) << 3);
        }
        /* now ready to add saved to the sponge */
        _ctx->s[_ctx->word_index] ^= _ctx->saved;
        _ctx->byte_index = 0;
        _ctx->saved = 0;
        if (++_ctx->word_index == (SHA3_KECCAK_SPONGE_WORDS - _ctx->capacity_words))
        {
            keccakf(_ctx->s);
            _ctx->word_index = 0;
        }
    }

    /* now work in full words directly from input */
    size_t words = _n >> 3;
    for (size_t i = 0; i != words; ++i, p += 8)
    {
        uint64_t t;
        LOAD64L(t, p);
        _ctx->s[_ctx->word_index] ^= t;
        if (++_ctx->word_index == (SHA3_KECCAK_SPONGE_WORDS - _ctx->capacity_words))
        {
            keccakf(_ctx->s);
            _ctx->word_index = 0;
        }
    }

    /* finally, save the partial word */
    unsigned int tail = (unsigned int)(_n % 8);
    while (tail--)
    {
        _ctx->saved |= (uint64_t)(*(p++)) << ((_ctx->byte_index++) << 3);
    }

    return A_HASH_SUCCESS;
}

unsigned char *a_sha3_done(a_sha3_t *_ctx, void *_out)
{
    aassert(_ctx);

    return a_done(_ctx, _out, 0x06);
}

unsigned char *a_keccak_done(a_sha3_t *_ctx, void *_out)
{
    aassert(_ctx);

    return a_done(_ctx, _out, 0x01);
}

void a_shake128_init(a_sha3_t *_ctx)
{
    aassert(_ctx);

    memset(_ctx, 0, sizeof(*_ctx));
    _ctx->capacity_words = 128 >> 5;
}

void a_shake256_init(a_sha3_t *_ctx)
{
    aassert(_ctx);

    memset(_ctx, 0, sizeof(*_ctx));
    _ctx->capacity_words = 256 >> 5;
}

int a_sha3shake_init(a_sha3_t *_ctx, unsigned int _num)
{
    aassert(_ctx);

    if (_num != 0x80 && _num != 0x100)
    {
        return A_HASH_INVALID;
    }

    memset(_ctx, 0, sizeof(*_ctx));
    _ctx->capacity_words = (unsigned short)(_num >> 5);

    return A_HASH_SUCCESS;
}

unsigned char *a_shake128_done(a_sha3_t *_ctx, void *_out)
{
    aassert(_ctx);

    a_sha3shake_done(_ctx, _ctx->out, 128 >> 3);
    if (_out && (_out != _ctx->out))
    {
        memcpy(_out, _ctx->out, 128 >> 3);
    }

    return _ctx->out;
}

unsigned char *a_shake256_done(a_sha3_t *_ctx, void *_out)
{
    aassert(_ctx);

    a_sha3shake_done(_ctx, _ctx->out, 256 >> 3);
    if (_out && (_out != _ctx->out))
    {
        memcpy(_out, _ctx->out, 256 >> 3);
    }

    return _ctx->out;
}

void a_sha3shake_done(a_sha3_t *_ctx, unsigned char *_out, unsigned int _siz)
{
    /* IMPORTANT NOTE: a_sha3shake_done can be called many times */
    aassert(_ctx);
    aassert(!_siz || _out);

    if (_siz == 0) /* nothing to do */
    {
        return;
    }

    if (!_ctx->xof_flag)
    {
        /* shake_xof operation must be done only once */
        _ctx->s[_ctx->word_index] ^= (_ctx->saved ^ (0x1FU << (_ctx->byte_index << 3)));
        _ctx->s[SHA3_KECCAK_SPONGE_WORDS - _ctx->capacity_words - 1] ^= 0x8000000000000000;
        keccakf(_ctx->s);
        /* store _ctx->s[] as little-endian bytes into _ctx->out */
        for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
        {
            STORE64L(_ctx->s[i], _ctx->out + sizeof(*_ctx->s) * i);
        }
        _ctx->byte_index = 0;
        _ctx->xof_flag = 1;
    }

    for (unsigned int idx = 0; idx != _siz; ++idx)
    {
        if (_ctx->byte_index >= (SHA3_KECCAK_SPONGE_WORDS - _ctx->capacity_words) << 3)
        {
            keccakf(_ctx->s);
            /* store _ctx->s[] as little-endian bytes into _ctx->out */
            for (unsigned int i = 0; i != SHA3_KECCAK_SPONGE_WORDS; ++i)
            {
                STORE64L(_ctx->s[i], _ctx->out + sizeof(*_ctx->s) * i);
            }
            _ctx->byte_index = 0;
        }
        _out[idx] = _ctx->out[_ctx->byte_index++];
    }
}

/* END OF FILE */
