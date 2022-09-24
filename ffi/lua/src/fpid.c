#include "fpid.h"

int fpid_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, FPID_META_);
    return 1;
}

int fpid_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, FPID_FUNC_);
    return 1;
}

int fpid_from_(lua_State *L, int idx, a_fpid_s *ctx)
{
    GFnum fpid[] = {
        {"sigma", &ctx->sigma},
        {"alpha", &ctx->alpha},
        {"kp", &ctx->kp},
        {"ki", &ctx->ki},
        {"kd", &ctx->kd},
        {NULL, NULL},
    };
    get_fnums(L, idx, fpid);
    idx = idx < 0 ? idx - 1 : idx;
    lua_pushstring(L, "mkp");
    if (lua_rawget(L, idx) == LUA_TTABLE)
    {
        ctx->pid->num = (a_uint_t)lua_rawlen(L, -1);
        ctx->mkp = tablenum_get(L, -1, 0);
    }
    lua_pop(L, 1);
    lua_pushstring(L, "mki");
    if (lua_rawget(L, idx) == LUA_TTABLE)
    {
        ctx->mki = tablenum_get(L, -1, 0);
    }
    lua_pop(L, 1);
    lua_pushstring(L, "mkd");
    if (lua_rawget(L, idx) == LUA_TTABLE)
    {
        ctx->mkd = tablenum_get(L, -1, 0);
    }
    lua_pop(L, 1);
    lua_pushstring(L, "mma");
    if (lua_rawget(L, idx) == LUA_TTABLE)
    {
        ctx->mma = tablenum_get(L, -1, 0);
    }
    lua_pop(L, 1);
    lua_pushstring(L, "pid");
    if (lua_rawget(L, idx) == LUA_TTABLE)
    {
        pid_from_(L, -1, ctx->pid);
    }
    lua_pop(L, 1);
    return 0;
}

int fpid_into_(lua_State *L, a_fpid_s *ctx)
{
    a_uint_t num = ctx->pid->num;
    SFnum fpid[] = {
        {"sigma", ctx->sigma},
        {"alpha", ctx->alpha},
        {"kp", ctx->kp},
        {"ki", ctx->ki},
        {"kd", ctx->kd},
        {NULL, 0},
    };
    lua_createtable(L, 0, Larray(fpid) + 1);
    set_fnums(L, -1, fpid);
    lua_pushstring(L, "mkp");
    tablenum_set(L, -2, ctx->mkp, num * num, num);
    lua_pushstring(L, "mki");
    tablenum_set(L, -2, ctx->mki, num * num, num);
    lua_pushstring(L, "mkd");
    tablenum_set(L, -2, ctx->mkd, num * num, num);
    lua_pushstring(L, "mma");
    mf_into_(L, -2, ctx->mma);
    lua_pushstring(L, "pid");
    pid_into_(L, ctx->pid);
    lua_rawset(L, -3);
    return 1;
}

static int fpid_from(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        lua_rotate(L, -2, 1);
    }
    else
    {
        ctx = (a_fpid_s *)lua_newuserdata(L, sizeof(a_fpid_s));
    }
    fpid_meta_(L);
    lua_setmetatable(L, -2);
    fpid_from_(L, -2, ctx);
    return 1;
}

static int fpid_into(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        return fpid_into_(L, ctx);
    }
    return 0;
}

static int fpid_init_(lua_State *L, a_fpid_s *ctx)
{
    a_uint_t max = (a_uint_t)luaL_checkinteger(L, 1);
    lua_Number ts = luaL_checknumber(L, 2);
    lua_Number imin = luaL_checknumber(L, 7);
    lua_Number imax = luaL_checknumber(L, 8);
    lua_Number omin = luaL_checknumber(L, 9);
    lua_Number omax = luaL_checknumber(L, 10);
    a_uint_t num = (a_uint_t)lua_rawlen(L, 4);
    a_real_t *mma = tablenum_get(L, 3, 0);
    a_real_t *mkp = tablenum_get(L, 4, 0);
    a_real_t *mki = tablenum_get(L, 5, 0);
    a_real_t *mkd = tablenum_get(L, 6, 0);
    a_fpid_init(ctx, ts, num, mma, mkp, mki, mkd, imin, imax, omin, omax);
    a_fpid_buf1(ctx, lua_newuserdata(L, A_FPID_BUF1(max)), max);
    lua_pop(L, 1);
    return 1;
}

static int fpid_init(lua_State *L)
{
    if (lua_gettop(L) > 10)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_rotate(L, 1, -1);
            lua_pop(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, 1);
        lua_rotate(L, 1, -1);
        return fpid_init_(L, ctx);
    }
    return 0;
}

static int fpid_new(lua_State *L)
{
    if (lua_gettop(L) > 9)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_rotate(L, 1, -1);
            lua_pop(L, 1);
        }
        a_fpid_s *ctx = (a_fpid_s *)lua_newuserdata(L, sizeof(a_fpid_s));
        fpid_meta_(L);
        lua_setmetatable(L, -2);
        fpid_init_(L, ctx);
        return 1;
    }
    return 0;
}

static int fpid_proc(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t set = luaL_checknumber(L, -2);
        a_real_t ref = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_fpid_proc(ctx, set, ref));
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

static int fpid_done(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_done(ctx);
        return 1;
    }
    return 0;
}

static int fpid_base(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -5);
    if (ctx)
    {
        a_uint_t num = (a_uint_t)lua_rawlen(L, -3);
        a_real_t *mma = tablenum_get(L, -4, 0);
        a_real_t *mkp = tablenum_get(L, -3, 0);
        a_real_t *mki = tablenum_get(L, -2, 0);
        a_real_t *mkd = tablenum_get(L, -1, 0);
        a_fpid_base(ctx, num, mma, mkp, mki, mkd);
        lua_pop(L, 4);
        return 1;
    }
    return 0;
}

static int fpid_buff(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_uint_t max = (a_uint_t)luaL_checkinteger(L, -1);
        a_fpid_buf1(ctx, lua_newuserdata(L, A_FPID_BUF1(max)), max);
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

static int fpid_kpid(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -4);
    if (ctx)
    {
        a_real_t kp = luaL_checknumber(L, -3);
        a_real_t ki = luaL_checknumber(L, -2);
        a_real_t kd = luaL_checknumber(L, -1);
        a_fpid_kpid(ctx, kp, ki, kd);
        lua_pop(L, 3);
        return 1;
    }
    return 0;
}

static int fpid_time(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_fpid_time(ctx, luaL_checknumber(L, -1));
        lua_pop(L, 1);
        return 1;
    }
    return 0;
}

static int fpid_pos(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_fpid_pos(ctx, luaL_checknumber(L, -1));
        lua_pop(L, 1);
        return 1;
    }
    return 0;
}

static int fpid_inc(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_inc(ctx);
        return 1;
    }
    return 0;
}

static int fpid_off(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_off(ctx);
        return 1;
    }
    return 0;
}

int luaopen_liba_fpid(lua_State *L)
{
    const SEnum enums[] = {
        {"OFF", A_PID_OFF},
        {"POS", A_PID_POS},
        {"INC", A_PID_INC},
        {NULL, 0},
    };
    const SFunc funcs[] = {
        {"from", fpid_from},
        {"into", fpid_into},
        {"init", fpid_init},
        {"proc", fpid_proc},
        {"done", fpid_done},
        {"base", fpid_base},
        {"buff", fpid_buff},
        {"kpid", fpid_kpid},
        {"time", fpid_time},
        {"pos", fpid_pos},
        {"inc", fpid_inc},
        {"off", fpid_off},
        {"new", fpid_new},
        {NULL, NULL},
    };
    const SFunc metas[] = {
        {"__call", fpid_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(enums) + Larray(funcs) - 2);
    set_enums(L, -1, enums);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);
    lua_setmetatable(L, -2);

    lua_createtable(L, 0, 2);
    set_func(L, -1, "__call", fpid_proc);
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -3);
    lua_rawset(L, -3);

    lua_rawsetp(L, LUA_REGISTRYINDEX, FPID_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, FPID_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, FPID_FUNC_);

    return 1;
}
