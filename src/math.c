#include "math.h"

a_f32_t a_sqrt_inv(a_f32_t x)
{
    union
    {
        a_f32_t x;
        a_u32_t u;
    } u;
    u.x = x;
    if (a_likely(x > 0))
    {
        a_f32_t xh = A_F32_C(0.5) * x;
        u.u = A_U32_C(0x5F3759DF) - (u.u >> 1);
        u.x *= A_F32_C(1.5) - u.x * u.x * xh;
        u.x *= A_F32_C(1.5) - u.x * u.x * xh;
    }
    else if (x < 0)
    {
        u.u = A_F32_NNAN;
    }
    else
    {
        u.u |= A_F32_PINF;
    }
    return u.x;
}

a_u32_t a_u32_sqrt(a_u32_t x)
{
    a_u32_t y = 0;
    for (a_uint_t i = 0; i < 32; i += 2)
    {
        a_u32_t k = A_U32_C(0x40000000) >> i;
        a_u32_t j = y + k;
        if (x >= j)
        {
            x -= j;
            y = (y >> 1) | k;
        }
        else
        {
            y >>= 1;
        }
    }
    return y;
}

a_u64_t a_u64_sqrt(a_u64_t x)
{
    a_u64_t y = 0;
    for (a_uint_t i = 0; i < 64; i += 2)
    {
        a_u64_t k = A_U64_C(0x4000000000000000) >> i;
        a_u64_t j = y + k;
        if (x >= j)
        {
            x -= j;
            y = (y >> 1) | k;
        }
        else
        {
            y >>= 1;
        }
    }
    return y;
}
