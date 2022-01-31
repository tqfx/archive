/*!
 @file test_math.c
 @brief test math
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_math.h"

#include <stdio.h>
#include <math.h>

#pragma pack(push, 4)
static union
{
    float f32;
    unsigned long u32;
    struct
    {
        unsigned long f : 23;
        unsigned long e : 8;
        unsigned long s : 1;
    } s32[1];
} b32[1];
#pragma pack(pop)

static union
{
    double f64;
    unsigned long long u64;
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
        (double)NAN,
        (double)INFINITY,
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
        printf("0x%lX    %u,0x%02X,0x%06lX    %+f\n",
               b32->u32,
               (unsigned int)b32->s32->s,
               (unsigned int)b32->s32->e,
               (unsigned long)b32->s32->f,
               (double)b32->f32);
    }
    for (unsigned int i = 0; i != sizeof(datat) / sizeof(double); ++i)
    {
        b64->f64 = datat[i];
        printf("0x%llX    %u,0x%03X,0x%014llX    %+f\n",
               b64->u64,
               (unsigned int)b64->s64->s,
               (unsigned int)b64->s64->e,
               (unsigned long long)b64->s64->f,
               b64->f64);
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
        printf("1/sqrt(%g):\t%-10g%-10g\n",
               (double)datasqrt[i],
               1 / (double)sqrtf(datasqrt[i]),
               (double)a_inv_sqrt(datasqrt[i]));
    }

    printf("a_sqrt(4):\t%-10lu%-10llu\n", a_sqrtul(4), a_sqrtull(4));

    return 0;
}
