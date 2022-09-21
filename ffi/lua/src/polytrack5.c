#include "lua.h"
#include "a/polytrack.h"

int polytrack5_from_(lua_State *L, a_polytrack5_s *ctx);
int polytrack5_into_(lua_State *L, a_polytrack5_s *ctx);

int polytrack5_from_(lua_State *L, a_polytrack5_s *ctx)
{
    GFnums polytrack5[] = {
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"a", ctx->a, 2},
        {"k", ctx->k, 6},
        {NULL, NULL, 0},
    };
    arraynum_gets(L, -1, polytrack5);
    return 1;
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

static int polytrack5_meta_(lua_State *L, int idx);

static int polytrack5_from(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)lua_touserdata(L, -2);
    if (ctx == NULL)
    {
        ctx = (a_polytrack5_s *)lua_newuserdata(L, sizeof(a_polytrack5_s));
    }
    polytrack5_from_(L, ctx);
    return polytrack5_meta_(L, -1);
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
        a_polytrack5_init(ctx, source, target);
        return polytrack5_meta_(L, -1);
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

static const SFunc polytrack5TF[] = {
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

static int polytrack5_meta_(lua_State *L, int idx)
{
    lua_createtable(L, 0, 2);
    lua_pushstring(L, "__index");
    lua_createtable(L, 0, Larray(polytrack5TF) - 1);
    set_funcs(L, -1, polytrack5TF);
    lua_rawset(L, -3);
    set_func(L, -1, "__call", polytrack5_all);
    lua_setmetatable(L, idx < 0 ? idx - 1 : idx);
    return 1;
}

static const SFunc polytrack5TM[] = {
    {"__call", polytrack5_new},
    {NULL, NULL},
};

int luaopen_liba_polytrack5(lua_State *L)
{
    lua_createtable(L, 0, Larray(polytrack5TF) - 1);
    set_funcs(L, -1, polytrack5TF);
    lua_createtable(L, 0, Larray(polytrack5TM) - 1);
    set_funcs(L, -1, polytrack5TM);
    lua_setmetatable(L, -2);
    return 1;
}
