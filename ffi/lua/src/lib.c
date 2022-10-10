/***
 algorithm library
 @module liba
*/

#include "lua.h"
#include "a/math.h"

/***
 fast inverse square-root
 @tparam number x independent variable
 @tparam number ... independent variables
 @treturn number calculated result
 @function sqrt_inv
*/
static int sqrt_inv(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_remove(L, 1);
    }
    int n = lua_gettop(L);
    for (int i = 0; i++ != n;)
    {
        a_f32_t x = (a_f32_t)luaL_checknumber(L, i);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* diagnostic */
        lua_Number y = a_sqrt_inv(x);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
        lua_pushnumber(L, y);
    }
    return n;
}

int luaopen_liba(lua_State *L)
{
    luaL_checkversion(L);

    const SFunc funcs[] = {
        {"sqrt_inv", sqrt_inv},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);

    lua_pushstring(L, "mf");
    luaopen_liba_mf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "tf");
    luaopen_liba_tf(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "pid");
    luaopen_liba_pid(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "fpid");
    luaopen_liba_fpid(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack3");
    luaopen_liba_polytrack3(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack5");
    luaopen_liba_polytrack5(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "polytrack7");
    luaopen_liba_polytrack7(L);
    lua_rawset(L, -3);

    lua_pushstring(L, "version");
    luaopen_liba_version(L);
    lua_rawset(L, -3);

    return 1;
}
