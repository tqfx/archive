#ifndef __POLYTRACK5_H__
#define __POLYTRACK5_H__

#include "lua.h"
#include "a/polytrack.h"

#define POLYTRACK5_META_ (void *)(intptr_t)polytrack5_meta_
#define POLYTRACK5_FUNC_ (void *)(intptr_t)polytrack5_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int polytrack5_from_(lua_State *L, int idx, a_polytrack5_s *ctx);
int polytrack5_into_(lua_State *L, a_polytrack5_s *ctx);
int polytrack5_meta_(lua_State *L);
int polytrack5_func_(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __POLYTRACK5_H__ */
