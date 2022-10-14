#ifndef __LUA_H__
#define __LUA_H__

#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#endif /* _MSC_VER */

#include "a/a.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* diagnostic */
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include "lauxlib.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
#if defined(_MSC_VER)
#pragma warning(pop)
#endif /* _MSC_VER */
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

#if (LUA_VERSION_NUM <= 501)
#define lua_rawsetp(L, idx, p) (lua_pushlightuserdata(L, p), lua_insert(L, -2), lua_rawset(L, idx))
#define lua_rawgetp(L, idx, p) (lua_pushlightuserdata(L, p), lua_rawget(L, idx))
#define lua_rawlen(L, i) lua_objlen(L, i)
#define luaL_checkversion(L)
#endif /* LUA_VERSION_NUM */

#define Larray(A) (sizeof(A) / sizeof(*A))
#define Lstack(L) l_stack(L, __LINE__)
#define LNAME "__name"
#define LNEW "__call"
#define LDIE "__gc"
#define LSET "__newindex"
#define LGET "__index"

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

void *l_cmalloc(size_t siz);
void *l_realloc(const void *ptr, size_t siz);
void l_dealloc(const void *var);

int l_setter(lua_State *L);
void l_stack(lua_State *L, int line);
int l_field(lua_State *L, const char *i, const char *s, uint32_t v);

lua_Integer get_enum(lua_State *L, int idx, const char *name);
void set_enum(lua_State *L, int idx, const char *name, lua_Integer data);
void set_enums(lua_State *L, int idx, const SEnum *tab);
lua_Number get_fnum(lua_State *L, int idx, const char *name);
void set_fnum(lua_State *L, int idx, const char *name, lua_Number data);
void set_fnums(lua_State *L, int idx, const SFnum *tab);
void get_fnums(lua_State *L, int idx, const GFnum *tab);
void set_func(lua_State *L, int idx, const char *name, lua_CFunction func);
void set_funcs(lua_State *L, int idx, const SFunc *tab);
const char *get_name(lua_State *L, int idx, const char *name);
void set_name(lua_State *L, int idx, const char *name, const char *data);

void arraynum_get(lua_State *L, int idx, lua_Number *ptr, unsigned int num);
void arraynum_set(lua_State *L, int idx, const lua_Number *ptr, unsigned int num);
void arraynum_gets(lua_State *L, int idx, const GFnums *tab);
void arraynum_sets(lua_State *L, int idx, const SFnums *tab);

size_t tablenum_len(lua_State *L, int idx);
lua_Number *tablenum_num(lua_State *L, int idx, lua_Number *ptr);
lua_Number *tablenum_get(lua_State *L, int idx, const lua_Number *ptr, size_t *num);
void tablenum_set(lua_State *L, int idx, const lua_Number *ptr, size_t num, unsigned int col);

int luaopen_liba_mf(lua_State *L);
int luaopen_liba_tf(lua_State *L);
int luaopen_liba_pid(lua_State *L);
int luaopen_liba_fpid(lua_State *L);
int luaopen_liba_polytrack3(lua_State *L);
int luaopen_liba_polytrack5(lua_State *L);
int luaopen_liba_polytrack7(lua_State *L);
int luaopen_liba_version(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

A_PUBLIC int luaopen_liba(lua_State *L);

#endif /* __LUA_H__ */
