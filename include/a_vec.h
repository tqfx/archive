/*!
 @file a_vec.h
 @brief basic vector library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_VEC_H__
#define __A_VEC_H__

#include "liba.h"

typedef struct a_vec_s a_vec_s;
typedef struct a_vec_vt_s a_vec_vt_s;

struct a_vec_s
{
    a_vec_vt_s *_vt;
    void *_v;  /* vector */
    size_t _m; /* memory */
    size_t _n; /* length */
    size_t _z; /* sizeof */
};

__STATIC_INLINE
void *a_vec_ptr(a_vec_s *ctx)
{
    return ctx->_v;
}
__STATIC_INLINE
void *a_vec_end(a_vec_s *ctx)
{
    return (unsigned char *)ctx->_v + ctx->_n * ctx->_z;
}
__STATIC_INLINE
size_t a_vec_mem(const a_vec_s *ctx)
{
    return ctx->_m;
}
__STATIC_INLINE
size_t a_vec_num(const a_vec_s *ctx)
{
    return ctx->_n;
}
__STATIC_INLINE
size_t a_vec_siz(const a_vec_s *ctx)
{
    return ctx->_z;
}
__STATIC_INLINE
size_t a_vec_use(const a_vec_s *ctx)
{
    return ctx->_n * ctx->_z;
}
__STATIC_INLINE
void *a_vec_at(a_vec_s *ctx, size_t idx)
{
    return (unsigned char *)ctx->_v + ctx->_z * idx;
}

struct a_vec_vt_s
{
    void (*erase)(a_vec_s *, void *);
    int (*clone)(const a_vec_s *, const void *, void *);
    int (*swap)(const a_vec_s *, void *, void *);
};

__BEGIN_DECLS

void a_vec_ctor(a_vec_s *ctx, size_t siz);
void a_vec_dtor(a_vec_s *ctx);
a_vec_s *a_vec_new(size_t siz);
void a_vec_delete(a_vec_s *ctx);

int a_vec_copy(const a_vec_s *ctx, a_vec_s *dst);
void a_vec_reuse(a_vec_s *ctx, size_t siz);
void a_vec_move(a_vec_s *ctx, a_vec_s *dst);
int a_vec_push(a_vec_s *ctx, void *ptr);
int a_vec_pop(a_vec_s *ctx, void *ptr);

void a_vec_cleanup(a_vec_s *ctx);
void a_vec_erase(a_vec_s *ctx, void *ptr);
int a_vec_clone(const a_vec_s *ctx, const void *src, void *dst);
int a_vec_swap(const a_vec_s *ctx, void *a, void *b);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_VEC_H__ */
