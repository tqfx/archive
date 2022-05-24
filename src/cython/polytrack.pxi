'''
 @file polytrack.pxi
 @brief cython for polynomial trajectory
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''
from polytrack cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack3:
    cdef a_polytrack3_s ctx[1]
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
    def __call__(self, t):
        if not isinstance(t, typing.Iterable):
            a_polytrack3_all(self.ctx, t, self.out)
            return self.out[0], self.out[1], self.out[2]
        p, v, a = [], [], []
        for i in t:
            a_polytrack3_all(self.ctx, i, self.out)
            p.append(self.out[0])
            v.append(self.out[1])
            a.append(self.out[2])
        return p, v, a
    def pos(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack3_pos(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack3_pos(self.ctx, i))
        return y
    def vec(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack3_vec(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack3_vec(self.ctx, i))
        return y
    def acc(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack3_acc(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack3_acc(self.ctx, i))
        return y
    def label(self):
        p_label = 'p='
        if self.ctx.k[0]:
            p_label +=  '%g' % (self.ctx.k[0])
        if self.ctx.k[1]:
            p_label += '%+g%s' % (self.ctx.k[1], 't')
        if self.ctx.k[2]:
            p_label += '%+g%s' % (self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            p_label += '%+g%s' % (self.ctx.k[3], 't^3')
        v_label = 'v='
        if self.ctx.k[1]:
            v_label += '%g' % (self.ctx.k[1])
        if self.ctx.k[2]:
            v_label += '%+g%s' % (self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            v_label += '%+g%s' % (self.ctx.k[3] * 3, 't^2')
        a_label = 'a='
        if self.ctx.k[2]:
            a_label += '%g' % (self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            a_label += '%+g%s' % (self.ctx.k[3] * 6, 't')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
        )

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack5:
    cdef a_polytrack5_s ctx[1]
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
    def __call__(self, t):
        if not isinstance(t, typing.Iterable):
            a_polytrack5_all(self.ctx, t, self.out)
            return self.out[0], self.out[1], self.out[2]
        p, v, a = [], [], []
        for i in t:
            a_polytrack5_all(self.ctx, i, self.out)
            p.append(self.out[0])
            v.append(self.out[1])
            a.append(self.out[2])
        return p, v, a
    def pos(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack5_pos(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack5_pos(self.ctx, i))
        return y
    def vec(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack5_vec(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack5_vec(self.ctx, i))
        return y
    def acc(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack5_acc(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack5_acc(self.ctx, i))
        return y
    def label(self):
        p_label = 'p='
        if self.ctx.k[0]:
            p_label += '%g' % (self.ctx.k[0])
        if self.ctx.k[1]:
            p_label += '%+g%s' % (self.ctx.k[1], 't')
        if self.ctx.k[2]:
            p_label += '%+g%s' % (self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            p_label += '%+g%s' % (self.ctx.k[3], 't^3')
        if self.ctx.k[4]:
            p_label += '%+g%s' % (self.ctx.k[4], 't^4')
        if self.ctx.k[5]:
            p_label += '%+g%s' % (self.ctx.k[5], 't^5')
        v_label = 'v='
        if self.ctx.k[1]:
            v_label += '%g' % (self.ctx.k[1])
        if self.ctx.k[2]:
            v_label += '%+g%s' % (self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            v_label += '%+g%s' % (self.ctx.k[3] * 3, 't^2')
        if self.ctx.k[4]:
            v_label += '%+g%s' % (self.ctx.k[4] * 4, 't^3')
        if self.ctx.k[5]:
            v_label += '%+g%s' % (self.ctx.k[5] * 5, 't^4')
        a_label = 'a='
        if self.ctx.k[2]:
            a_label += '%g' % (self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            a_label += '%+g%s' % (self.ctx.k[3] * 6, 't')
        if self.ctx.k[4]:
            a_label += '%+g%s' % (self.ctx.k[4] * 12, 't^2')
        if self.ctx.k[5]:
            a_label += '%+g%s' % (self.ctx.k[3] * 20, 't^3')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
        )

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack7:
    cdef a_polytrack7_s ctx[1]
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
    def __call__(self, t):
        if not isinstance(t, typing.Iterable):
            a_polytrack7_all(self.ctx, t, self.out)
            return self.out[0], self.out[1], self.out[2], self.out[3]
        p, v, a, j = [], [], [], []
        for i in t:
            a_polytrack7_all(self.ctx, i, self.out)
            p.append(self.out[0])
            v.append(self.out[1])
            a.append(self.out[2])
            j.append(self.out[3])
        return p, v, a, j
    def pos(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack7_pos(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack7_pos(self.ctx, i))
        return y
    def vec(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack7_vec(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack7_vec(self.ctx, i))
        return y
    def acc(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack7_acc(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack7_acc(self.ctx, i))
        return y
    def jer(self, t):
        if not isinstance(t, typing.Iterable):
            return a_polytrack7_jer(self.ctx, t)
        y = []
        for i in t:
            y.append(a_polytrack7_jer(self.ctx, i))
        return y
    def label(self):
        p_label = 'p='
        if self.ctx.k[0]:
            p_label += '%g' % (self.ctx.k[0])
        if self.ctx.k[1]:
            p_label += '%+g%s' % (self.ctx.k[1], 't')
        if self.ctx.k[2]:
            p_label += '%+g%s' % (self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            p_label += '%+g%s' % (self.ctx.k[3], 't^3')
        if self.ctx.k[4]:
            p_label += '%+g%s' % (self.ctx.k[4], 't^4')
        if self.ctx.k[5]:
            p_label += '%+g%s' % (self.ctx.k[5], 't^5')
        if self.ctx.k[6]:
            p_label += '%+g%s' % (self.ctx.k[6], 't^6')
        if self.ctx.k[7]:
            p_label += '%+g%s' % (self.ctx.k[7], 't^7')
        v_label = 'v='
        if self.ctx.k[1]:
            v_label += '%g' % (self.ctx.k[1])
        if self.ctx.k[2]:
            v_label += '%+g%s' % (self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            v_label += '%+g%s' % (self.ctx.k[3] * 3, 't^2')
        if self.ctx.k[4]:
            v_label += '%+g%s' % (self.ctx.k[4] * 4, 't^3')
        if self.ctx.k[5]:
            v_label += '%+g%s' % (self.ctx.k[5] * 5, 't^4')
        if self.ctx.k[6]:
            v_label += '%+g%s' % (self.ctx.k[6] * 6, 't^5')
        if self.ctx.k[7]:
            v_label += '%+g%s' % (self.ctx.k[7] * 7, 't^6')
        a_label = 'a='
        if self.ctx.k[2]:
            a_label += '%g' % (self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            a_label += '%+g%s' % (self.ctx.k[3] * 6, 't')
        if self.ctx.k[4]:
            a_label += '%+g%s' % (self.ctx.k[4] * 12, 't^2')
        if self.ctx.k[5]:
            a_label += '%+g%s' % (self.ctx.k[3] * 20, 't^3')
        if self.ctx.k[6]:
            a_label += '%+g%s' % (self.ctx.k[6] * 30, 't^4')
        if self.ctx.k[7]:
            a_label += '%+g%s' % (self.ctx.k[7] * 42, 't^5')
        j_label = 'j='
        if self.ctx.k[3]:
            j_label += '%g' % (self.ctx.k[3] * 6)
        if self.ctx.k[4]:
            j_label += '%+g%s' % (self.ctx.k[4] * 12, 't')
        if self.ctx.k[5]:
            j_label += '%+g%s' % (self.ctx.k[3] * 60, 't^2')
        if self.ctx.k[6]:
            j_label += '%+g%s' % (self.ctx.k[6] * 120, 't^3')
        if self.ctx.k[7]:
            j_label += '%+g%s' % (self.ctx.k[7] * 210, 't^4')
        return (
            p_label.replace('=+', '='),
            v_label.replace('=+', '='),
            a_label.replace('=+', '='),
            j_label.replace('=+', '='),
        )
