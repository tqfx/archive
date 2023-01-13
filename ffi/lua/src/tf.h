/***
 transfer function
 @classmod tf
*/

/***
 transfer function
 @field num numerator table
 @field den denominator table
 @table tf
*/

#ifndef FFI_TF_H
#define FFI_TF_H

#include "lua.h"
#include "a/tf.h"

#define TF_FUNC_ (void *)(intptr_t)tf_func_ // NOLINT(performance-no-int-to-ptr)
#define TF_META_ (void *)(intptr_t)tf_meta_ // NOLINT(performance-no-int-to-ptr)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int tf_func_(lua_State *L);
int tf_meta_(lua_State *L);

/***
 destructor for transfer function
 @function die
*/
int tf_die(lua_State *L);

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

#endif /* FFI_TF_H */
