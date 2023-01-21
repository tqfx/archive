/***
 algorithm library version
 @module liba.version
*/

#define LUA_LIB
#include "a.h"
#include "a/version.h"

/***
 algorithm library version string
 @treturn string version string
 @function version
*/
static int l_version(lua_State *L)
{
    lua_pushstring(L, a_version());
    return 1;
}

/***
 algorithm library version string
 @field major algorithm library version major
 @field minor algorithm library version minor
 @field patch algorithm library version patch
 @table version
*/
int luaopen_liba_version(lua_State *L)
{
    const l_int_s enums[] = {
        {"major", A_VERSION_MAJOR},
        {"minor", A_VERSION_MINOR},
        {"patch", A_VERSION_PATCH},
        {NULL, 0},
    };
    const l_func_s metas[] = {
        {"__call", l_version},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(enums) - 1);
    l_int_reg(L, -1, enums);
    lua_createtable(L, 0, L_ARRAY(metas) - 1);
    l_func_reg(L, -1, metas);
    lua_setmetatable(L, -2);
    return 1;
}
