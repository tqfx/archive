#ifndef __POLYTRACK7_H__
#define __POLYTRACK7_H__

#include "lua.h"
#include "a/polytrack.h"

#define POLYTRACK7_META_ (void *)(intptr_t)polytrack7_meta_
#define POLYTRACK7_FUNC_ (void *)(intptr_t)polytrack7_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int polytrack7_from_(lua_State *L, int idx, a_polytrack7_s *ctx);
int polytrack7_into_(lua_State *L, a_polytrack7_s *ctx);
int polytrack7_meta_(lua_State *L);
int polytrack7_func_(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __POLYTRACK7_H__ */
