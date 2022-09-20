#include "lua.h"
#include "a/polytrack.h"

int polytrack5_from_(lua_State *L, int idx, a_polytrack5_s *ctx);
int polytrack5_into_(lua_State *L, int idx, a_polytrack5_s *ctx);

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
    return 1;
}

int polytrack5_into_(lua_State *L, int idx, a_polytrack5_s *ctx)
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
    arraynum_sets(L, idx, polytrack5);
    return 1;
}

static int polytrack5_from(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)userdata_new(L, sizeof(a_polytrack5_s), 1);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        userdata_setp(L, 1, ctx); /* :from() */
    }
    return polytrack5_from_(L, -1, ctx);
}

static int polytrack5_into(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)userdata_get(L);
    if (ctx)
    {
        return polytrack5_into_(L, -1, ctx);
    }
    return 0;
}

static int polytrack5_init(lua_State *L)
{
    int n = lua_gettop(L);
    if (n > 1)
    {
        a_real_t target[4];
        a_real_t source[4];
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        if (n > 2)
        {
            luaL_checktype(L, 3, LUA_TTABLE);
        }
        a_polytrack5_s *ctx = (a_polytrack5_s *)userdata_new(L, sizeof(a_polytrack5_s), 2);
        arraynum_get(L, 1, source, Larray(source));
        arraynum_get(L, 2, target, Larray(target));
        a_polytrack5_init(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack5_all(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t out[3];
        a_real_t ts = luaL_checknumber(L, 2);
        a_polytrack5_all(ctx, ts, out);
        lua_createtable(L, 3, 0);
        arraynum_set(L, -1, out, 3);
        return 1;
    }
    return 0;
}

static int polytrack5_pos(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack5_pos(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack5_vec(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack5_vec(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack5_acc(lua_State *L)
{
    a_polytrack5_s *ctx = (a_polytrack5_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack5_acc(ctx, ts));
        return 1;
    }
    return 0;
}

static const SFunc polytrack5TF[] = {
    {"from", polytrack5_from},
    {"into", polytrack5_into},
    {"init", polytrack5_init},
    {"all", polytrack5_all},
    {"pos", polytrack5_pos},
    {"vec", polytrack5_vec},
    {"acc", polytrack5_acc},
    {NULL, NULL},
};

static int polytrack5_new(lua_State *L)
{
    if (lua_istable(L, 1) && lua_istable(L, 2) && lua_istable(L, 3) && lua_gettop(L) > 3)
    {
        /* :polytrack5() */
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }

    int ok = polytrack5_init(L);

    lua_createtable(L, 0, Larray(polytrack5TF) - 1);
    set_funcs(L, -1, polytrack5TF);
    userdata_seti(L, -1, -2);

    lua_createtable(L, 0, 1);
    set_func(L, -1, "__call", polytrack5_all);
    lua_setmetatable(L, -2);

    return ok;
}

static const SFunc polytrack5TM[] = {
    {"__call", polytrack5_new},
    {NULL, NULL},
};

int luaopen_liba_polytrack5(lua_State *L)
{
    lua_createtable(L, 0, Larray(polytrack5TF) - 1);
    set_funcs(L, -1, polytrack5TF);
    lua_createtable(L, 0, Larray(polytrack5TM));
    set_funcs(L, -1, polytrack5TM);
    set_name(L, -1, "polytrack5");
    lua_setmetatable(L, -2);
    return 1;
}
