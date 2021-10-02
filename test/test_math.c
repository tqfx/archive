/*!
 @file           test_math.c
 @brief          math test
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

#include "liba.h"

#include <stdio.h>
#include <math.h>

static union
{
    long i32;
    float f32;
    struct
    {
        unsigned long f : 23;
        unsigned long e : 8;
        unsigned long s : 1;
    } s32[1];
} b32[1];

static union
{
    double f64;
    long long i64;
    struct
    {
        unsigned long long f : 53;
        unsigned long long e : 10;
        unsigned long long s : 1;
    } s64[1];
} b64[1];

int main(void)
{
    static double datat[] = {
        -0.0,
        1,
        1.0625,
        1.125,
        1.25,
        1.5,
        1.75,
        1.9999999,
        -2,
    };

    for (unsigned int i = 0; i != sizeof(datat) / sizeof(double); ++i)
    {
        b32->f32 = (float)datat[i];
        printf("%+f\t0x%zX\t%u,0x%02X,0x%06X\n",
               (double)b32->f32,
               b32->i32,
               b32->s32->s,
               b32->s32->e,
               b32->s32->f);
    }
    for (unsigned int i = 0; i != sizeof(datat) / sizeof(double); ++i)
    {
        b64->f64 = datat[i];
        printf("%+f\t0x%llX\t%u,0x%03X,0x%014llX\n",
               b64->f64,
               b64->i64,
               b64->s64->s,
               b64->s64->e,
               (unsigned long long)b64->s64->f);
    }

    static float datasqrt[] = {
        -1,
        -0,
        1e-10F,
        1,
        4,
        2.5F * 2.5F,
    };

    for (unsigned int i = 0; i != sizeof(datasqrt) / sizeof(float); ++i)
    {
        printf("1/sqrt(%g):\t%g\t%g\n",
               (double)datasqrt[i],
               1 / (double)sqrtf(datasqrt[i]),
               (double)a_inv_sqrt(datasqrt[i]));
    }

    return 0;
}

/* END OF FILE */
