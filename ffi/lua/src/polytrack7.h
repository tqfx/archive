/***
 hepta polynomial trajectory
 @classmod polytrack7
*/

#ifndef __POLYTRACK7_H__
#define __POLYTRACK7_H__

#include "lua.h"
#include "a/polytrack.h"

#define POLYTRACK7_META_ (void *)(intptr_t)polytrack7_meta_
#define POLYTRACK7_FUNC_ (void *)(intptr_t)polytrack7_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int polytrack7_from_(lua_State *L, int idx, a_polytrack7_s *ctx);
int polytrack7_into_(lua_State *L, a_polytrack7_s *ctx);
int polytrack7_meta_(lua_State *L);
int polytrack7_func_(lua_State *L);

/***
 convert hepta polynomial trajectory userdata from table
 @tparam table tab hepta polynomial trajectory table
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function from
*/
int polytrack7_from(lua_State *L);

/***
 convert hepta polynomial trajectory userdata into table
 @param ctx hepta polynomial trajectory userdata
 @treturn table hepta polynomial trajectory table
 @function into
*/
int polytrack7_into(lua_State *L);

/***
 constructor for hepta polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] number j0 jerk for source
 @tparam[opt] number j1 jerk for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function new
*/
int polytrack7_new(lua_State *L);

/***
 initialize function for hepta polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] number j0 jerk for source
 @tparam[opt] number j1 jerk for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function init
*/
int polytrack7_init(lua_State *L);

/***
 process function for hepta polynomial trajectory
 @tparam number ts current time unit(s)
 @treturn table {position,velocity,acceleration,jerk}
 @function out
*/
int polytrack7_out(lua_State *L);

/***
 process function for hepta polynomial trajectory position
 @tparam number ts current time unit(s)
 @treturn number position output
 @function pos
*/
int polytrack7_pos(lua_State *L);

/***
 process function for hepta polynomial trajectory velocity
 @tparam number ts current time unit(s)
 @treturn number velocity output
 @function vec
*/
int polytrack7_vec(lua_State *L);

/***
 process function for hepta polynomial trajectory acceleration
 @tparam number ts current time unit(s)
 @treturn number acceleration output
 @function acc
*/
int polytrack7_acc(lua_State *L);

/***
 process function for hepta polynomial trajectory jerk
 @tparam number ts current time unit(s)
 @treturn number jerk output
 @function jer
*/
int polytrack7_jer(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __POLYTRACK7_H__ */
