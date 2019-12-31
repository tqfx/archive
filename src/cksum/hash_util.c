/*!
 @file hash_util.c
 @brief hash library utils
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/cksum/hash_util.h"

#include <assert.h>
#include <stdarg.h>

int a_hash_memory(const a_hash_s *ctx, const void *pdata, size_t nbyte, void *out, size_t *siz)
{
    assert(ctx);
    assert(out);
    assert(siz);
    assert(!nbyte || pdata);

    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_OVERFLOW;
    }

    a_hash_u hash[1];

    ctx->init(hash);
    if (ctx->proc(hash, pdata, nbyte) != A_SUCCESS)
    {
        return A_FAILURE;
    }
    *siz = ctx->done(hash, out) ? ctx->outsiz : 0;

    return A_SUCCESS;
}

int a_hash_mmulti(const a_hash_s *ctx, void *out, size_t *siz, const void *pdata, size_t nbyte, ...)
{
    assert(ctx);
    assert(out);
    assert(siz);
    assert(!nbyte || pdata);

    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_OVERFLOW;
    }

    va_list arg;
    a_hash_u hash[1];
    int ret = A_SUCCESS;
    va_start(arg, nbyte);

    ctx->init(hash);
    for (;;)
    {
        ret = ctx->proc(hash, pdata, nbyte);
        if (ret != A_SUCCESS)
        {
            goto done;
        }
        pdata = va_arg(arg, const void *);
        if (pdata == 0)
        {
            break;
        }
        nbyte = va_arg(arg, size_t);
    }
    *siz = ctx->done(hash, out) ? ctx->outsiz : 0;

done:
    va_end(arg);
    return ret;
}

int a_hash_filehandle(const a_hash_s *ctx, FILE *in, void *out, size_t *siz)
{
    assert(in);
    assert(ctx);
    assert(out);
    assert(siz);

    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_OVERFLOW;
    }

    char buf[BUFSIZ];
    a_hash_u hash[1];

    ctx->init(hash);
    do
    {
        *siz = fread(buf, 1, BUFSIZ, in);
        ctx->proc(hash, buf, *siz);
    } while (*siz == BUFSIZ);
    *siz = ctx->done(hash, out) ? ctx->outsiz : 0;

    return A_SUCCESS;
}

int a_hash_file(const a_hash_s *ctx, const char *fname, void *out, size_t *siz)
{
    assert(ctx);
    assert(out);
    assert(siz);
    assert(fname);

    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_OVERFLOW;
    }

    FILE *in = fopen(fname, "rb");
    if (in == 0)
    {
        return A_NOTFOUND;
    }

    int ret = a_hash_filehandle(ctx, in, out, siz);

    if (fclose(in))
    {
        return A_FAILURE;
    }

    return ret;
}
