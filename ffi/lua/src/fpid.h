/***
 fuzzy proportional integral derivative controller
 @classmod fpid
*/

#ifndef __FPID_H__
#define __FPID_H__

#include "mf.h"
#include "pid.h"
#include "a/fpid.h"

#define FPID_META_ (void *)(intptr_t)fpid_meta_
#define FPID_FUNC_ (void *)(intptr_t)fpid_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int fpid_from_(lua_State *L, int idx, a_fpid_s *ctx);
int fpid_into_(lua_State *L, a_fpid_s *ctx);
int fpid_meta_(lua_State *L);
int fpid_func_(lua_State *L);

/***
 convert fuzzy PID controller userdata from table
 @tparam table tab fuzzy PID controller table
 @treturn fpid fuzzy PID controller userdata
 @function from
*/
int fpid_from(lua_State *L);

/***
 convert fuzzy PID controller userdata into table
 @param ctx fuzzy PID controller userdata
 @treturn table fuzzy PID controller table
 @function into
*/
int fpid_into(lua_State *L);

/***
 constructor for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @tparam number dt sampling time unit(s)
 @tparam table mmp points to membership function parameter table, an array terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @tparam number imin minimum input
 @tparam number imax maximum input
 @tparam number omin minimum output
 @tparam number omax maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function new
*/
int fpid_new(lua_State *L);

/***
 initialize function for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @tparam number dt sampling time unit(s)
 @tparam table mmp points to membership function parameter table, an array terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @tparam number imin minimum input
 @tparam number imax maximum input
 @tparam number omin minimum output
 @tparam number omax maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function init
*/
int fpid_init(lua_State *L);

/***
 calculate function for fuzzy PID controller
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function proc
*/
int fpid_proc(lua_State *L);

/***
 zero function for fuzzy PID controller
 @treturn fpid fuzzy PID controller userdata
 @function zero
*/
int fpid_zero(lua_State *L);

/***
 set rule base for fuzzy PID controller
 @tparam table mmp points to membership function parameter table, an array terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @treturn fpid fuzzy PID controller userdata
 @function buff
*/
int fpid_base(lua_State *L);

/***
 set buffer for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @treturn fpid fuzzy PID controller userdata
 @function buff
*/
int fpid_buff(lua_State *L);

/***
 set proportional integral derivative constant for fuzzy PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn fpid fuzzy PID controller userdata
 @function kpid
*/
int fpid_kpid(lua_State *L);

/***
 set sampling period for fuzzy PID controller
 @tparam number dt sampling time unit(s)
 @treturn fpid fuzzy PID controller userdata
 @function time
*/
int fpid_time(lua_State *L);

/***
 positional fuzzy PID controller
 @tparam number max maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function pos
*/
int fpid_pos(lua_State *L);

/***
 incremental fuzzy PID controller
 @treturn fpid fuzzy PID controller userdata
 @function inc
*/
int fpid_inc(lua_State *L);

/***
 turn off fuzzy PID controller
 @treturn fpid fuzzy PID controller userdata
 @function off
*/
int fpid_off(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __FPID_H__ */
