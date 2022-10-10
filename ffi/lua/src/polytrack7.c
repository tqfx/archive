/***
 hepta polynomial trajectory
 @module liba.polytrack7
*/

#include "polytrack7.h"

int polytrack7_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK7_META_);
    return 1;
}

int polytrack7_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK7_FUNC_);
    return 1;
}

int polytrack7_from_(lua_State *L, int idx, a_polytrack7_s *ctx)
{
    GFnums polytrack7[] = {
        {"k", ctx->k, 8},
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"a", ctx->a, 2},
        {"j", ctx->j, 2},
        {NULL, NULL, 0},
    };
    arraynum_gets(L, idx, polytrack7);
    return 0;
}

int polytrack7_into_(lua_State *L, a_polytrack7_s *ctx)
{
    SFnums polytrack7[] = {
        {"k", ctx->k, 8},
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"a", ctx->a, 2},
        {"j", ctx->j, 2},
        {NULL, NULL, 0},
    };
    lua_createtable(L, 0, Larray(polytrack7) - 1);
    arraynum_sets(L, -1, polytrack7);
    return 1;
}

static int polytrack7_from(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        lua_pushvalue(L, -2);
        lua_remove(L, -3);
    }
    else
    {
        ctx = (a_polytrack7_s *)lua_newuserdata(L, sizeof(a_polytrack7_s));
    }
    polytrack7_meta_(L);
    lua_setmetatable(L, -2);
    polytrack7_from_(L, -2, ctx);
    return 1;
}

static int polytrack7_into(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        return polytrack7_into_(L, ctx);
    }
    return 0;
}

static int polytrack7_init_(lua_State *L, a_polytrack7_s *ctx)
{
    a_real_t t0 = 0, q0 = 0, v0 = 0, a0 = 0, j0 = 0;
    a_real_t t1 = 0, q1 = 0, v1 = 0, a1 = 0, j1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 10:
    {
        j1 = luaL_checknumber(L, 10);
        A_FALLTHROUGH;
    }
    case 9:
    {
        j0 = luaL_checknumber(L, 9);
        A_FALLTHROUGH;
    }
    case 8:
    {
        a1 = luaL_checknumber(L, 8);
        A_FALLTHROUGH;
    }
    case 7:
    {
        a0 = luaL_checknumber(L, 7);
        A_FALLTHROUGH;
    }
    case 6:
    {
        v1 = luaL_checknumber(L, 6);
        A_FALLTHROUGH;
    }
    case 5:
    {
        v0 = luaL_checknumber(L, 5);
        A_FALLTHROUGH;
    }
    case 4:
    {
        q1 = luaL_checknumber(L, 4);
        q0 = luaL_checknumber(L, 3);
        t1 = luaL_checknumber(L, 2);
        t0 = luaL_checknumber(L, 1);
    }
    break;
    default:
        break;
    }
    a_polytrack7_init(ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    return 1;
}

static int polytrack7_init(lua_State *L)
{
    int top = lua_gettop(L);
    int type = lua_type(L, -1);
    if (top > 4 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return polytrack7_init_(L, ctx);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_real_t target[5] = {0};
        a_real_t source[5] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -3);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack7_init2(ctx, source, target);
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

static int polytrack7_new(lua_State *L)
{
    int top = lua_gettop(L);
    int type = lua_type(L, -1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_polytrack7_s *ctx = (a_polytrack7_s *)lua_newuserdata(L, sizeof(a_polytrack7_s));
        polytrack7_meta_(L);
        lua_setmetatable(L, -2);
        return polytrack7_init_(L, ctx);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_real_t target[5] = {0};
        a_real_t source[5] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack7_s *ctx = (a_polytrack7_s *)lua_newuserdata(L, sizeof(a_polytrack7_s));
        polytrack7_meta_(L);
        lua_setmetatable(L, -2);
        a_polytrack7_init2(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack7_out(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t out[4];
        a_real_t ts = luaL_checknumber(L, -1);
        a_polytrack7_out(ctx, ts, out);
        lua_createtable(L, 4, 0);
        arraynum_set(L, -1, out, 4);
        return 1;
    }
    return 0;
}

static int polytrack7_pos(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack7_pos(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack7_vec(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack7_vec(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack7_acc(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack7_acc(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack7_jer(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack7_jer(ctx, ts));
        return 1;
    }
    return 0;
}

int luaopen_liba_polytrack7(lua_State *L)
{
    const SFunc funcs[] = {
        {"from", polytrack7_from},
        {"into", polytrack7_into},
        {"init", polytrack7_init},
        {"new", polytrack7_new},
        {"out", polytrack7_out},
        {"pos", polytrack7_pos},
        {"vec", polytrack7_vec},
        {"acc", polytrack7_acc},
        {"jer", polytrack7_jer},
        {NULL, NULL},
    };
    const SFunc metas[] = {
        {"__call", polytrack7_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, 2);
    set_func(L, -1, "__call", polytrack7_out);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);

    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK7_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK7_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK7_FUNC_);

    return 1;
}
