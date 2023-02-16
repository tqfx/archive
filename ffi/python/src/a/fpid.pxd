from a.pid cimport *

cdef extern from "a/fpid.h":
    ctypedef struct a_fpid_s:
        a_pid_s pid[1]
        a_real_t kp
        a_real_t ki
        a_real_t kd
    a_size_t A_FPID_BUF1(a_uint_t max)
    a_fpid_s *a_fpid_off(a_fpid_s *ctx)
    a_fpid_s *a_fpid_inc(a_fpid_s *ctx)
    a_fpid_s *a_fpid_pos(a_fpid_s *ctx, a_real_t max)
    a_fpid_s *a_fpid_ilim(a_fpid_s *ctx, a_real_t min, a_real_t max)
    a_fpid_s *a_fpid_olim(a_fpid_s *ctx, a_real_t min, a_real_t max)
    a_fpid_s *a_fpid_buf1(a_fpid_s *ctx, a_vptr_t ptr, a_size_t max)
    a_fpid_s *a_fpid_kpid(a_fpid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
    a_fpid_s *a_fpid_buff(a_fpid_s *ctx, a_uint_t *idx, a_real_t *mms, a_real_t *mat)
    a_fpid_s *a_fpid_setv(a_fpid_s *ctx, a_real_t *out, a_real_t *fdb, a_real_t *sum, a_real_t *ec, a_real_t *e)
    a_fpid_s *a_fpid_base(a_fpid_s *ctx, a_uint_t num, a_real_t const *mmp, a_real_t const *mkp, a_real_t const *mki, a_real_t const *mkd)
    a_fpid_s *a_fpid_init(a_fpid_s *ctx, a_real_t dt, a_uint_t num, a_real_t const *mmp,
                          a_real_t const *mkp, a_real_t const *mki, a_real_t const *mkd,
                          a_real_t imin, a_real_t imax, a_real_t omin, a_real_t omax)
    a_real_t *a_fpid_outp(a_fpid_s *ctx, a_real_t *set, a_real_t *fdb)
    a_real_t a_fpid_outv(a_fpid_s *ctx, a_real_t set, a_real_t fdb)
    a_fpid_s *a_fpid_exit(a_fpid_s *ctx)
    a_fpid_s *a_fpid_zero(a_fpid_s *ctx)
    a_uint_t a_fpid_bufnum(a_fpid_s const *ctx)
    a_vptr_t a_fpid_bufptr(a_fpid_s const *ctx)
    a_uint_t a_fpid_col(a_fpid_s const *ctx)
