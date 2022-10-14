from a.poly cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_eval(x, *a):
    d, n = array('d', a), len(a)
    cdef a_real_t *p = d.data.as_doubles
    if iterable(x):
        y = array('d', x)
        a_poly_evaln(p, n, y.data.as_doubles, len(x), y.data.as_doubles)
        return y
    return a_poly_eval(p, n, x)

@cython.wraparound(False)
@cython.boundscheck(False)
def poly_evar(x, *a):
    d, n = array('d', a), len(a)
    cdef a_real_t *p = d.data.as_doubles
    if iterable(x):
        y = array('d', x)
        a_poly_evarn(p, n, y.data.as_doubles, len(x), y.data.as_doubles)
        return y
    return a_poly_evar(p, n, x)
