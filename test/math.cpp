/*!
 @file math.cpp
 @brief test math
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

#include "a_math.h"

#include <math.h>
#include <stdio.h>
#include <inttypes.h>

#ifndef _MSC_VER
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* _MSC_VER */
static union
{
    float f32;
    uint32_t u32;
    struct
    {
        uint32_t f : 23;
        uint32_t e : 8;
        uint32_t s : 1;
    } s32[1];
} b32[1];
#ifndef _MSC_VER
#pragma GCC diagnostic pop
#endif /* _MSC_VER */

static union
{
    double f64;
    uint64_t u64;
    struct
    {
        uint64_t f : 53;
        uint64_t e : 10;
        uint64_t s : 1;
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
        printf("0x%" PRIX32 "    %" PRIu32 ",0x%02" PRIX32 ",0x%06" PRIX32 "    %+f\n",
               b32->u32, b32->s32->s, b32->s32->e, b32->s32->f, (double)b32->f32);
    }
    for (unsigned int i = 0; i != sizeof(datat) / sizeof(double); ++i)
    {
        b64->f64 = datat[i];
        printf("0x%" PRIX64 "    %" PRIu64 ",0x%03" PRIX64 ",0x%014" PRIX64 "    %+f\n",
               b64->u64, (uint64_t)b64->s64->s, (uint64_t)b64->s64->e, b64->s64->f, b64->f64);
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
        printf("1/sqrt(%g):\t%-10g%-10g\n", (double)datasqrt[i],
               1 / (double)sqrtf(datasqrt[i]),
               (double)a_inv_sqrt(datasqrt[i]));
    }

    printf("a_sqrt(4):\t%-10lu%-10llu\n", a_sqrtul(4), a_sqrtull(4));

    return 0;
}
