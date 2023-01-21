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

#include "a.h"
#include "a/complex.h"

#define L_COMPLEX_FUNC_ (void *)(intptr_t)l_complex_func_ // NOLINT(performance-no-int-to-ptr)
#define L_COMPLEX_META_ (void *)(intptr_t)l_complex_meta_ // NOLINT(performance-no-int-to-ptr)

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

int l_complex_func_(lua_State *L);
int l_complex_meta_(lua_State *L);

/***
 constructor for complex number from rectangular Cartesian components
 @tparam number real real part of complex number
 @tparam number imag imaginary part of complex number
 @treturn complex complex number userdata
 @function new
*/
int l_complex_new(lua_State *L);

/***
 constructor for complex number from polar form
 @tparam number r a distance from a reference point
 @tparam number theta an angle from a reference direction
 @treturn complex complex number userdata
 @function polar
*/
int l_complex_polar(lua_State *L);

/***
 computes the natural logarithm of magnitude of a complex number
 @treturn complex complex number userdata
 @function logabs
*/

/***
 computes the squared magnitude of a complex number
 @treturn complex complex number userdata
 @function abs2
*/

/***
 computes the magnitude of a complex number
 @treturn complex complex number userdata
 @function abs
*/

/***
 computes the phase angle of a complex number
 @treturn complex complex number userdata
 @function arg
*/

/***
 computes the complex conjugate
 @treturn complex complex number userdata
 @function conj
*/

/***
 computes the complex negative
 @treturn complex complex number userdata
 @function unm
*/

/***
 inverse of a complex number
 @treturn complex complex number userdata
 @function inv
*/

/***
 addition of complex numbers
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function add
*/

/***
 subtraction of complex numbers
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function sub
*/

/***
 multiplication of complex numbers
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function mul
*/

/***
 division of complex numbers
 @tparam complex z complex number userdata
 @treturn complex complex number userdata
 @function div
*/

/***
 complex number z raised to complex power a
 @tparam complex a complex number userdata
 @treturn complex complex number userdata
 @function pow
*/

/***
 computes the complex base-b logarithm
 @tparam complex b complex number userdata
 @treturn complex complex number userdata
 @function logb
*/

/***
 computes the complex base-e exponential
 @treturn complex complex number userdata
 @function exp
*/

/***
 computes the complex natural logarithm
 @treturn complex complex number userdata
 @function log
*/

/***
 computes the complex square root
 @treturn complex complex number userdata
 @function sqrt
*/

/***
 computes the complex base-2 logarithm
 @treturn complex complex number userdata
 @function log2
*/

/***
 computes the complex base-10 logarithm
 @treturn complex complex number userdata
 @function log10
*/

/***
 computes the complex sine
 @treturn complex complex number userdata
 @function sin
*/

/***
 computes the complex cosine
 @treturn complex complex number userdata
 @function cos
*/

/***
 computes the complex tangent
 @treturn complex complex number userdata
 @function tan
*/

/***
 computes the complex secant
 @treturn complex complex number userdata
 @function sec
*/

/***
 computes the complex cosecant
 @treturn complex complex number userdata
 @function csc
*/

/***
 computes the complex cotangent
 @treturn complex complex number userdata
 @function cot
*/

/***
 computes the complex arc sine
 @treturn complex complex number userdata
 @function asin
*/

/***
 computes the complex arc cosine
 @treturn complex complex number userdata
 @function acos
*/

/***
 computes the complex arc tangent
 @treturn complex complex number userdata
 @function atan
*/

/***
 computes the complex arc secant
 @treturn complex complex number userdata
 @function asec
*/

/***
 computes the complex arc cosecant
 @treturn complex complex number userdata
 @function acsc
*/

/***
 computes the complex arc cotangent
 @treturn complex complex number userdata
 @function acot
*/

/***
 computes the complex hyperbolic sine
 @treturn complex complex number userdata
 @function sinh
*/

/***
 computes the complex hyperbolic cosine
 @treturn complex complex number userdata
 @function cosh
*/

/***
 computes the complex hyperbolic tangent
 @treturn complex complex number userdata
 @function tanh
*/

/***
 computes the complex hyperbolic secant
 @treturn complex complex number userdata
 @function sech
*/

/***
 computes the complex hyperbolic cosecant
 @treturn complex complex number userdata
 @function csch
*/

/***
 computes the complex hyperbolic cotangent
 @treturn complex complex number userdata
 @function coth
*/

/***
 computes the complex arc hyperbolic sine
 @treturn complex complex number userdata
 @function asinh
*/

/***
 computes the complex arc hyperbolic cosine
 @treturn complex complex number userdata
 @function acosh
*/

/***
 computes the complex arc hyperbolic tangent
 @treturn complex complex number userdata
 @function atanh
*/

/***
 computes the complex arc hyperbolic secant
 @treturn complex complex number userdata
 @function asech
*/

/***
 computes the complex arc hyperbolic cosecant
 @treturn complex complex number userdata
 @function acsch
*/

/***
 computes the complex arc hyperbolic cotangent
 @treturn complex complex number userdata
 @function acoth
*/

#if defined(__cplusplus)
} /* extern "C" */
#endif /* __cplusplus */

#endif /* FFI_COMPLEX_H */
