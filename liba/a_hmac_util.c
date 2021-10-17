/*!
 @file           a_hmac_util.c
 @brief          hmac library utils
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_hmac_util.h"

#include <stdarg.h>

int a_hmac_memory(const a_hash_t *ctx,
                  const void *key,
                  size_t keysiz,
                  const void *msg,
                  size_t msgsiz,
                  void *out,
                  size_t *siz)
{
    /* assert(ctx) */
    /* assert(out) */
    /* assert(siz) */
    /* assert(!keysiz || key) */
    /* assert(!msgsiz || msg) */
    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    a_hmac_t stat[1];

    if (a_hmac_init(stat, ctx, key, keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    if (a_hmac_process(stat, msg, msgsiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    *siz = (a_hmac_done(stat, out) ? ctx->outsiz : 0);

    return A_HMAC_SUCCESS;
}

int a_hmac_mmulti(const a_hash_t *ctx,
                  void *out,
                  size_t *siz,
                  const void *key,
                  size_t keysiz,
                  const void *msg,
                  size_t msgsiz,
                  ...)
{
    /* assert(ctx) */
    /* assert(out) */
    /* assert(siz) */
    /* assert(!keysiz || key) */
    /* assert(!msgsiz || msg) */
    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    va_list arg;
    a_hmac_t stat[1];
    va_start(arg, msgsiz);

    if (a_hmac_init(stat, ctx, key, keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    for (;;)
    {
        if (a_hmac_process(stat, msg, msgsiz) != A_HMAC_SUCCESS)
        {
            va_end(arg);
            return A_HMAC_FAILURE;
        }
        msg = va_arg(arg, const void *);
        if (0 == msg)
        {
            va_end(arg);
            break;
        }
        msgsiz = va_arg(arg, size_t);
    };
    *siz = (a_hmac_done(stat, out) ? ctx->outsiz : 0);

    return A_HMAC_SUCCESS;
}

int a_hmac_filehandle(const a_hash_t *ctx,
                      const void *key,
                      size_t keysiz,
                      FILE *in,
                      void *out,
                      size_t *siz)
{
    /* assert(in) */
    /* assert(ctx) */
    /* assert(out) */
    /* assert(siz) */
    /* assert(!keysiz || key) */
    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    a_hmac_t stat[1];
    char buf[BUFSIZ];

    if (a_hmac_init(stat, ctx, key, keysiz) != A_HMAC_SUCCESS)
    {
        return A_HMAC_FAILURE;
    }
    do
    {
        *siz = fread(buf, 1, BUFSIZ, in);
        if (a_hmac_process(stat, buf, *siz) != A_HMAC_SUCCESS)
        {
            return A_HMAC_FAILURE;
        }
    } while (*siz == BUFSIZ);
    *siz = (a_hmac_done(stat, out) ? ctx->outsiz : 0);

    return A_HMAC_SUCCESS;
}

int a_hmac_file(const a_hash_t *ctx,
                const void *key,
                size_t keysiz,
                const char *fname,
                void *out,
                size_t *siz)
{
    /* assert(ctx) */
    /* assert(out) */
    /* assert(siz) */
    /* assert(fname) */
    /* assert(!keysiz || key) */
    if (*siz < ctx->outsiz)
    {
        *siz = ctx->outsiz;
        return A_HMAC_OVERFLOW;
    }

    FILE *in = fopen(fname, "rb");
    if (0 == in)
    {
        return A_HMAC_NOTFOUND;
    }

    int ret = a_hmac_filehandle(ctx, key, keysiz, in, out, siz);

    if (fclose(in))
    {
        return A_HMAC_FAILURE;
    }

    return ret;
}

/* END OF FILE */
