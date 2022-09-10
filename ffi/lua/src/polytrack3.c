#include "lua.h"
#include "a/polytrack.h"

static int polytrack3_from(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)userdata_new(L, sizeof(a_polytrack3_s), 1);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        userdata_setp(L, 1, ctx); /* :from() */
    }
#undef get
#define get(field, num)                       \
    lua_pushstring(L, #field);                \
    if (lua_rawget(L, -3) == LUA_TTABLE)      \
    {                                         \
        arraynum_get(L, -1, ctx->field, num); \
    }                                         \
    lua_pop(L, 1)
    get(t, 2);
    get(q, 2);
    get(v, 2);
    get(k, 4);
#undef get
    return 1;
}

static int polytrack3_into(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)userdata_get(L);
    if (ctx)
    {
        lua_createtable(L, 0, 4);
#undef set
#define set(field, num)                   \
    lua_pushstring(L, #field);            \
    lua_createtable(L, num, 0);           \
    arraynum_set(L, -1, ctx->field, num); \
    lua_rawset(L, -3)
        set(t, 2);
        set(q, 2);
        set(v, 2);
        set(k, 4);
#undef set
        return 1;
    }
    return 0;
}

static int polytrack3_init(lua_State *L)
{
    int n = lua_gettop(L);
    if (n > 1)
    {
        a_real_t target[3];
        a_real_t source[3];
        luaL_checktype(L, 1, LUA_TTABLE);
        luaL_checktype(L, 2, LUA_TTABLE);
        if (n > 2)
        {
            luaL_checktype(L, 3, LUA_TTABLE);
        }
        a_polytrack3_s *ctx = (a_polytrack3_s *)userdata_new(L, sizeof(a_polytrack3_s), 2);
        arraynum_get(L, 1, source, 3);
        arraynum_get(L, 2, target, 3);
        a_polytrack3_init(ctx, source, target);
        return 1;
    }
    return 0;
}

static int polytrack3_all(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t out[3];
        a_real_t ts = luaL_checknumber(L, 2);
        a_polytrack3_all(ctx, ts, out);
        lua_createtable(L, 3, 0);
        arraynum_set(L, -1, out, 3);
        return 1;
    }
    return 0;
}

static int polytrack3_pos(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack3_pos(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack3_vec(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack3_vec(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack3_acc(lua_State *L)
{
    a_polytrack3_s *ctx = (a_polytrack3_s *)userdata_get(L);
    if (ctx)
    {
        a_real_t ts = luaL_checknumber(L, 2);
        lua_pushnumber(L, a_polytrack3_acc(ctx, ts));
        return 1;
    }
    return 0;
}

static const RegFunc polytrack3TF[] = {
    {"from", polytrack3_from},
    {"into", polytrack3_into},
    {"init", polytrack3_init},
    {"all", polytrack3_all},
    {"pos", polytrack3_pos},
    {"vec", polytrack3_vec},
    {"acc", polytrack3_acc},
    {NULL, NULL},
};

static int polytrack3_new(lua_State *L)
{
    if (lua_istable(L, 1) && lua_istable(L, 2) && lua_istable(L, 3) && lua_gettop(L) > 3)
    {
        /* :polytrack3() */
        lua_rotate(L, 1, -1);
        lua_pop(L, 1);
    }

    int ok = polytrack3_init(L);

    lua_createtable(L, 0, Larray(polytrack3TF));
    reg_funcs(L, -1, polytrack3TF);
    userdata_seti(L, -1, -2);

    lua_createtable(L, 0, 1);
    reg_func(L, -1, "__call", polytrack3_all);
    lua_setmetatable(L, -2);

    return ok;
}

static const RegFunc polytrack3TM[] = {
    {"__call", polytrack3_new},
    {NULL, NULL},
};

int luaopen_liba_polytrack3(lua_State *L)
{
    lua_createtable(L, 0, Larray(polytrack3TF) - 1);
    reg_funcs(L, -1, polytrack3TF);
    lua_createtable(L, 0, Larray(polytrack3TM));
    reg_funcs(L, -1, polytrack3TM);
    reg_name(L, -1, "polytrack3");
    lua_setmetatable(L, -2);
    return 1;
}
