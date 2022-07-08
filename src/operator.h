/*!
 @file operator.h
 @brief algorithm library internal operators
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#ifndef __OPERATOR_H__
#define __OPERATOR_H__

// clang-format off

#define inc ++ //!< increment
#define dec -- //!< decrement

#define pos + //!< positive
#define neg - //!< negative

#ifndef __cplusplus

#define not   ! //!< logical NOT
#define compl ~ //!< bitwise NOT

#endif /* __cplusplus */

#define mul * //!< multiplication
#define div / //!< division
#define mod % //!< remainder

#define add + //!< addition
#define sub - //!< subtraction

#define lshift << //!< bitwise left shift
#define rshift >> //!< bitwise right shift

#define lt <  //!< less than
#define gt >  //!< greater than
#define le <= //!< less than or equal
#define ge >= //!< greater than or equal
#define eq == //!< equal
#define ne != //!< not equal

#ifndef __cplusplus

#define bitand & //!< bitwise AND
#define bitxor ^ //!< bitwise XOR (exclusive or)
#define bitor  | //!< bitwise OR (inclusive or)

#define and && //!< logical AND
#define or  || //!< logical OR

#endif /* __cplusplus */

#define add_eq += //!< in-place assignment by sum
#define sub_eq -= //!< in-place assignment by difference
#define mul_eq *= //!< in-place assignment by product
#define div_eq /= //!< in-place assignment by quotient
#define mod_eq %= //!< in-place assignment by remainder

#define shl_eq <<= //!< in-place assignment by bitwise left shift
#define shr_eq >>= //!< in-place assignment by bitwise right shift

#ifndef __cplusplus

#define and_eq &= //!< in-place assignment by bitwise AND
#define xor_eq ^= //!< in-place assignment by bitwise XOR (exclusive or)
#define or_eq  |= //!< in-place assignment by bitwise OR (inclusive or)

#endif /* __cplusplus */

// clang-format on

#endif /* __OPERATOR_H__ */
