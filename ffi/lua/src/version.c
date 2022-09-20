#include "lua.h"
#include "a/version.h"

static int version(lua_State *L)
{
    lua_pushstring(L, a_version());
    return 1;
}

static const SEnum versionet[] = {
    {"major", A_VERSION_MAJOR},
    {"minor", A_VERSION_MINOR},
    {"patch", A_VERSION_PATCH},
    {NULL, 0},
};

static const SFunc versionmt[] = {
    {"__call", version},
    {NULL, NULL},
};

int luaopen_liba_version(lua_State *L)
{
    lua_createtable(L, 0, Larray(versionet) - 1);
    set_enums(L, -1, versionet);
    lua_createtable(L, 0, Larray(versionmt));
    set_funcs(L, -1, versionmt);
    set_name(L, -1, "version");
    lua_setmetatable(L, -2);
    return 1;
}
