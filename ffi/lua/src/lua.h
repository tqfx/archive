#ifndef __LUA_H__
#define __LUA_H__

#include "a/a.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* diagnostic */
#include "lauxlib.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
#include <string.h>

#define Larray(T) (sizeof(T) / sizeof(*(T)))
#define Lstack(L) lua_show(L, __LINE__)

typedef struct
{
    const char *name;
    lua_Integer data;
} RegEnum;

typedef struct
{
    const char *name;
    lua_Number data;
} RegFnum;

typedef struct
{
    const char *name;
    lua_CFunction func;
} RegFunc;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void lua_show(lua_State *L, int line);

void reg_enum(lua_State *L, int idx, const char *name, lua_Integer data);
void reg_enums(lua_State *L, int idx, const RegEnum *tab);
void reg_fnums(lua_State *L, int idx, const RegFnum *tab);
void reg_func(lua_State *L, int idx, const char *name, lua_CFunction func);
void reg_funcs(lua_State *L, int idx, const RegFunc *tab);
void reg_name(lua_State *L, int idx, const char *name);

void arraynum_get(lua_State *L, int idx, lua_Number *ptr, unsigned int num);
void arraynum_set(lua_State *L, int idx, const lua_Number *ptr, unsigned int num);

void *userdata_get(lua_State *L);
void *userdata_new(lua_State *L, size_t sz, int op);
void userdata_seti(lua_State *L, int idx, int dat);
void userdata_setp(lua_State *L, int idx, void *ptr);

int luaopen_liba_pid(lua_State *L);
int luaopen_liba_polytrack3(lua_State *L);
int luaopen_liba_polytrack5(lua_State *L);
int luaopen_liba_polytrack7(lua_State *L);
int luaopen_liba_version(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

A_PUBLIC LUA_API int luaopen_liba(lua_State *L);

#endif /* __LUA_H__ */
