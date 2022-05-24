'''
 @file mf.pxd
 @brief cython for membership function
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

cdef extern from "a/controller/mf.h":
    ctypedef enum a_mf_e "a_mf_e":
        A_MF_NONE  "A_MF_NONE"
        A_MF_GAUSS "A_MF_GAUSS"
        A_MF_GBELL "A_MF_GBELL"
        A_MF_SIG   "A_MF_SIG"
        A_MF_TRAP  "A_MF_TRAP"
        A_MF_TRI   "A_MF_TRI"
        A_MF_Z     "A_MF_Z"
    double a_mf_gauss "a_mf_gauss" (double x, double sigma, double c)
    double a_mf_gbell "a_mf_gbell" (double x, double a, double b, double c)
    double a_mf_sig   "a_mf_sig"   (double x, double a, double c)
    double a_mf_trap  "a_mf_trap"  (double x, double a, double b, double c, double d)
    double a_mf_tri   "a_mf_tri"   (double x, double a, double b, double c)
    double a_mf_z     "a_mf_z"     (double x, double a, double b)
    double a_mf       "a_mf"       (a_mf_e t, double x, double *p)
