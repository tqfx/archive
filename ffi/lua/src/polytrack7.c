/***
 hepta polynomial trajectory
 @module liba.polytrack7
*/

#include "polytrack7.h"

static int polytrack7_init_(lua_State *L, a_polytrack7_s *ctx)
{
    a_real_t t0 = 0, q0 = 0, v0 = 0, a0 = 0, j0 = 0;
    a_real_t t1 = 0, q1 = 0, v1 = 0, a1 = 0, j1 = 0;
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 10:
    {
        j1 = (a_real_t)luaL_checknumber(L, 10);
        A_FALLTHROUGH;
    }
    case 9:
    {
        j0 = (a_real_t)luaL_checknumber(L, 9);
        A_FALLTHROUGH;
    }
    case 8:
    {
        a1 = (a_real_t)luaL_checknumber(L, 8);
        A_FALLTHROUGH;
    }
    case 7:
    {
        a0 = (a_real_t)luaL_checknumber(L, 7);
        A_FALLTHROUGH;
    }
    case 6:
    {
        v1 = (a_real_t)luaL_checknumber(L, 6);
        A_FALLTHROUGH;
    }
    case 5:
    {
        v0 = (a_real_t)luaL_checknumber(L, 5);
        A_FALLTHROUGH;
    }
    case 4:
    {
        q1 = (a_real_t)luaL_checknumber(L, 4);
        q0 = (a_real_t)luaL_checknumber(L, 3);
        t1 = (a_real_t)luaL_checknumber(L, 2);
        t0 = (a_real_t)luaL_checknumber(L, 1);
    }
    break;
    default:
        break;
    }
    a_polytrack7_init(ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1);
    return 1;
}

/***
 constructor for hepta polynomial trajectory
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] number j0 jerk for source
 @tparam[opt] number j1 jerk for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function new
*/
int polytrack7_new(lua_State *L)
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

/***
 initialize function for hepta polynomial trajectory
 @param ctx hepta polynomial trajectory userdata
 @tparam number t0 time for source
 @tparam number t1 time for target
 @tparam number q0 position for source
 @tparam number q1 position for target
 @tparam[opt] number v0 velocity for source
 @tparam[opt] number v1 velocity for target
 @tparam[opt] number a0 acceleration for source
 @tparam[opt] number a1 acceleration for target
 @tparam[opt] number j0 jerk for source
 @tparam[opt] number j1 jerk for target
 @tparam[opt] table source source for trajectory
 @tparam[opt] table target target for trajectory
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function init
*/
int polytrack7_init(lua_State *L)
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

/***
 generation function for hepta polynomial trajectory
 @param ctx hepta polynomial trajectory userdata
 @treturn polytrack7 hepta polynomial trajectory userdata
 @function gen
*/
int polytrack7_gen(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_polytrack7_gen(ctx);
        return 1;
    }
    return 0;
}

/***
 process function for hepta polynomial trajectory
 @param ctx hepta polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn table {position,velocity,acceleration,jerk}
 @function out
*/
int polytrack7_out(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t out[4];
        a_real_t ts = (a_real_t)luaL_checknumber(L, -1);
        a_polytrack7_out(ctx, ts, out);
        lua_createtable(L, 4, 0);
        arraynum_set(L, -1, out, 4);
        return 1;
    }
    return 0;
}

/***
 process function for hepta polynomial trajectory position
 @param ctx hepta polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number position output
 @function pos
*/
int polytrack7_pos(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack7_pos(ctx, ts));
        return 1;
    }
    return 0;
}

/***
 process function for hepta polynomial trajectory velocity
 @param ctx hepta polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number velocity output
 @function vec
*/
int polytrack7_vec(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack7_vec(ctx, ts));
        return 1;
    }
    return 0;
}

/***
 process function for hepta polynomial trajectory acceleration
 @param ctx hepta polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number acceleration output
 @function acc
*/
int polytrack7_acc(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack7_acc(ctx, ts));
        return 1;
    }
    return 0;
}

/***
 process function for hepta polynomial trajectory jerk
 @param ctx hepta polynomial trajectory userdata
 @tparam number ts current time unit(s)
 @treturn number jerk output
 @function jer
*/
int polytrack7_jer(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_real_t ts = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_polytrack7_jer(ctx, ts));
        return 1;
    }
    return 0;
}

static int polytrack7_set(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x00000074: // t
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, Larray(ctx->t), 0);
        arraynum_get(L, 3, ctx->t, Larray(ctx->t));
        break;
    case 0x00000071: // q
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, Larray(ctx->q), 0);
        arraynum_get(L, 3, ctx->q, Larray(ctx->q));
        break;
    case 0x00000076: // v
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, Larray(ctx->v), 0);
        arraynum_get(L, 3, ctx->v, Larray(ctx->v));
        break;
    case 0x00000061: // a
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, Larray(ctx->a), 0);
        arraynum_get(L, 3, ctx->a, Larray(ctx->a));
        break;
    case 0x0000006A: // j
        luaL_checktype(L, 3, LUA_TTABLE);
        lua_createtable(L, Larray(ctx->j), 0);
        arraynum_get(L, 3, ctx->j, Larray(ctx->j));
        break;
    case 0x00003B8C: // t0
        ctx->t[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003A03: // q0
        ctx->q[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003C92: // v0
        ctx->v[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x000031D3: // a0
        ctx->a[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0000366E: // j0
        ctx->j[0] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003B8D: // t1
        ctx->t[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003A04: // q1
        ctx->q[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003C93: // v1
        ctx->v[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x000031D4: // a1
        ctx->a[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0000366F: // j1
        ctx->j[1] = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0xE8859EEB: // __name
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        return 0;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
        return 0;
    }
    a_polytrack7_gen(ctx);
    return 0;
}

static int polytrack7_get(lua_State *L)
{
    a_polytrack7_s *ctx = (a_polytrack7_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0000006B: // k
        lua_createtable(L, Larray(ctx->k), 0);
        arraynum_set(L, -1, ctx->k, Larray(ctx->k));
        break;
    case 0x00000074: // t
        lua_createtable(L, Larray(ctx->t), 0);
        arraynum_set(L, -1, ctx->t, Larray(ctx->t));
        break;
    case 0x00000071: // q
        lua_createtable(L, Larray(ctx->q), 0);
        arraynum_set(L, -1, ctx->q, Larray(ctx->q));
        break;
    case 0x00000076: // v
        lua_createtable(L, Larray(ctx->v), 0);
        arraynum_set(L, -1, ctx->v, Larray(ctx->v));
        break;
    case 0x00000061: // a
        lua_createtable(L, Larray(ctx->a), 0);
        arraynum_set(L, -1, ctx->a, Larray(ctx->a));
        break;
    case 0x0000006A: // j
        lua_createtable(L, Larray(ctx->j), 0);
        arraynum_set(L, -1, ctx->j, Larray(ctx->j));
        break;
    case 0x00003B8C: // t0
        lua_pushnumber(L, (lua_Number)ctx->t[0]);
        break;
    case 0x00003A03: // q0
        lua_pushnumber(L, (lua_Number)ctx->q[0]);
        break;
    case 0x00003C92: // v0
        lua_pushnumber(L, (lua_Number)ctx->v[0]);
        break;
    case 0x000031D3: // a0
        lua_pushnumber(L, (lua_Number)ctx->a[0]);
        break;
    case 0x0000366E: // j0
        lua_pushnumber(L, (lua_Number)ctx->j[0]);
        break;
    case 0x00003B8D: // t1
        lua_pushnumber(L, (lua_Number)ctx->t[1]);
        break;
    case 0x00003A04: // q1
        lua_pushnumber(L, (lua_Number)ctx->q[1]);
        break;
    case 0x00003C93: // v1
        lua_pushnumber(L, (lua_Number)ctx->v[1]);
        break;
    case 0x000031D4: // a1
        lua_pushnumber(L, (lua_Number)ctx->a[1]);
        break;
    case 0x0000366F: // j1
        lua_pushnumber(L, (lua_Number)ctx->j[1]);
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, polytrack7_new);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, polytrack7_init);
        break;
    case 0x001B2CBC: // gen
        lua_pushcfunction(L, polytrack7_gen);
        break;
    case 0x001D4D3A: // out
        lua_pushcfunction(L, polytrack7_out);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, polytrack7_pos);
        break;
    case 0x001F1A38: // vec
        lua_pushcfunction(L, polytrack7_vec);
        break;
    case 0x00199975: // acc
        lua_pushcfunction(L, polytrack7_acc);
        break;
    case 0x001BF5DB: // jer
        lua_pushcfunction(L, polytrack7_jer);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_polytrack7(lua_State *L)
{
    const SFunc funcs[] = {
        {"init", polytrack7_init},
        {"gen", polytrack7_gen},
        {"out", polytrack7_out},
        {"pos", polytrack7_pos},
        {"vec", polytrack7_vec},
        {"acc", polytrack7_acc},
        {"jer", polytrack7_jer},
        {"new", polytrack7_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, 2);
    set_func(L, -1, LSET, l_setter);
    set_func(L, -1, LNEW, polytrack7_new);
    lua_setmetatable(L, -2);

    const SFunc metas[] = {
        {LNEW, polytrack7_out},
        {LSET, polytrack7_set},
        {LGET, polytrack7_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(metas));
    set_name(L, -1, LNAME, "polytrack7");
    set_funcs(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK7_META_); // NOLINT(performance-no-int-to-ptr)
    lua_rawsetp(L, LUA_REGISTRYINDEX, POLYTRACK7_FUNC_); // NOLINT(performance-no-int-to-ptr)

    return polytrack7_func_(L);
}

int polytrack7_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK7_FUNC_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}

int polytrack7_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, POLYTRACK7_META_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}
