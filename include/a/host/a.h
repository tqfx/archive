/*!
 @file a.h
 @brief algorithm library on host
 @copyright Copyright (C) 2020-present tqfx, All rights reserved.
*/

#ifndef LIBA_HOST_A_H
#define LIBA_HOST_A_H

#include "../a.h"
#include <stdlib.h>

#if defined(A_HAVE_MIMALLOC_H)
#include <mimalloc-override.h>
#endif /* A_HAVE_MIMALLOC_H */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_EXTERN a_vptr_t a_alloc(a_vptr_t vptr, a_size_t size);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

A_INTERN a_void_t a_die(a_vptr_t ptr)
{
    a_alloc(ptr, 0);
}

A_INTERN a_vptr_t a_new(a_vptr_t ptr, a_size_t siz)
{
    return a_alloc(ptr, siz);
}

#define a_new(T, ptr, num) a_cast_s(T *, a_new(ptr, sizeof(T) * (num)))

#endif /* LIBA_HOST_A_H */
