/***
 cubic polynomial trajectory
 @classmod polytrack3
*/

#ifndef __POLYTRACK3_H__
#define __POLYTRACK3_H__

#include "lua.h"
#include "a/polytrack.h"

#define POLYTRACK3_META_ (void *)(intptr_t)polytrack3_meta_
#define POLYTRACK3_FUNC_ (void *)(intptr_t)polytrack3_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int polytrack3_from_(lua_State *L, int idx, a_polytrack3_s *ctx);
int polytrack3_into_(lua_State *L, a_polytrack3_s *ctx);
int polytrack3_meta_(lua_State *L);
int polytrack3_func_(lua_State *L);

/***
 convert cubic polynomial trajectory userdata from table
 @tparam table tab cubic polynomial trajectory table
 @treturn polytrack3 cubic polynomial trajectory userdata
 @function from
*/
int polytrack3_from(lua_State *L);

/***
 convert cubic polynomial trajectory userdata into table
 @param ctx cubic polynomial trajectory userdata
 @treturn table cubic polynomial trajectory table
 @function into
*/
int polytrack3_into(lua_State *L);

/***
 constructor for cubic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack3 cubic polynomial trajectory userdata
 @function new
*/
int polytrack3_new(lua_State *L);

/***
 initialize function for cubic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack3 cubic polynomial trajectory userdata
 @function init
*/
int polytrack3_init(lua_State *L);

/***
 process function for cubic polynomial trajectory
 @tparam number ts current time unit(s)
 @treturn table {position,velocity,acceleration}
 @function out
*/
int polytrack3_out(lua_State *L);

/***
 process function for cubic polynomial trajectory position
 @tparam number ts current time unit(s)
 @treturn number position output
 @function pos
*/
int polytrack3_pos(lua_State *L);

/***
 process function for cubic polynomial trajectory velocity
 @tparam number ts current time unit(s)
 @treturn number velocity output
 @function vec
*/
int polytrack3_vec(lua_State *L);

/***
 process function for cubic polynomial trajectory acceleration
 @tparam number ts current time unit(s)
 @treturn number acceleration output
 @function acc
*/
int polytrack3_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __POLYTRACK3_H__ */
