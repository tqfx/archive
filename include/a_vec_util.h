/*!
 @file a_vec_util.h
 @brief basic vector util library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_VEC_UTIL_H__
#define __A_VEC_UTIL_H__

#include "a_vec.h"

#undef A_VEC_T
#define A_VEC_T(name, type)         \
    typedef struct a_vec_##name##_s \
    {                               \
        a_vec_s vec[1];             \
        type *ptr;                  \
    } a_vec_##name##_s
A_VEC_T(i8, int8_t);
A_VEC_T(u8, uint8_t);
A_VEC_T(i16, int16_t);
A_VEC_T(u16, uint16_t);
A_VEC_T(i32, int32_t);
A_VEC_T(u32, uint32_t);
A_VEC_T(i64, int64_t);
A_VEC_T(u64, uint64_t);
A_VEC_T(f32, float);
A_VEC_T(f64, double);
A_VEC_T(str, char *);
#undef A_VEC_T

#undef A_VEC_AT
#define A_VEC_AT(name, type)                                    \
    __NONNULL((1))                                              \
    __STATIC_INLINE                                             \
    type a_vec_##name##_at(a_vec_##name##_s *ctx, size_t index) \
    {                                                           \
        AASSERT(ctx);                                           \
        return ctx->ptr[index];                                 \
    }
A_VEC_AT(i8, int8_t)
A_VEC_AT(u8, uint8_t)
A_VEC_AT(i16, int16_t)
A_VEC_AT(u16, uint16_t)
A_VEC_AT(i32, int32_t)
A_VEC_AT(u32, uint32_t)
A_VEC_AT(i64, int64_t)
A_VEC_AT(u64, uint64_t)
A_VEC_AT(f32, float)
A_VEC_AT(f64, double)
A_VEC_AT(str, char *)
#undef A_VEC_AT

__BEGIN_DECLS

a_vec_i8_s *a_vec_i8_new(void) __RESULT_USE_CHECK;
a_vec_u8_s *a_vec_u8_new(void) __RESULT_USE_CHECK;
a_vec_i16_s *a_vec_i16_new(void) __RESULT_USE_CHECK;
a_vec_u16_s *a_vec_u16_new(void) __RESULT_USE_CHECK;
a_vec_i32_s *a_vec_i32_new(void) __RESULT_USE_CHECK;
a_vec_u32_s *a_vec_u32_new(void) __RESULT_USE_CHECK;
a_vec_i64_s *a_vec_i64_new(void) __RESULT_USE_CHECK;
a_vec_u64_s *a_vec_u64_new(void) __RESULT_USE_CHECK;
a_vec_f32_s *a_vec_f32_new(void) __RESULT_USE_CHECK;
a_vec_f64_s *a_vec_f64_new(void) __RESULT_USE_CHECK;
a_vec_str_s *a_vec_str_new(void) __RESULT_USE_CHECK;

void a_vec_i8_delete(a_vec_i8_s *ctx);
void a_vec_u8_delete(a_vec_u8_s *ctx);
void a_vec_i16_delete(a_vec_i16_s *ctx);
void a_vec_u16_delete(a_vec_u16_s *ctx);
void a_vec_i32_delete(a_vec_i32_s *ctx);
void a_vec_u32_delete(a_vec_u32_s *ctx);
void a_vec_i64_delete(a_vec_i64_s *ctx);
void a_vec_u64_delete(a_vec_u64_s *ctx);
void a_vec_f32_delete(a_vec_f32_s *ctx);
void a_vec_f64_delete(a_vec_f64_s *ctx);
void a_vec_str_delete(a_vec_str_s *ctx);

void a_vec_i8_ctor(a_vec_i8_s *ctx) __NONNULL_ALL;
void a_vec_u8_ctor(a_vec_u8_s *ctx) __NONNULL_ALL;
void a_vec_i16_ctor(a_vec_i16_s *ctx) __NONNULL_ALL;
void a_vec_u16_ctor(a_vec_u16_s *ctx) __NONNULL_ALL;
void a_vec_i32_ctor(a_vec_i32_s *ctx) __NONNULL_ALL;
void a_vec_u32_ctor(a_vec_u32_s *ctx) __NONNULL_ALL;
void a_vec_i64_ctor(a_vec_i64_s *ctx) __NONNULL_ALL;
void a_vec_u64_ctor(a_vec_u64_s *ctx) __NONNULL_ALL;
void a_vec_f32_ctor(a_vec_f32_s *ctx) __NONNULL_ALL;
void a_vec_f64_ctor(a_vec_f64_s *ctx) __NONNULL_ALL;
void a_vec_str_ctor(a_vec_str_s *ctx) __NONNULL_ALL;

void a_vec_i8_dtor(a_vec_i8_s *ctx) __NONNULL_ALL;
void a_vec_u8_dtor(a_vec_u8_s *ctx) __NONNULL_ALL;
void a_vec_i16_dtor(a_vec_i16_s *ctx) __NONNULL_ALL;
void a_vec_u16_dtor(a_vec_u16_s *ctx) __NONNULL_ALL;
void a_vec_i32_dtor(a_vec_i32_s *ctx) __NONNULL_ALL;
void a_vec_u32_dtor(a_vec_u32_s *ctx) __NONNULL_ALL;
void a_vec_i64_dtor(a_vec_i64_s *ctx) __NONNULL_ALL;
void a_vec_u64_dtor(a_vec_u64_s *ctx) __NONNULL_ALL;
void a_vec_f32_dtor(a_vec_f32_s *ctx) __NONNULL_ALL;
void a_vec_f64_dtor(a_vec_f64_s *ctx) __NONNULL_ALL;
void a_vec_str_dtor(a_vec_str_s *ctx) __NONNULL_ALL;

__END_DECLS

/* Enddef to prevent recursive inclusion */
#endif /* __A_VEC_UTIL_H__ */
