/*!
 @file           a_hmac_util.c
 @brief          hmac library utils
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_hmac_util.h"

#include <stdarg.h>

int a_hmac_memory(const a_hash_t *_ctx,
                  const void *_key,
                  size_t _keysiz,
                  const void *_msg,
                  size_t _msgsiz,
                  void *_out,
                  size_t *_siz)
{
    a_assert(_ctx);
    a_assert(_out);
    a_assert(_siz);
    a_assert(!_keysiz || _key);
    a_assert(!_msgsiz || _msg);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    a_hmac_t stat[1];

    if (a_hmac_init(stat, _ctx, _key, _keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    if (a_hmac_process(stat, _msg, _msgsiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    *_siz = a_hmac_done(stat, _out) ? _ctx->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_mmulti(const a_hash_t *_ctx,
                  void *_out,
                  size_t *_siz,
                  const void *_key,
                  size_t _keysiz,
                  const void *_msg,
                  size_t _msgsiz,
                  ...)
{
    a_assert(_ctx);
    a_assert(_out);
    a_assert(_siz);
    a_assert(!_keysiz || _key);
    a_assert(!_msgsiz || _msg);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    va_list arg;
    a_hmac_t stat[1];
    va_start(arg, _msgsiz);

    if (a_hmac_init(stat, _ctx, _key, _keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    for (;;)
    {
        if (a_hmac_process(stat, _msg, _msgsiz) != A_HMAC_SUCCESS)
        {
            va_end(arg);
            return A_HMAC_FAILURE;
        }
        _msg = va_arg(arg, const void *);
        if (0 == _msg)
        {
            va_end(arg);
            break;
        }
        _msgsiz = va_arg(arg, size_t);
    };
    *_siz = a_hmac_done(stat, _out) ? _ctx->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_filehandle(const a_hash_t *_ctx,
                      const void *_key,
                      size_t _keysiz,
                      FILE *_in,
                      void *_out,
                      size_t *_siz)
{
    a_assert(_in);
    a_assert(_ctx);
    a_assert(_out);
    a_assert(_siz);
    a_assert(!_keysiz || _key);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    a_hmac_t stat[1];
    char buf[BUFSIZ];

    if (a_hmac_init(stat, _ctx, _key, _keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    do
    {
        *_siz = fread(buf, 1, BUFSIZ, _in);
        if (a_hmac_process(stat, buf, *_siz) != A_HMAC_SUCCESS)
        {
            return A_HMAC_FAILURE;
        }
    } while (*_siz == BUFSIZ);
    *_siz = a_hmac_done(stat, _out) ? _ctx->outsiz : 0;

    return A_HMAC_SUCCESS;
}

int a_hmac_file(const a_hash_t *_ctx,
                const void *_key,
                size_t _keysiz,
                const char *_fname,
                void *_out,
                size_t *_siz)
{
    a_assert(_ctx);
    a_assert(_out);
    a_assert(_siz);
    a_assert(_fname);
    a_assert(!_keysiz || _key);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    FILE *in = fopen(_fname, "rb");
    if (0 == in)
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
