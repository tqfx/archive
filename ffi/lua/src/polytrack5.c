#include "polytrack5.h"

int polytrack5_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, (void *)polytrack5_meta_);
    return 1;
}

int polytrack5_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, (void *)polytrack5_func_);
    return 1;
}

int polytrack5_from_(lua_State *L, int idx, a_polytrack5_s *ctx)
{
    GFnums polytrack5[] = {
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"a", ctx->a, 2},
        {"k", ctx->k, 6},
        {NULL, NULL, 0},
    };
    arraynum_gets(L, idx, polytrack5);
    return 0;
}

int polytrack5_into_(lua_State *L, a_polytrack5_s *ctx)
{
    SFnums polytrack5[] = {
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"a", ctx->a, 2},
        {"k", ctx->k, 6},
        {NULL, NULL, 0},
    };
    lua_createtable(L, 0, Larray(polytrack5) - 1);
    arraynum_sets(L, -1, polytrack5);
    return 1;
}

static int polytrack5_from(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        lua_rotate(L, -2, 1);
    }
    else
    {
        ctx = (a_polytrack5_s *)lua_newuserdata(L, sizeof(a_polytrack5_s));
    }
    polytrack5_meta_(L);
    lua_setmetatable(L, -2);
    polytrack5_from_(L, -2, ctx);
    return 1;
}

static int polytrack5_into(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        return polytrack5_into_(L, ctx);
    }
    return 0;
}

static int polytrack5_init(lua_State *L)
{
    if (lua_gettop(L) > 2)
    {
        a_real_t target[4];
        a_real_t source[4];
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -3, LUA_TUSERDATA);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, -3);
        a_polytrack5_init(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack5_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
    {
        a_real_t target[4];
        a_real_t source[4];
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack5_s *ctx = (a_polytrack5_s *)lua_newuserdata(L, sizeof(a_polytrack5_s));
        polytrack5_meta_(L);
        lua_setmetatable(L, -2);
        a_polytrack5_init(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack5_all(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t out[3];
        a_real_t ts = luaL_checknumber(L, -1);
        a_polytrack5_all(ctx, ts, out);
        lua_createtable(L, 3, 0);
        arraynum_set(L, -1, out, 3);
        return 1;
    }
    return 0;
}

static int polytrack5_pos(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack5_pos(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack5_vec(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack5_vec(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack5_acc(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_polytrack5_acc(ctx, ts));
        return 1;
    }
    return 0;
}

int luaopen_liba_polytrack5(lua_State *L)
{
    const SFunc funcs[] = {
        {"from", polytrack5_from},
        {"into", polytrack5_into},
        {"init", polytrack5_init},
        {"new", polytrack5_new},
        {"all", polytrack5_all},
        {"pos", polytrack5_pos},
        {"vec", polytrack5_vec},
        {"acc", polytrack5_acc},
        {NULL, NULL},
    };
    const SFunc metas[] = {
        {"__call", polytrack5_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, 2);
    set_func(L, -1, "__call", polytrack5_all);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);

    lua_rawsetp(L, LUA_REGISTRYINDEX, (void *)polytrack5_meta_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, (void *)polytrack5_func_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, (void *)polytrack5_func_);

    return 1;
}
