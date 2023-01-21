/***
 membership function
 @module liba.mf
*/

#define LUA_LIB
#include "a.h"
#include "a/mf.h"

/***
 gaussian membership function
 @tparam number x any element
 @tparam number sigma sigma
 @tparam number c c
 @treturn number membership
 @function gauss
*/
static int l_mf_gauss(lua_State *L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_real_t x = (a_real_t)luaL_checknumber(L, 1);
    a_real_t sigma = (a_real_t)luaL_checknumber(L, 2);
    a_real_t c = (a_real_t)luaL_checknumber(L, 3);
    lua_pushnumber(L, (lua_Number)a_mf_gauss(x, sigma, c));
    return 1;
}

/***
 generalized bell-shaped membership function
 @tparam number x any element
 @tparam number a a
 @tparam number b b
 @tparam number c c
 @treturn number membership
 @function gbell
*/
static int l_mf_gbell(lua_State *L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_real_t x = (a_real_t)luaL_checknumber(L, 1);
    a_real_t a = (a_real_t)luaL_checknumber(L, 2);
    a_real_t b = (a_real_t)luaL_checknumber(L, 3);
    a_real_t c = (a_real_t)luaL_checknumber(L, 4);
    lua_pushnumber(L, (lua_Number)a_mf_gbell(x, a, b, c));
    return 1;
}

/***
 sigmoidal membership function
 @tparam number x any element
 @tparam number a a
 @tparam number c c
 @treturn number membership
 @function sig
*/
static int l_mf_sig(lua_State *L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_real_t x = (a_real_t)luaL_checknumber(L, 1);
    a_real_t a = (a_real_t)luaL_checknumber(L, 2);
    a_real_t c = (a_real_t)luaL_checknumber(L, 3);
    lua_pushnumber(L, (lua_Number)a_mf_sig(x, a, c));
    return 1;
}

/***
 trapezoidal membership function
 @tparam number x any element
 @tparam number a a
 @tparam number b b
 @tparam number c c
 @tparam number d d
 @treturn number membership
 @function trap
*/
static int l_mf_trap(lua_State *L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_real_t x = (a_real_t)luaL_checknumber(L, 1);
    a_real_t a = (a_real_t)luaL_checknumber(L, 2);
    a_real_t b = (a_real_t)luaL_checknumber(L, 3);
    a_real_t c = (a_real_t)luaL_checknumber(L, 4);
    a_real_t d = (a_real_t)luaL_checknumber(L, 5);
    lua_pushnumber(L, (lua_Number)a_mf_trap(x, a, b, c, d));
    return 1;
}

/***
 triangular membership function
 @tparam number x any element
 @tparam number a a
 @tparam number b b
 @tparam number c c
 @treturn number membership
 @function tri
*/
static int l_mf_tri(lua_State *L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_real_t x = (a_real_t)luaL_checknumber(L, 1);
    a_real_t a = (a_real_t)luaL_checknumber(L, 2);
    a_real_t b = (a_real_t)luaL_checknumber(L, 3);
    a_real_t c = (a_real_t)luaL_checknumber(L, 4);
    lua_pushnumber(L, (lua_Number)a_mf_tri(x, a, b, c));
    return 1;
}

/***
 z-shaped membership function
 @tparam number x any element
 @tparam number a a
 @tparam number b b
 @treturn number membership
 @function z
*/
static int l_mf_z(lua_State *L)
{
    if (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_real_t x = (a_real_t)luaL_checknumber(L, 1);
    a_real_t a = (a_real_t)luaL_checknumber(L, 2);
    a_real_t b = (a_real_t)luaL_checknumber(L, 3);
    lua_pushnumber(L, (lua_Number)a_mf_z(x, a, b));
    return 1;
}

/***
 membership function
 @tparam int e type for membership function
 @tparam number x any element
 @tparam number ... paramarrays
 @treturn number membership
 @function mf
*/
static int l_mf(lua_State *L)
{
    while (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    lua_Integer e = luaL_checkinteger(L, 1);
    lua_remove(L, 1);
    switch (e)
    {
    case A_MF_GAUSS:
        return l_mf_gauss(L);
    case A_MF_GBELL:
        return l_mf_gbell(L);
    case A_MF_SIG:
        return l_mf_sig(L);
    case A_MF_TRAP:
        return l_mf_trap(L);
    case A_MF_TRI:
        return l_mf_tri(L);
    case A_MF_Z:
        return l_mf_z(L);
    case A_MF_NUL:
    default:
        return 0;
    }
}

/***
 type for membership function
 @field NUL none
 @field GAUSS gaussian membership function
 @field GBELL generalized bell-shaped membership function
 @field SIG sigmoidal membership function
 @field TRAP trapezoidal membership function
 @field TRI triangular membership function
 @field Z z-shaped membership function
 @table mf
*/
int luaopen_liba_mf(lua_State *L)
{
    const l_int_s enums[] = {
        {"NUL", A_MF_NUL},
        {"GAUSS", A_MF_GAUSS},
        {"GBELL", A_MF_GBELL},
        {"SIG", A_MF_SIG},
        {"TRAP", A_MF_TRAP},
        {"TRI", A_MF_TRI},
        {"Z", A_MF_Z},
        {NULL, 0},
    };
    const l_func_s funcs[] = {
        {"gauss", l_mf_gauss},
        {"gbell", l_mf_gbell},
        {"sig", l_mf_sig},
        {"trap", l_mf_trap},
        {"tri", l_mf_tri},
        {"z", l_mf_z},
        {NULL, NULL},
    };
    const l_func_s metas[] = {
        {"__call", l_mf},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(enums) + L_ARRAY(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, L_ARRAY(metas) - 1);
    l_func_reg(L, -1, metas);
    lua_setmetatable(L, -2);
    return 1;
}
