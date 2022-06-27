from mf cimport *

@cython.wraparound(False)
@cython.boundscheck(False)
cdef class mf:
    '''membership function'''
    NONE  = A_MF_NONE
    GAUSS = A_MF_GAUSS
    GBELL = A_MF_GBELL
    SIG   = A_MF_SIG
    TRAP  = A_MF_TRAP
    TRI   = A_MF_TRI
    Z     = A_MF_Z
    @staticmethod
    def __call__(t: a_mf_e, x, p):
        cdef array.array a = array.array('d', p)
        if not isinstance(x, _typing.Iterable):
            return a_mf(t, x, a.data.as_doubles)
        y = []
        for i in x:
            y.append(a_mf(t, i, a.data.as_doubles))
        return y
    @staticmethod
    def gauss(x, sigma: float, c: float):
        '''Gaussian membership function'''
        if not isinstance(x, _typing.Iterable):
            return a_mf_gauss(x, sigma, c)
        y = []
        for i in x:
            y.append(a_mf_gauss(i, sigma, c))
        return y
    @staticmethod
    def gbell(x, a: float, b: float, c: float):
        '''Generalized bell-shaped membership function'''
        if not isinstance(x, _typing.Iterable):
            return a_mf_gbell(x, a, b, c)
        y = []
        for i in x:
            y.append(a_mf_gbell(i, a, b, c))
        return y
    @staticmethod
    def sig(x, a: float, c: float):
        '''Sigmoidal membership function'''
        if not isinstance(x, _typing.Iterable):
            return a_mf_sig(x, a, c)
        y = []
        for i in x:
            y.append(a_mf_sig(i, a, c))
        return y
    @staticmethod
    def trap(x, a: float, b: float, c: float, d: float):
        '''Trapezoidal membership function'''
        if not isinstance(x, _typing.Iterable):
            return a_mf_trap(x, a, b, c, d)
        y = []
        for i in x:
            y.append(a_mf_trap(i, a, b, c, d))
        return y
    @staticmethod
    def tri(x, a: float, b: float, c: float):
        '''Triangular membership function'''
        if not isinstance(x, _typing.Iterable):
            return a_mf_tri(x, a, b, c)
        y = []
        for i in x:
            y.append(a_mf_tri(i, a, b, c))
        return y
    @staticmethod
    def z(x, a: float, b: float):
        '''Z-shaped membership function'''
        if not isinstance(x, _typing.Iterable):
            return a_mf_z(x, a, b)
        y = []
        for i in x:
            y.append(a_mf_z(i, a, b))
        return y
