/*!
 @file           a_hash_util.c
 @brief          hash library utils
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_hash_util.h"

#include <stdarg.h>

int a_hash_memory(const a_hash_t *ctx, const void *p, size_t n, void *out, size_t *siz)
{
    /* assert(ctx) */
    /* assert(out) */
    /* assert(siz) */
    /* assert(!n || p) */
    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    a_hash_stat_t stat[1];

    ctx->init(stat);
    if (ctx->process(stat, p, n) != A_HASH_SUCCESS)
    {
        return A_HASH_FAILURE;
    }
    *siz = (ctx->done(stat, out) ? ctx->outsiz : 0);

    return A_HASH_SUCCESS;
}

int a_hash_mmulti(const a_hash_t *ctx, void *out, size_t *siz, const void *p, size_t n, ...)
{
    /* assert(ctx) */
    /* assert(out) */
    /* assert(siz) */
    /* assert(!n || p) */
    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    va_list arg;
    va_start(arg, n);
    a_hash_stat_t stat[1];

    ctx->init(stat);
    for (;;)
    {
        if (ctx->process(stat, p, n) != A_HASH_SUCCESS)
        {
            va_end(arg);
            return A_HASH_FAILURE;
        }
        p = va_arg(arg, const void *);
        if (0 == p)
        {
            va_end(arg);
            break;
        }
        n = va_arg(arg, size_t);
    };
    *siz = (ctx->done(stat, out) ? ctx->outsiz : 0);

    return A_HASH_SUCCESS;
}

int a_hash_filehandle(const a_hash_t *ctx, FILE *in, void *out, size_t *siz)
{
    /* assert(in) */
    /* assert(ctx) */
    /* assert(out) */
    /* assert(siz) */
    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    a_hash_stat_t stat[1];

    char buf[BUFSIZ];
    ctx->init(stat);
    do
    {
        *siz = fread(buf, 1, BUFSIZ, in);
        ctx->process(stat, buf, *siz);
    } while (*siz == BUFSIZ);
    *siz = (ctx->done(stat, out) ? ctx->outsiz : 0);

    return A_HASH_SUCCESS;
}

int a_hash_file(const a_hash_t *ctx, const char *fname, void *out, size_t *siz)
{
    /* assert(ctx) */
    /* assert(out) */
    /* assert(siz) */
    /* assert(fname) */
    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HASH_OVERFLOW;
    }

    FILE *in = fopen(fname, "rb");
    if (0 == in)
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

/* END OF FILE */
