/*!
 @file a.c
 @brief algorithm library
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#include "a/a.h"

a_noret_t a_swap(a_size_t siz, a_vptr_t lhs, a_vptr_t rhs)
{
    a_byte_t *l = (a_byte_t *)lhs;
    a_byte_t *r = (a_byte_t *)rhs;
    for (a_byte_t *d = r + siz; r != d; ++l, ++r)
    {
        *l ^= *r;
        *r ^= *l;
        *l ^= *r;
    }
}
