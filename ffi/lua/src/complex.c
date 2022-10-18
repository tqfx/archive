/***
 complex number
 @module liba.complex
*/

#include "complex.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* __GNUC__ || __clang__ */

static a_complex_s *complex_new_(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_newuserdata(L, sizeof(a_complex_s));
    complex_meta_(L);
    lua_setmetatable(L, -2);
    return ctx;
}

static int complex_tostring(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, 1);
    if (ctx)
    {
        lua_pushfstring(L, "(%f,%f)", (lua_Number)ctx->real, (lua_Number)ctx->imag);
        return 1;
    }
    return 0;
}

/***
 constructor for complex number from rectangular Cartesian components
 @tparam number real real part of complex number
 @tparam number imag imaginary part of complex number
 @treturn complex complex number userdata
 @function new
*/
int complex_new(lua_State *L)
{
    if (lua_gettop(L) > 1)
    {
        a_real_t real = (a_real_t)luaL_checknumber(L, -2);
        a_real_t imag = (a_real_t)luaL_checknumber(L, -1);
        a_complex_s *ctx = complex_new_(L);
        *ctx = a_complex_c(real, imag);
        return 1;
    }
    return 0;
}

/***
 constructor for complex number from polar form
 @tparam number r a distance from a reference point
 @tparam number theta an angle from a reference direction
 @treturn complex complex number userdata
 @function polar
*/
int complex_polar(lua_State *L)
{
    if (lua_gettop(L) > 1)
    {
        a_real_t r = (a_real_t)luaL_checknumber(L, -2);
        a_real_t theta = (a_real_t)luaL_checknumber(L, -1);
        a_complex_s *ctx = complex_new_(L);
        *ctx = a_complex_polar(r, theta);
        return 1;
    }
    return 0;
}

/***
 complex conjugate value
 @tparam complex ctx complex number userdata
 @treturn complex complex number userdata
 @function conj
*/
int complex_conj(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        *complex_new_(L) = a_complex_conj(*ctx);
        return 1;
    }
    return 0;
}

/***
 - complex unary – operator
 @tparam complex ctx complex number userdata
 @treturn complex complex number userdata
 @function unm
*/
int complex_unm(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, -1);
    if (ctx)
    {
        *complex_new_(L) = a_complex_neg(*ctx);
        return 1;
    }
    return 0;
}

/***
 + complex addition operator
 @tparam complex ctx complex number userdata
 @tparam complex obj complex number userdata
 @treturn complex complex number userdata
 @function add
*/
int complex_add(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        int e = lua_type(L, -1);
        if (e == LUA_TUSERDATA)
        {
            const char *field = 0;
            if (lua_getmetatable(L, -1))
            {
                field = get_name(L, -1, LNAME);
                lua_pop(L, 1);
            }
            a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
            switch (hash)
            {
            case 0x77E40C08: // complex
            {
                a_complex_s *x = (a_complex_s *)lua_touserdata(L, -1);
                *complex_new_(L) = a_complex_add(*ctx, *x);
                break;
            }
            case 0x0E2E9172: // imag
            {
                a_real_t *x = (a_real_t *)lua_touserdata(L, -1);
                *complex_new_(L) = a_complex_add_imag(*ctx, *x);
                break;
            }
            default:
                return luaL_error(L, "'complex' not support '%s'", field ? field : "");
            }
        }
        else if (e == LUA_TNUMBER)
        {
            a_real_t x = (a_real_t)lua_tonumber(L, -1);
            *complex_new_(L) = a_complex_add_real(*ctx, x);
        }
    }
    return 1;
}

/***
 - complex subtraction operator
 @tparam complex ctx complex number userdata
 @tparam complex obj complex number userdata
 @treturn complex complex number userdata
 @function sub
*/
int complex_sub(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        int e = lua_type(L, -1);
        if (e == LUA_TUSERDATA)
        {
            const char *field = 0;
            if (lua_getmetatable(L, -1))
            {
                field = get_name(L, -1, LNAME);
                lua_pop(L, 1);
            }
            a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
            switch (hash)
            {
            case 0x77E40C08: // complex
            {
                a_complex_s *x = (a_complex_s *)lua_touserdata(L, -1);
                *complex_new_(L) = a_complex_sub(*ctx, *x);
                break;
            }
            case 0x0E2E9172: // imag
            {
                a_real_t *x = (a_real_t *)lua_touserdata(L, -1);
                *complex_new_(L) = a_complex_sub_imag(*ctx, *x);
                break;
            }
            default:
                return luaL_error(L, "'complex' not support '%s'", field ? field : "");
            }
        }
        else if (e == LUA_TNUMBER)
        {
            a_real_t x = (a_real_t)lua_tonumber(L, -1);
            *complex_new_(L) = a_complex_sub_real(*ctx, x);
        }
    }
    return 1;
}

/***
 * complex multiplication operator
 @tparam complex ctx complex number userdata
 @tparam complex obj complex number userdata
 @treturn complex complex number userdata
 @function mul
*/
int complex_mul(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        int e = lua_type(L, -1);
        if (e == LUA_TUSERDATA)
        {
            const char *field = 0;
            if (lua_getmetatable(L, -1))
            {
                field = get_name(L, -1, LNAME);
                lua_pop(L, 1);
            }
            a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
            switch (hash)
            {
            case 0x77E40C08: // complex
            {
                a_complex_s *x = (a_complex_s *)lua_touserdata(L, -1);
                *complex_new_(L) = a_complex_mul(*ctx, *x);
                break;
            }
            case 0x0E2E9172: // imag
            {
                a_real_t *x = (a_real_t *)lua_touserdata(L, -1);
                *complex_new_(L) = a_complex_mul_imag(*ctx, *x);
                break;
            }
            default:
                return luaL_error(L, "'complex' not support '%s'", field ? field : "");
            }
        }
        else if (e == LUA_TNUMBER)
        {
            a_real_t x = (a_real_t)lua_tonumber(L, -1);
            *complex_new_(L) = a_complex_mul_real(*ctx, x);
        }
    }
    return 1;
}

/***
 / complex division operator
 @tparam complex ctx complex number userdata
 @tparam complex obj complex number userdata
 @treturn complex complex number userdata
 @function div
*/
int complex_div(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, -2);
    if (ctx)
    {
        int e = lua_type(L, -1);
        if (e == LUA_TUSERDATA)
        {
            const char *field = 0;
            if (lua_getmetatable(L, -1))
            {
                field = get_name(L, -1, LNAME);
                lua_pop(L, 1);
            }
            a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
            switch (hash)
            {
            case 0x77E40C08: // complex
            {
                a_complex_s *x = (a_complex_s *)lua_touserdata(L, -1);
                *complex_new_(L) = a_complex_div(*ctx, *x);
                break;
            }
            case 0x0E2E9172: // imag
            {
                a_real_t *x = (a_real_t *)lua_touserdata(L, -1);
                *complex_new_(L) = a_complex_div_imag(*ctx, *x);
                break;
            }
            default:
                return luaL_error(L, "'complex' not support '%s'", field ? field : "");
            }
        }
        else if (e == LUA_TNUMBER)
        {
            a_real_t x = (a_real_t)lua_tonumber(L, -1);
            *complex_new_(L) = a_complex_div_real(*ctx, x);
        }
    }
    return 1;
}

static int complex_set(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0F6133A2: // real
        ctx->real = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0E2E9172: // imag
        ctx->imag = (a_real_t)luaL_checknumber(L, 3);
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

static int complex_get(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0F6133A2: // real
        lua_pushnumber(L, (lua_Number)ctx->real);
        break;
    case 0x0E2E9172: // imag
        lua_pushnumber(L, (lua_Number)ctx->imag);
        break;
    case 0x00000072: // r
        lua_pushnumber(L, (lua_Number)a_complex_abs(*ctx));
        break;
    case 0x0240D1F6: // theta
        lua_pushnumber(L, (lua_Number)a_complex_arg(*ctx));
        break;
    case 0x0D614C8C: // conj
        lua_pushcfunction(L, complex_conj);
        break;
    case 0x001EDBD4: // unm
        lua_pushcfunction(L, complex_unm);
        break;
    case 0x001999F9: // add
        lua_pushcfunction(L, complex_add);
        break;
    case 0x001E594C: // sub
        lua_pushcfunction(L, complex_sub);
        break;
    case 0x001CC720: // mul
        lua_pushcfunction(L, complex_mul);
        break;
    case 0x001A65B5: // div
        lua_pushcfunction(L, complex_div);
        break;
    default:
        lua_getmetatable(L, 1);
        lua_getfield(L, 3, field);
    }
    return 1;
}

int luaopen_liba_complex(lua_State *L)
{
    const SFunc funcs[] = {
        {"polar", complex_polar},
        {"conj", complex_conj},
        {"add", complex_add},
        {"sub", complex_sub},
        {"mul", complex_mul},
        {"div", complex_div},
        {"unm", complex_unm},
        {"new", complex_new},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(funcs) - 1);
    set_funcs(L, -1, funcs);
    lua_createtable(L, 0, 2);
    set_func(L, -1, LSET, l_setter);
    set_func(L, -1, LNEW, complex_new);
    lua_setmetatable(L, -2);

    const SFunc metas[] = {
        {LPRI, complex_tostring},
        {LNEW, complex_new},
        {LGET, complex_get},
        {LSET, complex_set},
        {LADD, complex_add},
        {LSUB, complex_sub},
        {LMUL, complex_mul},
        {LDIV, complex_div},
        {LUNM, complex_unm},
        {NULL, NULL},
    };
    lua_createtable(L, 0, Larray(metas));
    set_name(L, -1, LNAME, "complex");
    set_funcs(L, -1, metas);

    lua_rawsetp(L, LUA_REGISTRYINDEX, COMPLEX_META_); // NOLINT(performance-no-int-to-ptr)
    lua_rawsetp(L, LUA_REGISTRYINDEX, COMPLEX_FUNC_); // NOLINT(performance-no-int-to-ptr)

    return complex_func_(L);
}

int complex_func_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, COMPLEX_FUNC_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}

int complex_meta_(lua_State *L)
{
    lua_rawgetp(L, LUA_REGISTRYINDEX, COMPLEX_META_); // NOLINT(performance-no-int-to-ptr)
    return 1;
}
