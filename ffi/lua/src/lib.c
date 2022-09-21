#include "lua.h"
#include "a/math.h"

static int inv_sqrt(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    int n = lua_gettop(L);
    for (int i = 0; i++ != n;)
    {
        a_f32_t x = (a_f32_t)luaL_checknumber(L, i);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdouble-promotion"
#endif /* diagnostic */
        lua_Number y = a_inv_sqrt(x);
#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic pop
#endif /* diagnostic */
        lua_pushnumber(L, y);
    }
    return n;
}

static const SFunc funcs[] = {
    {"inv_sqrt", inv_sqrt},
    {NULL, NULL},
};

int luaopen_liba(lua_State *L)
{
    luaL_checkversion(L);
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);

    lua_pushstring(L, "mf");
    luaopen_liba_mf(L);
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
