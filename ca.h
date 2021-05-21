/*!
 @file           ca.h
 @brief          Algorithm library
 @author         tqfx tqfx@foxmail.com
 @version        0
 @date           2021-05-21
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
#ifndef __CA_H__
#define __CA_H__

#undef __BEGIN_DECLS
#undef __END_DECLS
#if defined(__cplusplus)
#define __BEGIN_DECLS \
    extern "C"        \
    {
#define __END_DECLS \
    }
#else
#define __BEGIN_DECLS
#define __END_DECLS
#endif /* __cplusplus */

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static inline
#endif /* __STATIC_INLINE */

/**
 * @addtogroup     CA Algorithm
 * @details        computational algorithm
 *                 control algorithm
 *                 filtering algorithm
 *                 conversion algorithm
*/

/**
 * @brief          Computational algorithm
*/
#include "ca_math.h"

/**
 * @brief          Control algorithm
*/
#include "ca_pid.h"

/**
 * @brief          Filtering algorithm
*/
#include "ca_lpf.h"

/**
 * @brief          Conversion algorithm
*/
#include "ahrs.h"
#include "zyx.h"

/* Enddef to prevent recursive inclusion */
#endif /* __CA_H__ */

/* END OF FILE */
