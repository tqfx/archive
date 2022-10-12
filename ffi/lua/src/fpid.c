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

static int fpid_init_(lua_State *L, a_fpid_s *ctx)
{
    a_vptr_t buf = a_fpid_bufptr(ctx);
    a_uint_t max = (a_uint_t)luaL_checkinteger(L, 1);
    lua_Number dt = luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    luaL_checktype(L, 4, LUA_TTABLE);
    luaL_checktype(L, 5, LUA_TTABLE);
    luaL_checktype(L, 6, LUA_TTABLE);
    lua_Number imin = luaL_checknumber(L, 7);
    lua_Number imax = luaL_checknumber(L, 8);
    lua_Number omin = luaL_checknumber(L, 9);
    lua_Number omax = luaL_checknumber(L, 10);
    a_uint_t num = (a_uint_t)lua_rawlen(L, 4);
    a_real_t *mmp = tablenum_get(L, 3, ctx->mmp, 0);
    a_real_t *mkp = tablenum_get(L, 4, ctx->mkp, 0);
    a_real_t *mki = tablenum_get(L, 5, ctx->mki, 0);
    a_real_t *mkd = tablenum_get(L, 6, ctx->mkd, 0);
    a_fpid_init(ctx, dt, num, mmp, mkp, mki, mkd, imin, imax, omin, omax);
    a_fpid_buf1(ctx, l_realloc(buf, A_FPID_BUF1(max)), max);
    lua_type(L, 11) == LUA_TNUMBER
        ? a_fpid_pos(ctx, lua_tonumber(L, 11))
        : a_fpid_inc(ctx);
    return 1;
}

/***
 destructor for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @function die
*/
int fpid_die(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        l_dealloc(&ctx->mmp);
        l_dealloc(&ctx->mkp);
        l_dealloc(&ctx->mki);
        l_dealloc(&ctx->mkd);
        l_dealloc(&a_fpid_bufptr(ctx));
        ctx->idx = 0;
        ctx->mms = 0;
        ctx->mat = 0;
    }
    return 0;
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
        memset(ctx, 0, sizeof(a_fpid_s));
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
        a_real_t *mmp = tablenum_get(L, -4, ctx->mmp, 0);
        a_real_t *mkp = tablenum_get(L, -3, ctx->mkp, 0);
        a_real_t *mki = tablenum_get(L, -2, ctx->mki, 0);
        a_real_t *mkd = tablenum_get(L, -1, ctx->mkd, 0);
        a_fpid_base(ctx, num, mmp, mkp, mki, mkd);
        lua_pop(L, 4);
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
 set input extreme value for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number min mininum input
 @tparam number max maxinum input
 @treturn fpid fuzzy PID controller userdata
 @function ilim
*/
int fpid_ilim(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t min = luaL_checknumber(L, -2);
        a_real_t max = luaL_checknumber(L, -1);
        a_fpid_ilim(ctx, min, max);
        lua_pop(L, 2);
        return 1;
    }
    return 0;
}

/***
 set output extreme value for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @tparam number min mininum output
 @tparam number max maxinum output
 @treturn fpid fuzzy PID controller userdata
 @function olim
*/
int fpid_olim(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t min = luaL_checknumber(L, -2);
        a_real_t max = luaL_checknumber(L, -1);
        a_fpid_olim(ctx, min, max);
        lua_pop(L, 2);
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

static int fpid_set(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    uint32_t hash = l_hashs(field);
    switch (hash)
    {
    case 0x000033A0: // dt
        a_pid_set_dt(ctx->pid, luaL_checknumber(L, 3));
        break;
    case 0x00003731: // kp
        ctx->kp = luaL_checknumber(L, 3);
        break;
    case 0x0000372A: // ki
        ctx->ki = luaL_checknumber(L, 3);
        break;
    case 0x00003725: // kd
        ctx->kd = luaL_checknumber(L, 3);
        break;
    case 0x0019E5B7: // buf
    {
        a_uint_t max = (a_uint_t)luaL_checkinteger(L, -1);
        a_vptr_t ptr = l_realloc(a_fpid_bufptr(ctx), A_FPID_BUF1(max));
        a_fpid_buf1(ctx, ptr, max);
        break;
    }
    case 0x10E9FF9D: // summax
        ctx->pid->summax = luaL_checknumber(L, 3);
        break;
    case 0x0EB84F77: // mode
        a_pid_set_reg(ctx->pid, (a_uint_t)luaL_checkinteger(L, 3));
        break;
    default:
        return l_field(L, "setter", field, hash);
    }
    return 0;
}

static int fpid_get(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    uint32_t hash = l_hashs(field);
    switch (hash)
    {
    case 0x000033A0: // dt
        lua_pushnumber(L, a_pid_dt(ctx->pid));
        break;
    case 0x00003731: // kp
        lua_pushnumber(L, ctx->kp);
        break;
    case 0x0000372A: // ki
        lua_pushnumber(L, ctx->ki);
        break;
    case 0x00003725: // kd
        lua_pushnumber(L, ctx->kd);
        break;
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, ctx->pid->outmin);
        break;
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, ctx->pid->outmax);
        break;
    case 0x10E9FF9D: // summax
        lua_pushnumber(L, ctx->pid->summax);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, ctx->pid->out.x);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, ctx->pid->fdb.x);
        break;
    case 0x00003412: // ec
        lua_pushnumber(L, ctx->pid->ec.x);
        break;
    case 0x00000065: // e
        lua_pushnumber(L, ctx->pid->e.x);
        break;
    case 0x001A25B4: // col
        lua_pushinteger(L, a_fpid_col(ctx));
        break;
    case 0x0019E5B7: // buf
        lua_pushinteger(L, a_fpid_bufnum(ctx));
        break;
    case 0x0EB84F77: // mode
        lua_pushinteger(L, a_pid_reg(ctx->pid));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, fpid_new);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, fpid_init);
        break;
    case 0x0F200702: // proc
        lua_pushcfunction(L, fpid_proc);
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, fpid_zero);
        break;
    case 0x0D3B56FD: // base
        lua_pushcfunction(L, fpid_base);
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, fpid_kpid);
        break;
    case 0x0E2E5287: // ilim
        lua_pushcfunction(L, fpid_ilim);
        break;
    case 0x0EFC2429: // olim
        lua_pushcfunction(L, fpid_olim);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, fpid_pos);
        break;
    case 0x001BB75E: // inc
        lua_pushcfunction(L, fpid_inc);
        break;
    case 0x001D457F: // off
        lua_pushcfunction(L, fpid_off);
        break;
    default:
        return l_field(L, "getter", field, hash);
    }
    return 1;
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
        {"init", fpid_init},
        {"proc", fpid_proc},
        {"zero", fpid_zero},
        {"base", fpid_base},
        {"kpid", fpid_kpid},
        {"ilim", fpid_ilim},
        {"olim", fpid_olim},
        {"pos", fpid_pos},
        {"inc", fpid_inc},
        {"off", fpid_off},
        {"new", fpid_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(enums) + Larray(funcs) - 2);
    set_enums(L, -1, enums);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, 2);
    set_func(L, -1, LSET, l_setter);
    set_func(L, -1, LNEW, fpid_new);
    lua_setmetatable(L, -2);

    const SFunc metas[] = {
        {LNEW, fpid_proc},
        {LDIE, fpid_die},
        {LSET, fpid_set},
        {LGET, fpid_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(metas) - 1);
    set_funcs(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, FPID_META_);
    lua_rawsetp(L, LUA_REGISTRYINDEX, FPID_FUNC_);
    lua_rawgetp(L, LUA_REGISTRYINDEX, FPID_FUNC_);

    return 1;
}
