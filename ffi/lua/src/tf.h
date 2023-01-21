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

#include "a.h"
#include "a/tf.h"

#define L_TF_FUNC_ (void *)(intptr_t)l_tf_func_ // NOLINT(performance-no-int-to-ptr)
#define L_TF_META_ (void *)(intptr_t)l_tf_meta_ // NOLINT(performance-no-int-to-ptr)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int l_tf_func_(lua_State *L);
int l_tf_meta_(lua_State *L);

/***
 destructor for transfer function
 @function die
*/
int l_tf_die(lua_State *L);

/***
 constructor for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn tf transfer function userdata
 @function new
*/
int l_tf_new(lua_State *L);

/***
 initialize function for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn tf transfer function userdata
 @function init
*/
int l_tf_init(lua_State *L);

/***
 process function for transfer function
 @tparam number x controller output
 @treturn number feedback
 @function proc
*/
int l_tf_proc(lua_State *L);

/***
 zero function for transfer function
 @treturn tf transfer function userdata
 @function zero
*/
int l_tf_zero(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FFI_TF_H */
