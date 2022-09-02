from ac.math cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def inv_sqrt(x: float) -> float:
    '''fast inverse square-root'''
    return a_inv_sqrt(x)
