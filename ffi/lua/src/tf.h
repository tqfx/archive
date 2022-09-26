#ifndef __TF_H__
#define __TF_H__

#include "lua.h"
#include "a/tf.h"

#define TF_META_ (void *)(intptr_t)tf_meta_
#define TF_FUNC_ (void *)(intptr_t)tf_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int tf_from_(lua_State *L, int idx, a_tf_s *ctx);
int tf_into_(lua_State *L, a_tf_s *ctx);
int tf_meta_(lua_State *L);
int tf_func_(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __TF_H__ */
