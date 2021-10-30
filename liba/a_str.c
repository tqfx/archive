/*!
 @file           a_str.h
 @brief          basic string library
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

#include "a_str.h"

#include <stdio.h> /* vsnprintf */

/*!
 @brief          Boyer-Moore algorithm
 @ref            http://www-igm.univ-mlv.fr/~lecroq/string/node14.html
 @param[in]      pat: pointer of search patterns
 @param[in]      m: length of search patterns
 @return         void *prep[m + 0x100]
*/
static int *bm_prep(const unsigned char *pat, int m);

static int *bm_prep(const unsigned char *_pat, int _m)
{
    int *prep = (int *)acalloc((size_t)(_m + 0x100), sizeof(int));

    int *bmGs = prep;
    int *bmBc = prep + _m;

    int m_1 = _m ? _m - 1 : 0;

    { /* preBmBc() */
        int *pi = bmBc;
        int *pd = bmBc + 0x100;
        while (pi != pd)
        {
            *pi++ = _m;
        }
        for (int i = 0; i != m_1; ++i)
        {
            bmBc[_pat[i]] = m_1 - i;
        }
    }

    int *suff = (int *)acalloc((size_t)_m, sizeof(int));

    { /* suffixes() */
        suff[m_1] = _m;
        int f = 0;
        int g = m_1;
        for (int i = m_1 - 1; - 1 != i; --i)
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
                while ((-1 != g) && (_pat[g] == _pat[g + m_1 - f]))
                {
                    --g;
                }
                suff[i] = f - g;
            }
        }
    }

    { /* preBmGs() */
        int *pi = bmGs;
        int *pd = bmGs + _m;
        while (pi != pd)
        {
            *pi++ = _m;
        }
        int j = 0;
        for (int i = m_1; - 1 != i; --i)
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

    afree(suff);
    suff = 0;

    return prep;
}

void *a_memmem(const void *_str, int _n, const void *_pat, int _m, int **_prep)
{
    union
    {
        void *ret;
        const unsigned char *p;
    } up[1] = {{.ret = 0}};

    const unsigned char *str = (const unsigned char *)_str;
    const unsigned char *pat = (const unsigned char *)_pat;

    int *prep = ((_prep == 0) || (*_prep == 0)) ? bm_prep(pat, _m) : *_prep;
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
        while ((-1 != i) && (pat[i] == str[i + j]))
        {
            --i;
        }
        if (-1 != i)
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
            up->p = str + j;
            return up->ret;
        }
    }

    if (_prep == 0)
    {
        afree(prep);
        prep = 0;
    }

    return 0;
}

char *a_strnstr(const char *_str, int _n, const char *_pat, int **_prep)
{
    return (char *)a_memmem(_str, _n, _pat, (int)strlen(_pat), _prep);
}

char *a_strstr(const char *_str, const char *_pat, int **_prep)
{
    return (char *)a_memmem(_str, (int)strlen(_str), _pat, (int)strlen(_pat), _prep);
}

a_str_t *a_str_init(const void *_p, size_t _n)
{
    a_str_t *ctx = (a_str_t *)amalloc(sizeof(a_str_t));
    if (ctx)
    {
        ctx->n = _n;
        ctx->m = _n + 1;
        aroundup32(ctx->m);
        ctx->s = (char *)amalloc(ctx->m);
        if (_p && _n)
        {
            memcpy(ctx->s, _p, _n);
        }
        ctx->s[ctx->n] = 0;
    }
    return ctx;
}

char *a_str_done(a_str_t *_ctx)
{
    aassert(_ctx);
    char *s = _ctx->s;
    if (_ctx->s)
    {
        _ctx->s[_ctx->n] = 0;
        _ctx->s = 0;
    }
    _ctx->m = 0;
    _ctx->n = 0;
    return s;
}

void a_str_free(a_str_t *_ctx)
{
    if (_ctx)
    {
        if (_ctx->s)
        {
            afree(_ctx->s);
            _ctx->s = 0;
        }
        afree(_ctx);
    }
}

int a_str_resize_(a_str_t *_ctx, size_t _m)
{
    aassert(_ctx);
    aroundup32(_m);
    char *s = (char *)arealloc(_ctx->s, _m);
    if (!s && _m)
    {
        return -1;
    }
    _ctx->s = s;
    _ctx->m = _m;
    return 0;
}

int a_str_resize(a_str_t *_ctx, size_t _m)
{
    aassert(_ctx);
    if (_ctx->m < _m)
    {
        return a_str_resize_(_ctx, _m);
    }
    return 0;
}

int a_str_putn_(a_str_t *_ctx, const void *_p, size_t _n)
{
    aassert(_ctx);
    if (_p && _n)
    {
        if (a_str_resize(_ctx, _ctx->n + _n))
        {
            return -1;
        }
        memcpy(_ctx->s + _ctx->n, _p, _n);
        _ctx->n = _ctx->n + _n;
    }
    return 0;
}

int a_str_putn(a_str_t *_ctx, const void *_p, size_t _n)
{
    aassert(_ctx);
    if (_p && _n)
    {
        if (a_str_resize(_ctx, _ctx->n + _n + 1))
        {
            return -1;
        }
        memcpy(_ctx->s + _ctx->n, _p, _n);
        _ctx->n = _ctx->n + _n;
        _ctx->s[_ctx->n] = 0;
    }
    return 0;
}

int a_str_puts(a_str_t *_ctx, const char *_s)
{
    aassert(_s);
    aassert(_ctx);
    return a_str_putn(_ctx, _s, strlen(_s));
}

int a_str_putc_(a_str_t *_ctx, int _c)
{
    aassert(_ctx);
    if (a_str_resize(_ctx, _ctx->n + 1))
    {
        return -1;
    }
    _ctx->s[_ctx->n++] = (char)_c;
    return _c;
}

int a_str_putc(a_str_t *_ctx, int _c)
{
    aassert(_ctx);
    if (_c == 0)
    {
        return a_str_putc_(_ctx, _c);
    }
    if (a_str_resize(_ctx, _ctx->n + 2))
    {
        return -1;
    }
    _ctx->s[_ctx->n++] = (char)_c;
    _ctx->s[_ctx->n] = 0;
    return _c;
}

int a_str_vprintf(a_str_t *_ctx, const char *_fmt, va_list _ap)
{
    aassert(_ctx);
    aassert(_fmt);
    va_list ap;

    va_copy(ap, _ap);
    char *s = _ctx->s ? (_ctx->s + _ctx->n) : 0;
    int ret = vsnprintf(s, _ctx->m - _ctx->n, _fmt, ap);
    va_end(ap);

    if (_ctx->m - _ctx->n < (size_t)ret + 1)
    {
        if (a_str_resize_(_ctx, _ctx->n + (size_t)ret + 1))
        {
            return -1;
        }

        va_copy(ap, _ap);
        s = _ctx->s + _ctx->n;
        ret = vsnprintf(s, _ctx->m - _ctx->n, _fmt, ap);
        va_end(ap);
    }

    _ctx->n += (size_t)ret;

    return ret;
}

int a_str_printf(a_str_t *_ctx, const char *_fmt, ...)
{
    aassert(_ctx);
    aassert(_fmt);
    va_list ap;

    va_start(ap, _fmt);
    int ret = a_str_vprintf(_ctx, _fmt, ap);
    va_end(ap);

    return ret;
}

/* END OF FILE */
