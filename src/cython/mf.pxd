'''
 @file mf.pxd
 @brief cython for membership function
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
'''

cdef extern from "a/controller/mf.h":
    ctypedef enum c_mf_e "a_mf_e":
        C_MF_NONE  "A_MF_NONE"
        C_MF_GAUSS "A_MF_GAUSS"
        C_MF_GBELL "A_MF_GBELL"
        C_MF_SIG   "A_MF_SIG"
        C_MF_TRAP  "A_MF_TRAP"
        C_MF_TRI   "A_MF_TRI"
        C_MF_Z     "A_MF_Z"
    double c_mf_gauss "a_mf_gauss" (double x, double sigma, double c)
    double c_mf_gbell "a_mf_gbell" (double x, double a, double b, double c)
    double c_mf_sig   "a_mf_sig"   (double x, double a, double c)
    double c_mf_trap  "a_mf_trap"  (double x, double a, double b, double c, double d)
    double c_mf_tri   "a_mf_tri"   (double x, double a, double b, double c)
    double c_mf_z     "a_mf_z"     (double x, double a, double b)
    double c_mf       "a_mf"       (c_mf_e t, double x, double *p)
