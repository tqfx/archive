/*!
 @file a_sha2.c
 @brief RFC 5754 compliant SHA2 implementation
 @details https://www.ietf.org/rfc/rfc5754.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_sha2.h"

#include "a_hash.h"

#undef Ch
#undef Maj
#undef S
#undef R
#undef Sigma0
#undef Sigma1
#undef Gamma0
#undef Gamma1

#undef RND
#define RND(_a, _b, _c, _d, _e, _f, _g, _h, _i)            \
    t0 = _h + Sigma1(_e) + Ch(_e, _f, _g) + k[_i] + w[_i]; \
    t1 = Sigma0(_a) + Maj(_a, _b, _c);                     \
    _d += t0;                                              \
    _h = t0 + t1;

/* Various logical functions */
#define S(_x, _n)       RORc((_x), (_n))
#define R(_x, _n)       (((_x)&0xFFFFFFFF) >> (_n))
#define Ch(_x, _y, _z)  (_z ^ (_x & (_y ^ _z)))
#define Maj(_x, _y, _z) (((_x | _y) & _z) | (_x & _y))
#define Sigma0(_x)      (S(_x, 2) ^ S(_x, 13) ^ S(_x, 22))
#define Sigma1(_x)      (S(_x, 6) ^ S(_x, 11) ^ S(_x, 25))
#define Gamma0(_x)      (S(_x, 7) ^ S(_x, 18) ^ R(_x, 3))
#define Gamma1(_x)      (S(_x, 17) ^ S(_x, 19) ^ R(_x, 10))

static void a_sha256_compress(a_sha256_s *_ctx, const unsigned char *_buf)
{
    static const uint32_t k[0x40] = {
        /* clang-format off */
        0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
        0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
        0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
        0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
        0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
        0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
        0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
        0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2,
        /* clang-format on */
    };

    uint32_t w[0x40], t0, t1;
    uint32_t s[sizeof(_ctx->state) / sizeof(*_ctx->state)];

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        s[i] = _ctx->state[i];
    }

    /* copy the state into 512-bits into w[0..15] */
    for (unsigned int i = 0x00; i != 0x10; ++i)
    {
        LOAD32H(w[i], _buf + sizeof(*_ctx->state) * i);
    }

    /* fill w[16..63] */
    for (unsigned int i = 0x10; i != 0x40; ++i)
    {
        w[i] = Gamma1(w[i - 2]) + w[i - 7] + Gamma0(w[i - 15]) + w[i - 16];
    }

    /* compress */
    for (unsigned int i = 0; i != 0x40; i += 8)
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

    /* feedback */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        _ctx->state[i] += s[i];
    }
}

#undef Ch
#undef Maj
#undef S
#undef R
#undef Sigma0
#undef Sigma1
#undef Gamma0
#undef Gamma1

/* Various logical functions */
#define S(_x, _n)       ROR64c(_x, _n)
#define R(_x, _n)       (((_x)&0xFFFFFFFFFFFFFFFF) >> (_n))
#define Ch(_x, _y, _z)  (_z ^ (_x & (_y ^ _z)))
#define Maj(_x, _y, _z) (((_x | _y) & _z) | (_x & _y))
#define Sigma0(_x)      (S(_x, 28) ^ S(_x, 34) ^ S(_x, 39))
#define Sigma1(_x)      (S(_x, 14) ^ S(_x, 18) ^ S(_x, 41))
#define Gamma0(_x)      (S(_x, 1) ^ S(_x, 8) ^ R(_x, 7))
#define Gamma1(_x)      (S(_x, 19) ^ S(_x, 61) ^ R(_x, 6))

static void a_sha512_compress(a_sha512_s *_ctx, const unsigned char *_buf)
{
    static const uint64_t k[0x50] = {
        /* clang-format off */
        0x428A2F98D728AE22, 0x7137449123EF65CD, 0xB5C0FBCFEC4D3B2F, 0xE9B5DBA58189DBBC,
        0x3956C25BF348B538, 0x59F111F1B605D019, 0x923F82A4AF194F9B, 0xAB1C5ED5DA6D8118,
        0xD807AA98A3030242, 0x12835B0145706FBE, 0x243185BE4EE4B28C, 0x550C7DC3D5FFB4E2,
        0x72BE5D74F27B896F, 0x80DEB1FE3B1696B1, 0x9BDC06A725C71235, 0xC19BF174CF692694,
        0xE49B69C19EF14AD2, 0xEFBE4786384F25E3, 0x0FC19DC68B8CD5B5, 0x240CA1CC77AC9C65,
        0x2DE92C6F592B0275, 0x4A7484AA6EA6E483, 0x5CB0A9DCBD41FBD4, 0x76F988DA831153B5,
        0x983E5152EE66DFAB, 0xA831C66D2DB43210, 0xB00327C898FB213F, 0xBF597FC7BEEF0EE4,
        0xC6E00BF33DA88FC2, 0xD5A79147930AA725, 0x06CA6351E003826F, 0x142929670A0E6E70,
        0x27B70A8546D22FFC, 0x2E1B21385C26C926, 0x4D2C6DFC5AC42AED, 0x53380D139D95B3DF,
        0x650A73548BAF63DE, 0x766A0ABB3C77B2A8, 0x81C2C92E47EDAEE6, 0x92722C851482353B,
        0xA2BFE8A14CF10364, 0xA81A664BBC423001, 0xC24B8B70D0F89791, 0xC76C51A30654BE30,
        0xD192E819D6EF5218, 0xD69906245565A910, 0xF40E35855771202A, 0x106AA07032BBD1B8,
        0x19A4C116B8D2D0C8, 0x1E376C085141AB53, 0x2748774CDF8EEB99, 0x34B0BCB5E19B48A8,
        0x391C0CB3C5C95A63, 0x4ED8AA4AE3418ACB, 0x5B9CCA4F7763E373, 0x682E6FF3D6B2B8A3,
        0x748F82EE5DEFB2FC, 0x78A5636F43172F60, 0x84C87814A1F0AB72, 0x8CC702081A6439EC,
        0x90BEFFFA23631E28, 0xA4506CEBDE82BDE9, 0xBEF9A3F7B2C67915, 0xC67178F2E372532B,
        0xCA273ECEEA26619C, 0xD186B8C721C0C207, 0xEADA7DD6CDE0EB1E, 0xF57D4F7FEE6ED178,
        0x06F067AA72176FBA, 0x0A637DC5A2C898A6, 0x113F9804BEF90DAE, 0x1B710B35131C471B,
        0x28DB77F523047D84, 0x32CAAB7B40C72493, 0x3C9EBE0A15C9BEBC, 0x431D67C49C100D4C,
        0x4CC5D4BECB3E42B6, 0x597F299CFC657E2A, 0x5FCB6FAB3AD6FAEC, 0x6C44198C4A475817,
        /* clang-format on */
    };

    uint64_t w[0x50], t0, t1;
    uint64_t s[sizeof(_ctx->state) / sizeof(*_ctx->state)];

    /* copy state into s */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        s[i] = _ctx->state[i];
    }

    /* copy the state into 1024-bits into w[0..15] */
    for (unsigned int i = 0x00; i != 0x10; ++i)
    {
        LOAD64H(w[i], _buf + sizeof(*_ctx->state) * i);
    }

    /* fill w[16..79] */
    for (unsigned int i = 0x10; i != 0x50; ++i)
    {
        w[i] = Gamma1(w[i - 2]) + w[i - 7] + Gamma0(w[i - 15]) + w[i - 16];
    }

    /* compress */
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

    /* feedback */
    for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)
    {
        _ctx->state[i] += s[i];
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
#undef RND

void a_sha256_init(a_sha256_s *_ctx)
{
    aassert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x6A09E667;
    _ctx->state[1] = 0xBB67AE85;
    _ctx->state[2] = 0x3C6EF372;
    _ctx->state[3] = 0xA54FF53A;
    _ctx->state[4] = 0x510E527F;
    _ctx->state[5] = 0x9B05688C;
    _ctx->state[6] = 0x1F83D9AB;
    _ctx->state[7] = 0x5BE0CD19;
}

void a_sha224_init(a_sha256_s *_ctx)
{
    aassert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0xC1059ED8;
    _ctx->state[1] = 0x367CD507;
    _ctx->state[2] = 0x3070DD17;
    _ctx->state[3] = 0xF70E5939;
    _ctx->state[4] = 0xFFC00B31;
    _ctx->state[5] = 0x68581511;
    _ctx->state[6] = 0x64F98FA7;
    _ctx->state[7] = 0xBEFA4FA4;
}

void a_sha512_init(a_sha512_s *_ctx)
{
    aassert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x6A09E667F3BCC908;
    _ctx->state[1] = 0xBB67AE8584CAA73B;
    _ctx->state[2] = 0x3C6EF372FE94F82B;
    _ctx->state[3] = 0xA54FF53A5F1D36F1;
    _ctx->state[4] = 0x510E527FADE682D1;
    _ctx->state[5] = 0x9B05688C2B3E6C1F;
    _ctx->state[6] = 0x1F83D9ABFB41BD6B;
    _ctx->state[7] = 0x5BE0CD19137E2179;
}

void a_sha384_init(a_sha512_s *_ctx)
{
    aassert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0xCBBB9D5DC1059ED8;
    _ctx->state[1] = 0x629A292A367CD507;
    _ctx->state[2] = 0x9159015A3070DD17;
    _ctx->state[3] = 0x152FECD8F70E5939;
    _ctx->state[4] = 0x67332667FFC00B31;
    _ctx->state[5] = 0x8EB44A8768581511;
    _ctx->state[6] = 0xDB0C2E0D64F98FA7;
    _ctx->state[7] = 0x47B5481DBEFA4FA4;
}

void a_sha512_224_init(a_sha512_s *_ctx)
{
    aassert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x8C3D37C819544DA2;
    _ctx->state[1] = 0x73E1996689DCD4D6;
    _ctx->state[2] = 0x1DFAB7AE32FF9C82;
    _ctx->state[3] = 0x679DD514582F9FCF;
    _ctx->state[4] = 0x0F6D2B697BD44DA8;
    _ctx->state[5] = 0x77E36F7304C48942;
    _ctx->state[6] = 0x3F9D85A86A1D36C8;
    _ctx->state[7] = 0x1112E6AD91D692A1;
}

void a_sha512_256_init(a_sha512_s *_ctx)
{
    aassert(_ctx);

    _ctx->cursiz = 0;
    _ctx->length = 0;

    _ctx->state[0] = 0x22312194FC2BF72C;
    _ctx->state[1] = 0x9F555FA3C84C64C2;
    _ctx->state[2] = 0x2393B86B6F53B151;
    _ctx->state[3] = 0x963877195940EABD;
    _ctx->state[4] = 0x96283EE2A88EFFE3;
    _ctx->state[5] = 0xBE5E1E2553863992;
    _ctx->state[6] = 0x2B0199FC2C85B8AA;
    _ctx->state[7] = 0x0EB72DDC81C52CA2;
}

__A_HASH_PROCESS(a_sha256_s, a_sha256_process, a_sha256_compress)
__A_HASH_PROCESS(a_sha512_s, a_sha512_process, a_sha512_compress)

__A_HASH_DONE(a_sha256_s, a_sha256_done, a_sha256_compress, STORE64H, STORE32H, 0x80, 0x38, 0x38)
__A_HASH_DONE(a_sha512_s, a_sha512_done, a_sha512_compress, STORE64H, STORE64H, 0x80, 0x70, 0x78)

#undef __A_SHA2_DONE
#define __A_SHA2_DONE(_bit, _func, _size)                         \
    unsigned char *_func(a_sha##_bit##_s *_ctx, void *_out)       \
    {                                                             \
        unsigned char *ret = a_sha##_bit##_done(_ctx, _ctx->out); \
                                                                  \
        if (ret && _out && (_out != _ctx->out))                   \
        {                                                         \
            memcpy(_out, _ctx->out, _size);                       \
        }                                                         \
                                                                  \
        return ret;                                               \
    }
__A_SHA2_DONE(256, a_sha224_done, 224 >> 3)
__A_SHA2_DONE(512, a_sha384_done, 382 >> 3)
__A_SHA2_DONE(512, a_sha512_224_done, 224 >> 3)
__A_SHA2_DONE(512, a_sha512_256_done, 256 >> 3)
#undef __A_SHA512_DONE

/* END OF FILE */
