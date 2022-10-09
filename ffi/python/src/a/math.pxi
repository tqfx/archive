from a.math cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def sqrt_inv(x):
    '''fast inverse square-root'''
    if iterable(x):
        y = array('d', x)
        for i, it in enumerate(x):
            y[i] = a_sqrt_inv(it)
        return y
    return a_sqrt_inv(x)
