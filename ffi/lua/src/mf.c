/***
 membership function
 @module liba.mf
*/

#include "lua.h"
#include "a/mf.h"

/***
 gaussian membership function
 @tparam number x any element
 @tparam number sigma sigma
 @tparam number c c
 @treturn number membership
 @function gauss
*/
static int mf_gauss(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_remove(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number sigma = luaL_checknumber(L, 2);
    lua_Number c = luaL_checknumber(L, 3);
    lua_pushnumber(L, a_mf_gauss(x, sigma, c));
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
static int mf_gbell(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_remove(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number b = luaL_checknumber(L, 3);
    lua_Number c = luaL_checknumber(L, 4);
    lua_pushnumber(L, a_mf_gbell(x, a, b, c));
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
static int mf_sig(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_remove(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number c = luaL_checknumber(L, 3);
    lua_pushnumber(L, a_mf_sig(x, a, c));
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
static int mf_trap(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_remove(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number b = luaL_checknumber(L, 3);
    lua_Number c = luaL_checknumber(L, 4);
    lua_Number d = luaL_checknumber(L, 5);
    lua_pushnumber(L, a_mf_trap(x, a, b, c, d));
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
static int mf_tri(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_remove(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number b = luaL_checknumber(L, 3);
    lua_Number c = luaL_checknumber(L, 4);
    lua_pushnumber(L, a_mf_tri(x, a, b, c));
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
static int mf_z(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_remove(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number b = luaL_checknumber(L, 3);
    lua_pushnumber(L, a_mf_z(x, a, b));
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
static int mf(lua_State *L)
{
    while (lua_istable(L, 1))
    {
        lua_remove(L, 1);
    }
    lua_Integer e = luaL_checkinteger(L, 1);
    lua_remove(L, 1);
    switch (e)
    {
    case A_MF_GAUSS:
        return mf_gauss(L);
    case A_MF_GBELL:
        return mf_gbell(L);
    case A_MF_SIG:
        return mf_sig(L);
    case A_MF_TRAP:
        return mf_trap(L);
    case A_MF_TRI:
        return mf_tri(L);
    case A_MF_Z:
        return mf_z(L);
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
    const SEnum enums[] = {
        {"NUL", A_MF_NUL},
        {"GAUSS", A_MF_GAUSS},
        {"GBELL", A_MF_GBELL},
        {"SIG", A_MF_SIG},
        {"TRAP", A_MF_TRAP},
        {"TRI", A_MF_TRI},
        {"Z", A_MF_Z},
        {NULL, 0},
    };
    const SFunc funcs[] = {
        {"gauss", mf_gauss},
        {"gbell", mf_gbell},
        {"sig", mf_sig},
        {"trap", mf_trap},
        {"tri", mf_tri},
        {"z", mf_z},
        {NULL, NULL},
    };
    const SFunc metas[] = {
        {"__call", mf},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(enums) + Larray(funcs) - 2);
    set_enums(L, -1, enums);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);
    lua_setmetatable(L, -2);
    return 1;
}
