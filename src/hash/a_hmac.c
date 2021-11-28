/*!
 @file a_hmac.c
 @brief RFC 2104 compliant HMAC implementation
 @details https://www.ietf.org/rfc/rfc2104.txt
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_hmac.h"

#undef A_HMAC_IPAD
#undef A_HMAC_OPAD
#define A_HMAC_IPAD 0x36
#define A_HMAC_OPAD 0x5c

int a_hmac_init(a_hmac_s *_ctx, const a_hash_s *_hash, const void *_p, size_t _n)
{
    aassert(_ctx);
    aassert(_hash);
    aassert(!_n || _p);

    if (sizeof(_ctx->buf) < _hash->bufsiz)
    {
        return A_HMAC_OVERFLOW;
    }

    _ctx->hash = _hash;
    _ctx->outsiz = _ctx->hash->outsiz;

    if (_ctx->hash->bufsiz < _n)
    {
        _ctx->hash->init(_ctx->state);
        if (_ctx->hash->process(_ctx->state, _p, _n) != A_HASH_SUCCESS)
        {
            return A_HMAC_FAILURE;
        }
        if (_ctx->hash->done(_ctx->state, _ctx->buf) == 0)
        {
            return A_HMAC_FAILURE;
        }
        _n = _ctx->hash->outsiz;
    }
    else if (_n)
    {
        memcpy(_ctx->buf, _p, _n);
    }

    if (_n < _ctx->hash->bufsiz)
    {
        memset(_ctx->buf + _n, 0, sizeof(_ctx->buf) - _n);
    }

    unsigned char buf[sizeof(_ctx->buf)];
    for (unsigned int i = 0; i != _ctx->hash->bufsiz; ++i)
    {
        buf[i] = _ctx->buf[i] ^ A_HMAC_IPAD;
    }

    _ctx->hash->init(_ctx->state);
    return _ctx->hash->process(_ctx->state, buf, _ctx->hash->bufsiz);
}

int a_hmac_process(a_hmac_s *_ctx, const void *_p, size_t _n)
{
    aassert(_ctx);
    aassert(!_n || _p);

    return _ctx->hash->process(_ctx->state, _p, _n);
}

unsigned char *a_hmac_done(a_hmac_s *_ctx, void *_out)
{
    aassert(_ctx);

    unsigned char buf[sizeof(_ctx->buf)];

    if (_ctx->hash->done(_ctx->state, buf) == 0)
    {
        return 0;
    }

    for (unsigned int i = 0; i != _ctx->hash->bufsiz; ++i)
    {
        _ctx->buf[i] ^= A_HMAC_OPAD;
    }

    _ctx->hash->init(_ctx->state);
    if (_ctx->hash->process(_ctx->state, _ctx->buf, _ctx->hash->bufsiz) != A_HASH_SUCCESS)
    {
        return 0;
    }
    if (_ctx->hash->process(_ctx->state, buf, _ctx->hash->outsiz) != A_HASH_SUCCESS)
    {
        return 0;
    }
    if (_ctx->hash->done(_ctx->state, _ctx->buf) == 0)
    {
        return 0;
    }

    if (_out && _out != _ctx->buf)
    {
        memcpy(_out, _ctx->buf, _ctx->hash->outsiz);
    }

    return _ctx->buf;
}

#undef A_HMAC_IPAD
#undef A_HMAC_OPAD

/* END OF FILE */
