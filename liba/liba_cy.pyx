'''
 @file           liba_cy.pyx
 @brief          Algorithm library cython
 @author         tqfx tqfx@foxmail.com
 @copyright      Copyright (C) 2020 tqfx
'''
cimport cython
from libc.stdint cimport *
from libc.stdlib cimport *
from libc.string cimport *
from libc.stdio cimport *

cdef extern from "liba.h":
    ctypedef float float32_t
    ctypedef double float64_t

cdef extern from "a_lpf.h":
    ctypedef struct a_lpf_t:
        double o
        double k
        double t
    void a_lpf_init(a_lpf_t *ctx, double k, double t)
    double a_lpf_process(a_lpf_t *ctx, double x)
    void a_lpf_reset(a_lpf_t *ctx)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_lpf:
    cdef a_lpf_t ctx[1]

    def __cinit__(self, double k, double t):
        a_lpf_init(self.ctx, k, t)

    def reset(self):
        a_lpf_reset(self.ctx)
        return self

    def lpf(self, x):
        for i in x:
            yield a_lpf_process(self.ctx, i)

    cpdef double _lpf(self, double x):
        return a_lpf_process(self.ctx, x)

cdef extern from "a_pid.h":
    ctypedef enum a_pid_mode_t:
        A_PID_POS
        A_PID_INC
    ctypedef struct a_pid_t:
        a_pid_mode_t mode
        double kp
        double ki
        double kd
        double omax
        double omin
        double omaxi
        double a[3]
        double x[2]
        double y
    void a_pid_init(a_pid_t *ctx, a_pid_mode_t mode, const double kpid[3], double omin, double omax, double omaxi)
    void a_pid_pos(a_pid_t *ctx, const double kpid[3], double omin, double omax, double omaxi)
    void a_pid_inc(a_pid_t *ctx, const double kpid[3], double omin, double omax)
    double a_pid_process(a_pid_t *ctx, double ref, double set)
    void a_pid_reset(a_pid_t *ctx)

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_pid:
    cdef a_pid_t ctx[1]

    def __cinit__(self, a_pid_mode_t mode,
            double kp, double ki, double kd,
            double omin, double omax, double omaxi
        ):
        cdef double kpid[3]
        kpid[0] = kp
        kpid[1] = ki
        kpid[2] = kd
        a_pid_init(self.ctx, mode, kpid, omin, omax, omaxi)

    def reset(self):
        a_pid_reset(self.ctx)
        return self

    cpdef double pid(self, double ref, double set):
        return a_pid_process(self.ctx, ref, set)

cdef extern from "a_polytrack.h":
    ctypedef struct a_polytrack3_t:
        double t[2]
        double q[2]
        double v[2]
        double k[4]
    void a_polytrack3_init(a_polytrack3_t *ctx, const double source[3], const double target[3])
    double a_polytrack3_pos(const a_polytrack3_t *ctx, double t)
    double a_polytrack3_vec(const a_polytrack3_t *ctx, double t)
    double a_polytrack3_acc(const a_polytrack3_t *ctx, double t)
    void a_polytrack3_all(const a_polytrack3_t *ctx, double t, double o[3])

    ctypedef struct a_polytrack5_t:
        double t[2]
        double q[2]
        double v[2]
        double a[2]
        double k[6]
    void a_polytrack5_init(a_polytrack5_t *ctx, const double source[4], const double target[4])
    double a_polytrack5_pos(const a_polytrack5_t *ctx, double t)
    double a_polytrack5_vec(const a_polytrack5_t *ctx, double t)
    double a_polytrack5_acc(const a_polytrack5_t *ctx, double t)
    void a_polytrack5_all(const a_polytrack5_t *ctx, double t, double o[3])

    ctypedef struct a_polytrack7_t:
        double t[2]
        double q[2]
        double v[2]
        double a[2]
        double j[2]
        double k[8]
    void a_polytrack7_init(a_polytrack7_t *ctx, const double source[5], const double target[5])
    double a_polytrack7_pos(const a_polytrack7_t *ctx, double t)
    double a_polytrack7_vec(const a_polytrack7_t *ctx, double t)
    double a_polytrack7_acc(const a_polytrack7_t *ctx, double t)
    double a_polytrack7_jer(const a_polytrack7_t *ctx, double t)
    void a_polytrack7_all(const a_polytrack7_t *ctx, double t, double o[4])

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class a_polytrack3:
    cdef a_polytrack3_t ctx[1]
    cdef double source[3]
    cdef double target[3]
    cdef double out[3]

    def __cinit__(self, source, target):
        self.source[0] = source[0]
        self.source[1] = source[1]
        self.source[2] = source[2]
        self.target[0] = target[0]
        self.target[1] = target[1]
        self.target[2] = target[2]
        a_polytrack3_init(self.ctx, self.source, self.target)

    cpdef double _pos(self, double t):
        return a_polytrack3_pos(self.ctx, t)

    def pos(self, t):
        for i in t:
            yield a_polytrack3_pos(self.ctx, i)

    cpdef double _vec(self, double t):
        return a_polytrack3_vec(self.ctx, t)

    def vec(self, t):
        for i in t:
            yield a_polytrack3_vec(self.ctx, i)

    cpdef double _acc(self, double t):
        return a_polytrack3_acc(self.ctx, t)

    def acc(self, t):
        for i in t:
            yield a_polytrack3_acc(self.ctx, i)

    cpdef tuple _all(self, double t):
        a_polytrack3_all(self.ctx, t, self.out)
        return (self.out[0], self.out[1], self.out[2])

    def all(self, t):
        for i in t:
            a_polytrack3_all(self.ctx, i, self.out)
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
    cdef a_polytrack5_t ctx[1]
    cdef double source[4]
    cdef double target[4]
    cdef double out[3]

    def __cinit__(self, source, target):
        self.source[0] = source[0]
        self.source[1] = source[1]
        self.source[2] = source[2]
        self.source[3] = source[3]
        self.target[0] = target[0]
        self.target[1] = target[1]
        self.target[2] = target[2]
        self.target[3] = target[3]
        a_polytrack5_init(self.ctx, self.source, self.target)

    cpdef double _pos(self, double t):
        return a_polytrack5_pos(self.ctx, t)

    def pos(self, t):
        for i in t:
            yield a_polytrack5_pos(self.ctx, i)

    cpdef double _vec(self, double t):
        return a_polytrack5_vec(self.ctx, t)

    def vec(self, t):
        for i in t:
            yield a_polytrack5_vec(self.ctx, i)

    cpdef double _acc(self, double t):
        return a_polytrack5_acc(self.ctx, t)

    def acc(self, t):
        for i in t:
            yield a_polytrack5_acc(self.ctx, i)

    cpdef tuple _all(self, double t):
        a_polytrack5_all(self.ctx, t, self.out)
        return (self.out[0], self.out[1], self.out[2])

    def all(self, t):
        for i in t:
            a_polytrack5_all(self.ctx, i, self.out)
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
    cdef a_polytrack7_t ctx[1]
    cdef double source[5]
    cdef double target[5]
    cdef double out[4]

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
        a_polytrack7_init(self.ctx, self.source, self.target)

    cpdef double _pos(self, double t):
        return a_polytrack7_pos(self.ctx, t)

    def pos(self, t):
        for i in t:
            yield a_polytrack7_pos(self.ctx, i)

    cpdef double _vec(self, double t):
        return a_polytrack7_vec(self.ctx, t)

    def vec(self, t):
        for i in t:
            yield a_polytrack7_vec(self.ctx, i)

    cpdef double _acc(self, double t):
        return a_polytrack7_acc(self.ctx, t)

    def acc(self, t):
        for i in t:
            yield a_polytrack7_acc(self.ctx, i)

    cpdef double _jer(self, double t):
        return a_polytrack7_jer(self.ctx, t)

    def jer(self, t):
        for i in t:
            yield a_polytrack7_jer(self.ctx, i)

    cpdef tuple _all(self, double t):
        a_polytrack7_all(self.ctx, t, self.out)
        return (self.out[0], self.out[1], self.out[2], self.out[3])

    def all(self, t):
        for i in t:
            a_polytrack7_all(self.ctx, i, self.out)
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
