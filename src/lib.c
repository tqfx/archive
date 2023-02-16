#define LIBA_A_C
#include "a/a.h"

a_void_t a_swap(a_size_t const siz, a_vptr_t const lhs, a_vptr_t const rhs)
{
    a_byte_t *l = a_byte_p(lhs);
    a_byte_t *r = a_byte_p(rhs);
    for (a_byte_t *const d = r + siz; r != d; ++l, ++r)
    {
        *l ^= *r;
        *r ^= *l;
        *l ^= *r;
    }
}

a_umax_t a_hash_bkdr(a_cptr_t const str, a_umax_t val)
{
    if (str)
    {
        for (a_u8_t const *p = A_U8_P(str); *p; ++p)
        {
            val = val * 131 + *p;
        }
    }
    return val;
}

a_umax_t a_hash_bkdrn(a_cptr_t const ptr, a_size_t siz, a_umax_t val)
{
    if (ptr && siz)
    {
        for (a_u8_t const *p = A_U8_P(ptr); siz--; ++p)
        {
            val = val * 131 + *p;
        }
    }
    return val;
}
