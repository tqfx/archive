/*!
 @file           a_polytrack.h
 @brief          polynomial trajectory
 @details        Trajectory Planning for Automatic Machines and Robots.
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2021 tqfx
 \n \n
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 \n \n
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 \n \n
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
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

/*!
 @brief          Instance structure for cubic polynomial trajectory
*/
typedef struct
{
    float t[2];  //!< time
    float q[2];  //!< position
    float v[2];  //!< velocity
    float k[4];  //!< quantity
} a_polytrack3_t;

/*!
 @brief          Instance structure for quintic polynomial trajectory
*/
typedef struct
{
    float t[2];  //!< time
    float q[2];  //!< position
    float v[2];  //!< velocity
    float a[2];  //!< acceleration
    float k[6];  //!< quantity
} a_polytrack5_t;

/*!
 @brief          Instance structure for hepta polynomial trajectory
*/
typedef struct
{
    float t[2];  //!< time
    float q[2];  //!< position
    float v[2];  //!< velocity
    float a[2];  //!< acceleration
    float j[2];  //!< jerk
    float k[8];  //!< quantity
} a_polytrack7_t;

__BEGIN_DECLS

/*!
 @brief          Initialization function for cubic polynomial trajectory
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
 @param[in,out]  p: points to an instance of cubic polynomial trajectory
 @param[in]      source: source of trajectory
  @arg           0 time of source
  @arg           1 position of source
  @arg           2 velocity of source
 @param[in]      target: target of trajectory
  @arg           0 time of target
  @arg           1 position of target
  @arg           2 velocity of target
*/
extern void a_polytrack3_init(a_polytrack3_t *p,
                              float source[3],
                              float target[3]);

/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3} \\
  \end{array}
 \f}
 @param[in]      p: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
extern float a_polytrack3_pos(const a_polytrack3_t *p,
                              float t);

/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2} \\
  \end{array}
 \f}
 @param[in]      p: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
extern float a_polytrack3_vec(const a_polytrack3_t *p,
                              float t);

/*!
 @brief          Process function for cubic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)
  \end{array}
 \f}
 @param[in]      p: points to an instance of cubic polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
extern float a_polytrack3_acc(const a_polytrack3_t *p,
                              float t);

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
 @param[in]      p: points to an instance of cubic polynomial trajectory
 @param[out]     out: buffer of result
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
 @param[in]      t: current time
*/
extern void a_polytrack3_all(const a_polytrack3_t *p,
                             float out[3],
                             float t);

/*!
 @brief          Initialization function for quintic polynomial trajectory
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
 @param[in,out]  p: points to an instance of quintic polynomial trajectory
 @param[in]      source: source of trajectory
  @arg           0 time of source
  @arg           1 position of source
  @arg           2 velocity of source
  @arg           3 acceleration of source
 @param[in]      target: target of trajectory
  @arg           0 time of target
  @arg           1 position of target
  @arg           2 velocity of target
  @arg           3 acceleration of target
*/
extern void a_polytrack5_init(a_polytrack5_t *p,
                              float source[4],
                              float target[4]);

/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in]      p: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
extern float a_polytrack5_pos(const a_polytrack5_t *p,
                              float t);

/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}\\
  \end{array}
 \f}
 @param[in]      p: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
extern float a_polytrack5_vec(const a_polytrack5_t *p,
                              float t);

/*!
 @brief          Process function for quintic polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}
  \end{array}
 \f}
 @param[in]      p: points to an instance of quintic polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
extern float a_polytrack5_acc(const a_polytrack5_t *p,
                              float t);

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
 @param[in]      p: points to an instance of quintic polynomial trajectory
 @param[out]     out: buffer of result
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
 @param[in]      t: current time
*/
extern void a_polytrack5_all(const a_polytrack5_t *p,
                             float out[3],
                             float t);

/*!
 @brief          Initialization function for hepta polynomial trajectory
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
 @param[in,out]  p: points to an instance of hepta polynomial trajectory
 @param[in]      source: source of trajectory
  @arg           0 time of source
  @arg           1 position of source
  @arg           2 velocity of source
  @arg           3 acceleration of source
  @arg           4 jerk of source
 @param[in]      target: target of trajectory
  @arg           0 time of target
  @arg           1 position of target
  @arg           2 velocity of target
  @arg           3 acceleration of target
  @arg           4 jerk of target
*/
extern void a_polytrack7_init(a_polytrack7_t *p,
                              float source[5],
                              float target[5]);

/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q(t)=k_{0}+k_{1}\left(t-t_{0}\right)+k_{2}\left(t-t_{0}\right)^{2}+k_{3}\left(t-t_{0}\right)^{3}+k_{4}\left(t-t_{0}\right)^{4}+k_{5}\left(t-t_{0}\right)^{5}+k_{6}\left(t-t_{0}\right)^{6}+k_{7}\left(t-t_{0}\right)^{7}\\
  \end{array}
 \f}
 @param[in]      p: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         position output
*/
extern float a_polytrack7_pos(const a_polytrack7_t *p,
                              float t);

/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \dot{q}(t)=k_{1}+2 k_{2}\left(t-t_{0}\right)+3 k_{3}\left(t-t_{0}\right)^{2}+4 k_{4}\left(t-t_{0}\right)^{3}+5 k_{5}\left(t-t_{0}\right)^{4}+6 k_{6}\left(t-t_{0}\right)^{5}+7 k_{7}\left(t-t_{0}\right)^{6}\\
  \end{array}
 \f}
 @param[in]      p: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         velocity output
*/
extern float a_polytrack7_vec(const a_polytrack7_t *p,
                              float t);

/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  \ddot{q}(t)=2 k_{2}+6 k_{3}\left(t-t_{0}\right)+12 k_{4}\left(t-t_{0}\right)^{2}+20 k_{5}\left(t-t_{0}\right)^{3}+30 k_{6}\left(t-t_{0}\right)^{4}+42 k_{7}\left(t-t_{0}\right)^{5}\\
  \end{array}
 \f}
 @param[in]      p: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         acceleration output
*/
extern float a_polytrack7_acc(const a_polytrack7_t *p,
                              float t);

/*!
 @brief          Process function for hepta polynomial trajectory
 @details
 \f{aligned}{
  \begin{array}{l}
  q^{(3)}(t)=6 k_{3}+24 k_{4}\left(t-t_{0}\right)+60 k_{5}\left(t-t_{0}\right)^{2}+120 k_{6}\left(t-t_{0}\right)^{3}+210 k_{7}\left(t-t_{0}\right)^{4}
  \end{array}
 \f}
 @param[in]      p: points to an instance of hepta polynomial trajectory
 @param[in]      t: current time
 @return         jerk output
*/
extern float a_polytrack7_jer(const a_polytrack7_t *p,
                              float t);

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
 @param[in]      p: points to an instance of hepta polynomial trajectory
 @param[out]     out: buffer of result
  @arg           0 position output
  @arg           1 velocity output
  @arg           2 acceleration output
  @arg           3 jerk output
 @param[in]      t: current time
*/
extern void a_polytrack7_all(const a_polytrack7_t *p,
                             float out[4],
                             float t);

__END_DECLS

/*!< @} */

/* Enddef to prevent recursive inclusion */
#endif /* __A_POLYTRACK_H__ */

/* END OF FILE */
