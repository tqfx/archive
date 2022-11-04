from cpython.array cimport array
from cpython cimport *

include "a/__init__.pxi"
cdef array reals(object o = ()):
    IF A_REAL_BYTE == 8:
        return array('d', o)
    IF A_REAL_BYTE == 4:
        return array('f', o)
cdef bint iterable(object o):
    return PyObject_HasAttrString(o, "__contains__")

cimport cython
include "a/version.pxi"
include "a/math.pxi"
include "a/mf.pxi"
include "a/tf.pxi"
include "a/pid.pxi"
include "a/fpid.pxi"
include "a/poly.pxi"
include "a/polytrack.pxi"
