#include "lua.h"
#include "a/polytrack.h"

int polytrack7_from_(lua_State *L, int idx, a_polytrack7_s *ctx);
int polytrack7_into_(lua_State *L, int idx, a_polytrack7_s *ctx);

int polytrack7_from_(lua_State *L, int idx, a_polytrack7_s *ctx)
{
    GFnums polytrack7[] = {
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"a", ctx->a, 2},
        {"j", ctx->j, 2},
        {"k", ctx->k, 8},
        {NULL, NULL, 0},
    };
    arraynum_gets(L, idx, polytrack7);
    return 1;
}

int polytrack7_into_(lua_State *L, int idx, a_polytrack7_s *ctx)
{
    SFnums polytrack7[] = {
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {"a", ctx->a, 2},
        {"j", ctx->j, 2},
        {"k", ctx->k, 8},
        {NULL, NULL, 0},
    };
    lua_createtable(L, 0, Larray(polytrack7) - 1);
    arraynum_sets(L, idx, polytrack7);
    return 1;
}

static int polytrack7_from(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)userdata_new(L, sizeof(a_polytrack7_s), 1);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        userdata_setp(L, 1, ctx); /* :from() */
    }
    return polytrack7_from_(L, -1, ctx);
}

static int polytrack7_into(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)userdata_get(L);
    if (ctx)
    {
        return polytrack7_into_(L, -1, ctx);
    }
    return 0;
}

static int polytrack7_init(lua_State *L)
{
    int n = lua_gettop(L);
    if (n > 1)
    {
        a_real_t target[5];
        a_real_t source[5];
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        if (n > 2)
        {
            luaL_checktype(L, 3, LUA_TTABLE);
        }
        a_polytrack7_s *ctx = (a_polytrack7_s *)userdata_new(L, sizeof(a_polytrack7_s), 2);
        arraynum_get(L, 1, source, Larray(source));
        arraynum_get(L, 2, target, Larray(target));
        a_polytrack7_init(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack7_all(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t out[4];
        a_real_t ts = luaL_checknumber(L, 2);
        a_polytrack7_all(ctx, ts, out);
        lua_createtable(L, 4, 0);
        arraynum_set(L, -1, out, 4);
        return 1;
    }
    return 0;
}

static int polytrack7_pos(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack7_pos(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack7_vec(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack7_vec(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack7_acc(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack7_acc(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack7_jer(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack7_jer(ctx, ts));
        return 1;
    }
    return 0;
}

static const SFunc polytrack7TF[] = {
    {"from", polytrack7_from},
    {"into", polytrack7_into},
    {"init", polytrack7_init},
    {"all", polytrack7_all},
    {"pos", polytrack7_pos},
    {"vec", polytrack7_vec},
    {"acc", polytrack7_acc},
    {"jer", polytrack7_jer},
    {NULL, NULL},
};

static int polytrack7_new(lua_State *L)
{
    if (lua_istable(L, 1) && lua_istable(L, 2) && lua_istable(L, 3) && lua_gettop(L) > 3)
    {
        /* :polytrack7() */
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }

    int ok = polytrack7_init(L);

    lua_createtable(L, 0, Larray(polytrack7TF));
    set_funcs(L, -1, polytrack7TF);
    userdata_seti(L, -1, -2);

    lua_createtable(L, 0, 1);
    set_func(L, -1, "__call", polytrack7_all);
    lua_setmetatable(L, -2);

    return ok;
}

static const SFunc polytrack7TM[] = {
    {"__call", polytrack7_new},
    {NULL, NULL},
};

int luaopen_liba_polytrack7(lua_State *L)
{
    lua_createtable(L, 0, Larray(polytrack7TF) - 1);
    set_funcs(L, -1, polytrack7TF);
    lua_createtable(L, 0, Larray(polytrack7TM));
    set_funcs(L, -1, polytrack7TM);
    set_name(L, -1, "polytrack7");
    lua_setmetatable(L, -2);
    return 1;
}
