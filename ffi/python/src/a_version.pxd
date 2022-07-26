from a cimport *

cdef extern from "a/version.h":
    const a_char_t *a_version"a_version"()
    a_uint_t a_version_major"a_version_major"()
    a_uint_t a_version_minor"a_version_minor"()
    a_uint_t a_version_patch"a_version_patch"()
