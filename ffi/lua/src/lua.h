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

#define Larray(A) (sizeof(A) / sizeof(*A))
#define Lstack(L) lua_show(L, __LINE__)

typedef struct
{
    const char *name;
    lua_Integer data;
} SEnum;

typedef struct
{
    const char *name;
    lua_Integer *data;
} GEnum;

typedef struct
{
    const char *name;
    lua_Number data;
} SFnum;

typedef struct
{
    const char *name;
    lua_Number *data;
} GFnum;

typedef struct
{
    const char *name;
    const lua_Number *ptr;
    a_size_t num;
} SFnums;

typedef struct
{
    const char *name;
    lua_Number *ptr;
    a_size_t num;
} GFnums;

typedef struct
{
    const char *name;
    lua_CFunction func;
} SFunc;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

void lua_show(lua_State *L, int line);

lua_Integer get_enum(lua_State *L, int idx, const char *name);
void set_enum(lua_State *L, int idx, const char *name, lua_Integer data);
void set_enums(lua_State *L, int idx, const SEnum *tab);
lua_Number get_fnum(lua_State *L, int idx, const char *name);
void set_fnum(lua_State *L, int idx, const char *name, lua_Number data);
void set_fnums(lua_State *L, int idx, const SFnum *tab);
void get_fnums(lua_State *L, int idx, const GFnum *tab);
void set_func(lua_State *L, int idx, const char *name, lua_CFunction func);
void set_funcs(lua_State *L, int idx, const SFunc *tab);

void arraynum_get(lua_State *L, int idx, lua_Number *ptr, unsigned int num);
void arraynum_set(lua_State *L, int idx, const lua_Number *ptr, unsigned int num);
void arraynum_gets(lua_State *L, int idx, const GFnums *tab);
void arraynum_sets(lua_State *L, int idx, const SFnums *tab);

lua_Unsigned tablenum_len(lua_State *L, int idx);
lua_Number *tablenum_num(lua_State *L, int idx, lua_Number *ptr);
lua_Number *tablenum_get(lua_State *L, int idx, lua_Unsigned *num);
void tablenum_set(lua_State *L, int idx, const lua_Number *ptr, lua_Unsigned num, unsigned int col);

int luaopen_liba_mf(lua_State *L);
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
