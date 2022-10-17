/***
 complex number
 @classmod complex
*/

/***
 complex number
 @field real real part of complex number
 @field imag imaginary part of complex number
 @table complex
*/

#ifndef FFI_COMPLEX_H
#define FFI_COMPLEX_H

#include "lua.h"
#include "a/complex.h"

#define COMPLEX_FUNC_ (void *)(intptr_t)complex_func_ // NOLINT(performance-no-int-to-ptr)
#define COMPLEX_META_ (void *)(intptr_t)complex_meta_ // NOLINT(performance-no-int-to-ptr)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int complex_func_(lua_State *L);
int complex_meta_(lua_State *L);

/***
 constructor for complex number from rectangular Cartesian components
 @tparam number real real part of complex number
 @tparam number imag imaginary part of complex number
 @treturn complex complex number userdata
 @function new
*/
int complex_new(lua_State *L);

/***
 constructor for complex number from polar form
 @tparam number r a distance from a reference point
 @tparam number theta an angle from a reference direction
 @treturn complex complex number userdata
 @function polar
*/
int complex_polar(lua_State *L);

/***
 complex conjugate value
 @treturn complex complex number userdata
 @function conj
*/
int complex_conj(lua_State *L);

/***
 - complex unary – operator
 @treturn complex complex number userdata
 @function unm
*/
int complex_unm(lua_State *L);

/***
 + complex addition operator
 @tparam complex obj complex number userdata
 @treturn complex complex number userdata
 @function add
*/
int complex_add(lua_State *L);

/***
 - complex subtraction operator
 @tparam complex obj complex number userdata
 @treturn complex complex number userdata
 @function sub
*/
int complex_sub(lua_State *L);

/***
 * complex multiplication operator
 @tparam complex obj complex number userdata
 @treturn complex complex number userdata
 @function mul
*/
int complex_mul(lua_State *L);

/***
 / complex division operator
 @tparam complex obj complex number userdata
 @treturn complex complex number userdata
 @function div
*/
int complex_div(lua_State *L);

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FFI_COMPLEX_H */
