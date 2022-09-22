#ifndef __MF_H__
#define __MF_H__

#include "lua.h"
#include "a/mf.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int mf_into_(lua_State *L, int idx, a_real_t *ptr);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __MF_H__ */
