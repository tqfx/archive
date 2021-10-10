/*!
 @file           test_hash.h
 @brief          hash library test
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __TEST_HASH_H__
#define __TEST_HASH_H__

#include "a_convert.h"

#include <stdio.h>
#include <string.h>

#define __HASH_FPROCESS(hash, func, compress)                   \
    void func(hash *ctx, FILE *fp)                              \
    {                                                           \
        long idx = ftell(fp);                                   \
        for (;;)                                                \
        {                                                       \
            size_t m = sizeof(ctx->buf) - ctx->curlen;          \
            size_t n = fread(ctx->buf + ctx->curlen, 1, m, fp); \
            if (sizeof(ctx->buf) == ctx->curlen + n)            \
            {                                                   \
                compress(ctx, ctx->buf);                        \
                ctx->length += (sizeof(ctx->buf) << 3);         \
                ctx->curlen = 0;                                \
            }                                                   \
            else                                                \
            {                                                   \
                ctx->curlen += (uint32_t)n;                     \
                break;                                          \
            }                                                   \
        }                                                       \
        fseek(fp, idx, SEEK_SET);                               \
    }

#define __HASH_DIFF(src, dst, size, info)                        \
    do                                                           \
    {                                                            \
        if (memcmp(src, dst, size))                              \
        {                                                        \
            char _bsrc[((size) << 1) + 1];                       \
            char _bdst[((size) << 1) + 1];                       \
            a_digest((const unsigned char *)(src), size, _bsrc); \
            a_digest((const unsigned char *)(dst), size, _bdst); \
            printf("%s %s %s\n", _bsrc, _bdst, info);            \
        }                                                        \
    } while (0)

/* Enddef to prevent recursive inclusion */
#endif /* __TEST_HASH_H__ */

/* END OF FILE */
