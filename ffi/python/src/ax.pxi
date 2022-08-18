cimport cython

from ax_version cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def version() -> str:
    '''algorithm library version'''
    return a_version().decode()

@cython.wraparound(False)
@cython.boundscheck(False)
def version_major() -> int:
    '''algorithm library version major'''
    return a_version_major()

@cython.wraparound(False)
@cython.boundscheck(False)
def version_minor() -> int:
    '''algorithm library version minor'''
    return a_version_minor()

@cython.wraparound(False)
@cython.boundscheck(False)
def version_patch() -> int:
    '''algorithm library version patch'''
    return a_version_patch()
