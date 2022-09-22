#ifndef __PID_H__
#define __PID_H__

#include "lua.h"
#include "a/pid.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int pid_from_(lua_State *L, int idx, a_pid_s *ctx);
int pid_into_(lua_State *L, a_pid_s *ctx);
int pid_meta_(lua_State *L);
int pid_func_(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* __PID_H__ */
