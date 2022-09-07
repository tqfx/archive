from cpython.array cimport *
from cpython cimport *

cdef bint iterable(object obj):
    return PyObject_HasAttrString(obj, "__contains__")

cimport cython
include "ac/version.pxi"
include "ac/math.pxi"
include "ac/pid.pxi"
include "ac/poly.pxi"
include "ac/polytrack.pxi"
