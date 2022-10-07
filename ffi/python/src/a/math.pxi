from a.math cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def inv_sqrt(x):
    '''fast inverse square-root'''
    if iterable(x):
        y = array('d', x)
        for i, it in enumerate(x):
            y[i] = a_inv_sqrt(it)
        return y
    return a_inv_sqrt(x)
