/***
 fuzzy proportional integral derivative controller
 @module liba.fpid
*/

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
    lua_pushstring(L, "mmp");
    lua_rawget(L, idx);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        ctx->mmp = tablenum_get(L, -1, 0);
    }
    lua_pop(L, 1);
    lua_pushstring(L, "mkp");
    lua_rawget(L, idx);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        ctx->pid->num = (a_uint_t)lua_rawlen(L, -1);
        ctx->mkp = tablenum_get(L, -1, 0);
    }
    lua_pop(L, 1);
    lua_pushstring(L, "mki");
    lua_rawget(L, idx);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        ctx->mki = tablenum_get(L, -1, 0);
    }
    lua_pop(L, 1);
    lua_pushstring(L, "mkd");
    lua_rawget(L, idx);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        ctx->mkd = tablenum_get(L, -1, 0);
    }
    lua_pop(L, 1);
    lua_pushstring(L, "pid");
    lua_rawget(L, idx);
    if (lua_type(L, -1) == LUA_TTABLE)
    {
        pid_from_(L, -1, ctx->pid);
    }
    lua_pop(L, 1);
    return 0;
}

int fpid_into_(lua_State *L, a_fpid_s *ctx)
{
    a_uint_t num = ctx->pid->reg >> A_PID_REG;
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
    lua_pushstring(L, "mmp");
    mf_into_(L, -2, ctx->mmp);
    lua_pushstring(L, "mkp");
    tablenum_set(L, -2, ctx->mkp, num * num, num);
    lua_pushstring(L, "mki");
    tablenum_set(L, -2, ctx->mki, num * num, num);
    lua_pushstring(L, "mkd");
    tablenum_set(L, -2, ctx->mkd, num * num, num);
    lua_pushstring(L, "pid");
    pid_into_(L, ctx->pid);
    lua_rawset(L, -3);
    return 1;
}

/***
 convert fuzzy PID controller userdata from table
 @param[opt] ctx fuzzy PID controller userdata
 @tparam table tab fuzzy PID controller table
 @treturn fpid fuzzy PID controller userdata
 @function from
*/
int fpid_from(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        lua_pushvalue(L, -2);
        lua_remove(L, -3);
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

/***
 convert fuzzy PID controller userdata into table
 @param ctx fuzzy PID controller userdata
 @treturn table fuzzy PID controller table
 @function into
*/
int fpid_into(lua_State *L)
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
    lua_Number dt = luaL_checknumber(L, 2);
    lua_Number imin = luaL_checknumber(L, 7);
    lua_Number imax = luaL_checknumber(L, 8);
    lua_Number omin = luaL_checknumber(L, 9);
    lua_Number omax = luaL_checknumber(L, 10);
    a_uint_t num = (a_uint_t)lua_rawlen(L, 4);
    a_real_t *mmp = tablenum_get(L, 3, 0);
    a_real_t *mkp = tablenum_get(L, 4, 0);
    a_real_t *mki = tablenum_get(L, 5, 0);
    a_real_t *mkd = tablenum_get(L, 6, 0);
    a_fpid_init(ctx, dt, num, mmp, mkp, mki, mkd, imin, imax, omin, omax);
    a_fpid_buf1(ctx, lua_newuserdata(L, A_FPID_BUF1(max)), max);
    lua_type(L, 11) == LUA_TNUMBER
        ? a_fpid_pos(ctx, lua_tonumber(L, 11))
        : a_fpid_inc(ctx);
    lua_pop(L, 1);
    return 1;
}

/***
 constructor for fuzzy PID controller
 @tparam int num maximum number triggered by the rule
 @tparam number dt sampling time unit(s)
 @tparam table mmp points to membership function parameter table, an array terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @tparam number imin minimum input
 @tparam number imax maximum input
 @tparam number omin minimum output
 @tparam number omax maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function new
*/
int fpid_new(lua_State *L)
{
    if (lua_gettop(L) > 9)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_fpid_s *ctx = (a_fpid_s *)lua_newuserdata(L, sizeof(a_fpid_s));
        fpid_meta_(L);
        lua_setmetatable(L, -2);
        return fpid_init_(L, ctx);
    }
    return 0;
}

/***
 initialize function for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam int num maximum number triggered by the rule
 @tparam number dt sampling time unit(s)
 @tparam table mmp points to membership function parameter table, an array terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @tparam number imin minimum input
 @tparam number imax maximum input
 @tparam number omin minimum output
 @tparam number omax maximum output
 @tparam[opt] number sum maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function init
*/
int fpid_init(lua_State *L)
{
    if (lua_gettop(L) > 10)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        luaL_checktype(L, 1, LUA_TUSERDATA);
        a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, 1);
        lua_pushvalue(L, 1);
        lua_remove(L, 1);
        return fpid_init_(L, ctx);
    }
    return 0;
}

/***
 calculate function for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number set setpoint
 @tparam number fdb feedback
 @treturn number output
 @function proc
*/
int fpid_proc(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t set = luaL_checknumber(L, -2);
        a_real_t fdb = luaL_checknumber(L, -1);
        lua_pushnumber(L, a_fpid_cc_x(ctx, set, fdb));
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 zero function for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @treturn fpid fuzzy PID controller userdata
 @function zero
*/
int fpid_zero(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_zero(ctx);
        return 1;
    }
    return 0;
}

/***
 set rule base for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam table mmp points to membership function parameter table, an array terminated by 0
 @tparam table mkp points to Kp's rule base table, the rule base must be square
 @tparam table mki points to Ki's rule base table, the rule base must be square
 @tparam table mkd points to Kd's rule base table, the rule base must be square
 @treturn fpid fuzzy PID controller userdata
 @function buff
*/
int fpid_base(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -5);
    if (ctx)
    {
        a_uint_t num = (a_uint_t)lua_rawlen(L, -3);
        a_real_t *mmp = tablenum_get(L, -4, 0);
        a_real_t *mkp = tablenum_get(L, -3, 0);
        a_real_t *mki = tablenum_get(L, -2, 0);
        a_real_t *mkd = tablenum_get(L, -1, 0);
        a_fpid_base(ctx, num, mmp, mkp, mki, mkd);
        lua_pop(L, 4);
        return 1;
    }
    return 0;
}

/***
 set buffer for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam int num maximum number triggered by the rule
 @treturn fpid fuzzy PID controller userdata
 @function buff
*/
int fpid_buff(lua_State *L)
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

/***
 set proportional integral derivative constant for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number kp proportional constant
 @tparam number ki integral constant
 @tparam number kd derivative constant
 @treturn fpid fuzzy PID controller userdata
 @function kpid
*/
int fpid_kpid(lua_State *L)
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

/***
 set sampling period for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number dt sampling time unit(s)
 @treturn fpid fuzzy PID controller userdata
 @function time
*/
int fpid_time(lua_State *L)
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

/***
 positional fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number max maximum intergral output
 @treturn fpid fuzzy PID controller userdata
 @function pos
*/
int fpid_pos(lua_State *L)
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

/***
 incremental fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @treturn fpid fuzzy PID controller userdata
 @function inc
*/
int fpid_inc(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_inc(ctx);
        return 1;
    }
    return 0;
}

/***
 turn off fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @treturn fpid fuzzy PID controller userdata
 @function off
*/
int fpid_off(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_off(ctx);
        return 1;
    }
    return 0;
}

/***
 instance for fuzzy PID controller
 @field OFF turn off fuzzy PID controller
 @field POS positional fuzzy PID controller
 @field INC incremental fuzzy PID controller
 @table fpid
*/
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
        {"zero", fpid_zero},
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
