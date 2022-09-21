#include "lua.h"
#include "a/version.h"

static int version(lua_State *L)
{
    lua_pushstring(L, a_version());
    return 1;
}

static const SEnum versionTE[] = {
    {"major", A_VERSION_MAJOR},
    {"minor", A_VERSION_MINOR},
    {"patch", A_VERSION_PATCH},
    {NULL, 0},
};

static const SFunc versionTM[] = {
    {"__call", version},
    {NULL, NULL},
};

int luaopen_liba_version(lua_State *L)
{
    lua_createtable(L, 0, Larray(versionTE) - 1);
    set_enums(L, -1, versionTE);
    lua_createtable(L, 0, Larray(versionTM) - 1);
    set_funcs(L, -1, versionTM);
    lua_setmetatable(L, -2);
    return 1;
}
