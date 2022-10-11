/***
 quintic polynomial trajectory
 @classmod polytrack5
*/

#ifndef __POLYTRACK5_H__
#define __POLYTRACK5_H__

#include "lua.h"
#include "a/polytrack.h"

#define POLYTRACK5_META_ (void *)(intptr_t)polytrack5_meta_
#define POLYTRACK5_FUNC_ (void *)(intptr_t)polytrack5_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int polytrack5_from_(lua_State *L, int idx, a_polytrack5_s *ctx);
int polytrack5_into_(lua_State *L, a_polytrack5_s *ctx);
int polytrack5_meta_(lua_State *L);
int polytrack5_func_(lua_State *L);

/***
 convert quintic polynomial trajectory userdata from table
 @tparam table tab quintic polynomial trajectory table
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function from
*/
int polytrack5_from(lua_State *L);

/***
 convert quintic polynomial trajectory userdata into table
 @param ctx quintic polynomial trajectory userdata
 @treturn table quintic polynomial trajectory table
 @function into
*/
int polytrack5_into(lua_State *L);

/***
 constructor for quintic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function new
*/
int polytrack5_new(lua_State *L);

/***
 initialize function for quintic polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack5 quintic polynomial trajectory userdata
 @function init
*/
int polytrack5_init(lua_State *L);

/***
 process function for quintic polynomial trajectory
 @tparam number ts current time unit(s)
 @treturn table {position,velocity,acceleration}
 @function out
*/
int polytrack5_out(lua_State *L);

/***
 process function for quintic polynomial trajectory position
 @tparam number ts current time unit(s)
 @treturn number position output
 @function pos
*/
int polytrack5_pos(lua_State *L);

/***
 process function for quintic polynomial trajectory velocity
 @tparam number ts current time unit(s)
 @treturn number velocity output
 @function vec
*/
int polytrack5_vec(lua_State *L);

/***
 process function for quintic polynomial trajectory acceleration
 @tparam number ts current time unit(s)
 @treturn number acceleration output
 @function acc
*/
int polytrack5_acc(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __POLYTRACK5_H__ */
