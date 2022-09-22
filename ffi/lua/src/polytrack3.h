#ifndef __POLYTRACK3_H__
#define __POLYTRACK3_H__

#include "lua.h"
#include "a/polytrack.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int polytrack3_from_(lua_State *L, int idx, a_polytrack3_s *ctx);
int polytrack3_into_(lua_State *L, a_polytrack3_s *ctx);
int polytrack3_meta_(lua_State *L);
int polytrack3_func_(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __POLYTRACK3_H__ */
