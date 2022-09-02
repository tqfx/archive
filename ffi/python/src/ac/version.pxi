from ac.version cimport *

def version() -> str:
    '''algorithm library version'''
    return a_version().decode()

def version_major() -> int:
    '''algorithm library version major'''
    return a_version_major()

def version_minor() -> int:
    '''algorithm library version minor'''
    return a_version_minor()

def version_patch() -> int:
    '''algorithm library version patch'''
    return a_version_patch()
