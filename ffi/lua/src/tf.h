/***
 transfer function
 @classmod tf
*/

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

/***
 convert transfer function userdata from table
 @tparam table tab transfer function table
 @treturn tf transfer function userdata
 @function from
*/
int tf_from(lua_State *L);

/***
 convert transfer function userdata into table
 @treturn table transfer function table
 @function into
*/
int tf_into(lua_State *L);

/***
 constructor for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn tf transfer function userdata
 @function new
*/
int tf_new(lua_State *L);

/***
 initialize function for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn tf transfer function userdata
 @function init
*/
int tf_init(lua_State *L);

/***
 process function for transfer function
 @tparam number x controller output
 @treturn number feedback
 @function proc
*/
int tf_proc(lua_State *L);

/***
 zero function for transfer function
 @treturn tf transfer function userdata
 @function zero
*/
int tf_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __TF_H__ */
