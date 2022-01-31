/*!
 @file a_str.h
 @brief basic string library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_str.h"

#include <stdio.h> /* vsnprintf */

/*!
 @brief Boyer-Moore algorithm
 @details http://www-igm.univ-mlv.fr/~lecroq/string/node14.html
 @param[in] pat: points to search patterns
 @param[in] m: length of search patterns
 @return int *prep[m + 0x100]. You need to free memory.
*/
static int *a_bm_prep(const void *pat, int m);

static int *a_bm_prep(const void *_pat, int _m)
{
    const unsigned char *pat = (const unsigned char *)_pat;

    int *suff = (int *)calloc((size_t)(_m + 0x000), sizeof(int));
    int *prep = (int *)calloc((size_t)(_m + 0x100), sizeof(int));
    int *bmBc = prep + _m;
    int *bmGs = prep;

    int m_1 = _m ? _m - 1 : 0;

    /* preBmBc() */
    {
        int *pi = bmBc;
        int *pd = bmBc + 0x100;
        while (pi != pd)
        {
            *pi++ = _m;
        }
        for (int i = 0; i != m_1; ++i)
        {
            bmBc[pat[i]] = m_1 - i;
        }
    }

    /* suffixes() */
    {
        suff[m_1] = _m;
        int f = 0;
        int g = m_1;
        for (int i = m_1 - 1; i != -1; --i)
        {
            if ((i > g) && (suff[i + m_1 - f] < i - g))
            {
                suff[i] = suff[i + m_1 - f];
            }
            else
            {
                if (i < g)
                {
                    g = i;
                }
                f = i;
                while ((g != -1) && (pat[g] == pat[g + m_1 - f]))
                {
                    --g;
                }
                suff[i] = f - g;
            }
        }
    }

    /* preBmGs() */
    {
        int *pi = bmGs;
        int *pd = bmGs + _m;
        while (pi != pd)
        {
            *pi++ = _m;
        }
        int j = 0;
        for (int i = m_1; i != -1; --i)
        {
            if (suff[i] == i + 1)
            {
                int m_1_i = m_1 - i;
                while (j != m_1_i)
                {
                    if (bmGs[j] == _m)
                    {
                        bmGs[j] = m_1_i;
                    }
                    ++j;
                }
            }
        }
        for (int i = 0; i != m_1; ++i)
        {
            bmGs[m_1 - suff[i]] = m_1 - i;
        }
    }

    free(suff);

    return prep;
}

void *a_memmem(const void *_str, int _n, const void *_pat, int _m, int **_prep)
{
    union
    {
        void *ret;
        const unsigned char *p;
    } p_u = {
        .p = 0,
    };

    const unsigned char *str = (const unsigned char *)_str;
    const unsigned char *pat = (const unsigned char *)_pat;

    int *prep = ((_prep == 0) || (*_prep == 0)) ? a_bm_prep(pat, _m) : *_prep;
    if (_prep && (*_prep == 0))
    {
        *_prep = prep;
    }

    int *bmGs = prep;
    int *bmBc = prep + _m;

    int j = 0;
    while (j <= _n - _m)
    {
        int i = _m - 1;
        while ((i != -1) && (pat[i] == str[i + j]))
        {
            --i;
        }
        if (i != -1)
        {
            int max = bmBc[str[i + j]] - _m + 1 + i;
            if (max < bmGs[i])
            {
                max = bmGs[i];
            }
            j += max;
        }
        else
        {
            p_u.p = str + j;
            return p_u.ret;
        }
    }

    if (_prep == 0)
    {
        free(prep);
        prep = 0;
    }

    return 0;
}

char *a_strnstr(const void *_str, int _n, const void *_pat, int **_prep)
{
    const char *pat = (const char *)_pat;
    return (char *)a_memmem(_str, _n, _pat, (int)strlen(pat), _prep);
}

char *a_strstr(const void *_str, const void *_pat, int **_prep)
{
    const char *str = (const char *)_str;
    const char *pat = (const char *)_pat;
    return (char *)a_memmem(_str, (int)strlen(str), _pat, (int)strlen(pat), _prep);
}

a_str_s *a_str_init(const void *_p, size_t _n)
{
    a_str_s *ctx = (a_str_s *)malloc(sizeof(a_str_s));
    if (ctx)
    {
        ctx->n = _n;
        ctx->m = _n + 1;
        aroundup32(ctx->m);
        ctx->s = (char *)malloc(ctx->m);
        if (_p && _n)
        {
            memcpy(ctx->s, _p, _n);
        }
        ctx->s[ctx->n] = 0;
    }
    return ctx;
}

char *a_str_done(a_str_s *ctx)
{
    AASSERT(ctx);
    char *s = ctx->s;
    if (ctx->s)
    {
        ctx->s[ctx->n] = 0;
        ctx->s = 0;
    }
    ctx->m = 0;
    ctx->n = 0;
    return s;
}

void a_str_free(a_str_s *ctx)
{
    if (ctx)
    {
        if (ctx->s)
        {
            free(ctx->s);
            ctx->s = 0;
        }
        free(ctx);
    }
}

int a_str_resize_(a_str_s *ctx, size_t _m)
{
    AASSERT(ctx);
    aroundup32(_m);
    char *s = (char *)realloc(ctx->s, _m);
    if (!s && _m)
    {
        return -1;
    }
    ctx->s = s;
    ctx->m = _m;
    return 0;
}

int a_str_resize(a_str_s *ctx, size_t _m)
{
    AASSERT(ctx);
    if (ctx->m < _m)
    {
        return a_str_resize_(ctx, _m);
    }
    return 0;
}

int a_str_putn_(a_str_s *ctx, const void *_p, size_t _n)
{
    AASSERT(ctx);
    if (_p && _n)
    {
        if (a_str_resize(ctx, ctx->n + _n))
        {
            return -1;
        }
        memcpy(ctx->s + ctx->n, _p, _n);
        ctx->n = ctx->n + _n;
    }
    return 0;
}

int a_str_putn(a_str_s *ctx, const void *_p, size_t _n)
{
    AASSERT(ctx);
    if (_p)
    {
        if (a_str_resize(ctx, ctx->n + _n + 1))
        {
            return -1;
        }
        if (_n)
        {
            memcpy(ctx->s + ctx->n, _p, _n);
            ctx->n = ctx->n + _n;
        }
        ctx->s[ctx->n] = 0;
    }
    return 0;
}

int a_str_puts(a_str_s *ctx, const void *_s)
{
    AASSERT(_s);
    AASSERT(ctx);
    const char *s = (const char *)_s;
    return a_str_putn(ctx, s, strlen(s));
}

int a_str_putc_(a_str_s *ctx, int _c)
{
    AASSERT(ctx);
    if (a_str_resize(ctx, ctx->n + 1))
    {
        return -1;
    }
    ctx->s[ctx->n++] = (char)_c;
    return _c;
}

int a_str_putc(a_str_s *ctx, int _c)
{
    AASSERT(ctx);
    if (_c == 0)
    {
        return a_str_putc_(ctx, _c);
    }
    if (a_str_resize(ctx, ctx->n + 2))
    {
        return -1;
    }
    ctx->s[ctx->n++] = (char)_c;
    ctx->s[ctx->n] = 0;
    return _c;
}

int a_str_vprintf(a_str_s *ctx, const char *_fmt, va_list _ap)
{
    AASSERT(ctx);
    AASSERT(_fmt);
    va_list ap;

    va_copy(ap, _ap);
    char *s = ctx->s ? (ctx->s + ctx->n) : 0;
    int ret = vsnprintf(s, ctx->m - ctx->n, _fmt, ap);
    va_end(ap);

    if (ctx->m - ctx->n < (size_t)ret + 1)
    {
        if (a_str_resize_(ctx, ctx->n + (size_t)ret + 1))
        {
            return -1;
        }

        va_copy(ap, _ap);
        s = ctx->s + ctx->n;
        ret = vsnprintf(s, ctx->m - ctx->n, _fmt, ap);
        va_end(ap);
    }

    ctx->n += (size_t)ret;

    return ret;
}

int a_str_printf(a_str_s *ctx, const char *_fmt, ...)
{
    AASSERT(ctx);
    AASSERT(_fmt);
    va_list ap;

    va_start(ap, _fmt);
    int ret = a_str_vprintf(ctx, _fmt, ap);
    va_end(ap);

    return ret;
}
