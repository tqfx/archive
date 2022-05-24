'''
 @file config.pxi
 @brief cython for algorithm library configuration
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from config cimport *

def version() -> str:
    return a_version().decode()
