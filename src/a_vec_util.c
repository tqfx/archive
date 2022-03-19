/*!
 @file a_vec_util.c
 @brief basic vector util library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_vec_util.h"

#include "a_object.h"

#undef A_VEC_CREATE
#define A_VEC_CREATE(name) A_OBJECT_CREATE(a_vec_##name##_s, a_vec_##name##_new, a_vec_##name##_ctor)
A_VEC_CREATE(i8)
A_VEC_CREATE(u8)
A_VEC_CREATE(i16)
A_VEC_CREATE(u16)
A_VEC_CREATE(i32)
A_VEC_CREATE(u32)
A_VEC_CREATE(i64)
A_VEC_CREATE(u64)
A_VEC_CREATE(f32)
A_VEC_CREATE(f64)
A_VEC_CREATE(str)
#undef A_VEC_CREATE

#undef A_VEC_DELETE
#define A_VEC_DELETE(name) A_OBJECT_DELETE(a_vec_##name##_s, a_vec_##name##_delete, a_vec_##name##_dtor)
A_VEC_DELETE(i8)
A_VEC_DELETE(u8)
A_VEC_DELETE(i16)
A_VEC_DELETE(u16)
A_VEC_DELETE(i32)
A_VEC_DELETE(u32)
A_VEC_DELETE(i64)
A_VEC_DELETE(u64)
A_VEC_DELETE(f32)
A_VEC_DELETE(f64)
A_VEC_DELETE(str)
#undef A_VEC_DELETE

#undef A_VEC_VIRTUAL_ADDRESS
#define A_VEC_VIRTUAL_ADDRESS(name)                       \
    __STATIC_INLINE                                       \
    void *virtual_address_##name(void *obj, size_t index) \
    {                                                     \
        a_vec_##name##_s *ctx = (a_vec_##name##_s *)obj;  \
        return ctx->ptr + index;                          \
    }
A_VEC_VIRTUAL_ADDRESS(i8)
A_VEC_VIRTUAL_ADDRESS(u8)
A_VEC_VIRTUAL_ADDRESS(i16)
A_VEC_VIRTUAL_ADDRESS(u16)
A_VEC_VIRTUAL_ADDRESS(i32)
A_VEC_VIRTUAL_ADDRESS(u32)
A_VEC_VIRTUAL_ADDRESS(i64)
A_VEC_VIRTUAL_ADDRESS(u64)
A_VEC_VIRTUAL_ADDRESS(f32)
A_VEC_VIRTUAL_ADDRESS(f64)
A_VEC_VIRTUAL_ADDRESS(str)
#undef A_VEC_VIRTUAL_ADDRESS

#undef A_VEC_VIRTUAL_REALLOC
#define A_VEC_VIRTUAL_REALLOC(name, type)                               \
    __STATIC_INLINE                                                     \
    int virtual_realloc_##name(void *obj, size_t capacity)              \
    {                                                                   \
        a_vec_##name##_s *ctx = (a_vec_##name##_s *)obj;                \
        type *ptr = (type *)realloc(ctx->ptr, sizeof(type) * capacity); \
        return ptr ? (ctx->ptr = ptr, 0) : ~0;                          \
    }
A_VEC_VIRTUAL_REALLOC(i8, int8_t)
A_VEC_VIRTUAL_REALLOC(u8, uint8_t)
A_VEC_VIRTUAL_REALLOC(i16, int16_t)
A_VEC_VIRTUAL_REALLOC(u16, uint16_t)
A_VEC_VIRTUAL_REALLOC(i32, int32_t)
A_VEC_VIRTUAL_REALLOC(u32, uint32_t)
A_VEC_VIRTUAL_REALLOC(i64, int64_t)
A_VEC_VIRTUAL_REALLOC(u64, uint64_t)
A_VEC_VIRTUAL_REALLOC(f32, float)
A_VEC_VIRTUAL_REALLOC(f64, double)
A_VEC_VIRTUAL_REALLOC(str, char *)
#undef A_VEC_VIRTUAL_REALLOC

#undef A_VEC_CTOR
#define A_VEC_CTOR(name)                            \
    void a_vec_##name##_ctor(a_vec_##name##_s *ctx) \
    {                                               \
        AASSERT(ctx);                               \
        static const a_vec_vtbl_s vtbl = {          \
            virtual_address_##name,                 \
            virtual_realloc_##name,                 \
        };                                          \
        a_vec_ctor(ctx->vec);                       \
        ctx->vec->vptr = &vtbl;                     \
        ctx->ptr = 0;                               \
    }
A_VEC_CTOR(i8)
A_VEC_CTOR(u8)
A_VEC_CTOR(i16)
A_VEC_CTOR(u16)
A_VEC_CTOR(i32)
A_VEC_CTOR(u32)
A_VEC_CTOR(i64)
A_VEC_CTOR(u64)
A_VEC_CTOR(f32)
A_VEC_CTOR(f64)
A_VEC_CTOR(str)
#undef A_VEC_CTOR

#undef A_VEC_DTOR
#define A_VEC_DTOR(name)                            \
    void a_vec_##name##_dtor(a_vec_##name##_s *ctx) \
    {                                               \
        AASSERT(ctx);                               \
        a_vec_dtor(ctx->vec);                       \
        free(ctx->ptr);                             \
        ctx->ptr = 0;                               \
    }
A_VEC_DTOR(i8)
A_VEC_DTOR(u8)
A_VEC_DTOR(i16)
A_VEC_DTOR(u16)
A_VEC_DTOR(i32)
A_VEC_DTOR(u32)
A_VEC_DTOR(i64)
A_VEC_DTOR(u64)
A_VEC_DTOR(f32)
A_VEC_DTOR(f64)
#undef A_VEC_DTOR

void a_vec_str_dtor(a_vec_str_s *ctx)
{
    char **str = 0;
    while ((str = (char **)a_vec_pop(ctx), str))
    {
        free(*str);
    }
    a_vec_dtor(ctx->vec);
    free(ctx->ptr);
    ctx->ptr = 0;
}
