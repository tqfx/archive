from a.poly cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def poly(x, *a):
    b, n = array('d', a), len(a)
    cdef a_real_t *p = b.data.as_doubles
    if iterable(x):
        y = array('d', x)
        for i, it in enumerate(x):
            y[i] = a_poly_c(p, n, it)
        return y
    return a_poly_c(p, n, x)
