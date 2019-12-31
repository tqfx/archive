/*!
 @file mf.c
 @brief test membership function
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#include "a/controller/mf.h"

static void test(void)
{
    a_mf_gauss(0, 1, 0);
    a_mf_gbell(0, 1, 1, 0);
    a_mf_sig(0, 1, 0);
    a_mf_trap(0, 0, 1, 2, 3);
    a_mf_tri(0, 0, 1, 2);
    a_mf_z(0, 0, 1);
    a_real_t p[] = {1, 2, 3, 4};
    a_mf(A_MF_NONE, 2, p);
    a_mf(A_MF_GAUSS, 2, p);
    a_mf(A_MF_GBELL, 2, p);
    a_mf(A_MF_SIG, 2, p);
    a_mf(A_MF_TRAP, 2, p);
    a_mf(A_MF_TRI, 2, p);
    a_mf(A_MF_Z, 2, p);
}

int main(void)
{
    test();
    return 0;
}
