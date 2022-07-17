#include "lauxlib.h"

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
