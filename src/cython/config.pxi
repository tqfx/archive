'''
 @file config.pxi
 @brief cython for algorithm library configuration
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

from config cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
def version() -> str:
    '''algorithm library version'''
    return a_version().decode()
