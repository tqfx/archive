#include "polytrack3.h"

int polytrack3_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK3_META_);
    return 1;
}

int polytrack3_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK3_FUNC_);
    return 1;
}

int polytrack3_from_(lua_State *L, int idx, a_polytrack3_s *ctx)
{
    GFnums polytrack3[] = {
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"k", ctx->k, 4},
        {NULL, NULL, 0},
    };
    arraynum_gets(L, idx, polytrack3);
    return 0;
}

int polytrack3_into_(lua_State *L, a_polytrack3_s *ctx)
{
    SFnums polytrack3[] = {
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"k", ctx->k, 4},
        {NULL, NULL, 0},
    };
    lua_createtable(L, 0, Larray(polytrack3) - 1);
    arraynum_sets(L, -1, polytrack3);
    return 1;
}

static int polytrack3_from(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        lua_rotate(L, -2, 1);
    }
    else
    {
        ctx = (a_polytrack3_s *)lua_newuserdata(L, sizeof(a_polytrack3_s));
    }
    polytrack3_meta_(L);
    lua_setmetatable(L, -2);
    polytrack3_from_(L, -2, ctx);
    return 1;
}

static int polytrack3_into(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        return polytrack3_into_(L, ctx);
    }
    return 0;
}

static int polytrack3_init(lua_State *L)
{
    if (lua_gettop(L) > 2)
    {
        a_real_t target[3];
        a_real_t source[3];
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -3, LUA_TUSERDATA);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -3);
        a_polytrack3_init(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack3_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
    {
        a_real_t target[3];
        a_real_t source[3];
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_newuserdata(L, sizeof(a_polytrack3_s));
        polytrack3_meta_(L);
        lua_setmetatable(L, -2);
        a_polytrack3_init(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack3_all(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t out[3];
        a_real_t ts = luaL_checknumber(L, -1);
        a_polytrack3_all(ctx, ts, out);
        lua_createtable(L, Larray(out), 0);
        arraynum_set(L, -1, out, Larray(out));
        return 1;
    }
    return 0;
}

static int polytrack3_pos(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack3_pos(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack3_vec(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack3_vec(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack3_acc(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack3_acc(ctx, ts));
        return 1;
    }
    return 0;
}

int luaopen_liba_polytrack3(lua_State *L)
{
    const SFunc funcs[] = {
        {"from", polytrack3_from},
        {"into", polytrack3_into},
        {"init", polytrack3_init},
        {"new", polytrack3_new},
        {"all", polytrack3_all},
        {"pos", polytrack3_pos},
        {"vec", polytrack3_vec},
        {"acc", polytrack3_acc},
        {NULL, NULL},
    };
    const SFunc metas[] = {
        {"__call", polytrack3_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, 2);
    set_func(L, -1, "__call", polytrack3_all);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);

    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK3_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK3_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK3_FUNC_);

    return 1;
}
