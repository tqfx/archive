from a.polytrack cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack3:
    '''cubic polynomial trajectory'''
    cdef a_polytrack3_s ctx[1]
    def __cinit__(self, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0 = 0, a_real_t v1 = 0):
        a_polytrack3_init(self.ctx, t0, t1, q0, q1, v0, v1)
    def __call__(self, ts):
        '''calculate all'''
        cdef a_real_t out[3]
        if iterable(ts):
            p = array('d')
            v = array('d')
            a = array('d')
            for i, it in enumerate(ts):
                a_polytrack3_out(self.ctx, it, out)
                p.append(out[0])
                v.append(out[1])
                a.append(out[2])
            return p, v, a
        a_polytrack3_out(self.ctx, ts, out)
        return out[0], out[1], out[2]
    def pos(self, ts):
        '''calculate position'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack3_pos(self.ctx, it)
            return out
        return a_polytrack3_pos(self.ctx, ts)
    def vec(self, ts):
        '''calculate velocity'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack3_vec(self.ctx, it)
            return out
        return a_polytrack3_vec(self.ctx, ts)
    def acc(self, ts):
        '''calculate acceleration'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack3_acc(self.ctx, it)
            return out
        return a_polytrack3_acc(self.ctx, ts)
    def text(self):
        '''formula text'''
        text_p = 'p='
        if self.ctx.k[0]:
            text_p +=  '%g' % (self.ctx.k[0])
        if self.ctx.k[1]:
            text_p += '%+g%s' % (self.ctx.k[1], 't')
        if self.ctx.k[2]:
            text_p += '%+g%s' % (self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            text_p += '%+g%s' % (self.ctx.k[3], 't^3')
        text_v = 'v='
        if self.ctx.k[1]:
            text_v += '%g' % (self.ctx.k[1])
        if self.ctx.k[2]:
            text_v += '%+g%s' % (self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            text_v += '%+g%s' % (self.ctx.k[3] * 3, 't^2')
        text_a = 'a='
        if self.ctx.k[2]:
            text_a += '%g' % (self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            text_a += '%+g%s' % (self.ctx.k[3] * 6, 't')
        return (
            text_p.replace('=+', '='),
            text_v.replace('=+', '='),
            text_a.replace('=+', '='),
        )

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack5:
    '''quintic polynomial trajectory'''
    cdef a_polytrack5_s ctx[1]
    def __cinit__(self, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0 = 0, a_real_t v1 = 0, a_real_t a0 = 0, a_real_t a1 = 0):
        a_polytrack5_init(self.ctx, t0, t1, q0, q1, v0, v1, a0, a1)
    def __call__(self, ts):
        '''calculate all'''
        cdef a_real_t out[3]
        if iterable(ts):
            p = array('d')
            v = array('d')
            a = array('d')
            for i, it in enumerate(ts):
                a_polytrack5_out(self.ctx, it, out)
                p.append(out[0])
                v.append(out[1])
                a.append(out[2])
            return p, v, a
        a_polytrack5_out(self.ctx, ts, out)
        return out[0], out[1], out[2]
    def pos(self, ts):
        '''calculate position'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack5_pos(self.ctx, it)
            return out
        return a_polytrack5_pos(self.ctx, ts)
    def vec(self, ts):
        '''calculate velocity'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack5_vec(self.ctx, it)
            return out
        return a_polytrack5_vec(self.ctx, ts)
    def acc(self, ts):
        '''calculate acceleration'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack5_acc(self.ctx, it)
            return out
        return a_polytrack5_acc(self.ctx, ts)
    def text(self):
        '''formula text'''
        text_p = 'p='
        if self.ctx.k[0]:
            text_p += '%g' % (self.ctx.k[0])
        if self.ctx.k[1]:
            text_p += '%+g%s' % (self.ctx.k[1], 't')
        if self.ctx.k[2]:
            text_p += '%+g%s' % (self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            text_p += '%+g%s' % (self.ctx.k[3], 't^3')
        if self.ctx.k[4]:
            text_p += '%+g%s' % (self.ctx.k[4], 't^4')
        if self.ctx.k[5]:
            text_p += '%+g%s' % (self.ctx.k[5], 't^5')
        text_v = 'v='
        if self.ctx.k[1]:
            text_v += '%g' % (self.ctx.k[1])
        if self.ctx.k[2]:
            text_v += '%+g%s' % (self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            text_v += '%+g%s' % (self.ctx.k[3] * 3, 't^2')
        if self.ctx.k[4]:
            text_v += '%+g%s' % (self.ctx.k[4] * 4, 't^3')
        if self.ctx.k[5]:
            text_v += '%+g%s' % (self.ctx.k[5] * 5, 't^4')
        text_a = 'a='
        if self.ctx.k[2]:
            text_a += '%g' % (self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            text_a += '%+g%s' % (self.ctx.k[3] * 6, 't')
        if self.ctx.k[4]:
            text_a += '%+g%s' % (self.ctx.k[4] * 12, 't^2')
        if self.ctx.k[5]:
            text_a += '%+g%s' % (self.ctx.k[3] * 20, 't^3')
        return (
            text_p.replace('=+', '='),
            text_v.replace('=+', '='),
            text_a.replace('=+', '='),
        )

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class polytrack7:
    '''hepta polynomial trajectory'''
    cdef a_polytrack7_s ctx[1]
    def __cinit__(self, a_real_t t0, a_real_t t1, a_real_t q0, a_real_t q1, a_real_t v0 = 0, a_real_t v1 = 0, a_real_t a0 = 0, a_real_t a1 = 0, a_real_t j0 = 0, a_real_t j1 = 0):
        a_polytrack7_init(self.ctx, t0, t1, q0, q1, v0, v1, a0, a1, j0, j1)
    def __call__(self, ts):
        '''calculate all'''
        cdef a_real_t out[4]
        if iterable(ts):
            p = array('d')
            v = array('d')
            a = array('d')
            j = array('d')
            for i, it in enumerate(ts):
                a_polytrack7_out(self.ctx, it, out)
                p.append(out[0])
                v.append(out[1])
                a.append(out[2])
                j.append(out[3])
            return p, v, a, j
        a_polytrack7_out(self.ctx, ts, out)
        return out[0], out[1], out[2], out[3]
    def pos(self, ts):
        '''calculate position'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack7_pos(self.ctx, it)
            return out
        return a_polytrack7_pos(self.ctx, ts)
    def vec(self, ts):
        '''calculate velocity'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack7_vec(self.ctx, it)
            return out
        return a_polytrack7_vec(self.ctx, ts)
    def acc(self, ts):
        '''calculate acceleration'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack7_acc(self.ctx, it)
            return out
        return a_polytrack7_acc(self.ctx, ts)
    def jer(self, ts):
        '''calculate jerk'''
        if iterable(ts):
            out = array('d', ts)
            for i, it in enumerate(ts):
                out[i] = a_polytrack7_jer(self.ctx, it)
            return out
        return a_polytrack7_jer(self.ctx, ts)
    def text(self):
        '''formula text'''
        text_p = 'p='
        if self.ctx.k[0]:
            text_p += '%g' % (self.ctx.k[0])
        if self.ctx.k[1]:
            text_p += '%+g%s' % (self.ctx.k[1], 't')
        if self.ctx.k[2]:
            text_p += '%+g%s' % (self.ctx.k[2], 't^2')
        if self.ctx.k[3]:
            text_p += '%+g%s' % (self.ctx.k[3], 't^3')
        if self.ctx.k[4]:
            text_p += '%+g%s' % (self.ctx.k[4], 't^4')
        if self.ctx.k[5]:
            text_p += '%+g%s' % (self.ctx.k[5], 't^5')
        if self.ctx.k[6]:
            text_p += '%+g%s' % (self.ctx.k[6], 't^6')
        if self.ctx.k[7]:
            text_p += '%+g%s' % (self.ctx.k[7], 't^7')
        text_v = 'v='
        if self.ctx.k[1]:
            text_v += '%g' % (self.ctx.k[1])
        if self.ctx.k[2]:
            text_v += '%+g%s' % (self.ctx.k[2] * 2, 't')
        if self.ctx.k[3]:
            text_v += '%+g%s' % (self.ctx.k[3] * 3, 't^2')
        if self.ctx.k[4]:
            text_v += '%+g%s' % (self.ctx.k[4] * 4, 't^3')
        if self.ctx.k[5]:
            text_v += '%+g%s' % (self.ctx.k[5] * 5, 't^4')
        if self.ctx.k[6]:
            text_v += '%+g%s' % (self.ctx.k[6] * 6, 't^5')
        if self.ctx.k[7]:
            text_v += '%+g%s' % (self.ctx.k[7] * 7, 't^6')
        text_a = 'a='
        if self.ctx.k[2]:
            text_a += '%g' % (self.ctx.k[2] * 2)
        if self.ctx.k[3]:
            text_a += '%+g%s' % (self.ctx.k[3] * 6, 't')
        if self.ctx.k[4]:
            text_a += '%+g%s' % (self.ctx.k[4] * 12, 't^2')
        if self.ctx.k[5]:
            text_a += '%+g%s' % (self.ctx.k[3] * 20, 't^3')
        if self.ctx.k[6]:
            text_a += '%+g%s' % (self.ctx.k[6] * 30, 't^4')
        if self.ctx.k[7]:
            text_a += '%+g%s' % (self.ctx.k[7] * 42, 't^5')
        text_j = 'j='
        if self.ctx.k[3]:
            text_j += '%g' % (self.ctx.k[3] * 6)
        if self.ctx.k[4]:
            text_j += '%+g%s' % (self.ctx.k[4] * 12, 't')
        if self.ctx.k[5]:
            text_j += '%+g%s' % (self.ctx.k[3] * 60, 't^2')
        if self.ctx.k[6]:
            text_j += '%+g%s' % (self.ctx.k[6] * 120, 't^3')
        if self.ctx.k[7]:
            text_j += '%+g%s' % (self.ctx.k[7] * 210, 't^4')
        return (
            text_p.replace('=+', '='),
            text_v.replace('=+', '='),
            text_a.replace('=+', '='),
            text_j.replace('=+', '='),
        )
