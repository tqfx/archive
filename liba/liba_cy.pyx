cimport cython
from libc.stdint cimport *
from libc.stdlib cimport *
from libc.string cimport *
from libc.stdio cimport *

cdef extern from "liba.h":
    ctypedef float float32_t
    ctypedef double float64_t

cdef extern from "a_lpf.h":
    ctypedef struct a_lpf_f64_t:
        float64_t o
        float64_t k
        float64_t t
    void a_lpf_f64_init(a_lpf_f64_t *ctx, float64_t k, float64_t t)
    float64_t a_lpf_f64(a_lpf_f64_t *ctx, float64_t x)
    void a_lpf_f64_reset(a_lpf_f64_t *ctx)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_lpf:
    cdef a_lpf_f64_t ctx[1]

    def __cinit__(self, float64_t k, float64_t t):
        a_lpf_f64_init(self.ctx, k, t)

    def reset(self):
        a_lpf_f64_reset(self.ctx)
        return self

    def lpf(self, x):
        for i in x:
            yield a_lpf_f64(self.ctx, i)

    cpdef float64_t _lpf(self, float64_t x):
        return a_lpf_f64(self.ctx, x)

cdef extern from "a_pid.h":
    ctypedef enum a_pid_mode_t:
        A_PID_POS
        A_PID_INC
    ctypedef struct a_pid_f64_t:
        a_pid_mode_t mode
        float64_t kp
        float64_t ki
        float64_t kd
        float64_t omax
        float64_t omin
        float64_t omaxi
        float64_t a[3]
        float64_t x[2]
        float64_t y
    void a_pid_f64_init(a_pid_f64_t *ctx, a_pid_mode_t mode, const float64_t kpid[3], const float64_t omin, const float64_t omax, const float64_t omaxi)
    void a_pid_f64_pos(a_pid_f64_t *ctx, const float64_t kpid[3], float64_t omin, float64_t omax, float64_t omaxi)
    void a_pid_f64_inc(a_pid_f64_t *ctx, const float64_t kpid[3], float64_t omin, float64_t omax)
    float64_t a_pid_f64(a_pid_f64_t *ctx, const float64_t ref, const float64_t set)
    void a_pid_f64_reset(a_pid_f64_t *ctx)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_pid:
    cdef a_pid_f64_t ctx[1]

    def __cinit__(self, a_pid_mode_t mode, float64_t kp, float64_t ki, float64_t kd, float64_t omin, float64_t omax, float64_t omaxi):
        cdef float64_t kpid[3]
        kpid[0] = kp
        kpid[1] = ki
        kpid[2] = kd
        a_pid_f64_init(self.ctx, mode, kpid, omin, omax, omaxi)

    def reset(self):
        a_pid_f64_reset(self.ctx)
        return self

    cpdef float64_t pid(self, float64_t ref, float64_t set):
        return a_pid_f64(self.ctx, ref, set)

cdef extern from "a_polytrack.h":
    ctypedef struct a_polytrack3_f64_t:
        float64_t t[2]
        float64_t q[2]
        float64_t v[2]
        float64_t k[4]
    void a_polytrack3_f64_init(a_polytrack3_f64_t *ctx, float64_t source[3], float64_t target[3])
    float64_t a_polytrack3_f64_pos(const a_polytrack3_f64_t *ctx, float64_t t)
    float64_t a_polytrack3_f64_vec(const a_polytrack3_f64_t *ctx, float64_t t)
    float64_t a_polytrack3_f64_acc(const a_polytrack3_f64_t *ctx, float64_t t)
    void a_polytrack3_f64_all(const a_polytrack3_f64_t *ctx, float64_t o[3], float64_t t)

    ctypedef struct a_polytrack5_f64_t:
        float64_t t[2]
        float64_t q[2]
        float64_t v[2]
        float64_t a[2]
        float64_t k[6]
    void a_polytrack5_f64_init(a_polytrack5_f64_t *ctx, float64_t source[4], float64_t target[4])
    float64_t a_polytrack5_f64_pos(const a_polytrack5_f64_t *ctx, float64_t t)
    float64_t a_polytrack5_f64_vec(const a_polytrack5_f64_t *ctx, float64_t t)
    float64_t a_polytrack5_f64_acc(const a_polytrack5_f64_t *ctx, float64_t t)
    void a_polytrack5_f64_all(const a_polytrack5_f64_t *ctx, float64_t o[3], float64_t t)

    ctypedef struct a_polytrack7_f64_t:
        float64_t t[2]
        float64_t q[2]
        float64_t v[2]
        float64_t a[2]
        float64_t j[2]
        float64_t k[8]
    void a_polytrack7_f64_init(a_polytrack7_f64_t *ctx, float64_t source[5], float64_t target[5])
    float64_t a_polytrack7_f64_pos(const a_polytrack7_f64_t *ctx, float64_t t)
    float64_t a_polytrack7_f64_vec(const a_polytrack7_f64_t *ctx, float64_t t)
    float64_t a_polytrack7_f64_acc(const a_polytrack7_f64_t *ctx, float64_t t)
    float64_t a_polytrack7_f64_jer(const a_polytrack7_f64_t *ctx, float64_t t)
    void a_polytrack7_f64_all(const a_polytrack7_f64_t *ctx, float64_t o[4], float64_t t)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_polytrack3:
    cdef a_polytrack3_f64_t ctx[1]
    cdef float64_t source[3]
    cdef float64_t target[3]
    cdef float64_t out[3]

    def __cinit__(self, source, target):
        self.source[0] = source[0]
        self.source[1] = source[1]
        self.source[2] = source[2]
        self.target[0] = target[0]
        self.target[1] = target[1]
        self.target[2] = target[2]
        a_polytrack3_f64_init(self.ctx, self.source, self.target)

    cpdef float64_t _pos(self, float64_t t):
        return a_polytrack3_f64_pos(self.ctx, t)

    def pos(self, t):
        for i in t:
            yield a_polytrack3_f64_pos(self.ctx, i)

    cpdef float64_t _vec(self, float64_t t):
        return a_polytrack3_f64_vec(self.ctx, t)

    def vec(self, t):
        for i in t:
            yield a_polytrack3_f64_vec(self.ctx, i)

    cpdef float64_t _acc(self, float64_t t):
        return a_polytrack3_f64_acc(self.ctx, t)

    def acc(self, t):
        for i in t:
            yield a_polytrack3_f64_acc(self.ctx, i)

    cpdef tuple _all(self, float64_t t):
        a_polytrack3_f64_all(self.ctx, self.out, t)
        return (self.out[0], self.out[1], self.out[2])

    def all(self, t):
        for i in t:
            a_polytrack3_f64_all(self.ctx, self.out, i)
            yield self.out[0], self.out[1], self.out[2]

    cpdef label(self):
        fmt = '{:+g}{}'
        p_label = 'p='
        if self.ctx.k[0]:
            p_label += '{:g}'.format(self.ctx.k[0])
        if self.ctx.k[1]:
            p_label += fmt.format(self.ctx.k[1], 't')
        if self.ctx.k[2]:
            p_label += fmt.format(self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            p_label += fmt.format(self.ctx.k[3], 't^3')
        v_label = 'v='
        if self.ctx.k[1]:
            v_label += '{:g}'.format(self.ctx.k[1])
        if self.ctx.k[2]:
            v_label += fmt.format(self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            v_label += fmt.format(self.ctx.k[3] * 3, 't^2')
        a_label = 'a='
        if self.ctx.k[2]:
            a_label += '{:g}'.format(self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            a_label += fmt.format(self.ctx.k[3] * 6, 't')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
        )

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_polytrack5:
    cdef a_polytrack5_f64_t ctx[1]
    cdef float64_t source[4]
    cdef float64_t target[4]
    cdef float64_t out[3]

    def __cinit__(self, source, target):
        self.source[0] = source[0]
        self.source[1] = source[1]
        self.source[2] = source[2]
        self.source[3] = source[3]
        self.target[0] = target[0]
        self.target[1] = target[1]
        self.target[2] = target[2]
        self.target[3] = target[3]
        a_polytrack5_f64_init(self.ctx, self.source, self.target)

    cpdef float64_t _pos(self, float64_t t):
        return a_polytrack5_f64_pos(self.ctx, t)

    def pos(self, t):
        for i in t:
            yield a_polytrack5_f64_pos(self.ctx, i)

    cpdef float64_t _vec(self, float64_t t):
        return a_polytrack5_f64_vec(self.ctx, t)

    def vec(self, t):
        for i in t:
            yield a_polytrack5_f64_vec(self.ctx, i)

    cpdef float64_t _acc(self, float64_t t):
        return a_polytrack5_f64_acc(self.ctx, t)

    def acc(self, t):
        for i in t:
            yield a_polytrack5_f64_acc(self.ctx, i)

    cpdef tuple _all(self, float64_t t):
        a_polytrack5_f64_all(self.ctx, self.out, t)
        return (self.out[0], self.out[1], self.out[2])

    def all(self, t):
        for i in t:
            a_polytrack5_f64_all(self.ctx, self.out, i)
            yield self.out[0], self.out[1], self.out[2]

    cpdef label(self):
        fmt = '{:+g}{}'
        p_label = 'p='
        if self.ctx.k[0]:
            p_label += '{:g}'.format(self.ctx.k[0])
        if self.ctx.k[1]:
            p_label += fmt.format(self.ctx.k[1], 't')
        if self.ctx.k[2]:
            p_label += fmt.format(self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            p_label += fmt.format(self.ctx.k[3], 't^3')
        if self.ctx.k[4]:
            p_label += fmt.format(self.ctx.k[4], 't^4')
        if self.ctx.k[5]:
            p_label += fmt.format(self.ctx.k[5], 't^5')
        v_label = 'v='
        if self.ctx.k[1]:
            v_label += '{:g}'.format(self.ctx.k[1])
        if self.ctx.k[2]:
            v_label += fmt.format(self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            v_label += fmt.format(self.ctx.k[3] * 3, 't^2')
        if self.ctx.k[4]:
            v_label += fmt.format(self.ctx.k[4] * 4, 't^3')
        if self.ctx.k[5]:
            v_label += fmt.format(self.ctx.k[5] * 5, 't^4')
        a_label = 'a='
        if self.ctx.k[2]:
            a_label += '{:g}'.format(self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            a_label += fmt.format(self.ctx.k[3] * 6, 't')
        if self.ctx.k[4]:
            a_label += fmt.format(self.ctx.k[4] * 12, 't^2')
        if self.ctx.k[5]:
            a_label += fmt.format(self.ctx.k[3] * 20, 't^3')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
        )

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_polytrack7:
    cdef a_polytrack7_f64_t ctx[1]
    cdef float64_t source[5]
    cdef float64_t target[5]
    cdef float64_t out[4]

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
        a_polytrack7_f64_init(self.ctx, self.source, self.target)

    cpdef float64_t _pos(self, float64_t t):
        return a_polytrack7_f64_pos(self.ctx, t)

    def pos(self, t):
        for i in t:
            yield a_polytrack7_f64_pos(self.ctx, i)

    cpdef float64_t _vec(self, float64_t t):
        return a_polytrack7_f64_vec(self.ctx, t)

    def vec(self, t):
        for i in t:
            yield a_polytrack7_f64_vec(self.ctx, i)

    cpdef float64_t _acc(self, float64_t t):
        return a_polytrack7_f64_acc(self.ctx, t)

    def acc(self, t):
        for i in t:
            yield a_polytrack7_f64_acc(self.ctx, i)

    cpdef float64_t _jer(self, float64_t t):
        return a_polytrack7_f64_jer(self.ctx, t)

    def jer(self, t):
        for i in t:
            yield a_polytrack7_f64_jer(self.ctx, i)

    cpdef tuple _all(self, float64_t t):
        a_polytrack7_f64_all(self.ctx, self.out, t)
        return (self.out[0], self.out[1], self.out[2], self.out[3])

    def all(self, t):
        for i in t:
            a_polytrack7_f64_all(self.ctx, self.out, i)
            yield self.out[0], self.out[1], self.out[2], self.out[3]

    cpdef label(self):
        fmt = '{:+g}{}'
        p_label = 'p='
        if self.ctx.k[0]:
            p_label += '{:g}'.format(self.ctx.k[0])
        if self.ctx.k[1]:
            p_label += fmt.format(self.ctx.k[1], 't')
        if self.ctx.k[2]:
            p_label += fmt.format(self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            p_label += fmt.format(self.ctx.k[3], 't^3')
        if self.ctx.k[4]:
            p_label += fmt.format(self.ctx.k[4], 't^4')
        if self.ctx.k[5]:
            p_label += fmt.format(self.ctx.k[5], 't^5')
        if self.ctx.k[6]:
            p_label += fmt.format(self.ctx.k[6], 't^6')
        if self.ctx.k[7]:
            p_label += fmt.format(self.ctx.k[7], 't^7')
        v_label = 'v='
        if self.ctx.k[1]:
            v_label += '{:g}'.format(self.ctx.k[1])
        if self.ctx.k[2]:
            v_label += fmt.format(self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            v_label += fmt.format(self.ctx.k[3] * 3, 't^2')
        if self.ctx.k[4]:
            v_label += fmt.format(self.ctx.k[4] * 4, 't^3')
        if self.ctx.k[5]:
            v_label += fmt.format(self.ctx.k[5] * 5, 't^4')
        if self.ctx.k[6]:
            v_label += fmt.format(self.ctx.k[6] * 6, 't^5')
        if self.ctx.k[7]:
            v_label += fmt.format(self.ctx.k[7] * 7, 't^6')
        a_label = 'a='
        if self.ctx.k[2]:
            a_label += '{:g}'.format(self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            a_label += fmt.format(self.ctx.k[3] * 6, 't')
        if self.ctx.k[4]:
            a_label += fmt.format(self.ctx.k[4] * 12, 't^2')
        if self.ctx.k[5]:
            a_label += fmt.format(self.ctx.k[3] * 20, 't^3')
        if self.ctx.k[6]:
            a_label += fmt.format(self.ctx.k[6] * 30, 't^4')
        if self.ctx.k[7]:
            a_label += fmt.format(self.ctx.k[7] * 42, 't^5')
        j_label = 'j='
        if self.ctx.k[3]:
            j_label += '{:g}'.format(self.ctx.k[3] * 6)
        if self.ctx.k[4]:
            j_label += fmt.format(self.ctx.k[4] * 12, 't')
        if self.ctx.k[5]:
            j_label += fmt.format(self.ctx.k[3] * 60, 't^2')
        if self.ctx.k[6]:
            j_label += fmt.format(self.ctx.k[6] * 120, 't^3')
        if self.ctx.k[7]:
            j_label += fmt.format(self.ctx.k[7] * 210, 't^4')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
            j_label.replace('=+', '='),
        )
