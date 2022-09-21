#include "lua.h"
#include "a/mf.h"

int mf_into_(lua_State *L, int idx, a_real_t *ptr);

int mf_into_(lua_State *L, int idx, a_real_t *ptr)
{
    a_uint_t i = 1;
    a_int_t e = A_MF_NUL;
    const a_real_t *a = ptr;
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

static int gauss(lua_State *L)
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

static int gbell(lua_State *L)
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

static int sig(lua_State *L)
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

static int trap(lua_State *L)
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

static int tri(lua_State *L)
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

static int z(lua_State *L)
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
        return gauss(L);
    case A_MF_GBELL:
        return gbell(L);
    case A_MF_SIG:
        return sig(L);
    case A_MF_TRAP:
        return trap(L);
    case A_MF_TRI:
        return tri(L);
    case A_MF_Z:
        return z(L);
    case A_MF_NUL:
    default:
        return 0;
    }
}

static const SEnum mfTE[] = {
    {"NUL", A_MF_NUL},
    {"GAUSS", A_MF_GAUSS},
    {"GBELL", A_MF_GBELL},
    {"SIG", A_MF_SIG},
    {"TRAP", A_MF_TRAP},
    {"TRI", A_MF_TRI},
    {"Z", A_MF_Z},
    {NULL, 0},
};

static const SFunc mfTF[] = {
    {"gauss", gauss},
    {"gbell", gbell},
    {"sig", sig},
    {"trap", trap},
    {"tri", tri},
    {"z", z},
    {NULL, NULL},
};

static const SFunc mfTM[] = {
    {"__call", mf},
    {NULL, NULL},
};

int luaopen_liba_mf(lua_State *L)
{
    lua_createtable(L, 0, Larray(mfTE) + Larray(mfTF) - 2);
    set_enums(L, -1, mfTE);
    set_funcs(L, -1, mfTF);
    lua_createtable(L, 0, Larray(mfTM) - 1);
    set_funcs(L, -1, mfTM);
    lua_setmetatable(L, -2);
    return 1;
}
