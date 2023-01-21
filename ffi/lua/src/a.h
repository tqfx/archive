#ifndef FFI_A_H
#define FFI_A_H

#include "a/a.h"
#if !defined FFI_NUM
#define FFI_NUM a_real_t
#endif /* FFI_NUM */
#include "ffi.h"

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

A_PUBLIC int l_field(lua_State *L, const char *i, const char *s, uint32_t v);
A_PUBLIC int l_setter(lua_State *L);
A_PUBLIC int luaopen_liba(lua_State *L);
A_PUBLIC int luaopen_liba_mf(lua_State *L);
A_PUBLIC int luaopen_liba_tf(lua_State *L);
A_PUBLIC int luaopen_liba_pid(lua_State *L);
A_PUBLIC int luaopen_liba_fpid(lua_State *L);
A_PUBLIC int luaopen_liba_complex(lua_State *L);
A_PUBLIC int luaopen_liba_polytrack3(lua_State *L);
A_PUBLIC int luaopen_liba_polytrack5(lua_State *L);
A_PUBLIC int luaopen_liba_polytrack7(lua_State *L);
A_PUBLIC int luaopen_liba_version(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FFI_A_H */
