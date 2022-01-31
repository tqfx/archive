/*!
 @file a_hash_util.c
 @brief hash library utils
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_hash_util.h"

#include <stdarg.h>

int a_hash_memory(const a_hash_s *ctx,
                  const void *pdata, size_t nbyte,
                  void *out, size_t *siz)
{
    AASSERT(ctx);
    AASSERT(out);
    AASSERT(siz);
    AASSERT(!nbyte || pdata);

    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    a_hash_u hash[1];

    ctx->init(hash);
    if (ctx->process(hash, pdata, nbyte) != A_HASH_SUCCESS)
    {
        return A_HASH_FAILURE;
    }
    *siz = ctx->done(hash, out) ? ctx->outsiz : 0;

    return A_HASH_SUCCESS;
}

int a_hash_mmulti(const a_hash_s *ctx,
                  void *out, size_t *siz,
                  const void *pdata, size_t nbyte, ...)
{
    AASSERT(ctx);
    AASSERT(out);
    AASSERT(siz);
    AASSERT(!nbyte || pdata);

    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    va_list arg;
    a_hash_u hash[1];
    va_start(arg, nbyte);

    ctx->init(hash);
    for (;;)
    {
        if (ctx->process(hash, pdata, nbyte) != A_HASH_SUCCESS)
        {
            va_end(arg);
            return A_HASH_FAILURE;
        }
        pdata = va_arg(arg, const void *);
        if (pdata == 0)
        {
            va_end(arg);
            break;
        }
        nbyte = va_arg(arg, size_t);
    };
    *siz = ctx->done(hash, out) ? ctx->outsiz : 0;

    return A_HASH_SUCCESS;
}

int a_hash_filehandle(const a_hash_s *ctx, FILE *in, void *out, size_t *siz)
{
    AASSERT(in);
    AASSERT(ctx);
    AASSERT(out);
    AASSERT(siz);

    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    a_hash_u hash[1];

    ctx->init(hash);
    do
    {
        char buf[BUFSIZ];
        *siz = fread(buf, 1, BUFSIZ, in);
        ctx->process(hash, buf, *siz);
    } while (*siz == BUFSIZ);
    *siz = ctx->done(hash, out) ? ctx->outsiz : 0;

    return A_HASH_SUCCESS;
}

int a_hash_file(const a_hash_s *ctx, const char *fname, void *out, size_t *siz)
{
    AASSERT(ctx);
    AASSERT(out);
    AASSERT(siz);
    AASSERT(fname);

    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    FILE *in = fopen(fname, "rb");
    if (in == 0)
    {
        return A_HASH_NOTFOUND;
    }

    int ret = a_hash_filehandle(ctx, in, out, siz);

    if (fclose(in))
    {
        return A_HASH_FAILURE;
    }

    return ret;
}
