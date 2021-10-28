/*!
 @file           a_hash.h
 @brief          hash library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_HASH_H__
#define __A_HASH_H__

#include "liba.h"

#include <string.h> /* memset, memcpy */

#include "a_md2.h"
#include "a_md4.h"
#include "a_md5.h"
#include "a_rmd.h"
#include "a_sha1.h"
#include "a_sha2.h"
#include "a_sha3.h"
#include "a_tiger.h"
#include "a_whirl.h"
#include "a_blake2s.h"
#include "a_blake2b.h"

/*!
    shake128    0xA8    168
    sha3-224    0x90    144
*/
#define A_HASH_BUFSIZ 0xA8

enum
{
    A_HASH_SUCCESS = A_SUCCESS,
    A_HASH_WARNING = A_WARNING,
    A_HASH_FAILURE = A_FAILURE,
    A_HASH_INVALID = A_INVALID,
    A_HASH_OVERFLOW = A_OVERFLOW,
    A_HASH_NOTFOUND = A_NOTFOUND,
};

typedef union a_hash_stat_t
{
    int state;
#if defined(__A_HASH_MD2_H__)
    a_md2_t md2[1];
#endif /* __A_HASH_MD2_H__ */
#if defined(__A_HASH_MD4_H__)
    a_md4_t md4[1];
#endif /* __A_HASH_MD4_H__ */
#if defined(__A_HASH_MD5_H__)
    a_md5_t md5[1];
#endif /* __A_HASH_MD5_H__ */
#if defined(__A_HASH_RMD_H__)
    a_rmd128_t rmd128[1];
    a_rmd160_t rmd160[1];
    a_rmd256_t rmd256[1];
    a_rmd320_t rmd320[1];
#endif /* __A_HASH_RMD_H__ */
#if defined(__A_HASH_SHA1_H__)
    a_sha1_t sha1[1];
#endif /* __A_HASH_SHA1_H__ */
#if defined(__A_HASH_SHA2_H__)
    a_sha256_t sha256[1];
    a_sha512_t sha512[1];
#endif /* __A_HASH_SHA2_H__ */
#if defined(__A_HASH_SHA3_H__)
    a_sha3_t sha3[1];
#endif /* __A_HASH_SHA3_H__ */
#if defined(__A_HASH_TIGER_H__)
    a_tiger_t tiger[1];
#endif /* __A_HASH_TIGER_H__ */
#if defined(__A_HASH_BLAKE2S_H__)
    a_blake2s_t blake2s[1];
#endif /* __A_HASH_BLAKE2S_H__ */
#if defined(__A_HASH_BLAKE2B_H__)
    a_blake2b_t blake2b[1];
#endif /* __A_HASH_BLAKE2B_H__ */
#if defined(__A_HASH_WHIRL_H__)
    a_whirlpool_t whirlpool[1];
#endif /* __A_HASH_WHIRL_H__ */
} a_hash_stat_t;

typedef struct a_hash_t
{
    /*!< size of block */
    unsigned int bufsiz;
    /*!< size of digest */
    unsigned int outsiz;
    /*!
     @brief          Initialize function for hash.
     @param[in,out]  ctx: points to an instance of hash state.
    */
    void (*init)(a_hash_stat_t *ctx) __NONNULL_ALL;
    /*!
     @brief          Process function for hash.
     @param[in,out]  ctx: points to an instance of hash state.
     @param[in]      p: points to data to hash.
     @param[in]      n: length of data to hash.
     @return         the execution state of the function.
      @retval        0 success
    */
    int (*process)(a_hash_stat_t *ctx, const void *p, size_t n) __NONNULL((1));
    /*!
     @brief          Terminate function for hash.
     @param[in,out]  ctx: points to an instance of hash state.
     @param[in,out]  out: points to buffer that holds the digest.
     @return         p the digest internal buffer.
      @retval        0 generic invalid argument.
    */
    unsigned char *(*done)(a_hash_stat_t *ctx, void *out)__NONNULL((1));
} a_hash_t;

__BEGIN_DECLS

#if defined(__A_HASH_MD2_H__)
extern const a_hash_t a_hash_md2;
#endif /* __A_HASH_MD2_H__ */
#if defined(__A_HASH_MD4_H__)
extern const a_hash_t a_hash_md4;
#endif /* __A_HASH_MD4_H__ */
#if defined(__A_HASH_MD5_H__)
extern const a_hash_t a_hash_md5;
#endif /* __A_HASH_MD5_H__ */
#if defined(__A_HASH_RMD_H__)
extern const a_hash_t a_hash_rmd128;
extern const a_hash_t a_hash_rmd160;
extern const a_hash_t a_hash_rmd256;
extern const a_hash_t a_hash_rmd320;
#endif /* __A_HASH_RMD_H__ */
#if defined(__A_HASH_SHA1_H__)
extern const a_hash_t a_hash_sha1;
#endif /* __A_HASH_SHA1_H__ */
#if defined(__A_HASH_SHA2_H__)
extern const a_hash_t a_hash_sha224;
extern const a_hash_t a_hash_sha256;
extern const a_hash_t a_hash_sha384;
extern const a_hash_t a_hash_sha512;
extern const a_hash_t a_hash_sha512_224;
extern const a_hash_t a_hash_sha512_256;
#endif /* __A_HASH_SHA2_H__ */
#if defined(__A_HASH_SHA3_H__)
extern const a_hash_t a_hash_sha3_224;
extern const a_hash_t a_hash_sha3_256;
extern const a_hash_t a_hash_sha3_384;
extern const a_hash_t a_hash_sha3_512;
extern const a_hash_t a_hash_shake128;
extern const a_hash_t a_hash_shake256;
extern const a_hash_t a_hash_keccak224;
extern const a_hash_t a_hash_keccak256;
extern const a_hash_t a_hash_keccak384;
extern const a_hash_t a_hash_keccak512;
#endif /* __A_HASH_SHA3_H__ */
#if defined(__A_HASH_TIGER_H__)
extern const a_hash_t a_hash_tiger;
#endif /* __A_HASH_TIGER_H__ */
#if defined(__A_HASH_BLAKE2S_H__)
extern const a_hash_t a_hash_blake2s_128;
extern const a_hash_t a_hash_blake2s_160;
extern const a_hash_t a_hash_blake2s_224;
extern const a_hash_t a_hash_blake2s_256;
#endif /* __A_HASH_BLAKE2S_H__ */
#if defined(__A_HASH_BLAKE2B_H__)
extern const a_hash_t a_hash_blake2b_160;
extern const a_hash_t a_hash_blake2b_256;
extern const a_hash_t a_hash_blake2b_384;
extern const a_hash_t a_hash_blake2b_512;
#endif /* __A_HASH_BLAKE2B_H__ */
#if defined(__A_HASH_WHIRL_H__)
extern const a_hash_t a_hash_whirlpool;
#endif /* __A_HASH_WHIRL_H__ */

__END_DECLS

#undef __A_HASH_PROCESS
#define __A_HASH_PROCESS(_hash, _func, _compress)                    \
    int _func(_hash *_ctx, const void *_p, size_t _n)                \
    {                                                                \
        a_assert(_ctx);                                              \
        a_assert(!_n || _p);                                         \
        if (sizeof(_ctx->buf) < _ctx->cursiz)                        \
        {                                                            \
            return A_HASH_INVALID;                                   \
        }                                                            \
        if (_ctx->length + (_n << 3) < _ctx->length)                 \
        {                                                            \
            return A_HASH_OVERFLOW;                                  \
        }                                                            \
        const unsigned char *p = (const unsigned char *)_p;          \
        while (_n)                                                   \
        {                                                            \
            if ((0 == _ctx->cursiz) && (sizeof(_ctx->buf) - 1 < _n)) \
            {                                                        \
                _compress(_ctx, p);                                  \
                _ctx->length += sizeof(_ctx->buf) << 3;              \
                _n -= sizeof(_ctx->buf);                             \
                p += sizeof(_ctx->buf);                              \
            }                                                        \
            else                                                     \
            {                                                        \
                uint32_t n = sizeof(_ctx->buf) - _ctx->cursiz;       \
                n = n < _n ? n : (uint32_t)_n;                       \
                memcpy(_ctx->buf + _ctx->cursiz, p, n);              \
                _ctx->cursiz += n;                                   \
                _n -= n;                                             \
                p += n;                                              \
                if (sizeof(_ctx->buf) == _ctx->cursiz)               \
                {                                                    \
                    _compress(_ctx, _ctx->buf);                      \
                    _ctx->length += sizeof(_ctx->buf) << 3;          \
                    _ctx->cursiz = 0;                                \
                }                                                    \
            }                                                        \
        }                                                            \
        return A_HASH_SUCCESS;                                       \
    }

#undef __A_HASH_DONE
#define __A_HASH_DONE(_hash, _func, _compress, _storelen, _storeout, _append, _above, _zero) \
    unsigned char *_func(_hash *_ctx, void *_out)                                            \
    {                                                                                        \
        a_assert(_ctx);                                                                      \
        if (sizeof(_ctx->buf) - 1 < _ctx->cursiz)                                            \
        {                                                                                    \
            return 0;                                                                        \
        }                                                                                    \
        /* increase the length of the message */                                             \
        _ctx->length += sizeof(_ctx->length) * _ctx->cursiz;                                 \
        /* append the '1' bit */                                                             \
        _ctx->buf[_ctx->cursiz++] = _append;                                                 \
        /* if the length is currently above _above bytes we append zeros    */               \
        /* then compress. Then we can fall back to padding zeros and length */               \
        /* encoding like normal.                                            */               \
        if ((_above) < _ctx->cursiz)                                                         \
        {                                                                                    \
            while (sizeof(_ctx->buf) != _ctx->cursiz)                                        \
            {                                                                                \
                _ctx->buf[_ctx->cursiz++] = 0;                                               \
            }                                                                                \
            _compress(_ctx, _ctx->buf);                                                      \
            _ctx->cursiz = 0;                                                                \
        }                                                                                    \
        /* pad up to _zero bytes of zeroes */                                                \
        while (_ctx->cursiz < (_zero))                                                       \
        {                                                                                    \
            _ctx->buf[_ctx->cursiz++] = 0;                                                   \
        }                                                                                    \
        /* store length */                                                                   \
        _storelen(_ctx->length, _ctx->buf + (_zero));                                        \
        _compress(_ctx, _ctx->buf);                                                          \
        /* copy output */                                                                    \
        for (unsigned int i = 0; i != sizeof(_ctx->state) / sizeof(*_ctx->state); ++i)       \
        {                                                                                    \
            _storeout(_ctx->state[i], _ctx->out + sizeof(*_ctx->state) * i);                 \
        }                                                                                    \
        if (_out && (_out != _ctx->out))                                                     \
        {                                                                                    \
            memcpy(_out, _ctx->out, sizeof(_ctx->state));                                    \
        }                                                                                    \
        return _ctx->out;                                                                    \
    }

/* Enddef to prevent recursive inclusion */
#endif /* __A_HASH_H__ */

/* END OF FILE */
