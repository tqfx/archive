/*!
 @file           a_polytrack.h
 @brief          polynomial trajectory
 @details        Trajectory Planning for Automatic Machines and Robots.
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
*/

/* Define to prevent recursive inclusion */
#ifndef __A_POLYTRACK_H__
#define __A_POLYTRACK_H__

#include "liba.h"

#undef __A_POLYTRACK3_T
#define __A_POLYTRACK3_T(bit)               \
    typedef struct a_polytrack3_f##bit##_t  \
    {                                       \
        float##bit##_t t[2]; /* time     */ \
        float##bit##_t q[2]; /* position */ \
        float##bit##_t v[2]; /* velocity */ \
        float##bit##_t k[4]; /* quantity */ \
    } a_polytrack3_f##bit##_t
__A_POLYTRACK3_T(32);
__A_POLYTRACK3_T(64);
#undef __A_POLYTRACK3_T

#undef __A_POLYTRACK5_T
#define __A_POLYTRACK5_T(bit)                   \
    typedef struct a_polytrack5_f##bit##_t      \
    {                                           \
        float##bit##_t t[2]; /* time         */ \
        float##bit##_t q[2]; /* position     */ \
        float##bit##_t v[2]; /* velocity     */ \
        float##bit##_t a[2]; /* acceleration */ \
        float##bit##_t k[6]; /* quantity     */ \
    } a_polytrack5_f##bit##_t
__A_POLYTRACK5_T(32);
__A_POLYTRACK5_T(64);
#undef __A_POLYTRACK5_T

#undef __A_POLYTRACK7_T
#define __A_POLYTRACK7_T(bit)                   \
    typedef struct a_polytrack7_f##bit##_t      \
    {                                           \
        float##bit##_t t[2]; /* time         */ \
        float##bit##_t q[2]; /* position     */ \
        float##bit##_t v[2]; /* velocity     */ \
        float##bit##_t a[2]; /* acceleration */ \
        float##bit##_t j[2]; /* jerk         */ \
        float##bit##_t k[8]; /* quantity     */ \
    } a_polytrack7_f##bit##_t
__A_POLYTRACK7_T(32);
__A_POLYTRACK7_T(64);
#undef __A_POLYTRACK7_T

__BEGIN_DECLS

/* function for cubic polynomial trajectory */

#undef __A_POLYTRACK3_INIT
#define __A_POLYTRACK3_INIT(bit, ctx, source, target) \
    void a_polytrack3_f##bit##_init(                  \
        a_polytrack3_f##bit##_t *ctx,                 \
        const float##bit##_t source[3],               \
        const float##bit##_t target[3])
extern __A_POLYTRACK3_INIT(32, ctx, source, target);
extern __A_POLYTRACK3_INIT(64, ctx, source, target);
#undef __A_POLYTRACK3_INIT

#undef __A_POLYTRACK3_POS
#define __A_POLYTRACK3_POS(bit, ctx, t)       \
    float##bit##_t a_polytrack3_f##bit##_pos( \
        const a_polytrack3_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK3_POS(32, ctx, t);
extern __A_POLYTRACK3_POS(64, ctx, t);
#undef __A_POLYTRACK3_POS

#undef __A_POLYTRACK3_VEC
#define __A_POLYTRACK3_VEC(bit, ctx, t)       \
    float##bit##_t a_polytrack3_f##bit##_vec( \
        const a_polytrack3_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK3_VEC(32, ctx, t);
extern __A_POLYTRACK3_VEC(64, ctx, t);
#undef __A_POLYTRACK3_VEC

#undef __A_POLYTRACK3_ACC
#define __A_POLYTRACK3_ACC(bit, ctx, t)       \
    float##bit##_t a_polytrack3_f##bit##_acc( \
        const a_polytrack3_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK3_ACC(32, ctx, t);
extern __A_POLYTRACK3_ACC(64, ctx, t);
#undef __A_POLYTRACK3_ACC

#undef __A_POLYTRACK3_ALL
#define __A_POLYTRACK3_ALL(bit, ctx, t, o)  \
    void a_polytrack3_f##bit##_all(         \
        const a_polytrack3_f##bit##_t *ctx, \
        const float##bit##_t t,             \
        float##bit##_t o[3])
extern __A_POLYTRACK3_ALL(32, ctx, t, o);
extern __A_POLYTRACK3_ALL(64, ctx, t, o);
#undef __A_POLYTRACK3_ALL

/* function for quintic polynomial trajectory */

#undef __A_POLYTRACK5_INIT
#define __A_POLYTRACK5_INIT(bit, ctx, source, target) \
    void a_polytrack5_f##bit##_init(                  \
        a_polytrack5_f##bit##_t *ctx,                 \
        const float##bit##_t source[4],               \
        const float##bit##_t target[4])
extern __A_POLYTRACK5_INIT(32, ctx, source, target);
extern __A_POLYTRACK5_INIT(64, ctx, source, target);
#undef __A_POLYTRACK5_INIT

#undef __A_POLYTRACK5_POS
#define __A_POLYTRACK5_POS(bit, ctx, t)       \
    float##bit##_t a_polytrack5_f##bit##_pos( \
        const a_polytrack5_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK5_POS(32, ctx, t);
extern __A_POLYTRACK5_POS(64, ctx, t);
#undef __A_POLYTRACK5_POS

#undef __A_POLYTRACK5_VEC
#define __A_POLYTRACK5_VEC(bit, ctx, t)       \
    float##bit##_t a_polytrack5_f##bit##_vec( \
        const a_polytrack5_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK5_VEC(32, ctx, t);
extern __A_POLYTRACK5_VEC(64, ctx, t);
#undef __A_POLYTRACK5_VEC

#undef __A_POLYTRACK5_ACC
#define __A_POLYTRACK5_ACC(bit, ctx, t)       \
    float##bit##_t a_polytrack5_f##bit##_acc( \
        const a_polytrack5_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK5_ACC(32, ctx, t);
extern __A_POLYTRACK5_ACC(64, ctx, t);
#undef __A_POLYTRACK5_ACC

#undef __A_POLYTRACK5_ALL
#define __A_POLYTRACK5_ALL(bit, ctx, t, o)  \
    void a_polytrack5_f##bit##_all(         \
        const a_polytrack5_f##bit##_t *ctx, \
        const float##bit##_t t,             \
        float##bit##_t o[3])
extern __A_POLYTRACK5_ALL(32, ctx, t, o);
extern __A_POLYTRACK5_ALL(64, ctx, t, o);
#undef __A_POLYTRACK5_ALL

/* function for hepta polynomial trajectory */

#undef __A_POLYTRACK7_INIT
#define __A_POLYTRACK7_INIT(bit, ctx, source, target) \
    void a_polytrack7_f##bit##_init(                  \
        a_polytrack7_f##bit##_t *ctx,                 \
        const float##bit##_t source[5],               \
        const float##bit##_t target[5])
extern __A_POLYTRACK7_INIT(32, ctx, source, target);
extern __A_POLYTRACK7_INIT(64, ctx, source, target);
#undef __A_POLYTRACK7_INIT

#undef __A_POLYTRACK7_POS
#define __A_POLYTRACK7_POS(bit, ctx, t)       \
    float##bit##_t a_polytrack7_f##bit##_pos( \
        const a_polytrack7_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK7_POS(32, ctx, t);
extern __A_POLYTRACK7_POS(64, ctx, t);
#undef __A_POLYTRACK7_POS

#undef __A_POLYTRACK7_VEC
#define __A_POLYTRACK7_VEC(bit, ctx, t)       \
    float##bit##_t a_polytrack7_f##bit##_vec( \
        const a_polytrack7_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK7_VEC(32, ctx, t);
extern __A_POLYTRACK7_VEC(64, ctx, t);
#undef __A_POLYTRACK7_VEC

#undef __A_POLYTRACK7_ACC
#define __A_POLYTRACK7_ACC(bit, ctx, t)       \
    float##bit##_t a_polytrack7_f##bit##_acc( \
        const a_polytrack7_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK7_ACC(32, ctx, t);
extern __A_POLYTRACK7_ACC(64, ctx, t);
#undef __A_POLYTRACK7_ACC

#undef __A_POLYTRACK7_JER
#define __A_POLYTRACK7_JER(bit, ctx, t)       \
    float##bit##_t a_polytrack7_f##bit##_jer( \
        const a_polytrack7_f##bit##_t *ctx,   \
        const float##bit##_t t)
extern __A_POLYTRACK7_JER(32, ctx, t);
extern __A_POLYTRACK7_JER(64, ctx, t);
#undef __A_POLYTRACK7_JER

#undef __A_POLYTRACK7_ALL
#define __A_POLYTRACK7_ALL(bit, ctx, t, o)  \
    void a_polytrack7_f##bit##_all(         \
        const a_polytrack7_f##bit##_t *ctx, \
        const float##bit##_t t,             \
        float##bit##_t o[4])
extern __A_POLYTRACK7_ALL(32, ctx, t, o);
extern __A_POLYTRACK7_ALL(64, ctx, t, o);
#undef __A_POLYTRACK7_ALL

__END_DECLS

/*!
 @ingroup        LIBA
 @defgroup       LIBA_POLYTRACK polynomial trajectory library
 @{
*/

#ifndef a_polytrack3_t
/*!
 @brief          Instance structure for cubic polynomial trajectory
 @param[in]      bit: bits for the floating-point data
*/
#define a_polytrack3_t(bit) a_polytrack3_f##bit##_t
#endif /* a_polytrack3_t */
#ifndef a_polytrack5_t
/*!
 @brief          Instance structure for quintic polynomial trajectory
 @param[in]      bit: bits for the floating-point data
*/
#define a_polytrack5_t(bit) a_polytrack5_f##bit##_t
#endif /* a_polytrack5_t */
#ifndef a_polytrack7_t
/*!
 @brief          Instance structure for hepta polynomial trajectory
 @param[in]      bit: bits for the floating-point data
*/
#define a_polytrack7_t(bit) a_polytrack7_f##bit##_t
#endif /* a_polytrack7_t */

#ifndef a_polytrack3_init
/*!
 @brief          Initialize function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \left\{\begin{array}{l}
  T=t_{1}-t_{0} \\
  h=q_{1}-q_{0} \\
  k_{0}=q_{0} \\
  k_{1}=v_{0} \\
  k_{2}=\cfrac{3 h-\left(2 v_{0}+v_{1}\right) T}{T^{2}} \\
  k_{3}=\cfrac{-2 h+\left(v_{0}+v_{1}\right) T}{T^{3}}
  \end{array}\right.
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of cubic polynomial trajectory
 @param[in]      source: source for trajectory
  @arg           0 time for source
  @arg           1 position for source
  @arg           2 velocity for source
 @param[in]      target: target for trajectory
  @arg           0 time for target
  @arg           1 position for target
  @arg           2 velocity for target
*/
#define a_polytrack3_init(bit, ctx, source, target) \
    a_polytrack3_f##bit##_init(ctx, source, target)
#endif /* a_polytrack3_init */

#ifndef a_polytrack3_pos
/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3} \\
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
#define a_polytrack3_pos(bit, ctx, t) \
    a_polytrack3_f##bit##_pos(ctx, t)
#endif /* a_polytrack3_pos */

#ifndef a_polytrack3_vec
/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2} \\
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
#define a_polytrack3_vec(bit, ctx, t) \
    a_polytrack3_f##bit##_vec(ctx, t)
#endif /* a_polytrack3_vec */

#ifndef a_polytrack3_acc
/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
#define a_polytrack3_acc(bit, ctx, t) \
    a_polytrack3_f##bit##_acc(ctx, t)
#endif /* a_polytrack3_acc */

#ifndef a_polytrack3_all
/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3} \\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2} \\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @param[out]     o: buffer of result
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
*/
#define a_polytrack3_all(bit, ctx, t, o) \
    a_polytrack3_f##bit##_all(ctx, t, o)
#endif /* a_polytrack3_all */

#ifndef a_polytrack5_init
/*!
 @brief          Initialize function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \left\{\begin{array}{l}
  T=t_{1}-t_{0} \\
  h=q_{1}-q_{0} \\
  k_{0}=q_{0} \\
  k_{1}=v_{0} \\
  k_{2}=\cfrac{a_{0}}{2} \\
  k_{3}=\cfrac{1}{2 T^{3}}\left[20 h-\left(8 v_{1}+12 v_{0}\right) T-\left(3 a_{0}-a_{1}\right) T^{2}\right] \\
  k_{4}=\cfrac{1}{2 T^{4}}\left[-30 h+\left(14 v_{1}+16 v_{0}\right) T+\left(3 a_{0}-2 a_{1}\right) T^{2}\right] \\
  k_{5}=\cfrac{1}{2 T^{5}}\left[12 h-6\left(v_{1}+v_{0}\right) T+\left(a_{1}-a_{0}\right) T^{2}\right]
  \end{array}\right.
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of quintic polynomial trajectory
 @param[in]      source: source for trajectory
  @arg           0 time for source
  @arg           1 position for source
  @arg           2 velocity for source
  @arg           3 acceleration for source
 @param[in]      target: target for trajectory
  @arg           0 time for target
  @arg           1 position for target
  @arg           2 velocity for target
  @arg           3 acceleration for target
*/
#define a_polytrack5_init(bit, ctx, source, target) \
    a_polytrack5_f##bit##_init(ctx, source, target)
#endif /* a_polytrack5_init */

#ifndef a_polytrack5_pos
/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
#define a_polytrack5_pos(bit, ctx, t) \
    a_polytrack5_f##bit##_pos(ctx, t)
#endif /* a_polytrack5_pos */

#ifndef a_polytrack5_vec
/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}\\
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
#define a_polytrack5_vec(bit, ctx, t) \
    a_polytrack5_f##bit##_vec(ctx, t)
#endif /* a_polytrack5_vec */

#ifndef a_polytrack5_acc
/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
#define a_polytrack5_acc(bit, ctx, t) \
    a_polytrack5_f##bit##_acc(ctx, t)
#endif /* a_polytrack5_acc */

#ifndef a_polytrack5_all
/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}\\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}\\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @param[out]     o: buffer of result
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
*/
#define a_polytrack5_all(bit, ctx, t, o) \
    a_polytrack5_f##bit##_all(ctx, t, o)
#endif /* a_polytrack5_all */

#ifndef a_polytrack7_init
/*!
 @brief          Initialize function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \left\{\begin{array}{l}
  T=t_{1}-t_{0} \\
  h=q_{1}-q_{0} \\
  k_{0}=q_{0} \\
  k_{1}=v_{0} \\
  k_{2}=\cfrac{a_{0}}{2} \\
  k_{3}=\cfrac{j_{0}}{6} \\
  k_{4}=\cfrac{210 h-T\left[\left(30 a_{0}-15 a_{1}\right) T+\left(4 j_{0}+j_{1}\right) T^{2}+120 v_{0}+90 v_{1}\right]}{6 T^{4}} \\
  k_{5}=\cfrac{-168 h+T\left[\left(20 a_{0}-14 a_{1}\right) T+\left(2 j_{0}+j_{1}\right) T^{2}+90 v_{0}+78 v_{1}\right]}{2 T^{5}} \\
  k_{6}=\cfrac{420 h-T\left[\left(45 a_{0}-39 a_{1}\right) T+\left(4 j_{0}+3 j_{1}\right) T^{2}+216 v_{0}+204 v_{1}\right]}{6 T^{6}} \\
  k_{7}=\cfrac{-120 h+T\left[\left(12 a_{0}-12 a_{1}\right) T+\left(j_{0}+j_{1}\right) T^{2}+60 v_{0}+60 v_{1}\right]}{6 T^{7}}
  \end{array}\right.
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in,out]  ctx: points to an instance of hepta polynomial trajectory
 @param[in]      source: source for trajectory
  @arg           0 time for source
  @arg           1 position for source
  @arg           2 velocity for source
  @arg           3 acceleration for source
  @arg           4 jerk for source
 @param[in]      target: target for trajectory
  @arg           0 time for target
  @arg           1 position for target
  @arg           2 velocity for target
  @arg           3 acceleration for target
  @arg           4 jerk for target
*/
#define a_polytrack7_init(bit, ctx, source, target) \
    a_polytrack7_f##bit##_init(ctx, source, target)
#endif /* a_polytrack7_init */

#ifndef a_polytrack7_pos
/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}+k_{6}\left(t-t_{0}\right)^{6}+k_{7}\left(t-t_{0}\right)^{7}\\
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
#define a_polytrack7_pos(bit, ctx, t) \
    a_polytrack7_f##bit##_pos(ctx, t)
#endif /* a_polytrack7_pos */

#ifndef a_polytrack7_vec
/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}+6 k_{6}\left(t-t_{0}\right)^{5}+7 k_{7}\left(t-t_{0}\right)^{6}\\
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
#define a_polytrack7_vec(bit, ctx, t) \
    a_polytrack7_f##bit##_vec(ctx, t)
#endif /* a_polytrack7_vec */

#ifndef a_polytrack7_acc
/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}+30 k_{6}\left(t-t_{0}\right)^{4}+42 k_{7}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
#define a_polytrack7_acc(bit, ctx, t) \
    a_polytrack7_f##bit##_acc(ctx, t)
#endif /* a_polytrack7_acc */

#ifndef a_polytrack7_jer
/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q^{(3)}(t)=6 k_{3}+24 k_{4}\left(t-t_{0}\right)+60 k_{5}\left(t-t_{0}\right)^{2}+120 k_{6}\left(t-t_{0}\right)^{3}+210 k_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         jerk output
*/
#define a_polytrack7_jer(bit, ctx, t) \
    a_polytrack7_f##bit##_jer(ctx, t)
#endif /* a_polytrack7_jer */

#ifndef a_polytrack7_all
/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}+k_{6}\left(t-t_{0}\right)^{6}+k_{7}\left(t-t_{0}\right)^{7}\\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}+6 k_{6}\left(t-t_{0}\right)^{5}+7 k_{7}\left(t-t_{0}\right)^{6}\\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}+30 k_{6}\left(t-t_{0}\right)^{4}+42 k_{7}\left(t-t_{0}\right)^{5}\\
  q^{(3)}(t)=6 k_{3}+24 k_{4}\left(t-t_{0}\right)+60 k_{5}\left(t-t_{0}\right)^{2}+120 k_{6}\left(t-t_{0}\right)^{3}+210 k_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in]      bit: bits for the floating-point data
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[out]     o: buffer of result
 @param[in]      t: current time
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
  @arg           3 jerk output
*/
#define a_polytrack7_all(bit, ctx, t, o) \
    a_polytrack7_f##bit##_all(ctx, t, o)
#endif /* a_polytrack7_all */

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_POLYTRACK_H__ */

/* END OF FILE */
