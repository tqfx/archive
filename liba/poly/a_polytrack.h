/*!
 @file a_polytrack.h
 @brief polynomial trajectory
 @details Trajectory Planning for Automatic Machines and Robots.
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_POLYTRACK_H__
#define __A_POLYTRACK_H__

#include "liba.h"

#undef __A_POLYTRACK3_T
/*!
 @brief Instance structure for cubic polynomial trajectory
*/
#define __A_POLYTRACK3_T(_def, _type) \
    typedef struct _def##_s           \
    {                                 \
        _type t[2]; /* time     */    \
        _type q[2]; /* position */    \
        _type v[2]; /* velocity */    \
        _type k[4]; /* quantity */    \
    } _def##_s
__A_POLYTRACK3_T(a_polytrack3, double);
__A_POLYTRACK3_T(a_polytrack3f, float);
#undef __A_POLYTRACK3_T

#undef __A_POLYTRACK5_T
/*!
 @brief Instance structure for quintic polynomial trajectory
*/
#define __A_POLYTRACK5_T(_def, _type)  \
    typedef struct _def##_s            \
    {                                  \
        _type t[2]; /* time         */ \
        _type q[2]; /* position     */ \
        _type v[2]; /* velocity     */ \
        _type a[2]; /* acceleration */ \
        _type k[6]; /* quantity     */ \
    } _def##_s
__A_POLYTRACK5_T(a_polytrack5, double);
__A_POLYTRACK5_T(a_polytrack5f, float);
#undef __A_POLYTRACK5_T

#undef __A_POLYTRACK7_T
/*!
 @brief Instance structure for hepta polynomial trajectory
*/
#define __A_POLYTRACK7_T(_def, _type)  \
    typedef struct _def##_s            \
    {                                  \
        _type t[2]; /* time         */ \
        _type q[2]; /* position     */ \
        _type v[2]; /* velocity     */ \
        _type a[2]; /* acceleration */ \
        _type j[2]; /* jerk         */ \
        _type k[8]; /* quantity     */ \
    } _def##_s
__A_POLYTRACK7_T(a_polytrack7, double);
__A_POLYTRACK7_T(a_polytrack7f, float);
#undef __A_POLYTRACK7_T

__BEGIN_DECLS

/* function for cubic polynomial trajectory */

/*!
 @brief Initialize function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  q=q_{1}-q_{0}\\
  k_{0}=q_{0}\\
  k_{1}=v_{0}\\
  k_{2}=\cfrac{\left(-2\,v_{0}-v_{1}\right)\,t+3\,q}{t^2}\\
  k_{3}=\cfrac{\left(v_{0}+v_{1}\right)\,t-2\,q}{t^3}
  \end{array}\right.
 \f}
 @param[in,out] ctx: points to an instance of cubic polynomial trajectory
 @param[in] source: source for trajectory
  @arg 0 time for source
  @arg 1 position for source
  @arg 2 velocity for source
 @param[in] target: target for trajectory
  @arg 0 time for target
  @arg 1 position for target
  @arg 2 velocity for target
*/
void a_polytrack3_init(a_polytrack3_s *ctx, const double source[3], const double target[3]) __NONNULL_ALL;
void a_polytrack3f_init(a_polytrack3f_s *ctx, const float source[3], const float target[3]) __NONNULL_ALL;

/*!
 @brief Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3} \\
  \end{array}
 \f}
 @param[in] ctx: points to an instance of cubic polynomial trajectory
 @param[in] t: current time
 @return position output
*/
double a_polytrack3_pos(const a_polytrack3_s *ctx, double t) __NONNULL((1));
float a_polytrack3f_pos(const a_polytrack3f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2} \\
  \end{array}
 \f}
 @param[in] ctx: points to an instance of cubic polynomial trajectory
 @param[in] t: current time
 @return velocity output
*/
double a_polytrack3_vec(const a_polytrack3_s *ctx, double t) __NONNULL((1));
float a_polytrack3f_vec(const a_polytrack3f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
 @param[in] ctx: points to an instance of cubic polynomial trajectory
 @param[in] t: current time
 @return acceleration output
*/
double a_polytrack3_acc(const a_polytrack3_s *ctx, double t) __NONNULL((1));
float a_polytrack3f_acc(const a_polytrack3f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3} \\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2} \\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
 @param[in] ctx: points to an instance of cubic polynomial trajectory
 @param[in] t: current time
 @param[out] o: buffer for result
  @arg 0 position output
  @arg 1 velocity output
  @arg 2 acceleration output
*/
void a_polytrack3_all(const a_polytrack3_s *ctx, double t, double o[3]) __NONNULL((1, 3));
void a_polytrack3f_all(const a_polytrack3f_s *ctx, float t, float o[3]) __NONNULL((1, 3));

/* function for quintic polynomial trajectory */

/*!
 @brief Initialize function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  q=q_{1}-q_{0}\\
  k_{0}=q_{0}\\
  k_{1}=v_{0}\\
  k_{2}=\cfrac{a_{0}}{2}\\
  k_{3}=\cfrac{\left(a_{1}-3\,a_{0}\right)\,t^2+\left(-12\,v_{0}-8\,v_{1}\right)\,t+20\,q}{2\,t^3}\\
  k_{4}=\cfrac{\left(3\,a_{0}-2\,a_{1}\right)\,t^2+\left(16\,v_{0}+14\,v_{1}\right)\,t-30\,q}{2\,t^4}\\
  k_{5}=\cfrac{\left(a_{1}-a_{0}\right)\,t^2+\left(-6\,v_{0}-6\,v_{1}\right)\,t+12\,q}{2\,t^5}
  \end{array}\right.
 \f}
 @param[in,out] ctx: points to an instance of quintic polynomial trajectory
 @param[in] source: source for trajectory
  @arg 0 time for source
  @arg 1 position for source
  @arg 2 velocity for source
  @arg 3 acceleration for source
 @param[in] target: target for trajectory
  @arg 0 time for target
  @arg 1 position for target
  @arg 2 velocity for target
  @arg 3 acceleration for target
*/
void a_polytrack5_init(a_polytrack5_s *ctx, const double source[4], const double target[4]) __NONNULL_ALL;
void a_polytrack5f_init(a_polytrack5f_s *ctx, const float source[4], const float target[4]) __NONNULL_ALL;

/*!
 @brief Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in] ctx: points to an instance of quintic polynomial trajectory
 @param[in] t: current time
 @return position output
*/
double a_polytrack5_pos(const a_polytrack5_s *ctx, double t) __NONNULL((1));
float a_polytrack5f_pos(const a_polytrack5f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}\\
  \end{array}
 \f}
 @param[in] ctx: points to an instance of quintic polynomial trajectory
 @param[in] t: current time
 @return velocity output
*/
double a_polytrack5_vec(const a_polytrack5_s *ctx, double t) __NONNULL((1));
float a_polytrack5f_vec(const a_polytrack5f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
 @param[in] ctx: points to an instance of quintic polynomial trajectory
 @param[in] t: current time
 @return acceleration output
*/
double a_polytrack5_acc(const a_polytrack5_s *ctx, double t) __NONNULL((1));
float a_polytrack5f_acc(const a_polytrack5f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}\\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}\\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
 @param[in] ctx: points to an instance of quintic polynomial trajectory
 @param[in] t: current time
 @param[out] o: buffer for result
  @arg 0 position output
  @arg 1 velocity output
  @arg 2 acceleration output
*/
void a_polytrack5_all(const a_polytrack5_s *ctx, double t, double o[3]) __NONNULL((1, 3));
void a_polytrack5f_all(const a_polytrack5f_s *ctx, float t, float o[3]) __NONNULL((1, 3));

/* function for hepta polynomial trajectory */

/*!
 @brief Initialize function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \left\{\begin{array}{l}
  t=t_{1}-t_{0}\\
  q=q_{1}-q_{0}\\
  k_{0}=q_{0}\\
  k_{1}=v_{0}\\
  k_{2}=\cfrac{a_{0}}{2}\\
  k_{3}=\cfrac{j_{0}}{6}\\
  k_{4}=\cfrac{\left(-4\,j_{0}-j_{1}\right)\,t^3+\left(15\,a_{1}-30\,a_{0}\right)\,t^2+\left(-120\,v_{0}-90\,v_{1}\right)\,t+210\,q}{6\,t^4}\\
  k_{5}=\cfrac{\left(2\,j_{0}+j_{1}\right)\,t^3+\left(20\,a_{0}-14\,a_{1}\right)\,t^2+\left(90\,v_{0}+78\,v_{1}\right)\,t-168\,q}{2\,t^5}\\
  k_{6}=\cfrac{\left(-4\,j_{0}-3\,j_{1}\right)\,t^3+\left(39\,a_{1}-45\,a_{0}\right)\,t^2+\left(-216\,v_{0}-204\,v_{1}\right)\,t+420\,q}{6\,t^6}\\
  k_{7}=\cfrac{\left(j_{0}+j_{1}\right)\,t^3+\left(12\,a_{0}-12\,a_{1}\right)\,t^2+\left(60\,v_{0}+60\,v_{1}\right)\,t-120\,q}{6\,t^7}
  \end{array}\right.
 \f}
 @param[in,out] ctx: points to an instance of hepta polynomial trajectory
 @param[in] source: source for trajectory
  @arg 0 time for source
  @arg 1 position for source
  @arg 2 velocity for source
  @arg 3 acceleration for source
  @arg 4 jerk for source
 @param[in] target: target for trajectory
  @arg 0 time for target
  @arg 1 position for target
  @arg 2 velocity for target
  @arg 3 acceleration for target
  @arg 4 jerk for target
*/
void a_polytrack7_init(a_polytrack7_s *ctx, const double source[5], const double target[5]) __NONNULL_ALL;
void a_polytrack7f_init(a_polytrack7f_s *ctx, const float source[5], const float target[5]) __NONNULL_ALL;

/*!
 @brief Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}+k_{6}\left(t-t_{0}\right)^{6}+k_{7}\left(t-t_{0}\right)^{7}\\
  \end{array}
 \f}
 @param[in] ctx: points to an instance of hepta polynomial trajectory
 @param[in] t: current time
 @return position output
*/
double a_polytrack7_pos(const a_polytrack7_s *ctx, double t) __NONNULL((1));
float a_polytrack7f_pos(const a_polytrack7f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}+6 k_{6}\left(t-t_{0}\right)^{5}+7 k_{7}\left(t-t_{0}\right)^{6}\\
  \end{array}
 \f}
 @param[in] ctx: points to an instance of hepta polynomial trajectory
 @param[in] t: current time
 @return velocity output
*/
double a_polytrack7_vec(const a_polytrack7_s *ctx, double t) __NONNULL((1));
float a_polytrack7f_vec(const a_polytrack7f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}+30 k_{6}\left(t-t_{0}\right)^{4}+42 k_{7}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in] ctx: points to an instance of hepta polynomial trajectory
 @param[in] t: current time
 @return acceleration output
*/
double a_polytrack7_acc(const a_polytrack7_s *ctx, double t) __NONNULL((1));
float a_polytrack7f_acc(const a_polytrack7f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q^{(3)}(t)=6 k_{3}+24 k_{4}\left(t-t_{0}\right)+60 k_{5}\left(t-t_{0}\right)^{2}+120 k_{6}\left(t-t_{0}\right)^{3}+210 k_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in] ctx: points to an instance of hepta polynomial trajectory
 @param[in] t: current time
 @return jerk output
*/
double a_polytrack7_jer(const a_polytrack7_s *ctx, double t) __NONNULL((1));
float a_polytrack7f_jer(const a_polytrack7f_s *ctx, float t) __NONNULL((1));

/*!
 @brief Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}+k_{6}\left(t-t_{0}\right)^{6}+k_{7}\left(t-t_{0}\right)^{7}\\
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}+6 k_{6}\left(t-t_{0}\right)^{5}+7 k_{7}\left(t-t_{0}\right)^{6}\\
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}+30 k_{6}\left(t-t_{0}\right)^{4}+42 k_{7}\left(t-t_{0}\right)^{5}\\
  q^{(3)}(t)=6 k_{3}+24 k_{4}\left(t-t_{0}\right)+60 k_{5}\left(t-t_{0}\right)^{2}+120 k_{6}\left(t-t_{0}\right)^{3}+210 k_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in] ctx: points to an instance of hepta polynomial trajectory
 @param[in] t: current time
 @param[out] o: buffer for result
  @arg 0 position output
  @arg 1 velocity output
  @arg 2 acceleration output
  @arg 3 jerk output
*/
void a_polytrack7_all(const a_polytrack7_s *ctx, double t, double o[4]) __NONNULL((1, 3));
void a_polytrack7f_all(const a_polytrack7f_s *ctx, float t, float o[4]) __NONNULL((1, 3));

__END_DECLS

#if defined(__STDC_VERSION__) && (__STDC_VERSION__ >= 201112)
/* function for cubic polynomial trajectory */
#define a_polytrack3_init(_ctx, _source, _target) \
    _Generic((_ctx),                              \
             default                              \
             : a_polytrack3_init,                 \
               a_polytrack3f_s *                  \
             : a_polytrack3f_init)(_ctx, _source, _target)
#define a_polytrack3_pos(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack3_pos,   \
               float               \
             : a_polytrack3f_pos)(_ctx, _t)
#define a_polytrack3_vec(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack3_vec,   \
               float               \
             : a_polytrack3f_vec)(_ctx, _t)
#define a_polytrack3_acc(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack3_acc,   \
               float               \
             : a_polytrack3f_acc)(_ctx, _t)
#define a_polytrack3_all(_ctx, _t, _o) \
    _Generic((_t),                     \
             default                   \
             : a_polytrack3_all,       \
               float                   \
             : a_polytrack3f_all)(_ctx, _t, _o)
/* function for quintic polynomial trajectory */
#define a_polytrack5_init(_ctx, _source, _target) \
    _Generic((_ctx),                              \
             default                              \
             : a_polytrack5_init,                 \
               a_polytrack5f_s *                  \
             : a_polytrack5f_init)(_ctx, _source, _target)
#define a_polytrack5_pos(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack5_pos,   \
               float               \
             : a_polytrack5f_pos)(_ctx, _t)
#define a_polytrack5_vec(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack5_vec,   \
               float               \
             : a_polytrack5f_vec)(_ctx, _t)
#define a_polytrack5_acc(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack5_acc,   \
               float               \
             : a_polytrack5f_acc)(_ctx, _t)
#define a_polytrack5_all(_ctx, _t, _o) \
    _Generic((_t),                     \
             default                   \
             : a_polytrack5_all,       \
               float                   \
             : a_polytrack5f_all)(_ctx, _t, _o)
/* function for hepta polynomial trajectory */
#define a_polytrack7_init(_ctx, _source, _target) \
    _Generic((_ctx),                              \
             default                              \
             : a_polytrack7_init,                 \
               a_polytrack7f_s *                  \
             : a_polytrack7f_init)(_ctx, _source, _target)
#define a_polytrack7_pos(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack7_pos,   \
               float               \
             : a_polytrack7f_pos)(_ctx, _t)
#define a_polytrack7_vec(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack7_vec,   \
               float               \
             : a_polytrack7f_vec)(_ctx, _t)
#define a_polytrack7_acc(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack7_acc,   \
               float               \
             : a_polytrack7f_acc)(_ctx, _t)
#define a_polytrack7_jer(_ctx, _t) \
    _Generic((_t),                 \
             default               \
             : a_polytrack7_jer,   \
               float               \
             : a_polytrack7f_jer)(_ctx, _t)
#define a_polytrack7_all(_ctx, _t, _o) \
    _Generic((_t),                     \
             default                   \
             : a_polytrack7_all,       \
               float                   \
             : a_polytrack7f_all)(_ctx, _t, _o)
#endif /* __STDC_VERSION__ */

/* Enddef to prevent recursive inclusion */
#endif /* __A_POLYTRACK_H__ */

/* END OF FILE */
