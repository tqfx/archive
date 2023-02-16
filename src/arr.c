#include "a/arr.h"
#include <string.h>
#include <stdlib.h>

#undef a_arr_at
#undef a_arr_at_
#undef a_arr_ptr
#undef a_arr_end
#undef a_arr_top
#undef a_arr_top_
#undef a_arr_push
#undef a_arr_pull
#undef a_arr_search
#undef a_arr_insert
#undef a_arr_remove
#undef a_arr_push_fore
#undef a_arr_push_back
#undef a_arr_pull_fore
#undef a_arr_pull_back

A_INTERN a_vptr_t a_arr_inc_(a_arr_s *const ctx)
{
    return a_byte_p(ctx->_ptr) + ctx->_siz * ctx->_num++;
}

A_INTERN a_vptr_t a_arr_dec_(a_arr_s *const ctx)
{
    return a_byte_p(ctx->_ptr) + ctx->_siz * --ctx->_num;
}

static a_void_t a_arr_drop_(a_arr_s *const ctx, a_size_t const bot, a_void_t (*const dtor)(a_vptr_t))
{
    if (dtor)
    {
        while (ctx->_num > bot)
        {
            dtor(a_arr_dec_(ctx));
        }
    }
    ctx->_num = bot;
}

a_void_t a_arr_ctor(a_arr_s *const ctx, a_vptr_t const ptr, a_size_t const siz, a_size_t const num)
{
    ctx->_ptr = ptr;
    ctx->_siz = siz;
    ctx->_mem = num;
    ctx->_num = 0;
}

a_void_t a_arr_dtor(a_arr_s *const ctx, a_void_t (*const dtor)(a_vptr_t))
{
    if (ctx->_ptr)
    {
        a_arr_drop_(ctx, 0, dtor);
        ctx->_ptr = A_NULL;
    }
    ctx->_mem = 0;
    ctx->_siz = 0;
}

a_arr_s *a_arr_move(a_arr_s *const ctx, a_arr_s *const obj)
{
    memcpy(ctx, obj, sizeof(*obj));
    memset(obj, 0, sizeof(*obj));
    return ctx;
}

a_void_t a_arr_drop(a_arr_s *const ctx, a_void_t (*const dtor)(a_vptr_t))
{
    a_arr_drop_(ctx, 0, dtor);
}

a_void_t a_arr_swap(a_arr_s const *const ctx, a_size_t lhs, a_size_t rhs)
{
    a_size_t const num = ctx->_num - 1;
    lhs = lhs < ctx->_num ? lhs : num;
    rhs = rhs < ctx->_num ? rhs : num;
    if (lhs != rhs)
    {
        a_byte_t *ptr = a_byte_p(ctx->_ptr);
        a_vptr_t lobj = ptr + lhs * ctx->_siz;
        a_vptr_t robj = ptr + rhs * ctx->_siz;
        a_swap(ctx->_siz, lobj, robj);
    }
}

a_void_t a_arr_sort(a_arr_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    qsort(ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

a_void_t a_arr_sort_fore(a_arr_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    if (ctx->_num > 1)
    {
        a_byte_t *ptr = a_byte_p(ctx->_ptr);
        a_byte_t *const end = a_byte_p(ctx->_ptr) + ctx->_siz * ctx->_num - ctx->_siz;
        do
        {
            a_byte_t *const cur = ptr + ctx->_siz;
            if (cmp(ptr, cur) > 0)
            {
                a_swap(ctx->_siz, cur, ptr);
            }
            else
            {
                break;
            }
            ptr = cur;
        } while (ptr != end);
    }
}

a_void_t a_arr_sort_back(a_arr_s const *const ctx, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    if (ctx->_num > 1)
    {
        a_byte_t *ptr = a_byte_p(ctx->_ptr) + ctx->_siz * ctx->_num - ctx->_siz;
        do
        {
            a_byte_t *const cur = ptr - ctx->_siz;
            if (cmp(cur, ptr) > 0)
            {
                a_swap(ctx->_siz, cur, ptr);
            }
            else
            {
                break;
            }
            ptr = cur;
        } while (ptr != ctx->_ptr);
    }
}

a_vptr_t a_arr_search(a_arr_s const *const ctx, a_cptr_t const obj, a_int_t (*const cmp)(a_cptr_t, a_cptr_t))
{
    return bsearch(obj, ctx->_ptr, ctx->_num, ctx->_siz, cmp);
}

a_vptr_t a_arr_insert(a_arr_s *const ctx, a_size_t const idx)
{
    if (a_likely(ctx->_num < ctx->_mem))
    {
        if (idx < ctx->_num)
        {
            a_byte_t *const src = a_byte_p(ctx->_ptr) + ctx->_siz * (idx + 0);
            a_byte_t *const dst = a_byte_p(ctx->_ptr) + ctx->_siz * (idx + 1);
            memmove(dst, src, (ctx->_num - idx) * ctx->_siz);
            ++ctx->_num;
            return src;
        }
        return a_arr_inc_(ctx);
    }
    return A_NULL;
}

a_vptr_t a_arr_push_fore(a_arr_s *const ctx) { return a_arr_insert(ctx, 0); }

a_vptr_t a_arr_push_back(a_arr_s *const ctx)
{
    return a_likely(ctx->_num < ctx->_mem) ? a_arr_inc_(ctx) : A_NULL;
}

a_vptr_t a_arr_remove(a_arr_s *const ctx, a_size_t const idx)
{
    if (ctx->_num && idx < ctx->_num - 1)
    {
        a_byte_t *const end = a_byte_p(ctx->_ptr) + ctx->_siz * ctx->_num;
        a_byte_t *const dst = a_byte_p(ctx->_ptr) + ctx->_siz * (idx + 0);
        a_byte_t *const src = a_byte_p(ctx->_ptr) + ctx->_siz * (idx + 1);
        a_swap(a_size_c(end - src), dst, src);
        --ctx->_num;
        return dst;
    }
    return a_likely(ctx->_num) ? a_arr_dec_(ctx) : A_NULL;
}

a_vptr_t a_arr_pull_fore(a_arr_s *const ctx) { return a_arr_remove(ctx, 0); }

a_vptr_t a_arr_pull_back(a_arr_s *const ctx)
{
    return a_likely(ctx->_num) ? a_arr_dec_(ctx) : A_NULL;
}
