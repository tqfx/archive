#ifndef __FPID_H__
#define __FPID_H__

#include "pid.h"
#include "a/fpid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int fpid_from_(lua_State *L, int idx, a_fpid_s *ctx);
int fpid_into_(lua_State *L, a_fpid_s *ctx);
int fpid_meta_(lua_State *L);
int fpid_func_(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __FPID_H__ */
