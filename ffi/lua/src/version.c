#include "lua.h"
#include "a/version.h"

static int version(lua_State *L)
{
    lua_pushstring(L, a_version());
    return 1;
}

int luaopen_liba_version(lua_State *L)
{
    const SEnum enums[] = {
        {"major", A_VERSION_MAJOR},
        {"minor", A_VERSION_MINOR},
        {"patch", A_VERSION_PATCH},
        {NULL, 0},
    };
    const SFunc metas[] = {
        {"__call", version},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(enums) - 1);
    set_enums(L, -1, enums);
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);
    lua_setmetatable(L, -2);
    return 1;
}
