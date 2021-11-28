/*!
 @file a_hmac_util.c
 @brief hmac library utils
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_hmac_util.h"

#include <stdarg.h>

int a_hmac_memory(const a_hash_s *_ctx,
                  const void *_key, size_t _keysiz,
                  const void *_msg, size_t _msgsiz,
                  void *_out, size_t *_siz)
{
    aassert(_ctx);
    aassert(_out);
    aassert(_siz);
    aassert(!_keysiz || _key);
    aassert(!_msgsiz || _msg);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    a_hmac_s ctx[1];

    if (a_hmac_init(ctx, _ctx, _key, _keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    if (a_hmac_process(ctx, _msg, _msgsiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    *_siz = a_hmac_done(ctx, _out) ? _ctx->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_mmulti(const a_hash_s *_ctx,
                  void *_out, size_t *_siz,
                  const void *_key, size_t _keysiz,
                  const void *_msg, size_t _msgsiz, ...)
{
    aassert(_ctx);
    aassert(_out);
    aassert(_siz);
    aassert(!_keysiz || _key);
    aassert(!_msgsiz || _msg);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    va_list arg;
    a_hmac_s ctx[1];
    va_start(arg, _msgsiz);

    if (a_hmac_init(ctx, _ctx, _key, _keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    for (;;)
    {
        if (a_hmac_process(ctx, _msg, _msgsiz) != A_HMAC_SUCCESS)
        {
            va_end(arg);
            return A_HMAC_FAILURE;
        }
        _msg = va_arg(arg, const void *);
        if (_msg == 0)
        {
            va_end(arg);
            break;
        }
        _msgsiz = va_arg(arg, size_t);
    };
    *_siz = a_hmac_done(ctx, _out) ? _ctx->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_filehandle(const a_hash_s *_ctx,
                      const void *_key, size_t _keysiz, FILE *_in,
                      void *_out, size_t *_siz)
{
    aassert(_in);
    aassert(_ctx);
    aassert(_out);
    aassert(_siz);
    aassert(!_keysiz || _key);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    a_hmac_s ctx[1];

    if (a_hmac_init(ctx, _ctx, _key, _keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    do
    {
        char buf[BUFSIZ];
        *_siz = fread(buf, 1, BUFSIZ, _in);
        if (a_hmac_process(ctx, buf, *_siz) != A_HMAC_SUCCESS)
        {
            return A_HMAC_FAILURE;
        }
    } while (*_siz == BUFSIZ);
    *_siz = a_hmac_done(ctx, _out) ? _ctx->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_file(const a_hash_s *_ctx,
                const void *_key, size_t _keysiz, const char *_fname,
                void *_out, size_t *_siz)
{
    aassert(_ctx);
    aassert(_out);
    aassert(_siz);
    aassert(_fname);
    aassert(!_keysiz || _key);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    FILE *in = fopen(_fname, "rb");
    if (in == 0)
    {
        return A_HMAC_NOTFOUND;
    }

    int ret = a_hmac_filehandle(_ctx, _key, _keysiz, in, _out, _siz);

    if (fclose(in))
    {
        return A_HMAC_FAILURE;
    }

    return ret;
}

/* END OF FILE */
