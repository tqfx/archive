/*!
 @file a_vec_util.h
 @brief basic vector util library
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_VEC_UTIL_H__
#define __A_VEC_UTIL_H__

#include "a_vec.h"

A_VEC_S(a_vec_i8_s, int8_t);
A_VEC_S(a_vec_u8_s, uint8_t);
A_VEC_S(a_vec_i16_s, int16_t);
A_VEC_S(a_vec_u16_s, uint16_t);
A_VEC_S(a_vec_i32_s, int32_t);
A_VEC_S(a_vec_u32_s, uint32_t);
A_VEC_S(a_vec_i64_s, int64_t);
A_VEC_S(a_vec_u64_s, uint64_t);
A_VEC_S(a_vec_f32_s, float);
A_VEC_S(a_vec_f64_s, double);
A_VEC_S(a_vec_str_s, char *);

A_VEC_AT(a_vec_i8_s, a_vec_i8_at, int8_t)
A_VEC_AT(a_vec_u8_s, a_vec_u8_at, uint8_t)
A_VEC_AT(a_vec_i16_s, a_vec_i16_at, int16_t)
A_VEC_AT(a_vec_u16_s, a_vec_u16_at, uint16_t)
A_VEC_AT(a_vec_i32_s, a_vec_i32_at, int32_t)
A_VEC_AT(a_vec_u32_s, a_vec_u32_at, uint32_t)
A_VEC_AT(a_vec_i64_s, a_vec_i64_at, int64_t)
A_VEC_AT(a_vec_u64_s, a_vec_u64_at, uint64_t)
A_VEC_AT(a_vec_f32_s, a_vec_f32_at, float)
A_VEC_AT(a_vec_f64_s, a_vec_f64_at, double)
A_VEC_AT(a_vec_str_s, a_vec_str_at, char *)

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
