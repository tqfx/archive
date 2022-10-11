/***
 proportional integral derivative controller
 @classmod pid
*/

#ifndef __PID_H__
#define __PID_H__

#include "lua.h"
#include "a/pid.h"

#define PID_META_ (void *)(intptr_t)pid_meta_
#define PID_FUNC_ (void *)(intptr_t)pid_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int pid_from_(lua_State *L, int idx, a_pid_s *ctx);
int pid_into_(lua_State *L, a_pid_s *ctx);
int pid_meta_(lua_State *L);
int pid_func_(lua_State *L);

/***
 convert PID controller userdata from table
 @tparam table tab PID controller table
 @treturn pid PID controller userdata
 @function from
*/
int pid_from(lua_State *L);

/***
 convert PID controller userdata into table
 @param ctx PID controller userdata
 @treturn table PID controller table
 @function into
*/
int pid_into(lua_State *L);

/***
 constructor for PID controller
 @tparam number dt sampling time unit(s)
 @tparam[opt] number kp proportional constant
 @tparam[opt] number ki integral constant
 @tparam[opt] number kd derivative constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid PID controller userdata
 @function new
*/
int pid_new(lua_State *L);

/***
 calculate function for PID controller
 @tparam number dt sampling time unit(s)
 @tparam[opt] number kp proportional constant
 @tparam[opt] number ki integral constant
 @tparam[opt] number kd derivative constant
 @tparam number min minimum output
 @tparam number max maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn pid PID controller userdata
 @function init
*/
int pid_init(lua_State *L);

/***
 calculate function for PID controller
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function proc
*/
int pid_proc(lua_State *L);

/***
 zero function for PID controller
 @treturn pid PID controller userdata
 @function zero
*/
int pid_zero(lua_State *L);

/***
 set proportional integral derivative constant for PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn pid PID controller userdata
 @function kpid
*/
int pid_kpid(lua_State *L);

/***
 set sampling period for PID controller
 @tparam number dt sampling time unit(s)
 @treturn pid PID controller userdata
 @function time
*/
int pid_time(lua_State *L);

/***
 positional PID controller
 @tparam number max maximum intergral output
 @treturn pid PID controller userdata
 @function pos
*/
int pid_pos(lua_State *L);

/***
 incremental PID controller
 @treturn pid PID controller userdata
 @function inc
*/
int pid_inc(lua_State *L);

/***
 turn off PID controller
 @treturn pid PID controller userdata
 @function off
*/
int pid_off(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __PID_H__ */
