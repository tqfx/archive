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

/*!
 @ingroup        LIBA
 @defgroup       LIBA_POLYTRACK polynomial trajectory library
 @{
*/

#undef __A_POLYTRACK3_T
/*!
 @brief          Instance structure for cubic polynomial trajectory
*/
#define __A_POLYTRACK3_T(def, type) \
    typedef struct def##_t          \
    {                               \
        type t[2]; /* time     */   \
        type q[2]; /* position */   \
        type v[2]; /* velocity */   \
        type k[4]; /* quantity */   \
    } def##_t
__A_POLYTRACK3_T(a_polytrack3, double);
__A_POLYTRACK3_T(a_polytrack3f, float);
#undef __A_POLYTRACK3_T

#undef __A_POLYTRACK5_T
/*!
 @brief          Instance structure for quintic polynomial trajectory
*/
#define __A_POLYTRACK5_T(def, type)   \
    typedef struct def##_t            \
    {                                 \
        type t[2]; /* time         */ \
        type q[2]; /* position     */ \
        type v[2]; /* velocity     */ \
        type a[2]; /* acceleration */ \
        type k[6]; /* quantity     */ \
    } def##_t
__A_POLYTRACK5_T(a_polytrack5, double);
__A_POLYTRACK5_T(a_polytrack5f, float);
#undef __A_POLYTRACK5_T

#undef __A_POLYTRACK7_T
/*!
 @brief          Instance structure for hepta polynomial trajectory
*/
#define __A_POLYTRACK7_T(def, type)   \
    typedef struct def##_t            \
    {                                 \
        type t[2]; /* time         */ \
        type q[2]; /* position     */ \
        type v[2]; /* velocity     */ \
        type a[2]; /* acceleration */ \
        type j[2]; /* jerk         */ \
        type k[8]; /* quantity     */ \
    } def##_t
__A_POLYTRACK7_T(a_polytrack7, double);
__A_POLYTRACK7_T(a_polytrack7f, float);
#undef __A_POLYTRACK7_T

__BEGIN_DECLS

/* function for cubic polynomial trajectory */

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
extern void a_polytrack3_init(a_polytrack3_t *ctx, const double source[3], const double target[3]);
extern void a_polytrack3f_init(a_polytrack3f_t *ctx, const float source[3], const float target[3]);

/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3} \\
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
extern double a_polytrack3_pos(const a_polytrack3_t *ctx, double t);
extern float a_polytrack3f_pos(const a_polytrack3f_t *ctx, float t);

/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2} \\
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
extern double a_polytrack3_vec(const a_polytrack3_t *ctx, double t);
extern float a_polytrack3f_vec(const a_polytrack3f_t *ctx, float t);

/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
extern double a_polytrack3_acc(const a_polytrack3_t *ctx, double t);
extern float a_polytrack3f_acc(const a_polytrack3f_t *ctx, float t);

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
 @param[in]      ctx: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @param[out]     o: buffer for result
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
*/
extern void a_polytrack3_all(const a_polytrack3_t *ctx, double t, double o[3]);
extern void a_polytrack3f_all(const a_polytrack3f_t *ctx, float t, float o[3]);

/* function for quintic polynomial trajectory */

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
extern void a_polytrack5_init(a_polytrack5_t *ctx, const double source[4], const double target[4]);
extern void a_polytrack5f_init(a_polytrack5f_t *ctx, const float source[4], const float target[4]);

/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
extern double a_polytrack5_pos(const a_polytrack5_t *ctx, double t);
extern float a_polytrack5f_pos(const a_polytrack5f_t *ctx, float t);

/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}\\
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
extern double a_polytrack5_vec(const a_polytrack5_t *ctx, double t);
extern float a_polytrack5f_vec(const a_polytrack5f_t *ctx, float t);

/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
extern double a_polytrack5_acc(const a_polytrack5_t *ctx, double t);
extern float a_polytrack5f_acc(const a_polytrack5f_t *ctx, float t);

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
 @param[in]      ctx: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @param[out]     o: buffer for result
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
*/
extern void a_polytrack5_all(const a_polytrack5_t *ctx, double t, double o[3]);
extern void a_polytrack5f_all(const a_polytrack5f_t *ctx, float t, float o[3]);

/* function for hepta polynomial trajectory */

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
extern void a_polytrack7_init(a_polytrack7_t *ctx, const double source[5], const double target[5]);
extern void a_polytrack7f_init(a_polytrack7f_t *ctx, const float source[5], const float target[5]);

/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}+k_{6}\left(t-t_{0}\right)^{6}+k_{7}\left(t-t_{0}\right)^{7}\\
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
extern double a_polytrack7_pos(const a_polytrack7_t *ctx, double t);
extern float a_polytrack7f_pos(const a_polytrack7f_t *ctx, float t);

/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}+6 k_{6}\left(t-t_{0}\right)^{5}+7 k_{7}\left(t-t_{0}\right)^{6}\\
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
extern double a_polytrack7_vec(const a_polytrack7_t *ctx, double t);
extern float a_polytrack7f_vec(const a_polytrack7f_t *ctx, float t);

/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}+30 k_{6}\left(t-t_{0}\right)^{4}+42 k_{7}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
extern double a_polytrack7_acc(const a_polytrack7_t *ctx, double t);
extern float a_polytrack7f_acc(const a_polytrack7f_t *ctx, float t);

/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q^{(3)}(t)=6 k_{3}+24 k_{4}\left(t-t_{0}\right)+60 k_{5}\left(t-t_{0}\right)^{2}+120 k_{6}\left(t-t_{0}\right)^{3}+210 k_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         jerk output
*/
extern double a_polytrack7_jer(const a_polytrack7_t *ctx, double t);
extern float a_polytrack7f_jer(const a_polytrack7f_t *ctx, float t);

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
 @param[in]      ctx: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @param[out]     o: buffer for result
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
  @arg           3 jerk output
*/
extern void a_polytrack7_all(const a_polytrack7_t *ctx, double t, double o[4]);
extern void a_polytrack7f_all(const a_polytrack7f_t *ctx, float t, float o[4]);

__END_DECLS

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_POLYTRACK_H__ */

/* END OF FILE */
