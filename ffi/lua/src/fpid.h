#ifndef __FPID_H__
#define __FPID_H__

#include "mf.h"
#include "pid.h"
#include "a/fpid.h"

#define FPID_META_ (void *)(intptr_t)fpid_meta_
#define FPID_FUNC_ (void *)(intptr_t)fpid_func_

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
