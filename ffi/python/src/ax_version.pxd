from ax cimport *

cdef extern from "a/version.hpp" namespace "a":
    const char_t *a_version"a::version"()
    uint_t a_version_major"a::version_major"()
    uint_t a_version_minor"a::version_minor"()
    uint_t a_version_patch"a::version_patch"()
