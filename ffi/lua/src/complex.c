/***
 complex number
 @module liba.complex
*/

#include "complex.h"

#if defined(__GNUC__) || defined(__clang__)
#pragma GCC diagnostic ignored "-Waggregate-return"
#endif /* __GNUC__ || __clang__ */

static int complex_isok(lua_State *L, int idx)
{
    int ok = 0;
    if (lua_getmetatable(L, idx))
    {
        complex_meta_(L);
        ok = lua_rawequal(L, -1, -2);
        lua_pop(L, 2);
    }
    return ok;
}

static a_complex_s complex_from_lua(lua_State *L, int idx)
{
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    switch (lua_type(L, idx))
    {
    case LUA_TUSERDATA:
        if (complex_isok(L, idx))
        {
            z = *(a_complex_s *)lua_touserdata(L, idx);
        }
        break;
    case LUA_TSTRING:
    case LUA_TNUMBER:
        a_complex_real(z) = (a_real_t)lua_tonumber(L, idx);
        break;
    default:
        break;
    }
    return z;
}

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
        lua_pushfstring(L, "(%f,%f)",
                        (lua_Number)a_complex_real(*ctx),
                        (lua_Number)a_complex_imag(*ctx));
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
    for (int e = lua_type(L, 1);
         e == LUA_TTABLE || e == LUA_TUSERDATA;
         e = lua_type(L, 1))
    {
        lua_remove(L, 1);
    }
    a_complex_s z = A_COMPLEX_C(0.0, 0.0);
    int top = lua_gettop(L);
    if (top >= 2)
    {
        a_complex_imag(z) = (a_real_t)lua_tonumber(L, 2);
    }
    if (top >= 1)
    {
        a_complex_real(z) = (a_real_t)lua_tonumber(L, 1);
    }
    *complex_new_(L) = z;
    return 1;
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
    for (int e = lua_type(L, 1);
         e == LUA_TTABLE || e == LUA_TUSERDATA;
         e = lua_type(L, 1))
    {
        lua_remove(L, 1);
    }
    a_real_t theta = A_REAL_C(0.0);
    a_real_t r = A_REAL_C(0.0);
    int top = lua_gettop(L);
    if (top >= 2)
    {
        theta = (a_real_t)lua_tonumber(L, 2);
    }
    if (top >= 1)
    {
        r = (a_real_t)lua_tonumber(L, 1);
    }
    *complex_new_(L) = a_complex_polar(r, theta);
    return 1;
}

#undef FUNC
#define FUNC(func)                                  \
    static int complex_##func(lua_State *L)         \
    {                                               \
        while (lua_type(L, 1) == LUA_TTABLE)        \
        {                                           \
            lua_remove(L, 1);                       \
        }                                           \
        if (lua_gettop(L) >= 1)                     \
        {                                           \
            a_complex_s z = complex_from_lua(L, 1); \
            a_real_t x = a_complex_##func(z);       \
            lua_pushnumber(L, (lua_Number)x);       \
            return 1;                               \
        }                                           \
        return 0;                                   \
    }
/***
 computes the natural logarithm of magnitude of a complex number
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function logabs
*/
FUNC(logabs)
/***
 computes the squared magnitude of a complex number
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function abs2
*/
FUNC(abs2)
/***
 computes the magnitude of a complex number
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function abs
*/
FUNC(abs)
/***
 computes the phase angle of a complex number
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function arg
*/
FUNC(arg)
#undef FUNC
#define FUNC(func)                                  \
    static int complex_##func(lua_State *L)         \
    {                                               \
        while (lua_type(L, 1) == LUA_TTABLE)        \
        {                                           \
            lua_remove(L, 1);                       \
        }                                           \
        if (lua_gettop(L) >= 1)                     \
        {                                           \
            a_complex_s z = complex_from_lua(L, 1); \
            *complex_new_(L) = a_complex_##func(z); \
            return 1;                               \
        }                                           \
        return 0;                                   \
    }
/***
 computes the complex conjugate
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function conj
*/
FUNC(conj)
/***
 computes the complex negative
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function unm
*/
FUNC(neg)
/***
 inverse of a complex number
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function inv
*/
FUNC(inv)
#undef FUNC
#define FUNC(func)                                     \
    static int complex_##func(lua_State *L)            \
    {                                                  \
        while (lua_type(L, 1) == LUA_TTABLE)           \
        {                                              \
            lua_remove(L, 1);                          \
        }                                              \
        if (lua_gettop(L) >= 2)                        \
        {                                              \
            a_complex_s x = complex_from_lua(L, 1);    \
            a_complex_s y = complex_from_lua(L, 2);    \
            *complex_new_(L) = a_complex_##func(x, y); \
            return 1;                                  \
        }                                              \
        return 0;                                      \
    }
/***
 addition of complex numbers
 @tparam complex x complex number userdata
 @tparam complex y complex number userdata
 @treturn complex complex number userdata
 @function add
*/
FUNC(add)
/***
 subtraction of complex numbers
 @tparam complex x complex number userdata
 @tparam complex y complex number userdata
 @treturn complex complex number userdata
 @function sub
*/
FUNC(sub)
/***
 multiplication of complex numbers
 @tparam complex x complex number userdata
 @tparam complex y complex number userdata
 @treturn complex complex number userdata
 @function mul
*/
FUNC(mul)
/***
 division of complex numbers
 @tparam complex x complex number userdata
 @tparam complex y complex number userdata
 @treturn complex complex number userdata
 @function div
*/
FUNC(div)
/***
 complex number z raised to complex power a
 @tparam complex z complex number userdata
 @tparam complex a complex number userdata
 @treturn complex complex number userdata
 @function pow
*/
FUNC(pow)
/***
 computes the complex base-b logarithm
 @tparam complex z complex number userdata
 @tparam complex b complex number userdata
 @treturn complex complex number userdata
 @function logb
*/
FUNC(logb)
#undef FUNC
#define FUNC(func)                                  \
    static int complex_##func(lua_State *L)         \
    {                                               \
        while (lua_type(L, 1) == LUA_TTABLE)        \
        {                                           \
            lua_remove(L, 1);                       \
        }                                           \
        if (lua_gettop(L) >= 1)                     \
        {                                           \
            a_complex_s z = complex_from_lua(L, 1); \
            *complex_new_(L) = a_complex_##func(z); \
            return 1;                               \
        }                                           \
        return 0;                                   \
    }
/***
 computes the complex base-e exponential
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function exp
*/
FUNC(exp)
/***
 computes the complex natural logarithm
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function log
*/
FUNC(log)
/***
 computes the complex square root
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function sqrt
*/
FUNC(sqrt)
/***
 computes the complex base-2 logarithm
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function log2
*/
FUNC(log2)
/***
 computes the complex base-10 logarithm
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function log10
*/
FUNC(log10)
/***
 computes the complex sine
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function sin
*/
FUNC(sin)
/***
 computes the complex cosine
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function cos
*/
FUNC(cos)
/***
 computes the complex tangent
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function tan
*/
FUNC(tan)
/***
 computes the complex secant
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function sec
*/
FUNC(sec)
/***
 computes the complex cosecant
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function csc
*/
FUNC(csc)
/***
 computes the complex cotangent
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function cot
*/
FUNC(cot)
/***
 computes the complex arc sine
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function asin
*/
FUNC(asin)
/***
 computes the complex arc cosine
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function acos
*/
FUNC(acos)
/***
 computes the complex arc tangent
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function atan
*/
FUNC(atan)
/***
 computes the complex arc secant
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function asec
*/
FUNC(asec)
/***
 computes the complex arc cosecant
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function acsc
*/
FUNC(acsc)
/***
 computes the complex arc cotangent
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function acot
*/
FUNC(acot)
/***
 computes the complex hyperbolic sine
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function sinh
*/
FUNC(sinh)
/***
 computes the complex hyperbolic cosine
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function cosh
*/
FUNC(cosh)
/***
 computes the complex hyperbolic tangent
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function tanh
*/
FUNC(tanh)
/***
 computes the complex hyperbolic secant
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function sech
*/
FUNC(sech)
/***
 computes the complex hyperbolic cosecant
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function csch
*/
FUNC(csch)
/***
 computes the complex hyperbolic cotangent
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function coth
*/
FUNC(coth)
/***
 computes the complex arc hyperbolic sine
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function asinh
*/
FUNC(asinh)
/***
 computes the complex arc hyperbolic cosine
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function acosh
*/
FUNC(acosh)
/***
 computes the complex arc hyperbolic tangent
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function atanh
*/
FUNC(atanh)
/***
 computes the complex arc hyperbolic secant
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function asech
*/
FUNC(asech)
/***
 computes the complex arc hyperbolic cosecant
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function acsch
*/
FUNC(acsch)
/***
 computes the complex arc hyperbolic cotangent
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function acoth
*/
FUNC(acoth)
#undef FUNC

static int complex_set(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0F6133A2: // real
        a_complex_real(*ctx) = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x0E2E9172: // imag
        a_complex_imag(*ctx) = (a_real_t)luaL_checknumber(L, 3);
        break;
    case 0x90705068: // __unm
    case 0x906B0E8D: // __add
    case 0x906FCDE0: // __sub
    case 0x906E3BB4: // __mul
    case 0x906BDA49: // __div
    case 0x906F01C8: // __pow
    case 0x906DF07D: // __len
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

static int complex_get(lua_State *L)
{
    a_complex_s *ctx = (a_complex_s *)lua_touserdata(L, 1);
    const char *field = lua_tostring(L, 2);
    a_u32_t hash = (a_u32_t)a_hash_bkdr(field, 0);
    switch (hash)
    {
    case 0x0F6133A2: // real
        lua_pushnumber(L, (lua_Number)a_complex_real(*ctx));
        break;
    case 0x0E2E9172: // imag
        lua_pushnumber(L, (lua_Number)a_complex_imag(*ctx));
        break;
    case 0x00000072: // r
        lua_pushnumber(L, (lua_Number)a_complex_abs(*ctx));
        break;
    case 0x0240D1F6: // theta
        lua_pushnumber(L, (lua_Number)a_complex_arg(*ctx));
        break;
    case 0xC628B402: // logabs
        lua_pushcfunction(L, complex_logabs);
        break;
    case 0xBCFBE386: // polar
        lua_pushcfunction(L, complex_polar);
        break;
    case 0x0D614C8C: // conj
        lua_pushcfunction(L, complex_conj);
        break;
    case 0x0D194C38: // abs2
        lua_pushcfunction(L, complex_abs2);
        break;
    case 0x00199902: // abs
        lua_pushcfunction(L, complex_abs);
        break;
    case 0x0019A126: // arg
        lua_pushcfunction(L, complex_arg);
        break;
    case 0x001EDBD4: // unm
        lua_pushcfunction(L, complex_neg);
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
    case 0x001BB771: // inv
        lua_pushcfunction(L, complex_inv);
        break;
    case 0x001D8D34: // pow
        lua_pushcfunction(L, complex_pow);
        break;
    case 0x001AB065: // exp
        lua_pushcfunction(L, complex_exp);
        break;
    case 0x001C8100: // log
        lua_pushcfunction(L, complex_log);
        break;
    case 0x0E960332: // log2
        lua_pushcfunction(L, complex_log2);
        break;
    case 0x76C3A243: // log10
        lua_pushcfunction(L, complex_log10);
        break;
    case 0x0E960362: // logb
        lua_pushcfunction(L, complex_logb);
        break;
    case 0x0F86AE64: // sqrt
        lua_pushcfunction(L, complex_sqrt);
        break;
    case 0x001E5334: // sin
        lua_pushcfunction(L, complex_sin);
        break;
    case 0x001A25BB: // cos
        lua_pushcfunction(L, complex_cos);
        break;
    case 0x001E9225: // tan
        lua_pushcfunction(L, complex_tan);
        break;
    case 0x001E511D: // sec
        lua_pushcfunction(L, complex_sec);
        break;
    case 0x001A27B7: // csc
        lua_pushcfunction(L, complex_csc);
        break;
    case 0x001A25BC: // cot
        lua_pushcfunction(L, complex_cot);
        break;
    case 0x0D1DBAEF: // asin
        lua_pushcfunction(L, complex_asin);
        break;
    case 0x0D198D76: // acos
        lua_pushcfunction(L, complex_acos);
        break;
    case 0x0D1DF9E0: // atan
        lua_pushcfunction(L, complex_atan);
        break;
    case 0x0D1DB8D8: // asec
        lua_pushcfunction(L, complex_asec);
        break;
    case 0x0D198F72: // acsc
        lua_pushcfunction(L, complex_acsc);
        break;
    case 0x0D198D77: // acot
        lua_pushcfunction(L, complex_acot);
        break;
    case 0x0F849404: // sinh
        lua_pushcfunction(L, complex_sinh);
        break;
    case 0x0D614F19: // cosh
        lua_pushcfunction(L, complex_cosh);
        break;
    case 0x0FA4C957: // tanh
        lua_pushcfunction(L, complex_tanh);
        break;
    case 0x0F83823F: // sech
        lua_pushcfunction(L, complex_sech);
        break;
    case 0x0D62530D: // csch
        lua_pushcfunction(L, complex_csch);
        break;
    case 0x0D614F9C: // coth
        lua_pushcfunction(L, complex_coth);
        break;
    case 0xB636A8B5: // asinh
        lua_pushcfunction(L, complex_asinh);
        break;
    case 0xB41363CA: // acosh
        lua_pushcfunction(L, complex_acosh);
        break;
    case 0xB656DE08: // atanh
        lua_pushcfunction(L, complex_atanh);
        break;
    case 0xB63596F0: // asech
        lua_pushcfunction(L, complex_asech);
        break;
    case 0xB41467BE: // acsch
        lua_pushcfunction(L, complex_acsch);
        break;
    case 0xB413644D: // acoth
        lua_pushcfunction(L, complex_acoth);
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
        {"new", complex_new},
        {"polar", complex_polar},
        {"logabs", complex_logabs},
        {"conj", complex_conj},
        {"abs2", complex_abs2},
        {"abs", complex_abs},
        {"arg", complex_arg},
        {"unm", complex_neg},
        {"add", complex_add},
        {"sub", complex_sub},
        {"mul", complex_mul},
        {"div", complex_div},
        {"inv", complex_inv},
        {"pow", complex_pow},
        {"exp", complex_exp},
        {"log", complex_log},
        {"log2", complex_log2},
        {"log10", complex_log10},
        {"logb", complex_logb},
        {"sqrt", complex_sqrt},
        {"sin", complex_sin},
        {"cos", complex_cos},
        {"tan", complex_tan},
        {"sec", complex_sec},
        {"csc", complex_csc},
        {"cot", complex_cot},
        {"asin", complex_asin},
        {"acos", complex_acos},
        {"atan", complex_atan},
        {"asec", complex_asec},
        {"acsc", complex_acsc},
        {"acot", complex_acot},
        {"sinh", complex_sinh},
        {"cosh", complex_cosh},
        {"tanh", complex_tanh},
        {"sech", complex_sech},
        {"csch", complex_csch},
        {"coth", complex_coth},
        {"asinh", complex_asinh},
        {"acosh", complex_acosh},
        {"atanh", complex_atanh},
        {"asech", complex_asech},
        {"acsch", complex_acsch},
        {"acoth", complex_acoth},
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
        {LUNM, complex_neg},
        {LADD, complex_add},
        {LSUB, complex_sub},
        {LMUL, complex_mul},
        {LDIV, complex_div},
        {LPOW, complex_pow},
        {LLEN, complex_abs},
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
