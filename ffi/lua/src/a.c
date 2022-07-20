#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpadded"
#endif /* __GNUC__ || __clang__ */
#include "lauxlib.h"
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* __GNUC__ || __clang__ */

#include "a/def.h"

static int version(lua_State *L)
{
    lua_pushstring(L, a_version());
    return 1;
}

static const struct luaL_Reg funcs[] = {
    {"version", version},
    {NULL, NULL},
};

LUA_API int luaopen_liba(lua_State *L);

LUA_API int luaopen_liba(lua_State *L)
{
    luaL_newlib(L, funcs);
    return 1;
}
