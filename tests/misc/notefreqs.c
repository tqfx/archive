/*!
 @file notefreqs.c
 @brief test note frequency
 @copyright Copyright (C) 2020 tqfx, All rights reserved.
*/

#define NOTEFREQS_PROPORT ((180000000 >> 1) / 200)
#define NOTEFREQS_TYPE    double
#include "a/misc/notefreqs.h"

#include <stdio.h>

static double song[][2] = {
    /* clang-format off */
    {NOTEFREQS_FREQ_C0,  NOTEFREQS_C0},  {NOTEFREQS_FREQ_C_0, NOTEFREQS_C_0},
    {NOTEFREQS_FREQ_D0,  NOTEFREQS_D0},  {NOTEFREQS_FREQ_D_0, NOTEFREQS_D_0},
    {NOTEFREQS_FREQ_E0,  NOTEFREQS_E0},  {NOTEFREQS_FREQ_F0,  NOTEFREQS_F0},
    {NOTEFREQS_FREQ_F_0, NOTEFREQS_F_0}, {NOTEFREQS_FREQ_G0,  NOTEFREQS_G0},
    {NOTEFREQS_FREQ_G_0, NOTEFREQS_G_0}, {NOTEFREQS_FREQ_A0,  NOTEFREQS_A0},
    {NOTEFREQS_FREQ_A_0, NOTEFREQS_A_0}, {NOTEFREQS_FREQ_B0,  NOTEFREQS_B0},
    {NOTEFREQS_FREQ_C1,  NOTEFREQS_C1},  {NOTEFREQS_FREQ_C_1, NOTEFREQS_C_1},
    {NOTEFREQS_FREQ_D1,  NOTEFREQS_D1},  {NOTEFREQS_FREQ_D_1, NOTEFREQS_D_1},
    {NOTEFREQS_FREQ_E1,  NOTEFREQS_E1},  {NOTEFREQS_FREQ_F1,  NOTEFREQS_F1},
    {NOTEFREQS_FREQ_F_1, NOTEFREQS_F_1}, {NOTEFREQS_FREQ_G1,  NOTEFREQS_G1},
    {NOTEFREQS_FREQ_G_1, NOTEFREQS_G_1}, {NOTEFREQS_FREQ_A1,  NOTEFREQS_A1},
    {NOTEFREQS_FREQ_A_1, NOTEFREQS_A_1}, {NOTEFREQS_FREQ_B1,  NOTEFREQS_B1},
    {NOTEFREQS_FREQ_C2,  NOTEFREQS_C2},  {NOTEFREQS_FREQ_C_2, NOTEFREQS_C_2},
    {NOTEFREQS_FREQ_D2,  NOTEFREQS_D2},  {NOTEFREQS_FREQ_D_2, NOTEFREQS_D_2},
    {NOTEFREQS_FREQ_E2,  NOTEFREQS_E2},  {NOTEFREQS_FREQ_F2,  NOTEFREQS_F2},
    {NOTEFREQS_FREQ_F_2, NOTEFREQS_F_2}, {NOTEFREQS_FREQ_G2,  NOTEFREQS_G2},
    {NOTEFREQS_FREQ_G_2, NOTEFREQS_G_2}, {NOTEFREQS_FREQ_A2,  NOTEFREQS_A2},
    {NOTEFREQS_FREQ_A_2, NOTEFREQS_A_2}, {NOTEFREQS_FREQ_B2,  NOTEFREQS_B2},
    {NOTEFREQS_FREQ_C3,  NOTEFREQS_C3},  {NOTEFREQS_FREQ_C_3, NOTEFREQS_C_3},
    {NOTEFREQS_FREQ_D3,  NOTEFREQS_D3},  {NOTEFREQS_FREQ_D_3, NOTEFREQS_D_3},
    {NOTEFREQS_FREQ_E3,  NOTEFREQS_E3},  {NOTEFREQS_FREQ_F3,  NOTEFREQS_F3},
    {NOTEFREQS_FREQ_F_3, NOTEFREQS_F_3}, {NOTEFREQS_FREQ_G3,  NOTEFREQS_G3},
    {NOTEFREQS_FREQ_G_3, NOTEFREQS_G_3}, {NOTEFREQS_FREQ_A3,  NOTEFREQS_A3},
    {NOTEFREQS_FREQ_A_3, NOTEFREQS_A_3}, {NOTEFREQS_FREQ_B3,  NOTEFREQS_B3},
    {NOTEFREQS_FREQ_C4,  NOTEFREQS_C4},  {NOTEFREQS_FREQ_C_4, NOTEFREQS_C_4},
    {NOTEFREQS_FREQ_D4,  NOTEFREQS_D4},  {NOTEFREQS_FREQ_D_4, NOTEFREQS_D_4},
    {NOTEFREQS_FREQ_E4,  NOTEFREQS_E4},  {NOTEFREQS_FREQ_F4,  NOTEFREQS_F4},
    {NOTEFREQS_FREQ_F_4, NOTEFREQS_F_4}, {NOTEFREQS_FREQ_G4,  NOTEFREQS_G4},
    {NOTEFREQS_FREQ_G_4, NOTEFREQS_G_4}, {NOTEFREQS_FREQ_A4,  NOTEFREQS_A4},
    {NOTEFREQS_FREQ_A_4, NOTEFREQS_A_4}, {NOTEFREQS_FREQ_B4,  NOTEFREQS_B4},
    {NOTEFREQS_FREQ_C5,  NOTEFREQS_C5},  {NOTEFREQS_FREQ_C_5, NOTEFREQS_C_5},
    {NOTEFREQS_FREQ_D5,  NOTEFREQS_D5},  {NOTEFREQS_FREQ_D_5, NOTEFREQS_D_5},
    {NOTEFREQS_FREQ_E5,  NOTEFREQS_E5},  {NOTEFREQS_FREQ_F5,  NOTEFREQS_F5},
    {NOTEFREQS_FREQ_F_5, NOTEFREQS_F_5}, {NOTEFREQS_FREQ_G5,  NOTEFREQS_G5},
    {NOTEFREQS_FREQ_G_5, NOTEFREQS_G_5}, {NOTEFREQS_FREQ_A5,  NOTEFREQS_A5},
    {NOTEFREQS_FREQ_A_5, NOTEFREQS_A_5}, {NOTEFREQS_FREQ_B5,  NOTEFREQS_B5},
    {NOTEFREQS_FREQ_C6,  NOTEFREQS_C6},  {NOTEFREQS_FREQ_C_6, NOTEFREQS_C_6},
    {NOTEFREQS_FREQ_D6,  NOTEFREQS_D6},  {NOTEFREQS_FREQ_D_6, NOTEFREQS_D_6},
    {NOTEFREQS_FREQ_E6,  NOTEFREQS_E6},  {NOTEFREQS_FREQ_F6,  NOTEFREQS_F6},
    {NOTEFREQS_FREQ_F_6, NOTEFREQS_F_6}, {NOTEFREQS_FREQ_G6,  NOTEFREQS_G6},
    {NOTEFREQS_FREQ_G_6, NOTEFREQS_G_6}, {NOTEFREQS_FREQ_A6,  NOTEFREQS_A6},
    {NOTEFREQS_FREQ_A_6, NOTEFREQS_A_6}, {NOTEFREQS_FREQ_B6,  NOTEFREQS_B6},
    {NOTEFREQS_FREQ_C7,  NOTEFREQS_C7},  {NOTEFREQS_FREQ_C_7, NOTEFREQS_C_7},
    {NOTEFREQS_FREQ_D7,  NOTEFREQS_D7},  {NOTEFREQS_FREQ_D_7, NOTEFREQS_D_7},
    {NOTEFREQS_FREQ_E7,  NOTEFREQS_E7},  {NOTEFREQS_FREQ_F7,  NOTEFREQS_F7},
    {NOTEFREQS_FREQ_F_7, NOTEFREQS_F_7}, {NOTEFREQS_FREQ_G7,  NOTEFREQS_G7},
    {NOTEFREQS_FREQ_G_7, NOTEFREQS_G_7}, {NOTEFREQS_FREQ_A7,  NOTEFREQS_A7},
    {NOTEFREQS_FREQ_A_7, NOTEFREQS_A_7}, {NOTEFREQS_FREQ_B7,  NOTEFREQS_B7},
    {NOTEFREQS_FREQ_C8,  NOTEFREQS_C8},  {NOTEFREQS_FREQ_C_8, NOTEFREQS_C_8},
    {NOTEFREQS_FREQ_D8,  NOTEFREQS_D8},  {NOTEFREQS_FREQ_D_8, NOTEFREQS_D_8},
    {NOTEFREQS_FREQ_E8,  NOTEFREQS_E8},  {NOTEFREQS_FREQ_F8,  NOTEFREQS_F8},
    {NOTEFREQS_FREQ_F_8, NOTEFREQS_F_8}, {NOTEFREQS_FREQ_G8,  NOTEFREQS_G8},
    {NOTEFREQS_FREQ_G_8, NOTEFREQS_G_8}, {NOTEFREQS_FREQ_A8,  NOTEFREQS_A8},
    {NOTEFREQS_FREQ_A_8, NOTEFREQS_A_8}, {NOTEFREQS_FREQ_B8,  NOTEFREQS_B8},
    /* clang-format on */
};

int main(void)
{
    unsigned int song_n = sizeof(song) / sizeof(*song);
    for (unsigned int i = 0; i != song_n; ++i)
    {
        printf("%g\t%g\r\n", song[i][0], song[i][1]);
    }

    return 0;
}
