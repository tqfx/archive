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
        {"k", ctx->k, 4},
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
        {NULL, NULL, 0},
    };
    arraynum_gets(L, idx, polytrack3);
    return 0;
}

int polytrack3_into_(lua_State *L, a_polytrack3_s *ctx)
{
    SFnums polytrack3[] = {
        {"k", ctx->k, 4},
        {"t", ctx->t, 2},
        {"q", ctx->q, 2},
        {"v", ctx->v, 2},
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

static int polytrack3_init_(lua_State *L, a_polytrack3_s *ctx)
{
    a_real_t t0 = 0, q0 = 0, v0 = 0;
    a_real_t t1 = 0, q1 = 0, v1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
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
    a_polytrack3_init(ctx, t0, t1, q0, q1, v0, v1);
    return 1;
}

static int polytrack3_init(lua_State *L)
{
    int top = lua_gettop(L);
    int type = lua_type(L, -1);
    if (top > 4 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_rotate(L, 1, -1);
            lua_pop(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, 1);
        lua_rotate(L, 1, -1);
        return polytrack3_init_(L, ctx);
    }
    if (top > 2 && type == LUA_TTABLE)
    {
        a_real_t target[3] = {0};
        a_real_t source[3] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        luaL_checktype(L, -3, LUA_TUSERDATA);
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -3);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack3_init2(ctx, source, target);
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

static int polytrack3_new(lua_State *L)
{
    int top = lua_gettop(L);
    int type = lua_type(L, -1);
    if (top > 3 && type == LUA_TNUMBER)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_rotate(L, 1, -1);
            lua_pop(L, 1);
        }
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_newuserdata(L, sizeof(a_polytrack3_s));
        polytrack3_meta_(L);
        lua_setmetatable(L, -2);
        return polytrack3_init_(L, ctx);
    }
    if (top > 1 && type == LUA_TTABLE)
    {
        a_real_t target[3] = {0};
        a_real_t source[3] = {0};
        luaL_checktype(L, -1, LUA_TTABLE);
        luaL_checktype(L, -2, LUA_TTABLE);
        arraynum_get(L, -1, target, Larray(target));
        arraynum_get(L, -2, source, Larray(source));
        a_polytrack3_s *ctx = (a_polytrack3_s *)lua_newuserdata(L, sizeof(a_polytrack3_s));
        polytrack3_meta_(L);
        lua_setmetatable(L, -2);
        a_polytrack3_init2(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack3_out(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t out[3];
        a_real_t ts = luaL_checknumber(L, -1);
        a_polytrack3_out(ctx, ts, out);
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
        {"out", polytrack3_out},
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
    set_func(L, -1, "__call", polytrack3_out);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);

    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK3_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK3_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK3_FUNC_);

    return 1;
}
