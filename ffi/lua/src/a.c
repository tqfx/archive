#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
#include "lauxlib.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#include "a/version.h"

static int version(lua_State *L)
{
    lua_pushstring(L, a_version());
    return 1;
}

static int version_major(lua_State *L)
{
    lua_pushinteger(L, a_version_major());
    return 1;
}

static int version_minor(lua_State *L)
{
    lua_pushinteger(L, a_version_minor());
    return 1;
}

static int version_patch(lua_State *L)
{
    lua_pushinteger(L, a_version_patch());
    return 1;
}

#include "a/math.h"

static int inv_sqrt(lua_State *L)
{
    int n = lua_gettop(L);
    for (int i = 0; i++ != n;)
    {
        a_f32_t x = (a_f32_t)luaL_checknumber(L, i);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* __GNUC__ || __clang__ */
        lua_Number y = a_inv_sqrt(x);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */
        lua_pushnumber(L, y);
    }
    return n;
}

static const struct luaL_Reg funcs[] = {
    {"version", version},
    {"version_major", version_major},
    {"version_minor", version_minor},
    {"version_patch", version_patch},
    {"inv_sqrt", inv_sqrt},
    {NULL, NULL},
};

A_PUBLIC LUA_API int luaopen_liba(lua_State *L);

#if defined(__clang__)
#pragma GCC diagnostic ignored "-Wcomma"
#endif /* __clang__ */

int luaopen_liba(lua_State *L)
{
    luaL_newlib(L, funcs);
    return 1;
}
