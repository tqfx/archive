from cpython.array cimport *
from cpython cimport *

cdef bint iterable(object obj):
    return PyObject_HasAttrString(obj, "__contains__")

cimport cython
include "a/version.pxi"
include "a/math.pxi"
include "a/mf.pxi"
include "a/tf.pxi"
include "a/pid.pxi"
include "a/fpid.pxi"
include "a/poly.pxi"
include "a/polytrack.pxi"
