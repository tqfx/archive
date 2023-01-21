/***
 fuzzy proportional integral derivative controller
 @module liba.fpid
*/

#define LUA_LIB
#include "fpid.h"
#include <string.h>

static int l_fpid_init_(lua_State *L, a_fpid_s *ctx)
{
    void *ud;
    a_vptr_t buf = a_fpid_bufptr(ctx);
    lua_Alloc alloc = lua_getallocf(L, &ud);
    a_uint_t max = (a_uint_t)luaL_checkinteger(L, 1);
    a_real_t dt = (a_real_t)luaL_checknumber(L, 2);
    luaL_checktype(L, 3, LUA_TTABLE);
    luaL_checktype(L, 4, LUA_TTABLE);
    luaL_checktype(L, 5, LUA_TTABLE);
    luaL_checktype(L, 6, LUA_TTABLE);
    a_real_t imin = (a_real_t)luaL_checknumber(L, 7);
    a_real_t imax = (a_real_t)luaL_checknumber(L, 8);
    a_real_t omin = (a_real_t)luaL_checknumber(L, 9);
    a_real_t omax = (a_real_t)luaL_checknumber(L, 10);
    a_uint_t num = (a_uint_t)lua_rawlen(L, 4);
    a_real_t *mmp = l_table_num_get(L, 3, ctx->mmp, 0);
    a_real_t *mkp = l_table_num_get(L, 4, ctx->mkp, 0);
    a_real_t *mki = l_table_num_get(L, 5, ctx->mki, 0);
    a_real_t *mkd = l_table_num_get(L, 6, ctx->mkd, 0);
    a_fpid_init(ctx, dt, num, mmp, mkp, mki, mkd, imin, imax, omin, omax);
    a_fpid_buf1(ctx, alloc(ud, buf, 0, A_FPID_BUF1(max)), max);
    lua_isnumber(L, 11)
        ? a_fpid_pos(ctx, (a_real_t)lua_tonumber(L, 11))
        : a_fpid_inc(ctx);
    return 1;
}

/***
 destructor for fuzzy PID controller
 @param ctx fuzzy PID controller userdata
 @function die
*/
int l_fpid_die(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        void *ud;
        lua_Alloc alloc = lua_getallocf(L, &ud);
        ctx->mmp = alloc(ud, (void *)(intptr_t)ctx->mmp, 0, 0); // NOLINT(performance-no-int-to-ptr)
        ctx->mkp = alloc(ud, (void *)(intptr_t)ctx->mkp, 0, 0); // NOLINT(performance-no-int-to-ptr)
        ctx->mki = alloc(ud, (void *)(intptr_t)ctx->mki, 0, 0); // NOLINT(performance-no-int-to-ptr)
        ctx->mkd = alloc(ud, (void *)(intptr_t)ctx->mkd, 0, 0); // NOLINT(performance-no-int-to-ptr)
        alloc(ud, a_fpid_bufptr(ctx), 0, 0);
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
int l_fpid_new(lua_State *L)
{
    if (lua_gettop(L) > 9)
    {
        while (lua_type(L, 1) == LUA_TTABLE)
        {
            lua_remove(L, 1);
        }
        a_fpid_s *ctx = (a_fpid_s *)lua_newuserdata(L, sizeof(a_fpid_s));
        memset(ctx, 0, sizeof(a_fpid_s));
        l_fpid_meta_(L);
        lua_setmetatable(L, -2);
        return l_fpid_init_(L, ctx);
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
int l_fpid_init(lua_State *L)
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
        return l_fpid_init_(L, ctx);
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
int l_fpid_proc(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t set = (a_real_t)luaL_checknumber(L, -2);
        a_real_t fdb = (a_real_t)luaL_checknumber(L, -1);
        lua_pushnumber(L, (lua_Number)a_fpid_outv(ctx, set, fdb));
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
int l_fpid_zero(lua_State *L)
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
int l_fpid_base(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -5);
    if (ctx)
    {
        a_uint_t num = (a_uint_t)lua_rawlen(L, -3);
        a_real_t *mmp = l_table_num_get(L, -4, ctx->mmp, 0);
        a_real_t *mkp = l_table_num_get(L, -3, ctx->mkp, 0);
        a_real_t *mki = l_table_num_get(L, -2, ctx->mki, 0);
        a_real_t *mkd = l_table_num_get(L, -1, ctx->mkd, 0);
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
int l_fpid_kpid(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -4);
    if (ctx)
    {
        a_real_t kp = (a_real_t)luaL_checknumber(L, -3);
        a_real_t ki = (a_real_t)luaL_checknumber(L, -2);
        a_real_t kd = (a_real_t)luaL_checknumber(L, -1);
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
int l_fpid_ilim(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t min = (a_real_t)luaL_checknumber(L, -2);
        a_real_t max = (a_real_t)luaL_checknumber(L, -1);
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
int l_fpid_olim(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -3);
    if (ctx)
    {
        a_real_t min = (a_real_t)luaL_checknumber(L, -2);
        a_real_t max = (a_real_t)luaL_checknumber(L, -1);
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
int l_fpid_pos(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        a_fpid_pos(ctx, (a_real_t)luaL_checknumber(L, -1));
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
int l_fpid_inc(lua_State *L)
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
int l_fpid_off(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        a_fpid_off(ctx);
        return 1;
    }
    return 0;
}

static int l_fpid_set(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x000033A0: // dt
        a_pid_set_dt(ctx->pid, (a_real_t)luaL_checknumber(L, 3));
        break;
    case 0x00003731: // kp
        ctx->kp = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0000372A: // ki
        ctx->ki = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x00003725: // kd
        ctx->kd = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0019E5B7: // buf
    {
        void *ud;
        lua_Alloc alloc = lua_getallocf(L, &ud);
        a_uint_t max = (a_uint_t)luaL_checkinteger(L, -1);
        a_vptr_t ptr = alloc(ud, a_fpid_bufptr(ctx), 0, A_FPID_BUF1(max));
        a_fpid_buf1(ctx, ptr, max);
        break;
    }
    case 0x10E9FF9D: // summax
        ctx->pid->summax = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0EB84F77: // mode
        a_pid_set_mode(ctx->pid, (a_uint_t)luaL_checkinteger(L, 3));
        break;
    case 0xE8859EEB: // __name
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
        break;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
    }
    return 0;
}

static int l_fpid_get(lua_State *L)
{
    a_fpid_s *ctx = (a_fpid_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x000033A0: // dt
        lua_pushnumber(L, (lua_Number)a_pid_dt(ctx->pid));
        break;
    case 0x00003731: // kp
        lua_pushnumber(L, (lua_Number)ctx->kp);
        break;
    case 0x0000372A: // ki
        lua_pushnumber(L, (lua_Number)ctx->ki);
        break;
    case 0x00003725: // kd
        lua_pushnumber(L, (lua_Number)ctx->kd);
        break;
    case 0x23C8F51C: // outmin
        lua_pushnumber(L, (lua_Number)ctx->pid->outmin);
        break;
    case 0x23C8F10E: // outmax
        lua_pushnumber(L, (lua_Number)ctx->pid->outmax);
        break;
    case 0x10E9FF9D: // summax
        lua_pushnumber(L, (lua_Number)ctx->pid->summax);
        break;
    case 0x001D4D3A: // out
        lua_pushnumber(L, (lua_Number)ctx->pid->out.v);
        break;
    case 0x001AE924: // fdb
        lua_pushnumber(L, (lua_Number)ctx->pid->fdb.v);
        break;
    case 0x00003412: // ec
        lua_pushnumber(L, (lua_Number)ctx->pid->ec.v);
        break;
    case 0x00000065: // e
        lua_pushnumber(L, (lua_Number)ctx->pid->e.v);
        break;
    case 0x001A25B4: // col
        lua_pushinteger(L, (lua_Integer)a_fpid_col(ctx));
        break;
    case 0x0019E5B7: // buf
        lua_pushinteger(L, (lua_Integer)a_fpid_bufnum(ctx));
        break;
    case 0x0EB84F77: // mode
        lua_pushinteger(L, (lua_Integer)a_pid_mode(ctx->pid));
        break;
    case 0x001D0204: // new
        lua_pushcfunction(L, l_fpid_new);
        break;
    case 0x0E2ED8A0: // init
        lua_pushcfunction(L, l_fpid_init);
        break;
    case 0x0F200702: // proc
        lua_pushcfunction(L, l_fpid_proc);
        break;
    case 0x1073A930: // zero
        lua_pushcfunction(L, l_fpid_zero);
        break;
    case 0x0D3B56FD: // base
        lua_pushcfunction(L, l_fpid_base);
        break;
    case 0x0E73F9D8: // kpid
        lua_pushcfunction(L, l_fpid_kpid);
        break;
    case 0x0E2E5287: // ilim
        lua_pushcfunction(L, l_fpid_ilim);
        break;
    case 0x0EFC2429: // olim
        lua_pushcfunction(L, l_fpid_olim);
        break;
    case 0x001D8D30: // pos
        lua_pushcfunction(L, l_fpid_pos);
        break;
    case 0x001BB75E: // inc
        lua_pushcfunction(L, l_fpid_inc);
        break;
    case 0x001D457F: // off
        lua_pushcfunction(L, l_fpid_off);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
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
    const l_int_s enums[] = {
        {"OFF", A_PID_OFF},
        {"POS", A_PID_POS},
        {"INC", A_PID_INC},
        {NULL, 0},
    };
    const l_func_s funcs[] = {
        {"init", l_fpid_init},
        {"proc", l_fpid_proc},
        {"zero", l_fpid_zero},
        {"base", l_fpid_base},
        {"kpid", l_fpid_kpid},
        {"ilim", l_fpid_ilim},
        {"olim", l_fpid_olim},
        {"pos", l_fpid_pos},
        {"inc", l_fpid_inc},
        {"off", l_fpid_off},
        {"new", l_fpid_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(enums) + L_ARRAY(funcs) - 2);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, l_setter);
    l_func_set(L, -1, L_NEW, l_fpid_new);
    lua_setmetatable(L, -2);

    const l_func_s metas[] = {
        {L_NEW, l_fpid_proc},
        {L_DIE, l_fpid_die},
        {L_SET, l_fpid_set},
        {L_GET, l_fpid_get},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(metas));
    l_str_set(L, -1, L_NAME, "fpid");
    l_func_reg(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, L_FPID_META_); // NOLINT(performance-no-int-to-ptr)
    lua_rawsetp(L, LUA_REGISTRYINDEX, L_FPID_FUNC_); // NOLINT(performance-no-int-to-ptr)

    return l_fpid_func_(L);
}

int l_fpid_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, L_FPID_FUNC_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}

int l_fpid_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, L_FPID_META_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}
