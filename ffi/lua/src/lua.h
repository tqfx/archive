#ifndef FFI_LUA_H
#define FFI_LUA_H

#if defined(_MSC_VER)
#if !defined _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif /* _CRT_SECURE_NO_WARNINGS */
#pragma warning(disable : 4820)
#endif /* _MSC_VER */
#include "a/a.h"
#if __has_warning("-Wcomma")
#pragma clang diagnostic ignored "-Wcomma"
#endif /* -Wcomma */
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* -Wpadded */
#include "lauxlib.h"
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
#define LLEN "__len"
#define LGET "__index"
#define LSET "__newindex"
#define LPRI "__tostring"
#define LUNM "__unm"
#define LADD "__add"
#define LSUB "__sub"
#define LMUL "__mul"
#define LDIV "__div"
#define LPOW "__pow"

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
    a_real_t data;
} SFnum;

typedef struct
{
    const char *name;
    a_real_t *data;
} GFnum;

typedef struct
{
    const char *name;
    lua_CFunction func;
} SFunc;

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int l_setter(lua_State *L);
int l_field(lua_State *L, const char *i, const char *s, uint32_t v);
void l_stack(lua_State *L, int line);

void *l_cmalloc(size_t siz);
void *l_realloc(const void *ptr, size_t siz);
void l_dealloc(const void *var);

void set_enum(lua_State *L, int idx, const char *name, lua_Integer data);
lua_Integer get_enum(lua_State *L, int idx, const char *name);
void set_enums(lua_State *L, int idx, const SEnum *tab);

void set_fnum(lua_State *L, int idx, const char *name, a_real_t data);
a_real_t get_fnum(lua_State *L, int idx, const char *name);
void set_fnums(lua_State *L, int idx, const SFnum *tab);
void get_fnums(lua_State *L, int idx, const GFnum *tab);

void set_func(lua_State *L, int idx, const char *name, lua_CFunction func);
void set_funcs(lua_State *L, int idx, const SFunc *tab);

const char *get_name(lua_State *L, int idx, const char *name);
void set_name(lua_State *L, int idx, const char *name, const char *data);

void arraynum_get(lua_State *L, int idx, a_real_t *ptr, unsigned int num);
void arraynum_set(lua_State *L, int idx, const a_real_t *ptr, unsigned int num);

a_real_t *tablenum_get(lua_State *L, int idx, const a_real_t *ptr, a_size_t *num);
void tablenum_set(lua_State *L, int idx, const a_real_t *ptr, a_size_t num, unsigned int col);

int luaopen_liba_mf(lua_State *L);
int luaopen_liba_tf(lua_State *L);
int luaopen_liba_pid(lua_State *L);
int luaopen_liba_fpid(lua_State *L);
int luaopen_liba_complex(lua_State *L);
int luaopen_liba_polytrack3(lua_State *L);
int luaopen_liba_polytrack5(lua_State *L);
int luaopen_liba_polytrack7(lua_State *L);
int luaopen_liba_version(lua_State *L);

A_PUBLIC int luaopen_liba(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#include <inttypes.h>

#endif /* FFI_LUA_H */
