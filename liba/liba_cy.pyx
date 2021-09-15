cimport cython
from libc.stdint cimport *
from libc.stdlib cimport *
from libc.string cimport *
from libc.stdio cimport *

cdef extern from "liba.h":
    ctypedef struct a_polytrack3_t:
        float t[2]
        float q[2]
        float v[2]
        float k[4]
    void a_polytrack3_init(a_polytrack3_t *p, float source[3], float target[3])
    float a_polytrack3_pos(const a_polytrack3_t *p, float t)
    float a_polytrack3_vec(const a_polytrack3_t *p, float t)
    float a_polytrack3_acc(const a_polytrack3_t *p, float t)
    void a_polytrack3_all(const a_polytrack3_t *p, float out[3], float t)

    ctypedef struct a_polytrack5_t:
        float t[2]
        float q[2]
        float v[2]
        float a[2]
        float k[6]
    void a_polytrack5_init(a_polytrack5_t *p, float source[4], float target[4])
    float a_polytrack5_pos(const a_polytrack5_t *p, float t)
    float a_polytrack5_vec(const a_polytrack5_t *p, float t)
    float a_polytrack5_acc(const a_polytrack5_t *p, float t)
    void a_polytrack5_all(const a_polytrack5_t *p, float out[3], float t)

    ctypedef struct a_polytrack7_t:
        float t[2]
        float q[2]
        float v[2]
        float a[2]
        float j[2]
        float k[8]
    void a_polytrack7_init(a_polytrack7_t *p, float source[5], float target[5])
    float a_polytrack7_pos(const a_polytrack7_t *p, float t)
    float a_polytrack7_vec(const a_polytrack7_t *p, float t)
    float a_polytrack7_acc(const a_polytrack7_t *p, float t)
    float a_polytrack7_jer(const a_polytrack7_t *p, float t)
    void a_polytrack7_all(const a_polytrack7_t *p, float out[4], float t)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_polytrack3():
    cdef a_polytrack3_t p[1]
    cdef float source[3]
    cdef float target[3]

    def __cinit__(self, source, target):
        self.source[0] = source[0]
        self.source[1] = source[1]
        self.source[2] = source[2]
        self.target[0] = target[0]
        self.target[1] = target[1]
        self.target[2] = target[2]
        a_polytrack3_init(self.p, self.source, self.target)

    cpdef float pos(self, float t):
        return a_polytrack3_pos(self.p, t)

    cpdef float vec(self, float t):
        return a_polytrack3_vec(self.p, t)

    cpdef float acc(self, float t):
        return a_polytrack3_acc(self.p, t)

    cpdef tuple all(self, float t):
        cdef float out[3]
        a_polytrack3_all(self.p, out, t)
        return (out[0], out[1], out[2])

    cpdef label(self):
        fmt = '{:+g}{}'
        p_label = 'p='
        if self.p.k[0]:
            p_label += '{:g}'.format(self.p.k[0])
        if self.p.k[1]:
            p_label += fmt.format(self.p.k[1], 't')
        if self.p.k[2]:
            p_label += fmt.format(self.p.k[2], 't^2')
        if self.p.k[3]:
            p_label += fmt.format(self.p.k[3], 't^3')
        v_label = 'v='
        if self.p.k[1]:
            v_label += '{:g}'.format(self.p.k[1])
        if self.p.k[2]:
            v_label += fmt.format(self.p.k[2] * 2, 't')
        if self.p.k[3]:
            v_label += fmt.format(self.p.k[3] * 3, 't^2')
        a_label = 'a='
        if self.p.k[2]:
            a_label += '{:g}'.format(self.p.k[2] * 2)
        if self.p.k[3]:
            a_label += fmt.format(self.p.k[3] * 6, 't')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
        )

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_polytrack5():
    cdef a_polytrack5_t p[1]
    cdef float source[4]
    cdef float target[4]
    cdef float out[3]

    def __cinit__(self, source, target):
        self.source[0] = source[0]
        self.source[1] = source[1]
        self.source[2] = source[2]
        self.source[3] = source[3]
        self.target[0] = target[0]
        self.target[1] = target[1]
        self.target[2] = target[2]
        self.target[3] = target[3]
        a_polytrack5_init(self.p, self.source, self.target)

    cpdef float pos(self, float t):
        return a_polytrack5_pos(self.p, t)

    cpdef float vec(self, float t):
        return a_polytrack5_vec(self.p, t)

    cpdef float acc(self, float t):
        return a_polytrack5_acc(self.p, t)

    cpdef tuple all(self, float t):
        cdef float out[3]
        a_polytrack5_all(self.p, out, t)
        return (out[0], out[1], out[2])

    cpdef label(self):
        fmt = '{:+g}{}'
        p_label = 'p='
        if self.p.k[0]:
            p_label += '{:g}'.format(self.p.k[0])
        if self.p.k[1]:
            p_label += fmt.format(self.p.k[1], 't')
        if self.p.k[2]:
            p_label += fmt.format(self.p.k[2], 't^2')
        if self.p.k[3]:
            p_label += fmt.format(self.p.k[3], 't^3')
        if self.p.k[4]:
            p_label += fmt.format(self.p.k[4], 't^4')
        if self.p.k[5]:
            p_label += fmt.format(self.p.k[5], 't^5')
        v_label = 'v='
        if self.p.k[1]:
            v_label += '{:g}'.format(self.p.k[1])
        if self.p.k[2]:
            v_label += fmt.format(self.p.k[2] * 2, 't')
        if self.p.k[3]:
            v_label += fmt.format(self.p.k[3] * 3, 't^2')
        if self.p.k[4]:
            v_label += fmt.format(self.p.k[4] * 4, 't^3')
        if self.p.k[5]:
            v_label += fmt.format(self.p.k[5] * 5, 't^4')
        a_label = 'a='
        if self.p.k[2]:
            a_label += '{:g}'.format(self.p.k[2] * 2)
        if self.p.k[3]:
            a_label += fmt.format(self.p.k[3] * 6, 't')
        if self.p.k[4]:
            a_label += fmt.format(self.p.k[4] * 12, 't^2')
        if self.p.k[5]:
            a_label += fmt.format(self.p.k[3] * 20, 't^3')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
        )

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_polytrack7():
    cdef a_polytrack7_t p[1]
    cdef float source[5]
    cdef float target[5]
    cdef float out[4]

    def __cinit__(self, source, target):
        self.source[0] = source[0]
        self.source[1] = source[1]
        self.source[2] = source[2]
        self.source[3] = source[3]
        self.source[4] = source[4]
        self.target[0] = target[0]
        self.target[1] = target[1]
        self.target[2] = target[2]
        self.target[3] = target[3]
        self.target[4] = target[4]
        a_polytrack7_init(self.p, self.source, self.target)

    cpdef float pos(self, float t):
        return a_polytrack7_pos(self.p, t)

    cpdef float vec(self, float t):
        return a_polytrack7_vec(self.p, t)

    cpdef float acc(self, float t):
        return a_polytrack7_acc(self.p, t)

    cpdef float jer(self, float t):
        return a_polytrack7_jer(self.p, t)

    cpdef tuple all(self, float t):
        cdef float out[4]
        a_polytrack7_all(self.p, out, t)
        return (out[0], out[1], out[2], out[3])

    cpdef label(self):
        fmt = '{:+g}{}'
        p_label = 'p='
        if self.p.k[0]:
            p_label += '{:g}'.format(self.p.k[0])
        if self.p.k[1]:
            p_label += fmt.format(self.p.k[1], 't')
        if self.p.k[2]:
            p_label += fmt.format(self.p.k[2], 't^2')
        if self.p.k[3]:
            p_label += fmt.format(self.p.k[3], 't^3')
        if self.p.k[4]:
            p_label += fmt.format(self.p.k[4], 't^4')
        if self.p.k[5]:
            p_label += fmt.format(self.p.k[5], 't^5')
        if self.p.k[6]:
            p_label += fmt.format(self.p.k[6], 't^6')
        if self.p.k[7]:
            p_label += fmt.format(self.p.k[7], 't^7')
        v_label = 'v='
        if self.p.k[1]:
            v_label += '{:g}'.format(self.p.k[1])
        if self.p.k[2]:
            v_label += fmt.format(self.p.k[2] * 2, 't')
        if self.p.k[3]:
            v_label += fmt.format(self.p.k[3] * 3, 't^2')
        if self.p.k[4]:
            v_label += fmt.format(self.p.k[4] * 4, 't^3')
        if self.p.k[5]:
            v_label += fmt.format(self.p.k[5] * 5, 't^4')
        if self.p.k[6]:
            v_label += fmt.format(self.p.k[6] * 6, 't^5')
        if self.p.k[7]:
            v_label += fmt.format(self.p.k[7] * 7, 't^6')
        a_label = 'a='
        if self.p.k[2]:
            a_label += '{:g}'.format(self.p.k[2] * 2)
        if self.p.k[3]:
            a_label += fmt.format(self.p.k[3] * 6, 't')
        if self.p.k[4]:
            a_label += fmt.format(self.p.k[4] * 12, 't^2')
        if self.p.k[5]:
            a_label += fmt.format(self.p.k[3] * 20, 't^3')
        if self.p.k[6]:
            a_label += fmt.format(self.p.k[6] * 30, 't^4')
        if self.p.k[7]:
            a_label += fmt.format(self.p.k[7] * 42, 't^5')
        j_label = 'j='
        if self.p.k[3]:
            j_label += '{:g}'.format(self.p.k[3] * 6)
        if self.p.k[4]:
            j_label += fmt.format(self.p.k[4] * 12, 't')
        if self.p.k[5]:
            j_label += fmt.format(self.p.k[3] * 60, 't^2')
        if self.p.k[6]:
            j_label += fmt.format(self.p.k[6] * 120, 't^3')
        if self.p.k[7]:
            j_label += fmt.format(self.p.k[7] * 210, 't^4')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
            j_label.replace('=+', '='),
        )
