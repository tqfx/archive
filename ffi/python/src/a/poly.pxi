from a.poly cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def poly(x, *a):
    d, n = array('d', a), len(a)
    cdef a_real_t *p = d.data.as_doubles
    if iterable(x):
        y = array('d', x)
        a_poly_xs(p, n, y.data.as_doubles, len(x), y.data.as_doubles)
        return y
    return a_poly_x(p, n, x)

@cython.wraparound(False)
@cython.boundscheck(False)
def polyr(x, *a):
    d, n = array('d', a), len(a)
    cdef a_real_t *p = d.data.as_doubles
    if iterable(x):
        y = array('d', x)
        a_poly_rs(p, n, y.data.as_doubles, len(x), y.data.as_doubles)
        return y
    return a_poly_r(p, n, x)
