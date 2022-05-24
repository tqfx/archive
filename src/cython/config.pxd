'''
 @file config.pxd
 @brief cython for algorithm library configuration
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

cdef extern from "a/def.h":
    const char *a_version "a_version" ()
