from ac.pid cimport *

cdef extern from "a/fpid.h":
    a_size_t A_FPID_BUF1 "A_FPID_BUF1" (a_uint_t N)
    ctypedef struct a_fpid_s "a_fpid_s":
        a_pid_s pid[1]
        const double *mkp
        const double *mki
        const double *mkd
        const double *mma
        a_uint_t *idx;
        a_real_t *mms;
        a_real_t *mat;
        a_real_t sigma;
        a_real_t alpha;
        a_real_t kp
        a_real_t ki
        a_real_t kd
        a_real_t (*op)(a_real_t, a_real_t)
    a_fpid_s *a_fpid_off  "a_fpid_off"  (a_fpid_s *ctx)
    a_fpid_s *a_fpid_inc  "a_fpid_inc"  (a_fpid_s *ctx)
    a_fpid_s *a_fpid_pos  "a_fpid_pos"  (a_fpid_s *ctx, a_real_t max)
    a_fpid_s *a_fpid_mode "a_fpid_mode" (a_fpid_s *ctx, a_uint_t mode)
    a_fpid_s *a_fpid_time "a_fpid_time" (a_fpid_s *ctx, a_real_t ts)
    a_fpid_s *a_fpid_ilim "a_fpid_ilim" (a_fpid_s *ctx, a_real_t min, a_real_t max)
    a_fpid_s *a_fpid_olim "a_fpid_olim" (a_fpid_s *ctx, a_real_t min, a_real_t max)
    a_fpid_s *a_fpid_buf1 "a_fpid_buf1" (a_fpid_s *ctx, a_vptr_t ptr, a_size_t max)
    a_fpid_s *a_fpid_kpid "a_fpid_kpid" (a_fpid_s *ctx, a_real_t kp, a_real_t ki, a_real_t kd)
    a_fpid_s *a_fpid_buff "a_fpid_buff" (a_fpid_s *ctx, a_uint_t *idx, a_real_t *mms, a_real_t *mat)
    a_fpid_s *a_fpid_base "a_fpid_base" (a_fpid_s *ctx, a_uint_t num, const a_real_t *mma, const a_real_t *mkp, const a_real_t *mki, const a_real_t *mkd)
    a_fpid_s *a_fpid_init "a_fpid_init" (a_fpid_s *ctx, a_real_t ts, a_uint_t num, const a_real_t *mma,
                                         const a_real_t *mkp, const a_real_t *mki, const a_real_t *mkd,
                                         a_real_t imin, a_real_t imax, a_real_t omin, a_real_t omax)
    a_real_t  a_fpid_proc "a_fpid_proc" (a_fpid_s *ctx, a_real_t set, a_real_t ref)
    a_fpid_s *a_fpid_done "a_fpid_done" (a_fpid_s *ctx)
