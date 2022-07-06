
#include "a/def.h"

#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"

static int version(lua_State *L)
{
    lua_pushstring(L, a_version());
    return 1;
}

static const struct luaL_Reg funcs[] = {
    {"version", version},
    {NULL, NULL},
};

LUAMOD_API int luaopen_liba(lua_State *L);

LUAMOD_API int luaopen_liba(lua_State *L)
{
    luaL_newlib(L, funcs);
    return 1;
}
