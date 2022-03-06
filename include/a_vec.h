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
typedef struct a_vec_vtbl_s a_vec_vtbl_s;

struct a_vec_vtbl_s
{
    /*!
     @retval 0 failure
    */
    void *(*address)(void *obj, size_t index);
    /*!
     @retval 0 success
     @retval -1 failure
    */
    int (*realloc)(void *obj, size_t capacity);
};

struct a_vec_s
{
    const a_vec_vtbl_s *vptr;
    size_t capacity;
    size_t length;
};

__STATIC_INLINE
size_t a_vec_mem(const void *obj)
{
    AASSERT(obj);
    const a_vec_s *ctx = (const a_vec_s *)obj;
    return ctx->capacity;
}

__STATIC_INLINE
size_t a_vec_len(const void *obj)
{
    AASSERT(obj);
    const a_vec_s *ctx = (const a_vec_s *)obj;
    return ctx->length;
}

__STATIC_INLINE
void *a_vec_ptr(void *obj, size_t index)
{
    AASSERT(obj);
    a_vec_s *ctx = (a_vec_s *)obj;
    return ctx->vptr->address(ctx, index);
}

__BEGIN_DECLS

a_vec_s *a_vec_new(void);
void a_vec_delete(a_vec_s *ctx);

void a_vec_ctor(a_vec_s *ctx);
void a_vec_dtor(a_vec_s *ctx);

void *a_vec_push(void *obj);
void *a_vec_pop(void *obj);

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_VEC_H__ */
