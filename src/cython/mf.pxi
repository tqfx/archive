'''
 @file mf.pxi
 @brief cython for membership function
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from mf cimport *

A_MF_NONE  = C_MF_NONE
A_MF_GAUSS = C_MF_GAUSS
A_MF_GBELL = C_MF_GBELL
A_MF_SIG   = C_MF_SIG
A_MF_TRAP  = C_MF_TRAP
A_MF_TRI   = C_MF_TRI
A_MF_Z     = C_MF_Z

@cython.wraparound(False)
@cython.boundscheck(False)
def a_mf_gauss(x, sigma: float, c: float):
    if not isinstance(x, typing.Iterable):
        return c_mf_gauss(x, sigma, c)
    y = []
    for i in x:
        y.append(c_mf_gauss(i, sigma, c))
    return y
@cython.wraparound(False)
@cython.boundscheck(False)
def a_mf_gbell(x, a: float, b: float, c: float):
    if not isinstance(x, typing.Iterable):
        return c_mf_gbell(x, a, b, c)
    y = []
    for i in x:
        y.append(c_mf_gbell(i, a, b, c))
    return y
@cython.wraparound(False)
@cython.boundscheck(False)
def a_mf_sig(x, a: float, c: float):
    if not isinstance(x, typing.Iterable):
        return c_mf_sig(x, a, c)
    y = []
    for i in x:
        y.append(c_mf_sig(i, a, c))
    return y
@cython.wraparound(False)
@cython.boundscheck(False)
def a_mf_trap(x, a: float, b: float, c: float, d: float):
    if not isinstance(x, typing.Iterable):
        return c_mf_trap(x, a, b, c, d)
    y = []
    for i in x:
        y.append(c_mf_trap(i, a, b, c, d))
    return y
@cython.wraparound(False)
@cython.boundscheck(False)
def a_mf_tri(x, a: float, b: float, c: float):
    if not isinstance(x, typing.Iterable):
        return c_mf_tri(x, a, b, c)
    y = []
    for i in x:
        y.append(c_mf_tri(i, a, b, c))
    return y
@cython.wraparound(False)
@cython.boundscheck(False)
def a_mf_z(x, a: float, b: float):
    if not isinstance(x, typing.Iterable):
        return c_mf_z(x, a, b)
    y = []
    for i in x:
        y.append(c_mf_z(i, a, b))
    return y
@cython.wraparound(False)
@cython.boundscheck(False)
def a_mf(t: c_mf_e, x, p):
    cdef array.array a = array.array('d', p)
    if not isinstance(x, typing.Iterable):
        return c_mf(t, x, a.data.as_doubles)
    y = []
    for i in x:
        y.append(c_mf(t, i, a.data.as_doubles))
    return y
