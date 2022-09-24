#include "mf.h"

int mf_into_(lua_State *L, int idx, const lua_Number *ptr)
{
    a_uint_t i = 1;
    a_int_t e = A_MF_NUL;
    const lua_Number *a = ptr;
    lua_createtable(L, 0, 0);
    while ((void)(e = (a_int_t)*a), e != A_MF_NUL)
    {
        switch (e)
        {
        case A_MF_GAUSS:
        case A_MF_SIG:
        case A_MF_Z:
        {
            lua_createtable(L, 3, 0);
            arraynum_set(L, -1, a, 3);
            lua_rawseti(L, -2, i);
            a += 3;
        }
        break;
        case A_MF_GBELL:
        case A_MF_TRI:
        {
            lua_createtable(L, 4, 0);
            arraynum_set(L, -1, a, 4);
            lua_rawseti(L, -2, i);
            a += 4;
        }
        break;
        case A_MF_TRAP:
        {
            lua_createtable(L, 5, 0);
            arraynum_set(L, -1, a, 5);
            lua_rawseti(L, -2, i);
            a += 5;
        }
        break;
        case A_MF_NUL:
        default:
            goto done;
        }
        ++i;
    }
done:
    lua_pushnumber(L, A_MF_NUL);
    lua_rawseti(L, -2, i);
    lua_rawset(L, idx < 0 ? idx - 1 : idx);
    return 1;
}

static int mf_gauss(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number sigma = luaL_checknumber(L, 2);
    lua_Number c = luaL_checknumber(L, 3);
    lua_pushnumber(L, a_mf_gauss(x, sigma, c));
    return 1;
}

static int mf_gbell(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number b = luaL_checknumber(L, 3);
    lua_Number c = luaL_checknumber(L, 4);
    lua_pushnumber(L, a_mf_gbell(x, a, b, c));
    return 1;
}

static int mf_sig(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number c = luaL_checknumber(L, 3);
    lua_pushnumber(L, a_mf_sig(x, a, c));
    return 1;
}

static int mf_trap(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number b = luaL_checknumber(L, 3);
    lua_Number c = luaL_checknumber(L, 4);
    lua_Number d = luaL_checknumber(L, 5);
    lua_pushnumber(L, a_mf_trap(x, a, b, c, d));
    return 1;
}

static int mf_tri(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number b = luaL_checknumber(L, 3);
    lua_Number c = luaL_checknumber(L, 4);
    lua_pushnumber(L, a_mf_tri(x, a, b, c));
    return 1;
}

static int mf_z(lua_State *L)
{
    if (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    lua_Number x = luaL_checknumber(L, 1);
    lua_Number a = luaL_checknumber(L, 2);
    lua_Number b = luaL_checknumber(L, 3);
    lua_pushnumber(L, a_mf_z(x, a, b));
    return 1;
}

static int mf(lua_State *L)
{
    while (lua_istable(L, 1))
    {
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }
    lua_Integer e = luaL_checkinteger(L, 1);
    lua_rotate(L, 1, -1);
    lua_pop(L, 1);
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
