#include "a/real.h"
#include <math.h>

#undef a_real_log1p
a_real_t a_real_log1p(a_real_t x)
{
    return A_REAL_F(log, x + 1);
}

#undef a_real_hypot
a_real_t a_real_hypot(a_real_t x, a_real_t y)
{
    return A_REAL_F(sqrt, x * x + y * y);
}

#undef a_real_atan2
a_real_t a_real_atan2(a_real_t x, a_real_t y)
{
    if (x > 0)
    {
        return A_REAL_F(atan, y / x);
    }
    if (x < 0)
    {
        if (y >= 0)
        {
            return A_REAL_F(atan, y / x) + A_REAL_PI;
        }
        return A_REAL_F(atan, y / x) - A_REAL_PI;
    }
    if (y > 0)
    {
        return +A_REAL_PI;
    }
    if (y < 0)
    {
        return -A_REAL_PI;
    }
    return 0;
}
