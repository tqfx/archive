/***
 proportional integral derivative controller
 @classmod pid
*/

/***
 proportional integral derivative controller
 @field dt sampling time unit(s)
 @field kp proportional constant
 @field ki integral constant
 @field kd derivative constant
 @field mode controller mode
 @field outmin minimum final output
 @field outmax maximum final output
 @field summax maximum integral output
 @field out controller output
 @field fdb cache feedback
 @field ec error change
 @field e error input
 @table pid
*/

#ifndef FFI_PID_H
#define FFI_PID_H

#include "a.h"
#include "a/pid.h"

#define L_PID_FUNC_ (void *)(intptr_t)l_pid_func_ // NOLINT(performance-no-int-to-ptr)
#define L_PID_META_ (void *)(intptr_t)l_pid_meta_ // NOLINT(performance-no-int-to-ptr)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int l_pid_func_(lua_State *L);
int l_pid_meta_(lua_State *L);

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
int l_pid_new(lua_State *L);

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
int l_pid_init(lua_State *L);

/***
 calculate function for PID controller
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function proc
*/
int l_pid_proc(lua_State *L);

/***
 zero function for PID controller
 @treturn pid PID controller userdata
 @function zero
*/
int l_pid_zero(lua_State *L);

/***
 set proportional integral derivative constant for PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn pid PID controller userdata
 @function kpid
*/
int l_pid_kpid(lua_State *L);

/***
 positional PID controller
 @tparam number max maximum intergral output
 @treturn pid PID controller userdata
 @function pos
*/
int l_pid_pos(lua_State *L);

/***
 incremental PID controller
 @treturn pid PID controller userdata
 @function inc
*/
int l_pid_inc(lua_State *L);

/***
 turn off PID controller
 @treturn pid PID controller userdata
 @function off
*/
int l_pid_off(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FFI_PID_H */
