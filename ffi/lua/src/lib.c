/***
 algorithm library
 @module liba
*/

#define LUA_LIB
#include "a.h"
#include "a/math.h"
#include "a/version.h"

/***
 fast inverse square-root
 @tparam number x independent variable
 @tparam number ... independent variables
 @treturn number calculated result
 @function rsqrt
*/
static int l_rsqrt(lua_State *L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    int n = lua_gettop(L);
    for (int i = 0; i++ != n;)
    {
        lua_Number x = luaL_checknumber(L, i);
#if A_REAL_TYPE == A_REAL_SINGLE
        x = (lua_Number)a_f32_rsqrt((a_f32_t)x);
#elif A_REAL_TYPE == A_REAL_DOUBLE
        x = (lua_Number)a_f64_rsqrt((a_f64_t)x);
#else /* !A_REAL_TYPE */
        x = (lua_Number)(1 / sqrt((double)x));
#endif /* A_REAL_TYPE */
        lua_pushnumber(L, x);
    }
    return n;
}

int luaopen_liba(lua_State *L)
{
    luaL_checkversion(L);

    const l_func_s funcs[] = {
        {"rsqrt", l_rsqrt},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(funcs));
    l_str_set(L, -1, "VERSION", A_VERSION);
    l_func_reg(L, -1, funcs);

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

    lua_pushstring(L, "complex");
    luaopen_liba_complex(L);
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

#include <stdio.h>
#include <inttypes.h>

int l_field(lua_State *L, const char *i, const char *s, uint32_t v)
{
    char h[11];
    (void)sprintf(h, "0x%08" PRIX32, v);
    return luaL_error(L, "field(%s) '%s' missing in %s", h, s, i);
}

int l_setter(lua_State *L)
{
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    return l_field(L, "setter", field, hash);
}
