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

#ifndef L_TF_H
#define L_TF_H

#include "a.h"
#include "a/tf.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int LMODULE(tf_func_)(lua_State *L, int ret);
A_PUBLIC int LMODULE(tf_meta_)(lua_State *L, int ret);

/***
 destructor for transfer function
 @function die
*/
A_PUBLIC int LMODULE(tf_die)(lua_State *L);

/***
 constructor for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn tf transfer function userdata
 @function new
*/
A_PUBLIC int LMODULE(tf_new)(lua_State *L);

/***
 initialize function for transfer function
 @tparam table num numerator table
 @tparam table den denominator table
 @treturn tf transfer function userdata
 @function init
*/
A_PUBLIC int LMODULE(tf_init)(lua_State *L);

/***
 process function for transfer function
 @tparam number x controller output
 @treturn number feedback
 @function proc
*/
A_PUBLIC int LMODULE(tf_proc)(lua_State *L);

/***
 zero function for transfer function
 @treturn tf transfer function userdata
 @function zero
*/
A_PUBLIC int LMODULE(tf_zero)(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* L_TF_H */
