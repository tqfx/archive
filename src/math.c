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
        u.x *= A_F32_C(1.5) - A_SQ(u.x) * xh;
        u.x *= A_F32_C(1.5) - A_SQ(u.x) * xh;
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
