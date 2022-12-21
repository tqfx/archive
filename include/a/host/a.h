/*!
 @file a.h
 @brief algorithm library on host
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef LIBA_HOST_A_H
#define LIBA_HOST_A_H

#include "a/a.h"
#include <stdlib.h>

A_INTERN a_void_t a_die(a_vptr_t ptr) { free(ptr); }
A_INTERN a_vptr_t a_new(a_vptr_t ptr, a_size_t siz)
{
    return realloc(ptr, siz);
}

#define a_new(T, ptr, num) a_cast_s(T *, a_new(ptr, sizeof(T) * (num)))

#endif /* LIBA_HOST_A_H */
