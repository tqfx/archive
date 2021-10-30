/*!
 @file a_hash_util.c
 @brief hash library utils
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_hash_util.h"

#include <stdarg.h>

int a_hash_memory(const a_hash_t *_ctx, const void *_p, size_t _n, void *_out, size_t *_siz)
{
    aassert(_ctx);
    aassert(_out);
    aassert(_siz);
    aassert(!_n || _p);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    a_hash_stat_t stat[1];

    _ctx->init(stat);
    if (_ctx->process(stat, _p, _n) != A_HASH_SUCCESS)
    {
        return A_HASH_FAILURE;
    }
    *_siz = _ctx->done(stat, _out) ? _ctx->outsiz : 0;

    return A_HASH_SUCCESS;
}

int a_hash_mmulti(const a_hash_t *_ctx, void *_out, size_t *_siz, const void *_p, size_t _n, ...)
{
    aassert(_ctx);
    aassert(_out);
    aassert(_siz);
    aassert(!_n || _p);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    va_list arg;
    va_start(arg, _n);
    a_hash_stat_t stat[1];

    _ctx->init(stat);
    for (;;)
    {
        if (_ctx->process(stat, _p, _n) != A_HASH_SUCCESS)
        {
            va_end(arg);
            return A_HASH_FAILURE;
        }
        _p = va_arg(arg, const void *);
        if (0 == _p)
        {
            va_end(arg);
            break;
        }
        _n = va_arg(arg, size_t);
    };
    *_siz = _ctx->done(stat, _out) ? _ctx->outsiz : 0;

    return A_HASH_SUCCESS;
}

int a_hash_filehandle(const a_hash_t *_ctx, FILE *_in, void *_out, size_t *_siz)
{
    aassert(_in);
    aassert(_ctx);
    aassert(_out);
    aassert(_siz);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    a_hash_stat_t stat[1];

    char buf[BUFSIZ];
    _ctx->init(stat);
    do
    {
        *_siz = fread(buf, 1, BUFSIZ, _in);
        _ctx->process(stat, buf, *_siz);
    } while (*_siz == BUFSIZ);
    *_siz = _ctx->done(stat, _out) ? _ctx->outsiz : 0;

    return A_HASH_SUCCESS;
}

int a_hash_file(const a_hash_t *_ctx, const char *_fname, void *_out, size_t *_siz)
{
    aassert(_ctx);
    aassert(_out);
    aassert(_siz);
    aassert(_fname);

    if (*_siz < _ctx->outsiz)
    {
        *_siz = _ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    FILE *in = fopen(_fname, "rb");
    if (0 == in)
    {
        return A_HASH_NOTFOUND;
    }

    int ret = a_hash_filehandle(_ctx, in, _out, _siz);

    if (fclose(in))
    {
        return A_HASH_FAILURE;
    }

    return ret;
}

/* END OF FILE */
