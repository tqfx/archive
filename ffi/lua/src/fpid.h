/***
 fuzzy proportional integral derivative controller
 @classmod fpid
*/

/***
 fuzzy proportional integral derivative controller
 @field dt sampling time unit(s)
 @field kp proportional constant
 @field ki integral constant
 @field kd derivative constant
 @field mode controller mode
 @field outmin minimum final output
 @field outmax maximum final output
 @field summax maximum integral output
 @field col number of columns in the rule base
 @field buf maximum number triggered by the rule
 @field out controller output
 @field fdb cache feedback
 @field ec error change
 @field e error input
 @table fpid
*/

#ifndef __FPID_H__
#define __FPID_H__

#include "pid.h"
#include "a/fpid.h"

#define FPID_META_ (void *)(intptr_t)fpid_meta_
#define FPID_FUNC_ (void *)(intptr_t)fpid_func_

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int fpid_meta_(lua_State *L);
int fpid_func_(lua_State *L);

/***
 destructor for fuzzy PID controller
 @function die
*/
int fpid_die(lua_State *L);

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
 set proportional integral derivative constant for fuzzy PID controller
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn fpid fuzzy PID controller userdata
 @function kpid
*/
int fpid_kpid(lua_State *L);

/***
 set input extreme value for fuzzy PID controller
 @tparam number min mininum input
 @tparam number max maxinum input
 @treturn fpid fuzzy PID controller userdata
 @function ilim
*/
int fpid_ilim(lua_State *L);

/***
 set output extreme value for fuzzy PID controller
 @tparam number min mininum output
 @tparam number max maxinum output
 @treturn fpid fuzzy PID controller userdata
 @function olim
*/
int fpid_olim(lua_State *L);

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
