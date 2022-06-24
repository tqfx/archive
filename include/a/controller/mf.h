/*!
 @file mf.h
 @brief membership function
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#pragma once
#ifndef __A_MF_H__
#define __A_MF_H__

#include "../def.h"
#include "../real.h"

#include <math.h>

/*!
 @brief Instance enumeration for membership function
*/
typedef enum a_mf_e
{
    A_MF_NONE,  //!< None
    A_MF_GAUSS, //!< Gaussian membership function
    A_MF_GBELL, //!< Generalized bell-shaped membership function
    A_MF_SIG,   //!< Sigmoidal membership function
    A_MF_TRAP,  //!< Trapezoidal membership function
    A_MF_TRI,   //!< Triangular membership function
    A_MF_Z,     //!< Z-shaped membership function
} a_mf_e;

/*!
 @brief Gaussian membership function
 @f[
  f(x,\sigma,c)=e^{-\frac{(x-c)^2}{2\sigma^2}}
 @f]
 @param[in] x Any element
 @param[in] sigma sigma
 @param[in] c c
 @return Membership
*/
A_INLINE a_real_t a_mf_gauss(a_real_t x, a_real_t sigma, a_real_t c)
{
    return A_REAL_F(exp, A_REAL_F(pow, (x - c) / sigma, 2) / -2);
}

/*!
 @brief Generalized bell-shaped membership function
 @f[
  f(x,a,b,c)=\frac{1}{1+\left|\frac{x-c}{a}\right|^{2b}}
 @f]
 @param[in] x Any element
 @param[in] a a
 @param[in] b b
 @param[in] c c
 @return Membership
*/
A_INLINE a_real_t a_mf_gbell(a_real_t x, a_real_t a, a_real_t b, a_real_t c)
{
    return 1 / (A_REAL_F(pow, A_REAL_F(fabs, (x - c) / a), 2 * b) + 1);
}

/*!
 @brief Sigmoidal membership function
 @f[
  f(x,a,c)=\frac{1}{1+e^{-a(x-c)}}
 @f]
 @param[in] x Any element
 @param[in] a a
 @param[in] c c
 @return Membership
*/
A_INLINE a_real_t a_mf_sig(a_real_t x, a_real_t a, a_real_t c)
{
    return 1 / (A_REAL_F(exp, (c - x) * a) + 1);
}

/*!
 @brief Trapezoidal membership function
 @f[
  f(x,a,b,c,d)=\begin{cases}
  0 & x \le a \\
  \frac{x-a}{b-a} & a \le x \le b \\
  1 & b \le x \le c \\
  \frac{d-x}{d-c} & c \le x \le d \\
  0 & x \ge d \\
  \end{cases}
 @f]
 @param[in] x Any element
 @param[in] a a
 @param[in] b b
 @param[in] c c
 @param[in] d d
 @return Membership
*/
A_INLINE a_real_t a_mf_trap(a_real_t x, a_real_t a, a_real_t b, a_real_t c, a_real_t d)
{
    if (x < a)
    {
        x = 0;
    }
    else if (x < b)
    {
        x = (x - a) / (b - a);
    }
    else if (x < c)
    {
        x = 1;
    }
    else if (x < d)
    {
        x = (d - x) / (d - c);
    }
    else
    {
        x = 0;
    }
    return x;
}

/*!
 @brief Triangular membership function
 @f[
  f(x,a,b,c,d)=\begin{cases}
  0 & x \le a \\
  \frac{x-a}{b-a} & a \le x \le b \\
  \frac{c-x}{c-b} & b \le x \le c \\
  0 & x \ge c \\
  \end{cases}
 @f]
 @param[in] x Any element
 @param[in] a a
 @param[in] b b
 @param[in] c c
 @return Membership
*/
A_INLINE a_real_t a_mf_tri(a_real_t x, a_real_t a, a_real_t b, a_real_t c)
{
    if (x < a)
    {
        x = 0;
    }
    else if (x < b)
    {
        x = (x - a) / (b - a);
    }
    else if (x < c)
    {
        x = (c - x) / (c - b);
    }
    else
    {
        x = 0;
    }
    return x;
}

/*!
 @brief Z-shaped membership function
 @f[
  f(x,a,b,c,d)=\begin{cases}
  1 & x \le a \\
  1-2(\frac{x-a}{b-a})^2 & a \le x \le \frac{a+b}{2} \\
  2(\frac{x-b}{b-a})^2 & \frac{a+b}{2} \le x \le b \\
  0 & x \ge c \\
  \end{cases}
 @f]
 @param[in] x Any element
 @param[in] a a
 @param[in] b b
 @return Membership
*/
A_INLINE a_real_t a_mf_z(a_real_t x, a_real_t a, a_real_t b)
{
    if (x < a)
    {
        x = 1;
    }
    else if (x < (a + b) / 2)
    {
        x = 1 - 2 * A_REAL_F(pow, (x - a) / (b - a), 2);
    }
    else if (x < b)
    {
        x = 2 * A_REAL_F(pow, (x - b) / (b - a), 2);
    }
    else
    {
        x = 0;
    }
    return x;
}

/*!
 @brief membership function
 @param[in] t Type for membership function
  @arg @ref A_MF_GAUSS a_mf_gauss(x, sigma, c)
  @arg @ref A_MF_GBELL a_mf_gbell(x, a, b, c)
  @arg @ref A_MF_SIG   a_mf_sig(x, a, c)
  @arg @ref A_MF_TRAP  a_mf_trap(x, a, b, c, d)
  @arg @ref A_MF_TRI   a_mf_tri(x, a, b, c)
  @arg @ref A_MF_Z     a_mf_z(x, a, b)
 @param[in] x Any element
 @param[in] p Paramarrays
  @arg p[2] @ref a_mf_gauss @ref a_mf_sig @ref a_mf_z
  @arg p[3] @ref a_mf_gbell @ref a_mf_tri
  @arg p[4] @ref a_mf_trap
 @return Membership
*/
A_INLINE a_real_t a_mf(unsigned int t, a_real_t x, a_real_t *p)
{
    switch (t)
    {
    case A_MF_GAUSS:
        return a_mf_gauss(x, p[0], p[1]);
    case A_MF_GBELL:
        return a_mf_gbell(x, p[0], p[1], p[2]);
    case A_MF_SIG:
        return a_mf_sig(x, p[0], p[1]);
    case A_MF_TRAP:
        return a_mf_trap(x, p[0], p[1], p[2], p[3]);
    case A_MF_TRI:
        return a_mf_tri(x, p[0], p[1], p[2]);
    case A_MF_Z:
        return a_mf_z(x, p[0], p[1]);
    case A_MF_NONE:
    default:
        return 0;
    }
}

#endif /* __A_MF_H__ */
