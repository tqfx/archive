/***
 algorithm library version
 @module liba.version
*/

#define LUA_LIB
#include "version.h"
#include <string.h>

static int l_version_tostring(lua_State *L)
{
    a_version_s *ctx = (a_version_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_pushfstring(L, "%d.%d.%d", ctx->major, ctx->minor, ctx->patch);
        return 1;
    }
    return 0;
}

static int l_version_init_(lua_State *L, a_version_s *ctx)
{
    switch (lua_gettop(L) - lua_isuserdata(L, -1))
    {
    case 3:
        ctx->patch = (a_uint_t)luaL_checkinteger(L, 3);
        A_FALLTHROUGH;
    case 2:
        ctx->minor = (a_uint_t)luaL_checkinteger(L, 2);
        A_FALLTHROUGH;
    case 1:
        ctx->major = (a_uint_t)luaL_checkinteger(L, 1);
        A_FALLTHROUGH;
    default:
        break;
    }
    return 1;
}

/***
 constructor for algorithm library version
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer patch version patch number
 @treturn algorithm library version userdata
 @function new
*/
int l_version_new(lua_State *L)
{
    while (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    a_version_s *ctx = (a_version_s *)lua_newuserdata(L, sizeof(a_version_s));
    memset(ctx, 0, sizeof(a_version_s));
    l_version_meta_(L);
    lua_setmetatable(L, -2);
    return l_version_init_(L, ctx);
}

/***
 initialize function for algorithm library version
 @param ctx algorithm library version userdata
 @tparam[opt] integer major version major number
 @tparam[opt] integer minor version minor number
 @tparam[opt] integer patch version patch number
 @treturn algorithm library version userdata
 @function init
*/
int l_version_init(lua_State *L)
{
    while (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    luaL_checktype(L, 1, LUA_TUSERDATA);
    a_version_s *ctx = (a_version_s *)lua_touserdata(L, 1);
    lua_pushvalue(L, 1);
    lua_remove(L, 1);
    return l_version_init_(L, ctx);
}

/***
 compare the version lhs with the version rhs
 @tparam lhs version structure to be compared
 @tparam rhs version structure to be compared
 @treturn integer `<0` version lhs < version rhs
 @treturn integer `>0` version lhs > version rhs
 @treturn integer 0 version lhs == version rhs
 @function cmp
*/
int l_version_cmp(lua_State *L)
{
    while (lua_type(L, 1) == LUA_TTABLE)
    {
        lua_remove(L, 1);
    }
    luaL_checktype(L, 1, LUA_TUSERDATA);
    a_version_s *lhs = (a_version_s *)lua_touserdata(L, 1);
    luaL_checktype(L, 2, LUA_TUSERDATA);
    a_version_s *rhs = (a_version_s *)lua_touserdata(L, 2);
    lua_pushinteger(L, a_version_cmp(lhs, rhs));
    return 1;
}

#undef FUNC
#define FUNC(func)                                              \
    int l_version_##func(lua_State *L)                          \
    {                                                           \
        while (lua_type(L, 1) == LUA_TTABLE)                    \
        {                                                       \
            lua_remove(L, 1);                                   \
        }                                                       \
        luaL_checktype(L, 1, LUA_TUSERDATA);                    \
        a_version_s *lhs = (a_version_s *)lua_touserdata(L, 1); \
        luaL_checktype(L, 2, LUA_TUSERDATA);                    \
        a_version_s *rhs = (a_version_s *)lua_touserdata(L, 2); \
        lua_pushboolean(L, a_version_##func(lhs, rhs));         \
        return 1;                                               \
    }
/***
 version lhs less than version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function lt
*/
FUNC(lt)
/***
 version lhs greater than version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function gt
*/
FUNC(gt)
/***
 version lhs less than or equal version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function le
*/
FUNC(le)
/***
 version lhs greater than or equal version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function ge
*/
FUNC(ge)
/***
 version lhs equal version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function eq
*/
FUNC(eq)
/***
 version lhs not equal version rhs
 @param lhs operand on the left
 @param rhs operand on the right
 @return result of comparison
 @function ne
*/
FUNC(ne)
#undef FUNC

static int l_version_set(lua_State *L)
{
    a_version_s *ctx = (a_version_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x86720331: // major
        ctx->major = (a_uint_t)luaL_checkinteger(L, 3);
        break;
    case 0x87857C2D: // minor
        ctx->minor = (a_uint_t)luaL_checkinteger(L, 3);
        break;
    case 0xBB1DBE50: // patch
        ctx->patch = (a_uint_t)luaL_checkinteger(L, 3);
        break;
    case 0x0CD3E494: // __lt
    case 0x0CD3E485: // __le
    case 0x0CD3E0FC: // __eq
    case 0xE8859EEB: // __name
    case 0xE70C48C6: // __call
    case 0xA65758B2: // __index
    case 0xAEB551C6: // __newindex
    case 0x5DA21A54: // __tostring
        break;
    default:
        lua_getmetatable(L, 1);
        lua_pushvalue(L, 3);
        lua_setfield(L, 4, field);
    }
    return 0;
}

static int l_version_get(lua_State *L)
{
    a_version_s *ctx = (a_version_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x86720331: // major
        lua_pushinteger(L, (lua_Integer)ctx->major);
        break;
    case 0x87857C2D: // minor
        lua_pushinteger(L, (lua_Integer)ctx->minor);
        break;
    case 0xBB1DBE50: // patch
        lua_pushinteger(L, (lua_Integer)ctx->patch);
        break;
    case 0x001A24B2: // cmp
        lua_pushcfunction(L, l_version_cmp);
        break;
    case 0x000037B8: // lt
        lua_pushcfunction(L, l_version_lt);
        break;
    case 0x00003529: // gt
        lua_pushcfunction(L, l_version_gt);
        break;
    case 0x000037A9: // le
        lua_pushcfunction(L, l_version_le);
        break;
    case 0x0000351A: // ge
        lua_pushcfunction(L, l_version_ge);
        break;
    case 0x00003420: // eq
        lua_pushcfunction(L, l_version_eq);
        break;
    case 0x000038AF: // ne
        lua_pushcfunction(L, l_version_ne);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

/***
 algorithm library version string
 @field major algorithm library version major
 @field minor algorithm library version minor
 @field patch algorithm library version patch
 @table version
*/
int luaopen_liba_version(lua_State *L)
{
    const l_int_s enums[] = {
        {"major", A_VERSION_MAJOR},
        {"minor", A_VERSION_MINOR},
        {"patch", A_VERSION_PATCH},
        {NULL, 0},
    };
    const l_func_s funcs[] = {
        {"init", l_version_init},
        {"new", l_version_new},
        {"cmp", l_version_cmp},
        {"lt", l_version_lt},
        {"gt", l_version_gt},
        {"le", l_version_le},
        {"ge", l_version_ge},
        {"eq", l_version_eq},
        {"ne", l_version_ne},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(enums) + L_ARRAY(funcs) - 1);
    l_int_reg(L, -1, enums);
    l_func_reg(L, -1, funcs);
    lua_createtable(L, 0, 2);
    l_func_set(L, -1, L_SET, l_setter);
    l_func_set(L, -1, L_NEW, l_version_new);
    lua_setmetatable(L, -2);

    const l_func_s metas[] = {
        {L_PRI, l_version_tostring},
        {L_NEW, l_version_new},
        {L_GET, l_version_get},
        {L_SET, l_version_set},
        {L_LT, l_version_lt},
        {L_LE, l_version_le},
        {L_EQ, l_version_eq},
        {NULL, NULL},
    };
    lua_createtable(L, 0, L_ARRAY(metas));
    l_str_set(L, -1, L_NAME, "version");
    l_func_reg(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, L_VERSION_META_); // NOLINT(performance-no-int-to-ptr)
    lua_rawsetp(L, LUA_REGISTRYINDEX, L_VERSION_FUNC_); // NOLINT(performance-no-int-to-ptr)

    return l_version_func_(L);
}

int l_version_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, L_VERSION_FUNC_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}

int l_version_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, L_VERSION_META_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}
