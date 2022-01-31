/*!
 @file a_notefreqs.h
 @brief Note frequency table
 @details
 The basic formula for the frequencies of the notes of the equal tempered scale is given by
 \f{aligned}{
 f_n = f_0 a^n
 \f}
 where \n
 \f$f_0\f$ = the frequency of one fixed note which must be defined.
 A common choice is setting the A above middle C (A4) at \f$f_0\f$ = 440 Hz. \n
 \f$n\f$ = the number of half steps away from the fixed note you are.
 If you are at a higher note, \f$n\f$ is positive. If you are on a lower note, \f$n\f$ is negative. \n
 \f$f_n\f$ = the frequency of the note \f$n\f$ half steps away. \n
 \f$a = 2^{\frac {1}{12}}\f$ = the twelth root of 2 =
 the number which when multiplied by itself 12 times equals 2 = 1.059463094359... \n
 \n
 The wavelength of the sound for the notes is found from
 \f[
 W_n = \cfrac {c} {f_n}
 \f]
 where \f$W\f$ is the wavelength and \f$c\f$ is the speed of sound.
 The speed of sound depends on temperature,
 but is approximately 345 m/s at "room temperature."
 http://pages.mtu.edu/~suits/notefreqs.html
 @copyright Copyright (C) 2020 tqfx. All rights reserved.
*/

/* Define to prevent recursive inclusion */
#ifndef __A_NOTEFREQS_H__
#define __A_NOTEFREQS_H__

#ifndef NOTEFREQS_PROPORT
#define NOTEFREQS_PROPORT 0
#endif /* NOTEFREQS_PROPORT */

#ifndef NOTEFREQS_TYPE
#define NOTEFREQS_TYPE unsigned int
#endif /* NOTEFREQS_TYPE */

#ifndef NOTEFREQS_MIDDLE_A4
#define NOTEFREQS_MIDDLE_A4 440
#endif /* NOTEFREQS_MIDDLE_A4 */

/*
 Speed of Sound = 345 m/s = 1130 ft/s = 770 miles/hr
 Note    Frequency (Hz)    Wavelength (cm)
*/
#if NOTEFREQS_MIDDLE_A4 == 432

#define NOTEFREQS_FREQ_C0  16.05   //!<  C0       16.05    2148.96
#define NOTEFREQS_FREQ_C_0 17.01   //!<  C#0      17.01    2028.35
#define NOTEFREQS_FREQ_Db0 17.01   //!<  Db0      17.01    2028.35
#define NOTEFREQS_FREQ_D0  18.02   //!<  D0       18.02    1914.50
#define NOTEFREQS_FREQ_D_0 19.09   //!<  D#0      19.09    1807.05
#define NOTEFREQS_FREQ_Eb0 19.09   //!<  Eb0      19.09    1807.05
#define NOTEFREQS_FREQ_E0  20.23   //!<  E0       20.23    1705.63
#define NOTEFREQS_FREQ_F0  21.43   //!<  F0       21.43    1609.90
#define NOTEFREQS_FREQ_F_0 22.70   //!<  F#0      22.70    1519.54
#define NOTEFREQS_FREQ_Gb0 22.70   //!<  Gb0      22.70    1519.54
#define NOTEFREQS_FREQ_G0  24.05   //!<  G0       24.05    1434.26
#define NOTEFREQS_FREQ_G_0 25.48   //!<  G#0      25.48    1353.76
#define NOTEFREQS_FREQ_Ab0 25.48   //!<  Ab0      25.48    1353.76
#define NOTEFREQS_FREQ_A0  27.00   //!<  A0       27.00    1277.78
#define NOTEFREQS_FREQ_A_0 28.61   //!<  A#0      28.61    1206.06
#define NOTEFREQS_FREQ_Bb0 28.61   //!<  Bb0      28.61    1206.06
#define NOTEFREQS_FREQ_B0  30.31   //!<  B0       30.31    1138.37
#define NOTEFREQS_FREQ_C1  32.11   //!<  C1       32.11    1074.48
#define NOTEFREQS_FREQ_C_1 34.02   //!<  C#1      34.02    1014.17
#define NOTEFREQS_FREQ_Db1 34.02   //!<  Db1      34.02    1014.17
#define NOTEFREQS_FREQ_D1  36.04   //!<  D1       36.04     957.25
#define NOTEFREQS_FREQ_D_1 38.18   //!<  D#1      38.18     903.53
#define NOTEFREQS_FREQ_Eb1 38.18   //!<  Eb1      38.18     903.53
#define NOTEFREQS_FREQ_E1  40.45   //!<  E1       40.45     852.81
#define NOTEFREQS_FREQ_F1  42.86   //!<  F1       42.86     804.95
#define NOTEFREQS_FREQ_F_1 45.41   //!<  F#1      45.41     759.77
#define NOTEFREQS_FREQ_Gb1 45.41   //!<  Gb1      45.41     759.77
#define NOTEFREQS_FREQ_G1  48.11   //!<  G1       48.11     717.13
#define NOTEFREQS_FREQ_G_1 50.97   //!<  G#1      50.97     676.88
#define NOTEFREQS_FREQ_Ab1 50.97   //!<  Ab1      50.97     676.88
#define NOTEFREQS_FREQ_A1  54.00   //!<  A1       54.00     638.89
#define NOTEFREQS_FREQ_A_1 57.21   //!<  A#1      57.21     603.03
#define NOTEFREQS_FREQ_Bb1 57.21   //!<  Bb1      57.21     603.03
#define NOTEFREQS_FREQ_B1  60.61   //!<  B1       60.61     569.19
#define NOTEFREQS_FREQ_C2  64.22   //!<  C2       64.22     537.24
#define NOTEFREQS_FREQ_C_2 68.04   //!<  C#2      68.04     507.09
#define NOTEFREQS_FREQ_Db2 68.04   //!<  Db2      68.04     507.09
#define NOTEFREQS_FREQ_D2  72.08   //!<  D2       72.08     478.63
#define NOTEFREQS_FREQ_D_2 76.37   //!<  D#2      76.37     451.76
#define NOTEFREQS_FREQ_Eb2 76.37   //!<  Eb2      76.37     451.76
#define NOTEFREQS_FREQ_E2  80.91   //!<  E2       80.91     426.41
#define NOTEFREQS_FREQ_F2  85.72   //!<  F2       85.72     402.47
#define NOTEFREQS_FREQ_F_2 90.82   //!<  F#2      90.82     379.89
#define NOTEFREQS_FREQ_Gb2 90.82   //!<  Gb2      90.82     379.89
#define NOTEFREQS_FREQ_G2  96.22   //!<  G2       96.22     358.56
#define NOTEFREQS_FREQ_G_2 101.94  //!<  G#2     101.94     338.44
#define NOTEFREQS_FREQ_Ab2 101.94  //!<  Ab2     101.94     338.44
#define NOTEFREQS_FREQ_A2  108.00  //!<  A2      108.00     319.44
#define NOTEFREQS_FREQ_A_2 114.42  //!<  A#2     114.42     301.52
#define NOTEFREQS_FREQ_Bb2 114.42  //!<  Bb2     114.42     301.52
#define NOTEFREQS_FREQ_B2  121.23  //!<  B2      121.23     284.59
#define NOTEFREQS_FREQ_C3  128.43  //!<  C3      128.43     268.62
#define NOTEFREQS_FREQ_C_3 136.07  //!<  C#3     136.07     253.54
#define NOTEFREQS_FREQ_Db3 136.07  //!<  Db3     136.07     253.54
#define NOTEFREQS_FREQ_D3  144.16  //!<  D3      144.16     239.31
#define NOTEFREQS_FREQ_D_3 152.74  //!<  D#3     152.74     225.88
#define NOTEFREQS_FREQ_Eb3 152.74  //!<  Eb3     152.74     225.88
#define NOTEFREQS_FREQ_E3  161.82  //!<  E3      161.82     213.20
#define NOTEFREQS_FREQ_F3  171.44  //!<  F3      171.44     201.24
#define NOTEFREQS_FREQ_F_3 181.63  //!<  F#3     181.63     189.94
#define NOTEFREQS_FREQ_Gb3 181.63  //!<  Gb3     181.63     189.94
#define NOTEFREQS_FREQ_G3  192.43  //!<  G3      192.43     179.28
#define NOTEFREQS_FREQ_G_3 203.88  //!<  G#3     203.88     169.22
#define NOTEFREQS_FREQ_Ab3 203.88  //!<  Ab3     203.88     169.22
#define NOTEFREQS_FREQ_A3  216.00  //!<  A3      216.00     159.72
#define NOTEFREQS_FREQ_A_3 228.84  //!<  A#3     228.84     150.76
#define NOTEFREQS_FREQ_Bb3 228.84  //!<  Bb3     228.84     150.76
#define NOTEFREQS_FREQ_B3  242.45  //!<  B3      242.45     142.30
#define NOTEFREQS_FREQ_C4  256.87  //!<  C4      256.87     134.31
#define NOTEFREQS_FREQ_C_4 272.14  //!<  C#4     272.14     126.77
#define NOTEFREQS_FREQ_Db4 272.14  //!<  Db4     272.14     126.77
#define NOTEFREQS_FREQ_D4  288.33  //!<  D4      288.33     119.66
#define NOTEFREQS_FREQ_D_4 305.47  //!<  D#4     305.47     112.94
#define NOTEFREQS_FREQ_Eb4 305.47  //!<  Eb4     305.47     112.94
#define NOTEFREQS_FREQ_E4  323.63  //!<  E4      323.63     106.60
#define NOTEFREQS_FREQ_F4  342.88  //!<  F4      342.88     100.62
#define NOTEFREQS_FREQ_F_4 363.27  //!<  F#4     363.27      94.97
#define NOTEFREQS_FREQ_Gb4 363.27  //!<  Gb4     363.27      94.97
#define NOTEFREQS_FREQ_G4  384.87  //!<  G4      384.87      89.64
#define NOTEFREQS_FREQ_G_4 407.75  //!<  G#4     407.75      84.61
#define NOTEFREQS_FREQ_Ab4 407.75  //!<  Ab4     407.75      84.61
#define NOTEFREQS_FREQ_A4  432.00  //!<  A4      432.00      79.86
#define NOTEFREQS_FREQ_A_4 457.69  //!<  A#4     457.69      75.38
#define NOTEFREQS_FREQ_Bb4 457.69  //!<  Bb4     457.69      75.38
#define NOTEFREQS_FREQ_B4  484.90  //!<  B4      484.90      71.15
#define NOTEFREQS_FREQ_C5  513.74  //!<  C5      513.74      67.15
#define NOTEFREQS_FREQ_C_5 544.29  //!<  C#5     544.29      63.39
#define NOTEFREQS_FREQ_Db5 544.29  //!<  Db5     544.29      63.39
#define NOTEFREQS_FREQ_D5  576.65  //!<  D5      576.65      59.83
#define NOTEFREQS_FREQ_D_5 610.94  //!<  D#5     610.94      56.47
#define NOTEFREQS_FREQ_Eb5 610.94  //!<  Eb5     610.94      56.47
#define NOTEFREQS_FREQ_E5  647.27  //!<  E5      647.27      53.30
#define NOTEFREQS_FREQ_F5  685.76  //!<  F5      685.76      50.31
#define NOTEFREQS_FREQ_F_5 726.53  //!<  F#5     726.53      47.49
#define NOTEFREQS_FREQ_Gb5 726.53  //!<  Gb5     726.53      47.49
#define NOTEFREQS_FREQ_G5  769.74  //!<  G5      769.74      44.82
#define NOTEFREQS_FREQ_G_5 815.51  //!<  G#5     815.51      42.30
#define NOTEFREQS_FREQ_Ab5 815.51  //!<  Ab5     815.51      42.30
#define NOTEFREQS_FREQ_A5  864.00  //!<  A5      864.00      39.93
#define NOTEFREQS_FREQ_A_5 915.38  //!<  A#5     915.38      37.69
#define NOTEFREQS_FREQ_Bb5 915.38  //!<  Bb5     915.38      37.69
#define NOTEFREQS_FREQ_B5  969.81  //!<  B5      969.81      35.57
#define NOTEFREQS_FREQ_C6  1027.47 //!<  C6     1027.47      33.58
#define NOTEFREQS_FREQ_C_6 1088.57 //!<  C#6    1088.57      31.69
#define NOTEFREQS_FREQ_Db6 1088.57 //!<  Db6    1088.57      31.69
#define NOTEFREQS_FREQ_D6  1153.30 //!<  D6     1153.30      29.91
#define NOTEFREQS_FREQ_D_6 1221.88 //!<  D#6    1221.88      28.24
#define NOTEFREQS_FREQ_Eb6 1221.88 //!<  Eb6    1221.88      28.24
#define NOTEFREQS_FREQ_E6  1294.54 //!<  E6     1294.54      26.65
#define NOTEFREQS_FREQ_F6  1371.51 //!<  F6     1371.51      25.15
#define NOTEFREQS_FREQ_F_6 1453.07 //!<  F#6    1453.07      23.74
#define NOTEFREQS_FREQ_Gb6 1453.07 //!<  Gb6    1453.07      23.74
#define NOTEFREQS_FREQ_G6  1539.47 //!<  G6     1539.47      22.41
#define NOTEFREQS_FREQ_G_6 1631.01 //!<  G#6    1631.01      21.15
#define NOTEFREQS_FREQ_Ab6 1631.01 //!<  Ab6    1631.01      21.15
#define NOTEFREQS_FREQ_A6  1728.00 //!<  A6     1728.00      19.97
#define NOTEFREQS_FREQ_A_6 1830.75 //!<  A#6    1830.75      18.84
#define NOTEFREQS_FREQ_Bb6 1830.75 //!<  Bb6    1830.75      18.84
#define NOTEFREQS_FREQ_B6  1939.61 //!<  B6     1939.61      17.79
#define NOTEFREQS_FREQ_C7  2054.95 //!<  C7     2054.95      16.79
#define NOTEFREQS_FREQ_C_7 2177.14 //!<  C#7    2177.14      15.85
#define NOTEFREQS_FREQ_Db7 2177.14 //!<  Db7    2177.14      15.85
#define NOTEFREQS_FREQ_D7  2306.60 //!<  D7     2306.60      14.96
#define NOTEFREQS_FREQ_D_7 2443.76 //!<  D#7    2443.76      14.12
#define NOTEFREQS_FREQ_Eb7 2443.76 //!<  Eb7    2443.76      14.12
#define NOTEFREQS_FREQ_E7  2589.07 //!<  E7     2589.07      13.33
#define NOTEFREQS_FREQ_F7  2743.03 //!<  F7     2743.03      12.58
#define NOTEFREQS_FREQ_F_7 2906.14 //!<  F#7    2906.14      11.87
#define NOTEFREQS_FREQ_Gb7 2906.14 //!<  Gb7    2906.14      11.87
#define NOTEFREQS_FREQ_G7  3078.95 //!<  G7     3078.95      11.21
#define NOTEFREQS_FREQ_G_7 3262.03 //!<  G#7    3262.03      10.58
#define NOTEFREQS_FREQ_Ab7 3262.03 //!<  Ab7    3262.03      10.58
#define NOTEFREQS_FREQ_A7  3456.00 //!<  A7     3456.00       9.98
#define NOTEFREQS_FREQ_A_7 3661.50 //!<  A#7    3661.50       9.42
#define NOTEFREQS_FREQ_Bb7 3661.50 //!<  Bb7    3661.50       9.42
#define NOTEFREQS_FREQ_B7  3879.23 //!<  B7     3879.23       8.89
#define NOTEFREQS_FREQ_C8  4109.90 //!<  C8     4109.90       8.39
#define NOTEFREQS_FREQ_C_8 4354.29 //!<  C#8    4354.29       7.92
#define NOTEFREQS_FREQ_Db8 4354.29 //!<  Db8    4354.29       7.92
#define NOTEFREQS_FREQ_D8  4613.21 //!<  D8     4613.21       7.48
#define NOTEFREQS_FREQ_D_8 4887.52 //!<  D#8    4887.52       7.06
#define NOTEFREQS_FREQ_Eb8 4887.52 //!<  Eb8    4887.52       7.06
#define NOTEFREQS_FREQ_E8  5178.15 //!<  E8     5178.15       6.66
#define NOTEFREQS_FREQ_F8  5486.06 //!<  F8     5486.06       6.29
#define NOTEFREQS_FREQ_F_8 5812.28 //!<  F#8    5812.28       5.94
#define NOTEFREQS_FREQ_Gb8 5812.28 //!<  Gb8    5812.28       5.94
#define NOTEFREQS_FREQ_G8  6157.89 //!<  G8     6157.89       5.60
#define NOTEFREQS_FREQ_G_8 6524.06 //!<  G#8    6524.06       5.29
#define NOTEFREQS_FREQ_Ab8 6524.06 //!<  Ab8    6524.06       5.29
#define NOTEFREQS_FREQ_A8  6912.00 //!<  A8     6912.00       4.99
#define NOTEFREQS_FREQ_A_8 7323.01 //!<  A#8    7323.01       4.71
#define NOTEFREQS_FREQ_Bb8 7323.01 //!<  Bb8    7323.01       4.71
#define NOTEFREQS_FREQ_B8  7758.46 //!<  B8     7758.46       4.45

#elif NOTEFREQS_MIDDLE_A4 == 434

#define NOTEFREQS_FREQ_C0  16.13   //!<  C0       16.13    2139.06
#define NOTEFREQS_FREQ_C_0 17.09   //!<  C#0      17.09    2019.00
#define NOTEFREQS_FREQ_Db0 17.09   //!<  Db0      17.09    2019.00
#define NOTEFREQS_FREQ_D0  18.10   //!<  D0       18.10    1905.68
#define NOTEFREQS_FREQ_D_0 19.18   //!<  D#0      19.18    1798.72
#define NOTEFREQS_FREQ_Eb0 19.18   //!<  Eb0      19.18    1798.72
#define NOTEFREQS_FREQ_E0  20.32   //!<  E0       20.32    1697.77
#define NOTEFREQS_FREQ_F0  21.53   //!<  F0       21.53    1602.48
#define NOTEFREQS_FREQ_F_0 22.81   //!<  F#0      22.81    1512.54
#define NOTEFREQS_FREQ_Gb0 22.81   //!<  Gb0      22.81    1512.54
#define NOTEFREQS_FREQ_G0  24.17   //!<  G0       24.17    1427.65
#define NOTEFREQS_FREQ_G_0 25.60   //!<  G#0      25.60    1347.52
#define NOTEFREQS_FREQ_Ab0 25.60   //!<  Ab0      25.60    1347.52
#define NOTEFREQS_FREQ_A0  27.12   //!<  A0       27.12    1271.89
#define NOTEFREQS_FREQ_A_0 28.74   //!<  A#0      28.74    1200.50
#define NOTEFREQS_FREQ_Bb0 28.74   //!<  Bb0      28.74    1200.50
#define NOTEFREQS_FREQ_B0  30.45   //!<  B0       30.45    1133.12
#define NOTEFREQS_FREQ_C1  32.26   //!<  C1       32.26    1069.53
#define NOTEFREQS_FREQ_C_1 34.18   //!<  C#1      34.18    1009.50
#define NOTEFREQS_FREQ_Db1 34.18   //!<  Db1      34.18    1009.50
#define NOTEFREQS_FREQ_D1  36.21   //!<  D1       36.21     952.84
#define NOTEFREQS_FREQ_D_1 38.36   //!<  D#1      38.36     899.36
#define NOTEFREQS_FREQ_Eb1 38.36   //!<  Eb1      38.36     899.36
#define NOTEFREQS_FREQ_E1  40.64   //!<  E1       40.64     848.88
#define NOTEFREQS_FREQ_F1  43.06   //!<  F1       43.06     801.24
#define NOTEFREQS_FREQ_F_1 45.62   //!<  F#1      45.62     756.27
#define NOTEFREQS_FREQ_Gb1 45.62   //!<  Gb1      45.62     756.27
#define NOTEFREQS_FREQ_G1  48.33   //!<  G1       48.33     713.82
#define NOTEFREQS_FREQ_G_1 51.21   //!<  G#1      51.21     673.76
#define NOTEFREQS_FREQ_Ab1 51.21   //!<  Ab1      51.21     673.76
#define NOTEFREQS_FREQ_A1  54.25   //!<  A1       54.25     635.94
#define NOTEFREQS_FREQ_A_1 57.48   //!<  A#1      57.48     600.25
#define NOTEFREQS_FREQ_Bb1 57.48   //!<  Bb1      57.48     600.25
#define NOTEFREQS_FREQ_B1  60.89   //!<  B1       60.89     566.56
#define NOTEFREQS_FREQ_C2  64.51   //!<  C2       64.51     534.76
#define NOTEFREQS_FREQ_C_2 68.35   //!<  C#2      68.35     504.75
#define NOTEFREQS_FREQ_Db2 68.35   //!<  Db2      68.35     504.75
#define NOTEFREQS_FREQ_D2  72.42   //!<  D2       72.42     476.42
#define NOTEFREQS_FREQ_D_2 76.72   //!<  D#2      76.72     449.68
#define NOTEFREQS_FREQ_Eb2 76.72   //!<  Eb2      76.72     449.68
#define NOTEFREQS_FREQ_E2  81.28   //!<  E2       81.28     424.44
#define NOTEFREQS_FREQ_F2  86.12   //!<  F2       86.12     400.62
#define NOTEFREQS_FREQ_F_2 91.24   //!<  F#2      91.24     378.14
#define NOTEFREQS_FREQ_Gb2 91.24   //!<  Gb2      91.24     378.14
#define NOTEFREQS_FREQ_G2  96.66   //!<  G2       96.66     356.91
#define NOTEFREQS_FREQ_G_2 102.41  //!<  G#2     102.41     336.88
#define NOTEFREQS_FREQ_Ab2 102.41  //!<  Ab2     102.41     336.88
#define NOTEFREQS_FREQ_A2  108.50  //!<  A2      108.50     317.97
#define NOTEFREQS_FREQ_A_2 114.95  //!<  A#2     114.95     300.13
#define NOTEFREQS_FREQ_Bb2 114.95  //!<  Bb2     114.95     300.13
#define NOTEFREQS_FREQ_B2  121.79  //!<  B2      121.79     283.28
#define NOTEFREQS_FREQ_C3  129.03  //!<  C3      129.03     267.38
#define NOTEFREQS_FREQ_C_3 136.70  //!<  C#3     136.70     252.37
#define NOTEFREQS_FREQ_Db3 136.70  //!<  Db3     136.70     252.37
#define NOTEFREQS_FREQ_D3  144.83  //!<  D3      144.83     238.21
#define NOTEFREQS_FREQ_D_3 153.44  //!<  D#3     153.44     224.84
#define NOTEFREQS_FREQ_Eb3 153.44  //!<  Eb3     153.44     224.84
#define NOTEFREQS_FREQ_E3  162.57  //!<  E3      162.57     212.22
#define NOTEFREQS_FREQ_F3  172.23  //!<  F3      172.23     200.31
#define NOTEFREQS_FREQ_F_3 182.47  //!<  F#3     182.47     189.07
#define NOTEFREQS_FREQ_Gb3 182.47  //!<  Gb3     182.47     189.07
#define NOTEFREQS_FREQ_G3  193.32  //!<  G3      193.32     178.46
#define NOTEFREQS_FREQ_G_3 204.82  //!<  G#3     204.82     168.44
#define NOTEFREQS_FREQ_Ab3 204.82  //!<  Ab3     204.82     168.44
#define NOTEFREQS_FREQ_A3  217.00  //!<  A3      217.00     158.99
#define NOTEFREQS_FREQ_A_3 229.90  //!<  A#3     229.90     150.06
#define NOTEFREQS_FREQ_Bb3 229.90  //!<  Bb3     229.90     150.06
#define NOTEFREQS_FREQ_B3  243.57  //!<  B3      243.57     141.64
#define NOTEFREQS_FREQ_C4  258.06  //!<  C4      258.06     133.69
#define NOTEFREQS_FREQ_C_4 273.40  //!<  C#4     273.40     126.19
#define NOTEFREQS_FREQ_Db4 273.40  //!<  Db4     273.40     126.19
#define NOTEFREQS_FREQ_D4  289.66  //!<  D4      289.66     119.11
#define NOTEFREQS_FREQ_D_4 306.88  //!<  D#4     306.88     112.42
#define NOTEFREQS_FREQ_Eb4 306.88  //!<  Eb4     306.88     112.42
#define NOTEFREQS_FREQ_E4  325.13  //!<  E4      325.13     106.11
#define NOTEFREQS_FREQ_F4  344.47  //!<  F4      344.47     100.16
#define NOTEFREQS_FREQ_F_4 364.95  //!<  F#4     364.95      94.53
#define NOTEFREQS_FREQ_Gb4 364.95  //!<  Gb4     364.95      94.53
#define NOTEFREQS_FREQ_G4  386.65  //!<  G4      386.65      89.23
#define NOTEFREQS_FREQ_G_4 409.64  //!<  G#4     409.64      84.22
#define NOTEFREQS_FREQ_Ab4 409.64  //!<  Ab4     409.64      84.22
#define NOTEFREQS_FREQ_A4  434.00  //!<  A4      434.00      79.49
#define NOTEFREQS_FREQ_A_4 459.81  //!<  A#4     459.81      75.03
#define NOTEFREQS_FREQ_Bb4 459.81  //!<  Bb4     459.81      75.03
#define NOTEFREQS_FREQ_B4  487.15  //!<  B4      487.15      70.82
#define NOTEFREQS_FREQ_C5  516.12  //!<  C5      516.12      66.85
#define NOTEFREQS_FREQ_C_5 546.81  //!<  C#5     546.81      63.09
#define NOTEFREQS_FREQ_Db5 546.81  //!<  Db5     546.81      63.09
#define NOTEFREQS_FREQ_D5  579.32  //!<  D5      579.32      59.55
#define NOTEFREQS_FREQ_D_5 613.77  //!<  D#5     613.77      56.21
#define NOTEFREQS_FREQ_Eb5 613.77  //!<  Eb5     613.77      56.21
#define NOTEFREQS_FREQ_E5  650.27  //!<  E5      650.27      53.06
#define NOTEFREQS_FREQ_F5  688.93  //!<  F5      688.93      50.08
#define NOTEFREQS_FREQ_F_5 729.90  //!<  F#5     729.90      47.27
#define NOTEFREQS_FREQ_Gb5 729.90  //!<  Gb5     729.90      47.27
#define NOTEFREQS_FREQ_G5  773.30  //!<  G5      773.30      44.61
#define NOTEFREQS_FREQ_G_5 819.28  //!<  G#5     819.28      42.11
#define NOTEFREQS_FREQ_Ab5 819.28  //!<  Ab5     819.28      42.11
#define NOTEFREQS_FREQ_A5  868.00  //!<  A5      868.00      39.75
#define NOTEFREQS_FREQ_A_5 919.61  //!<  A#5     919.61      37.52
#define NOTEFREQS_FREQ_Bb5 919.61  //!<  Bb5     919.61      37.52
#define NOTEFREQS_FREQ_B5  974.30  //!<  B5      974.30      35.41
#define NOTEFREQS_FREQ_C6  1032.23 //!<  C6     1032.23      33.42
#define NOTEFREQS_FREQ_C_6 1093.61 //!<  C#6    1093.61      31.55
#define NOTEFREQS_FREQ_Db6 1093.61 //!<  Db6    1093.61      31.55
#define NOTEFREQS_FREQ_D6  1158.64 //!<  D6     1158.64      29.78
#define NOTEFREQS_FREQ_D_6 1227.54 //!<  D#6    1227.54      28.11
#define NOTEFREQS_FREQ_Eb6 1227.54 //!<  Eb6    1227.54      28.11
#define NOTEFREQS_FREQ_E6  1300.53 //!<  E6     1300.53      26.53
#define NOTEFREQS_FREQ_F6  1377.86 //!<  F6     1377.86      25.04
#define NOTEFREQS_FREQ_F_6 1459.80 //!<  F#6    1459.80      23.63
#define NOTEFREQS_FREQ_Gb6 1459.80 //!<  Gb6    1459.80      23.63
#define NOTEFREQS_FREQ_G6  1546.60 //!<  G6     1546.60      22.31
#define NOTEFREQS_FREQ_G_6 1638.57 //!<  G#6    1638.57      21.05
#define NOTEFREQS_FREQ_Ab6 1638.57 //!<  Ab6    1638.57      21.05
#define NOTEFREQS_FREQ_A6  1736.00 //!<  A6     1736.00      19.87
#define NOTEFREQS_FREQ_A_6 1839.23 //!<  A#6    1839.23      18.76
#define NOTEFREQS_FREQ_Bb6 1839.23 //!<  Bb6    1839.23      18.76
#define NOTEFREQS_FREQ_B6  1948.59 //!<  B6     1948.59      17.71
#define NOTEFREQS_FREQ_C7  2064.46 //!<  C7     2064.46      16.71
#define NOTEFREQS_FREQ_C_7 2187.22 //!<  C#7    2187.22      15.77
#define NOTEFREQS_FREQ_Db7 2187.22 //!<  Db7    2187.22      15.77
#define NOTEFREQS_FREQ_D7  2317.28 //!<  D7     2317.28      14.89
#define NOTEFREQS_FREQ_D_7 2455.07 //!<  D#7    2455.07      14.05
#define NOTEFREQS_FREQ_Eb7 2455.07 //!<  Eb7    2455.07      14.05
#define NOTEFREQS_FREQ_E7  2601.06 //!<  E7     2601.06      13.26
#define NOTEFREQS_FREQ_F7  2755.73 //!<  F7     2755.73      12.52
#define NOTEFREQS_FREQ_F_7 2919.59 //!<  F#7    2919.59      11.82
#define NOTEFREQS_FREQ_Gb7 2919.59 //!<  Gb7    2919.59      11.82
#define NOTEFREQS_FREQ_G7  3093.20 //!<  G7     3093.20      11.15
#define NOTEFREQS_FREQ_G_7 3277.13 //!<  G#7    3277.13      10.53
#define NOTEFREQS_FREQ_Ab7 3277.13 //!<  Ab7    3277.13      10.53
#define NOTEFREQS_FREQ_A7  3472.00 //!<  A7     3472.00       9.94
#define NOTEFREQS_FREQ_A_7 3678.46 //!<  A#7    3678.46       9.38
#define NOTEFREQS_FREQ_Bb7 3678.46 //!<  Bb7    3678.46       9.38
#define NOTEFREQS_FREQ_B7  3897.19 //!<  B7     3897.19       8.85
#define NOTEFREQS_FREQ_C8  4128.93 //!<  C8     4128.93       8.36
#define NOTEFREQS_FREQ_C_8 4374.44 //!<  C#8    4374.44       7.89
#define NOTEFREQS_FREQ_Db8 4374.44 //!<  Db8    4374.44       7.89
#define NOTEFREQS_FREQ_D8  4634.56 //!<  D8     4634.56       7.44
#define NOTEFREQS_FREQ_D_8 4910.15 //!<  D#8    4910.15       7.03
#define NOTEFREQS_FREQ_Eb8 4910.15 //!<  Eb8    4910.15       7.03
#define NOTEFREQS_FREQ_E8  5202.12 //!<  E8     5202.12       6.63
#define NOTEFREQS_FREQ_F8  5511.46 //!<  F8     5511.46       6.26
#define NOTEFREQS_FREQ_F_8 5839.18 //!<  F#8    5839.18       5.91
#define NOTEFREQS_FREQ_Gb8 5839.18 //!<  Gb8    5839.18       5.91
#define NOTEFREQS_FREQ_G8  6186.40 //!<  G8     6186.40       5.58
#define NOTEFREQS_FREQ_G_8 6554.26 //!<  G#8    6554.26       5.26
#define NOTEFREQS_FREQ_Ab8 6554.26 //!<  Ab8    6554.26       5.26
#define NOTEFREQS_FREQ_A8  6944.00 //!<  A8     6944.00       4.97
#define NOTEFREQS_FREQ_A_8 7356.91 //!<  A#8    7356.91       4.69
#define NOTEFREQS_FREQ_Bb8 7356.91 //!<  Bb8    7356.91       4.69
#define NOTEFREQS_FREQ_B8  7794.38 //!<  B8     7794.38       4.43

#elif NOTEFREQS_MIDDLE_A4 == 436

#define NOTEFREQS_FREQ_C0  16.20   //!<  C0       16.20    2129.24
#define NOTEFREQS_FREQ_C_0 17.17   //!<  C#0      17.17    2009.74
#define NOTEFREQS_FREQ_Db0 17.17   //!<  Db0      17.17    2009.74
#define NOTEFREQS_FREQ_D0  18.19   //!<  D0       18.19    1896.94
#define NOTEFREQS_FREQ_D_0 19.27   //!<  D#0      19.27    1790.47
#define NOTEFREQS_FREQ_Eb0 19.27   //!<  Eb0      19.27    1790.47
#define NOTEFREQS_FREQ_E0  20.41   //!<  E0       20.41    1689.98
#define NOTEFREQS_FREQ_F0  21.63   //!<  F0       21.63    1595.13
#define NOTEFREQS_FREQ_F_0 22.91   //!<  F#0      22.91    1505.60
#define NOTEFREQS_FREQ_Gb0 22.91   //!<  Gb0      22.91    1505.60
#define NOTEFREQS_FREQ_G0  24.28   //!<  G0       24.28    1421.10
#define NOTEFREQS_FREQ_G_0 25.72   //!<  G#0      25.72    1341.34
#define NOTEFREQS_FREQ_Ab0 25.72   //!<  Ab0      25.72    1341.34
#define NOTEFREQS_FREQ_A0  27.25   //!<  A0       27.25    1266.06
#define NOTEFREQS_FREQ_A_0 28.87   //!<  A#0      28.87    1195.00
#define NOTEFREQS_FREQ_Bb0 28.87   //!<  Bb0      28.87    1195.00
#define NOTEFREQS_FREQ_B0  30.59   //!<  B0       30.59    1127.93
#define NOTEFREQS_FREQ_C1  32.41   //!<  C1       32.41    1064.62
#define NOTEFREQS_FREQ_C_1 34.33   //!<  C#1      34.33    1004.87
#define NOTEFREQS_FREQ_Db1 34.33   //!<  Db1      34.33    1004.87
#define NOTEFREQS_FREQ_D1  36.37   //!<  D1       36.37     948.47
#define NOTEFREQS_FREQ_D_1 38.54   //!<  D#1      38.54     895.24
#define NOTEFREQS_FREQ_Eb1 38.54   //!<  Eb1      38.54     895.24
#define NOTEFREQS_FREQ_E1  40.83   //!<  E1       40.83     844.99
#define NOTEFREQS_FREQ_F1  43.26   //!<  F1       43.26     797.56
#define NOTEFREQS_FREQ_F_1 45.83   //!<  F#1      45.83     752.80
#define NOTEFREQS_FREQ_Gb1 45.83   //!<  Gb1      45.83     752.80
#define NOTEFREQS_FREQ_G1  48.55   //!<  G1       48.55     710.55
#define NOTEFREQS_FREQ_G_1 51.44   //!<  G#1      51.44     670.67
#define NOTEFREQS_FREQ_Ab1 51.44   //!<  Ab1      51.44     670.67
#define NOTEFREQS_FREQ_A1  54.50   //!<  A1       54.50     633.03
#define NOTEFREQS_FREQ_A_1 57.74   //!<  A#1      57.74     597.50
#define NOTEFREQS_FREQ_Bb1 57.74   //!<  Bb1      57.74     597.50
#define NOTEFREQS_FREQ_B1  61.17   //!<  B1       61.17     563.96
#define NOTEFREQS_FREQ_C2  64.81   //!<  C2       64.81     532.31
#define NOTEFREQS_FREQ_C_2 68.67   //!<  C#2      68.67     502.43
#define NOTEFREQS_FREQ_Db2 68.67   //!<  Db2      68.67     502.43
#define NOTEFREQS_FREQ_D2  72.75   //!<  D2       72.75     474.23
#define NOTEFREQS_FREQ_D_2 77.07   //!<  D#2      77.07     447.62
#define NOTEFREQS_FREQ_Eb2 77.07   //!<  Eb2      77.07     447.62
#define NOTEFREQS_FREQ_E2  81.66   //!<  E2       81.66     422.50
#define NOTEFREQS_FREQ_F2  86.51   //!<  F2       86.51     398.78
#define NOTEFREQS_FREQ_F_2 91.66   //!<  F#2      91.66     376.40
#define NOTEFREQS_FREQ_Gb2 91.66   //!<  Gb2      91.66     376.40
#define NOTEFREQS_FREQ_G2  97.11   //!<  G2       97.11     355.27
#define NOTEFREQS_FREQ_G_2 102.88  //!<  G#2     102.88     335.33
#define NOTEFREQS_FREQ_Ab2 102.88  //!<  Ab2     102.88     335.33
#define NOTEFREQS_FREQ_A2  109.00  //!<  A2      109.00     316.51
#define NOTEFREQS_FREQ_A_2 115.48  //!<  A#2     115.48     298.75
#define NOTEFREQS_FREQ_Bb2 115.48  //!<  Bb2     115.48     298.75
#define NOTEFREQS_FREQ_B2  122.35  //!<  B2      122.35     281.98
#define NOTEFREQS_FREQ_C3  129.62  //!<  C3      129.62     266.16
#define NOTEFREQS_FREQ_C_3 137.33  //!<  C#3     137.33     251.22
#define NOTEFREQS_FREQ_Db3 137.33  //!<  Db3     137.33     251.22
#define NOTEFREQS_FREQ_D3  145.50  //!<  D3      145.50     237.12
#define NOTEFREQS_FREQ_D_3 154.15  //!<  D#3     154.15     223.81
#define NOTEFREQS_FREQ_Eb3 154.15  //!<  Eb3     154.15     223.81
#define NOTEFREQS_FREQ_E3  163.32  //!<  E3      163.32     211.25
#define NOTEFREQS_FREQ_F3  173.03  //!<  F3      173.03     199.39
#define NOTEFREQS_FREQ_F_3 183.32  //!<  F#3     183.32     188.20
#define NOTEFREQS_FREQ_Gb3 183.32  //!<  Gb3     183.32     188.20
#define NOTEFREQS_FREQ_G3  194.22  //!<  G3      194.22     177.64
#define NOTEFREQS_FREQ_G_3 205.76  //!<  G#3     205.76     167.67
#define NOTEFREQS_FREQ_Ab3 205.76  //!<  Ab3     205.76     167.67
#define NOTEFREQS_FREQ_A3  218.00  //!<  A3      218.00     158.26
#define NOTEFREQS_FREQ_A_3 230.96  //!<  A#3     230.96     149.37
#define NOTEFREQS_FREQ_Bb3 230.96  //!<  Bb3     230.96     149.37
#define NOTEFREQS_FREQ_B3  244.70  //!<  B3      244.70     140.99
#define NOTEFREQS_FREQ_C4  259.25  //!<  C4      259.25     133.08
#define NOTEFREQS_FREQ_C_4 274.66  //!<  C#4     274.66     125.61
#define NOTEFREQS_FREQ_Db4 274.66  //!<  Db4     274.66     125.61
#define NOTEFREQS_FREQ_D4  290.99  //!<  D4      290.99     118.56
#define NOTEFREQS_FREQ_D_4 308.30  //!<  D#4     308.30     111.90
#define NOTEFREQS_FREQ_Eb4 308.30  //!<  Eb4     308.30     111.90
#define NOTEFREQS_FREQ_E4  326.63  //!<  E4      326.63     105.62
#define NOTEFREQS_FREQ_F4  346.05  //!<  F4      346.05      99.70
#define NOTEFREQS_FREQ_F_4 366.63  //!<  F#4     366.63      94.10
#define NOTEFREQS_FREQ_Gb4 366.63  //!<  Gb4     366.63      94.10
#define NOTEFREQS_FREQ_G4  388.43  //!<  G4      388.43      88.82
#define NOTEFREQS_FREQ_G_4 411.53  //!<  G#4     411.53      83.83
#define NOTEFREQS_FREQ_Ab4 411.53  //!<  Ab4     411.53      83.83
#define NOTEFREQS_FREQ_A4  436.00  //!<  A4      436.00      79.13
#define NOTEFREQS_FREQ_A_4 461.93  //!<  A#4     461.93      74.69
#define NOTEFREQS_FREQ_Bb4 461.93  //!<  Bb4     461.93      74.69
#define NOTEFREQS_FREQ_B4  489.39  //!<  B4      489.39      70.50
#define NOTEFREQS_FREQ_C5  518.49  //!<  C5      518.49      66.54
#define NOTEFREQS_FREQ_C_5 549.33  //!<  C#5     549.33      62.80
#define NOTEFREQS_FREQ_Db5 549.33  //!<  Db5     549.33      62.80
#define NOTEFREQS_FREQ_D5  581.99  //!<  D5      581.99      59.28
#define NOTEFREQS_FREQ_D_5 616.60  //!<  D#5     616.60      55.95
#define NOTEFREQS_FREQ_Eb5 616.60  //!<  Eb5     616.60      55.95
#define NOTEFREQS_FREQ_E5  653.26  //!<  E5      653.26      52.81
#define NOTEFREQS_FREQ_F5  692.11  //!<  F5      692.11      49.85
#define NOTEFREQS_FREQ_F_5 733.26  //!<  F#5     733.26      47.05
#define NOTEFREQS_FREQ_Gb5 733.26  //!<  Gb5     733.26      47.05
#define NOTEFREQS_FREQ_G5  776.86  //!<  G5      776.86      44.41
#define NOTEFREQS_FREQ_G_5 823.06  //!<  G#5     823.06      41.92
#define NOTEFREQS_FREQ_Ab5 823.06  //!<  Ab5     823.06      41.92
#define NOTEFREQS_FREQ_A5  872.00  //!<  A5      872.00      39.56
#define NOTEFREQS_FREQ_A_5 923.85  //!<  A#5     923.85      37.34
#define NOTEFREQS_FREQ_Bb5 923.85  //!<  Bb5     923.85      37.34
#define NOTEFREQS_FREQ_B5  978.79  //!<  B5      978.79      35.25
#define NOTEFREQS_FREQ_C6  1036.99 //!<  C6     1036.99      33.27
#define NOTEFREQS_FREQ_C_6 1098.65 //!<  C#6    1098.65      31.40
#define NOTEFREQS_FREQ_Db6 1098.65 //!<  Db6    1098.65      31.40
#define NOTEFREQS_FREQ_D6  1163.98 //!<  D6     1163.98      29.64
#define NOTEFREQS_FREQ_D_6 1233.19 //!<  D#6    1233.19      27.98
#define NOTEFREQS_FREQ_Eb6 1233.19 //!<  Eb6    1233.19      27.98
#define NOTEFREQS_FREQ_E6  1306.52 //!<  E6     1306.52      26.41
#define NOTEFREQS_FREQ_F6  1384.21 //!<  F6     1384.21      24.92
#define NOTEFREQS_FREQ_F_6 1466.52 //!<  F#6    1466.52      23.53
#define NOTEFREQS_FREQ_Gb6 1466.52 //!<  Gb6    1466.52      23.53
#define NOTEFREQS_FREQ_G6  1553.73 //!<  G6     1553.73      22.20
#define NOTEFREQS_FREQ_G_6 1646.12 //!<  G#6    1646.12      20.96
#define NOTEFREQS_FREQ_Ab6 1646.12 //!<  Ab6    1646.12      20.96
#define NOTEFREQS_FREQ_A6  1744.00 //!<  A6     1744.00      19.78
#define NOTEFREQS_FREQ_A_6 1847.70 //!<  A#6    1847.70      18.67
#define NOTEFREQS_FREQ_Bb6 1847.70 //!<  Bb6    1847.70      18.67
#define NOTEFREQS_FREQ_B6  1957.57 //!<  B6     1957.57      17.62
#define NOTEFREQS_FREQ_C7  2073.98 //!<  C7     2073.98      16.63
#define NOTEFREQS_FREQ_C_7 2197.30 //!<  C#7    2197.30      15.70
#define NOTEFREQS_FREQ_Db7 2197.30 //!<  Db7    2197.30      15.70
#define NOTEFREQS_FREQ_D7  2327.96 //!<  D7     2327.96      14.82
#define NOTEFREQS_FREQ_D_7 2466.39 //!<  D#7    2466.39      13.99
#define NOTEFREQS_FREQ_Eb7 2466.39 //!<  Eb7    2466.39      13.99
#define NOTEFREQS_FREQ_E7  2613.05 //!<  E7     2613.05      13.20
#define NOTEFREQS_FREQ_F7  2768.43 //!<  F7     2768.43      12.46
#define NOTEFREQS_FREQ_F_7 2933.05 //!<  F#7    2933.05      11.76
#define NOTEFREQS_FREQ_Gb7 2933.05 //!<  Gb7    2933.05      11.76
#define NOTEFREQS_FREQ_G7  3107.45 //!<  G7     3107.45      11.10
#define NOTEFREQS_FREQ_G_7 3292.23 //!<  G#7    3292.23      10.48
#define NOTEFREQS_FREQ_Ab7 3292.23 //!<  Ab7    3292.23      10.48
#define NOTEFREQS_FREQ_A7  3488.00 //!<  A7     3488.00       9.89
#define NOTEFREQS_FREQ_A_7 3695.41 //!<  A#7    3695.41       9.34
#define NOTEFREQS_FREQ_Bb7 3695.41 //!<  Bb7    3695.41       9.34
#define NOTEFREQS_FREQ_B7  3915.15 //!<  B7     3915.15       8.81
#define NOTEFREQS_FREQ_C8  4147.95 //!<  C8     4147.95       8.32
#define NOTEFREQS_FREQ_C_8 4394.60 //!<  C#8    4394.60       7.85
#define NOTEFREQS_FREQ_Db8 4394.60 //!<  Db8    4394.60       7.85
#define NOTEFREQS_FREQ_D8  4655.92 //!<  D8     4655.92       7.41
#define NOTEFREQS_FREQ_D_8 4932.78 //!<  D#8    4932.78       6.99
#define NOTEFREQS_FREQ_Eb8 4932.78 //!<  Eb8    4932.78       6.99
#define NOTEFREQS_FREQ_E8  5226.09 //!<  E8     5226.09       6.60
#define NOTEFREQS_FREQ_F8  5536.85 //!<  F8     5536.85       6.23
#define NOTEFREQS_FREQ_F_8 5866.09 //!<  F#8    5866.09       5.88
#define NOTEFREQS_FREQ_Gb8 5866.09 //!<  Gb8    5866.09       5.88
#define NOTEFREQS_FREQ_G8  6214.91 //!<  G8     6214.91       5.55
#define NOTEFREQS_FREQ_G_8 6584.47 //!<  G#8    6584.47       5.24
#define NOTEFREQS_FREQ_Ab8 6584.47 //!<  Ab8    6584.47       5.24
#define NOTEFREQS_FREQ_A8  6976.00 //!<  A8     6976.00       4.95
#define NOTEFREQS_FREQ_A_8 7390.81 //!<  A#8    7390.81       4.67
#define NOTEFREQS_FREQ_Bb8 7390.81 //!<  Bb8    7390.81       4.67
#define NOTEFREQS_FREQ_B8  7830.30 //!<  B8     7830.30       4.41

#elif NOTEFREQS_MIDDLE_A4 == 438

#define NOTEFREQS_FREQ_C0  16.28   //!<  C0       16.28    2119.52
#define NOTEFREQS_FREQ_C_0 17.25   //!<  C#0      17.25    2000.56
#define NOTEFREQS_FREQ_Db0 17.25   //!<  Db0      17.25    2000.56
#define NOTEFREQS_FREQ_D0  18.27   //!<  D0       18.27    1888.28
#define NOTEFREQS_FREQ_D_0 19.36   //!<  D#0      19.36    1782.30
#define NOTEFREQS_FREQ_Eb0 19.36   //!<  Eb0      19.36    1782.30
#define NOTEFREQS_FREQ_E0  20.51   //!<  E0       20.51    1682.26
#define NOTEFREQS_FREQ_F0  21.73   //!<  F0       21.73    1587.85
#define NOTEFREQS_FREQ_F_0 23.02   //!<  F#0      23.02    1498.73
#define NOTEFREQS_FREQ_Gb0 23.02   //!<  Gb0      23.02    1498.73
#define NOTEFREQS_FREQ_G0  24.39   //!<  G0       24.39    1414.61
#define NOTEFREQS_FREQ_G_0 25.84   //!<  G#0      25.84    1335.21
#define NOTEFREQS_FREQ_Ab0 25.84   //!<  Ab0      25.84    1335.21
#define NOTEFREQS_FREQ_A0  27.38   //!<  A0       27.38    1260.27
#define NOTEFREQS_FREQ_A_0 29.00   //!<  A#0      29.00    1189.54
#define NOTEFREQS_FREQ_Bb0 29.00   //!<  Bb0      29.00    1189.54
#define NOTEFREQS_FREQ_B0  30.73   //!<  B0       30.73    1122.78
#define NOTEFREQS_FREQ_C1  32.55   //!<  C1       32.55    1059.76
#define NOTEFREQS_FREQ_C_1 34.49   //!<  C#1      34.49    1000.28
#define NOTEFREQS_FREQ_Db1 34.49   //!<  Db1      34.49    1000.28
#define NOTEFREQS_FREQ_D1  36.54   //!<  D1       36.54     944.14
#define NOTEFREQS_FREQ_D_1 38.71   //!<  D#1      38.71     891.15
#define NOTEFREQS_FREQ_Eb1 38.71   //!<  Eb1      38.71     891.15
#define NOTEFREQS_FREQ_E1  41.02   //!<  E1       41.02     841.13
#define NOTEFREQS_FREQ_F1  43.46   //!<  F1       43.46     793.92
#define NOTEFREQS_FREQ_F_1 46.04   //!<  F#1      46.04     749.36
#define NOTEFREQS_FREQ_Gb1 46.04   //!<  Gb1      46.04     749.36
#define NOTEFREQS_FREQ_G1  48.78   //!<  G1       48.78     707.30
#define NOTEFREQS_FREQ_G_1 51.68   //!<  G#1      51.68     667.61
#define NOTEFREQS_FREQ_Ab1 51.68   //!<  Ab1      51.68     667.61
#define NOTEFREQS_FREQ_A1  54.75   //!<  A1       54.75     630.14
#define NOTEFREQS_FREQ_A_1 58.01   //!<  A#1      58.01     594.77
#define NOTEFREQS_FREQ_Bb1 58.01   //!<  Bb1      58.01     594.77
#define NOTEFREQS_FREQ_B1  61.45   //!<  B1       61.45     561.39
#define NOTEFREQS_FREQ_C2  65.11   //!<  C2       65.11     529.88
#define NOTEFREQS_FREQ_C_2 68.98   //!<  C#2      68.98     500.14
#define NOTEFREQS_FREQ_Db2 68.98   //!<  Db2      68.98     500.14
#define NOTEFREQS_FREQ_D2  73.08   //!<  D2       73.08     472.07
#define NOTEFREQS_FREQ_D_2 77.43   //!<  D#2      77.43     445.57
#define NOTEFREQS_FREQ_Eb2 77.43   //!<  Eb2      77.43     445.57
#define NOTEFREQS_FREQ_E2  82.03   //!<  E2       82.03     420.57
#define NOTEFREQS_FREQ_F2  86.91   //!<  F2       86.91     396.96
#define NOTEFREQS_FREQ_F_2 92.08   //!<  F#2      92.08     374.68
#define NOTEFREQS_FREQ_Gb2 92.08   //!<  Gb2      92.08     374.68
#define NOTEFREQS_FREQ_G2  97.55   //!<  G2       97.55     353.65
#define NOTEFREQS_FREQ_G_2 103.35  //!<  G#2     103.35     333.80
#define NOTEFREQS_FREQ_Ab2 103.35  //!<  Ab2     103.35     333.80
#define NOTEFREQS_FREQ_A2  109.50  //!<  A2      109.50     315.07
#define NOTEFREQS_FREQ_A_2 116.01  //!<  A#2     116.01     297.39
#define NOTEFREQS_FREQ_Bb2 116.01  //!<  Bb2     116.01     297.39
#define NOTEFREQS_FREQ_B2  122.91  //!<  B2      122.91     280.69
#define NOTEFREQS_FREQ_C3  130.22  //!<  C3      130.22     264.94
#define NOTEFREQS_FREQ_C_3 137.96  //!<  C#3     137.96     250.07
#define NOTEFREQS_FREQ_Db3 137.96  //!<  Db3     137.96     250.07
#define NOTEFREQS_FREQ_D3  146.16  //!<  D3      146.16     236.03
#define NOTEFREQS_FREQ_D_3 154.86  //!<  D#3     154.86     222.79
#define NOTEFREQS_FREQ_Eb3 154.86  //!<  Eb3     154.86     222.79
#define NOTEFREQS_FREQ_E3  164.06  //!<  E3      164.06     210.28
#define NOTEFREQS_FREQ_F3  173.82  //!<  F3      173.82     198.48
#define NOTEFREQS_FREQ_F_3 184.16  //!<  F#3     184.16     187.34
#define NOTEFREQS_FREQ_Gb3 184.16  //!<  Gb3     184.16     187.34
#define NOTEFREQS_FREQ_G3  195.11  //!<  G3      195.11     176.83
#define NOTEFREQS_FREQ_G_3 206.71  //!<  G#3     206.71     166.90
#define NOTEFREQS_FREQ_Ab3 206.71  //!<  Ab3     206.71     166.90
#define NOTEFREQS_FREQ_A3  219.00  //!<  A3      219.00     157.53
#define NOTEFREQS_FREQ_A_3 232.02  //!<  A#3     232.02     148.69
#define NOTEFREQS_FREQ_Bb3 232.02  //!<  Bb3     232.02     148.69
#define NOTEFREQS_FREQ_B3  245.82  //!<  B3      245.82     140.35
#define NOTEFREQS_FREQ_C4  260.44  //!<  C4      260.44     132.47
#define NOTEFREQS_FREQ_C_4 275.92  //!<  C#4     275.92     125.04
#define NOTEFREQS_FREQ_Db4 275.92  //!<  Db4     275.92     125.04
#define NOTEFREQS_FREQ_D4  292.33  //!<  D4      292.33     118.02
#define NOTEFREQS_FREQ_D_4 309.71  //!<  D#4     309.71     111.39
#define NOTEFREQS_FREQ_Eb4 309.71  //!<  Eb4     309.71     111.39
#define NOTEFREQS_FREQ_E4  328.13  //!<  E4      328.13     105.14
#define NOTEFREQS_FREQ_F4  347.64  //!<  F4      347.64      99.24
#define NOTEFREQS_FREQ_F_4 368.31  //!<  F#4     368.31      93.67
#define NOTEFREQS_FREQ_Gb4 368.31  //!<  Gb4     368.31      93.67
#define NOTEFREQS_FREQ_G4  390.21  //!<  G4      390.21      88.41
#define NOTEFREQS_FREQ_G_4 413.42  //!<  G#4     413.42      83.45
#define NOTEFREQS_FREQ_Ab4 413.42  //!<  Ab4     413.42      83.45
#define NOTEFREQS_FREQ_A4  438.00  //!<  A4      438.00      78.77
#define NOTEFREQS_FREQ_A_4 464.04  //!<  A#4     464.04      74.35
#define NOTEFREQS_FREQ_Bb4 464.04  //!<  Bb4     464.04      74.35
#define NOTEFREQS_FREQ_B4  491.64  //!<  B4      491.64      70.17
#define NOTEFREQS_FREQ_C5  520.87  //!<  C5      520.87      66.24
#define NOTEFREQS_FREQ_C_5 551.85  //!<  C#5     551.85      62.52
#define NOTEFREQS_FREQ_Db5 551.85  //!<  Db5     551.85      62.52
#define NOTEFREQS_FREQ_D5  584.66  //!<  D5      584.66      59.01
#define NOTEFREQS_FREQ_D_5 619.43  //!<  D#5     619.43      55.70
#define NOTEFREQS_FREQ_Eb5 619.43  //!<  Eb5     619.43      55.70
#define NOTEFREQS_FREQ_E5  656.26  //!<  E5      656.26      52.57
#define NOTEFREQS_FREQ_F5  695.28  //!<  F5      695.28      49.62
#define NOTEFREQS_FREQ_F_5 736.63  //!<  F#5     736.63      46.84
#define NOTEFREQS_FREQ_Gb5 736.63  //!<  Gb5     736.63      46.84
#define NOTEFREQS_FREQ_G5  780.43  //!<  G5      780.43      44.21
#define NOTEFREQS_FREQ_G_5 826.83  //!<  G#5     826.83      41.73
#define NOTEFREQS_FREQ_Ab5 826.83  //!<  Ab5     826.83      41.73
#define NOTEFREQS_FREQ_A5  876.00  //!<  A5      876.00      39.38
#define NOTEFREQS_FREQ_A_5 928.09  //!<  A#5     928.09      37.17
#define NOTEFREQS_FREQ_Bb5 928.09  //!<  Bb5     928.09      37.17
#define NOTEFREQS_FREQ_B5  983.28  //!<  B5      983.28      35.09
#define NOTEFREQS_FREQ_C6  1041.74 //!<  C6     1041.74      33.12
#define NOTEFREQS_FREQ_C_6 1103.69 //!<  C#6    1103.69      31.26
#define NOTEFREQS_FREQ_Db6 1103.69 //!<  Db6    1103.69      31.26
#define NOTEFREQS_FREQ_D6  1169.32 //!<  D6     1169.32      29.50
#define NOTEFREQS_FREQ_D_6 1238.85 //!<  D#6    1238.85      27.85
#define NOTEFREQS_FREQ_Eb6 1238.85 //!<  Eb6    1238.85      27.85
#define NOTEFREQS_FREQ_E6  1312.52 //!<  E6     1312.52      26.29
#define NOTEFREQS_FREQ_F6  1390.56 //!<  F6     1390.56      24.81
#define NOTEFREQS_FREQ_F_6 1473.25 //!<  F#6    1473.25      23.42
#define NOTEFREQS_FREQ_Gb6 1473.25 //!<  Gb6    1473.25      23.42
#define NOTEFREQS_FREQ_G6  1560.85 //!<  G6     1560.85      22.10
#define NOTEFREQS_FREQ_G_6 1653.67 //!<  G#6    1653.67      20.86
#define NOTEFREQS_FREQ_Ab6 1653.67 //!<  Ab6    1653.67      20.86
#define NOTEFREQS_FREQ_A6  1752.00 //!<  A6     1752.00      19.69
#define NOTEFREQS_FREQ_A_6 1856.18 //!<  A#6    1856.18      18.59
#define NOTEFREQS_FREQ_Bb6 1856.18 //!<  Bb6    1856.18      18.59
#define NOTEFREQS_FREQ_B6  1966.55 //!<  B6     1966.55      17.54
#define NOTEFREQS_FREQ_C7  2083.49 //!<  C7     2083.49      16.56
#define NOTEFREQS_FREQ_C_7 2207.38 //!<  C#7    2207.38      15.63
#define NOTEFREQS_FREQ_Db7 2207.38 //!<  Db7    2207.38      15.63
#define NOTEFREQS_FREQ_D7  2338.64 //!<  D7     2338.64      14.75
#define NOTEFREQS_FREQ_D_7 2477.70 //!<  D#7    2477.70      13.92
#define NOTEFREQS_FREQ_Eb7 2477.70 //!<  Eb7    2477.70      13.92
#define NOTEFREQS_FREQ_E7  2625.03 //!<  E7     2625.03      13.14
#define NOTEFREQS_FREQ_F7  2781.13 //!<  F7     2781.13      12.41
#define NOTEFREQS_FREQ_F_7 2946.50 //!<  F#7    2946.50      11.71
#define NOTEFREQS_FREQ_Gb7 2946.50 //!<  Gb7    2946.50      11.71
#define NOTEFREQS_FREQ_G7  3121.71 //!<  G7     3121.71      11.05
#define NOTEFREQS_FREQ_G_7 3307.34 //!<  G#7    3307.34      10.43
#define NOTEFREQS_FREQ_Ab7 3307.34 //!<  Ab7    3307.34      10.43
#define NOTEFREQS_FREQ_A7  3504.00 //!<  A7     3504.00       9.85
#define NOTEFREQS_FREQ_A_7 3712.36 //!<  A#7    3712.36       9.29
#define NOTEFREQS_FREQ_Bb7 3712.36 //!<  Bb7    3712.36       9.29
#define NOTEFREQS_FREQ_B7  3933.11 //!<  B7     3933.11       8.77
#define NOTEFREQS_FREQ_C8  4166.98 //!<  C8     4166.98       8.28
#define NOTEFREQS_FREQ_C_8 4414.76 //!<  C#8    4414.76       7.81
#define NOTEFREQS_FREQ_Db8 4414.76 //!<  Db8    4414.76       7.81
#define NOTEFREQS_FREQ_D8  4677.28 //!<  D8     4677.28       7.38
#define NOTEFREQS_FREQ_D_8 4955.40 //!<  D#8    4955.40       6.96
#define NOTEFREQS_FREQ_Eb8 4955.40 //!<  Eb8    4955.40       6.96
#define NOTEFREQS_FREQ_E8  5250.07 //!<  E8     5250.07       6.57
#define NOTEFREQS_FREQ_F8  5562.25 //!<  F8     5562.25       6.20
#define NOTEFREQS_FREQ_F_8 5893.00 //!<  F#8    5893.00       5.85
#define NOTEFREQS_FREQ_Gb8 5893.00 //!<  Gb8    5893.00       5.85
#define NOTEFREQS_FREQ_G8  6243.42 //!<  G8     6243.42       5.53
#define NOTEFREQS_FREQ_G_8 6614.67 //!<  G#8    6614.67       5.22
#define NOTEFREQS_FREQ_Ab8 6614.67 //!<  Ab8    6614.67       5.22
#define NOTEFREQS_FREQ_A8  7008.00 //!<  A8     7008.00       4.92
#define NOTEFREQS_FREQ_A_8 7424.72 //!<  A#8    7424.72       4.65
#define NOTEFREQS_FREQ_Bb8 7424.72 //!<  Bb8    7424.72       4.65
#define NOTEFREQS_FREQ_B8  7866.21 //!<  B8     7866.21       4.39

#elif NOTEFREQS_MIDDLE_A4 == 440

#define NOTEFREQS_FREQ_C0  16.35   //!<  C0       16.35    2109.89
#define NOTEFREQS_FREQ_C_0 17.32   //!<  C#0      17.32    1991.47
#define NOTEFREQS_FREQ_Db0 17.32   //!<  Db0      17.32    1991.47
#define NOTEFREQS_FREQ_D0  18.35   //!<  D0       18.35    1879.69
#define NOTEFREQS_FREQ_D_0 19.45   //!<  D#0      19.45    1774.20
#define NOTEFREQS_FREQ_Eb0 19.45   //!<  Eb0      19.45    1774.20
#define NOTEFREQS_FREQ_E0  20.60   //!<  E0       20.60    1674.62
#define NOTEFREQS_FREQ_F0  21.83   //!<  F0       21.83    1580.63
#define NOTEFREQS_FREQ_F_0 23.12   //!<  F#0      23.12    1491.91
#define NOTEFREQS_FREQ_Gb0 23.12   //!<  Gb0      23.12    1491.91
#define NOTEFREQS_FREQ_G0  24.50   //!<  G0       24.50    1408.18
#define NOTEFREQS_FREQ_G_0 25.96   //!<  G#0      25.96    1329.14
#define NOTEFREQS_FREQ_Ab0 25.96   //!<  Ab0      25.96    1329.14
#define NOTEFREQS_FREQ_A0  27.50   //!<  A0       27.50    1254.55
#define NOTEFREQS_FREQ_A_0 29.14   //!<  A#0      29.14    1184.13
#define NOTEFREQS_FREQ_Bb0 29.14   //!<  Bb0      29.14    1184.13
#define NOTEFREQS_FREQ_B0  30.87   //!<  B0       30.87    1117.67
#define NOTEFREQS_FREQ_C1  32.70   //!<  C1       32.70    1054.94
#define NOTEFREQS_FREQ_C_1 34.65   //!<  C#1      34.65     995.73
#define NOTEFREQS_FREQ_Db1 34.65   //!<  Db1      34.65     995.73
#define NOTEFREQS_FREQ_D1  36.71   //!<  D1       36.71     939.85
#define NOTEFREQS_FREQ_D_1 38.89   //!<  D#1      38.89     887.10
#define NOTEFREQS_FREQ_Eb1 38.89   //!<  Eb1      38.89     887.10
#define NOTEFREQS_FREQ_E1  41.20   //!<  E1       41.20     837.31
#define NOTEFREQS_FREQ_F1  43.65   //!<  F1       43.65     790.31
#define NOTEFREQS_FREQ_F_1 46.25   //!<  F#1      46.25     745.96
#define NOTEFREQS_FREQ_Gb1 46.25   //!<  Gb1      46.25     745.96
#define NOTEFREQS_FREQ_G1  49.00   //!<  G1       49.00     704.09
#define NOTEFREQS_FREQ_G_1 51.91   //!<  G#1      51.91     664.57
#define NOTEFREQS_FREQ_Ab1 51.91   //!<  Ab1      51.91     664.57
#define NOTEFREQS_FREQ_A1  55.00   //!<  A1       55.00     627.27
#define NOTEFREQS_FREQ_A_1 58.27   //!<  A#1      58.27     592.07
#define NOTEFREQS_FREQ_Bb1 58.27   //!<  Bb1      58.27     592.07
#define NOTEFREQS_FREQ_B1  61.74   //!<  B1       61.74     558.84
#define NOTEFREQS_FREQ_C2  65.41   //!<  C2       65.41     527.47
#define NOTEFREQS_FREQ_C_2 69.30   //!<  C#2      69.30     497.87
#define NOTEFREQS_FREQ_Db2 69.30   //!<  Db2      69.30     497.87
#define NOTEFREQS_FREQ_D2  73.42   //!<  D2       73.42     469.92
#define NOTEFREQS_FREQ_D_2 77.78   //!<  D#2      77.78     443.55
#define NOTEFREQS_FREQ_Eb2 77.78   //!<  Eb2      77.78     443.55
#define NOTEFREQS_FREQ_E2  82.41   //!<  E2       82.41     418.65
#define NOTEFREQS_FREQ_F2  87.31   //!<  F2       87.31     395.16
#define NOTEFREQS_FREQ_F_2 92.50   //!<  F#2      92.50     372.98
#define NOTEFREQS_FREQ_Gb2 92.50   //!<  Gb2      92.50     372.98
#define NOTEFREQS_FREQ_G2  98.00   //!<  G2       98.00     352.04
#define NOTEFREQS_FREQ_G_2 103.83  //!<  G#2     103.83     332.29
#define NOTEFREQS_FREQ_Ab2 103.83  //!<  Ab2     103.83     332.29
#define NOTEFREQS_FREQ_A2  110.00  //!<  A2      110.00     313.64
#define NOTEFREQS_FREQ_A_2 116.54  //!<  A#2     116.54     296.03
#define NOTEFREQS_FREQ_Bb2 116.54  //!<  Bb2     116.54     296.03
#define NOTEFREQS_FREQ_B2  123.47  //!<  B2      123.47     279.42
#define NOTEFREQS_FREQ_C3  130.81  //!<  C3      130.81     263.74
#define NOTEFREQS_FREQ_C_3 138.59  //!<  C#3     138.59     248.93
#define NOTEFREQS_FREQ_Db3 138.59  //!<  Db3     138.59     248.93
#define NOTEFREQS_FREQ_D3  146.83  //!<  D3      146.83     234.96
#define NOTEFREQS_FREQ_D_3 155.56  //!<  D#3     155.56     221.77
#define NOTEFREQS_FREQ_Eb3 155.56  //!<  Eb3     155.56     221.77
#define NOTEFREQS_FREQ_E3  164.81  //!<  E3      164.81     209.33
#define NOTEFREQS_FREQ_F3  174.61  //!<  F3      174.61     197.58
#define NOTEFREQS_FREQ_F_3 185.00  //!<  F#3     185.00     186.49
#define NOTEFREQS_FREQ_Gb3 185.00  //!<  Gb3     185.00     186.49
#define NOTEFREQS_FREQ_G3  196.00  //!<  G3      196.00     176.02
#define NOTEFREQS_FREQ_G_3 207.65  //!<  G#3     207.65     166.14
#define NOTEFREQS_FREQ_Ab3 207.65  //!<  Ab3     207.65     166.14
#define NOTEFREQS_FREQ_A3  220.00  //!<  A3      220.00     156.82
#define NOTEFREQS_FREQ_A_3 233.08  //!<  A#3     233.08     148.02
#define NOTEFREQS_FREQ_Bb3 233.08  //!<  Bb3     233.08     148.02
#define NOTEFREQS_FREQ_B3  246.94  //!<  B3      246.94     139.71
#define NOTEFREQS_FREQ_C4  261.63  //!<  C4      261.63     131.87
#define NOTEFREQS_FREQ_C_4 277.18  //!<  C#4     277.18     124.47
#define NOTEFREQS_FREQ_Db4 277.18  //!<  Db4     277.18     124.47
#define NOTEFREQS_FREQ_D4  293.66  //!<  D4      293.66     117.48
#define NOTEFREQS_FREQ_D_4 311.13  //!<  D#4     311.13     110.89
#define NOTEFREQS_FREQ_Eb4 311.13  //!<  Eb4     311.13     110.89
#define NOTEFREQS_FREQ_E4  329.63  //!<  E4      329.63     104.66
#define NOTEFREQS_FREQ_F4  349.23  //!<  F4      349.23      98.79
#define NOTEFREQS_FREQ_F_4 369.99  //!<  F#4     369.99      93.24
#define NOTEFREQS_FREQ_Gb4 369.99  //!<  Gb4     369.99      93.24
#define NOTEFREQS_FREQ_G4  392.00  //!<  G4      392.00      88.01
#define NOTEFREQS_FREQ_G_4 415.30  //!<  G#4     415.30      83.07
#define NOTEFREQS_FREQ_Ab4 415.30  //!<  Ab4     415.30      83.07
#define NOTEFREQS_FREQ_A4  440.00  //!<  A4      440.00      78.41
#define NOTEFREQS_FREQ_A_4 466.16  //!<  A#4     466.16      74.01
#define NOTEFREQS_FREQ_Bb4 466.16  //!<  Bb4     466.16      74.01
#define NOTEFREQS_FREQ_B4  493.88  //!<  B4      493.88      69.85
#define NOTEFREQS_FREQ_C5  523.25  //!<  C5      523.25      65.93
#define NOTEFREQS_FREQ_C_5 554.37  //!<  C#5     554.37      62.23
#define NOTEFREQS_FREQ_Db5 554.37  //!<  Db5     554.37      62.23
#define NOTEFREQS_FREQ_D5  587.33  //!<  D5      587.33      58.74
#define NOTEFREQS_FREQ_D_5 622.25  //!<  D#5     622.25      55.44
#define NOTEFREQS_FREQ_Eb5 622.25  //!<  Eb5     622.25      55.44
#define NOTEFREQS_FREQ_E5  659.25  //!<  E5      659.25      52.33
#define NOTEFREQS_FREQ_F5  698.46  //!<  F5      698.46      49.39
#define NOTEFREQS_FREQ_F_5 739.99  //!<  F#5     739.99      46.62
#define NOTEFREQS_FREQ_Gb5 739.99  //!<  Gb5     739.99      46.62
#define NOTEFREQS_FREQ_G5  783.99  //!<  G5      783.99      44.01
#define NOTEFREQS_FREQ_G_5 830.61  //!<  G#5     830.61      41.54
#define NOTEFREQS_FREQ_Ab5 830.61  //!<  Ab5     830.61      41.54
#define NOTEFREQS_FREQ_A5  880.00  //!<  A5      880.00      39.20
#define NOTEFREQS_FREQ_A_5 932.33  //!<  A#5     932.33      37.00
#define NOTEFREQS_FREQ_Bb5 932.33  //!<  Bb5     932.33      37.00
#define NOTEFREQS_FREQ_B5  987.77  //!<  B5      987.77      34.93
#define NOTEFREQS_FREQ_C6  1046.50 //!<  C6     1046.50      32.97
#define NOTEFREQS_FREQ_C_6 1108.73 //!<  C#6    1108.73      31.12
#define NOTEFREQS_FREQ_Db6 1108.73 //!<  Db6    1108.73      31.12
#define NOTEFREQS_FREQ_D6  1174.66 //!<  D6     1174.66      29.37
#define NOTEFREQS_FREQ_D_6 1244.51 //!<  D#6    1244.51      27.72
#define NOTEFREQS_FREQ_Eb6 1244.51 //!<  Eb6    1244.51      27.72
#define NOTEFREQS_FREQ_E6  1318.51 //!<  E6     1318.51      26.17
#define NOTEFREQS_FREQ_F6  1396.91 //!<  F6     1396.91      24.70
#define NOTEFREQS_FREQ_F_6 1479.98 //!<  F#6    1479.98      23.31
#define NOTEFREQS_FREQ_Gb6 1479.98 //!<  Gb6    1479.98      23.31
#define NOTEFREQS_FREQ_G6  1567.98 //!<  G6     1567.98      22.00
#define NOTEFREQS_FREQ_G_6 1661.22 //!<  G#6    1661.22      20.77
#define NOTEFREQS_FREQ_Ab6 1661.22 //!<  Ab6    1661.22      20.77
#define NOTEFREQS_FREQ_A6  1760.00 //!<  A6     1760.00      19.60
#define NOTEFREQS_FREQ_A_6 1864.66 //!<  A#6    1864.66      18.50
#define NOTEFREQS_FREQ_Bb6 1864.66 //!<  Bb6    1864.66      18.50
#define NOTEFREQS_FREQ_B6  1975.53 //!<  B6     1975.53      17.46
#define NOTEFREQS_FREQ_C7  2093.00 //!<  C7     2093.00      16.48
#define NOTEFREQS_FREQ_C_7 2217.46 //!<  C#7    2217.46      15.56
#define NOTEFREQS_FREQ_Db7 2217.46 //!<  Db7    2217.46      15.56
#define NOTEFREQS_FREQ_D7  2349.32 //!<  D7     2349.32      14.69
#define NOTEFREQS_FREQ_D_7 2489.02 //!<  D#7    2489.02      13.86
#define NOTEFREQS_FREQ_Eb7 2489.02 //!<  Eb7    2489.02      13.86
#define NOTEFREQS_FREQ_E7  2637.02 //!<  E7     2637.02      13.08
#define NOTEFREQS_FREQ_F7  2793.83 //!<  F7     2793.83      12.35
#define NOTEFREQS_FREQ_F_7 2959.96 //!<  F#7    2959.96      11.66
#define NOTEFREQS_FREQ_Gb7 2959.96 //!<  Gb7    2959.96      11.66
#define NOTEFREQS_FREQ_G7  3135.96 //!<  G7     3135.96      11.00
#define NOTEFREQS_FREQ_G_7 3322.44 //!<  G#7    3322.44      10.38
#define NOTEFREQS_FREQ_Ab7 3322.44 //!<  Ab7    3322.44      10.38
#define NOTEFREQS_FREQ_A7  3520.00 //!<  A7     3520.00       9.80
#define NOTEFREQS_FREQ_A_7 3729.31 //!<  A#7    3729.31       9.25
#define NOTEFREQS_FREQ_Bb7 3729.31 //!<  Bb7    3729.31       9.25
#define NOTEFREQS_FREQ_B7  3951.07 //!<  B7     3951.07       8.73
#define NOTEFREQS_FREQ_C8  4186.01 //!<  C8     4186.01       8.24
#define NOTEFREQS_FREQ_C_8 4434.92 //!<  C#8    4434.92       7.78
#define NOTEFREQS_FREQ_Db8 4434.92 //!<  Db8    4434.92       7.78
#define NOTEFREQS_FREQ_D8  4698.63 //!<  D8     4698.63       7.34
#define NOTEFREQS_FREQ_D_8 4978.03 //!<  D#8    4978.03       6.93
#define NOTEFREQS_FREQ_Eb8 4978.03 //!<  Eb8    4978.03       6.93
#define NOTEFREQS_FREQ_E8  5274.04 //!<  E8     5274.04       6.54
#define NOTEFREQS_FREQ_F8  5587.65 //!<  F8     5587.65       6.17
#define NOTEFREQS_FREQ_F_8 5919.91 //!<  F#8    5919.91       5.83
#define NOTEFREQS_FREQ_Gb8 5919.91 //!<  Gb8    5919.91       5.83
#define NOTEFREQS_FREQ_G8  6271.93 //!<  G8     6271.93       5.50
#define NOTEFREQS_FREQ_G_8 6644.88 //!<  G#8    6644.88       5.19
#define NOTEFREQS_FREQ_Ab8 6644.88 //!<  Ab8    6644.88       5.19
#define NOTEFREQS_FREQ_A8  7040.00 //!<  A8     7040.00       4.90
#define NOTEFREQS_FREQ_A_8 7458.62 //!<  A#8    7458.62       4.63
#define NOTEFREQS_FREQ_Bb8 7458.62 //!<  Bb8    7458.62       4.63
#define NOTEFREQS_FREQ_B8  7902.13 //!<  B8     7902.13       4.37

#elif NOTEFREQS_MIDDLE_A4 == 442

#define NOTEFREQS_FREQ_C0  16.43   //!<  C0       16.43    2100.34
#define NOTEFREQS_FREQ_C_0 17.40   //!<  C#0      17.40    1982.46
#define NOTEFREQS_FREQ_Db0 17.40   //!<  Db0      17.40    1982.46
#define NOTEFREQS_FREQ_D0  18.44   //!<  D0       18.44    1871.19
#define NOTEFREQS_FREQ_D_0 19.53   //!<  D#0      19.53    1766.17
#define NOTEFREQS_FREQ_Eb0 19.53   //!<  Eb0      19.53    1766.17
#define NOTEFREQS_FREQ_E0  20.70   //!<  E0       20.70    1667.04
#define NOTEFREQS_FREQ_F0  21.93   //!<  F0       21.93    1573.48
#define NOTEFREQS_FREQ_F_0 23.23   //!<  F#0      23.23    1485.16
#define NOTEFREQS_FREQ_Gb0 23.23   //!<  Gb0      23.23    1485.16
#define NOTEFREQS_FREQ_G0  24.61   //!<  G0       24.61    1401.81
#define NOTEFREQS_FREQ_G_0 26.07   //!<  G#0      26.07    1323.13
#define NOTEFREQS_FREQ_Ab0 26.07   //!<  Ab0      26.07    1323.13
#define NOTEFREQS_FREQ_A0  27.62   //!<  A0       27.62    1248.87
#define NOTEFREQS_FREQ_A_0 29.27   //!<  A#0      29.27    1178.78
#define NOTEFREQS_FREQ_Bb0 29.27   //!<  Bb0      29.27    1178.78
#define NOTEFREQS_FREQ_B0  31.01   //!<  B0       31.01    1112.62
#define NOTEFREQS_FREQ_C1  32.85   //!<  C1       32.85    1050.17
#define NOTEFREQS_FREQ_C_1 34.81   //!<  C#1      34.81     991.23
#define NOTEFREQS_FREQ_Db1 34.81   //!<  Db1      34.81     991.23
#define NOTEFREQS_FREQ_D1  36.87   //!<  D1       36.87     935.59
#define NOTEFREQS_FREQ_D_1 39.07   //!<  D#1      39.07     883.08
#define NOTEFREQS_FREQ_Eb1 39.07   //!<  Eb1      39.07     883.08
#define NOTEFREQS_FREQ_E1  41.39   //!<  E1       41.39     833.52
#define NOTEFREQS_FREQ_F1  43.85   //!<  F1       43.85     786.74
#define NOTEFREQS_FREQ_F_1 46.46   //!<  F#1      46.46     742.58
#define NOTEFREQS_FREQ_Gb1 46.46   //!<  Gb1      46.46     742.58
#define NOTEFREQS_FREQ_G1  49.22   //!<  G1       49.22     700.90
#define NOTEFREQS_FREQ_G_1 52.15   //!<  G#1      52.15     661.57
#define NOTEFREQS_FREQ_Ab1 52.15   //!<  Ab1      52.15     661.57
#define NOTEFREQS_FREQ_A1  55.25   //!<  A1       55.25     624.43
#define NOTEFREQS_FREQ_A_1 58.54   //!<  A#1      58.54     589.39
#define NOTEFREQS_FREQ_Bb1 58.54   //!<  Bb1      58.54     589.39
#define NOTEFREQS_FREQ_B1  62.02   //!<  B1       62.02     556.31
#define NOTEFREQS_FREQ_C2  65.70   //!<  C2       65.70     525.08
#define NOTEFREQS_FREQ_C_2 69.61   //!<  C#2      69.61     495.61
#define NOTEFREQS_FREQ_Db2 69.61   //!<  Db2      69.61     495.61
#define NOTEFREQS_FREQ_D2  73.75   //!<  D2       73.75     467.80
#define NOTEFREQS_FREQ_D_2 78.14   //!<  D#2      78.14     441.54
#define NOTEFREQS_FREQ_Eb2 78.14   //!<  Eb2      78.14     441.54
#define NOTEFREQS_FREQ_E2  82.78   //!<  E2       82.78     416.76
#define NOTEFREQS_FREQ_F2  87.70   //!<  F2       87.70     393.37
#define NOTEFREQS_FREQ_F_2 92.92   //!<  F#2      92.92     371.29
#define NOTEFREQS_FREQ_Gb2 92.92   //!<  Gb2      92.92     371.29
#define NOTEFREQS_FREQ_G2  98.44   //!<  G2       98.44     350.45
#define NOTEFREQS_FREQ_G_2 104.30  //!<  G#2     104.30     330.78
#define NOTEFREQS_FREQ_Ab2 104.30  //!<  Ab2     104.30     330.78
#define NOTEFREQS_FREQ_A2  110.50  //!<  A2      110.50     312.22
#define NOTEFREQS_FREQ_A_2 117.07  //!<  A#2     117.07     294.69
#define NOTEFREQS_FREQ_Bb2 117.07  //!<  Bb2     117.07     294.69
#define NOTEFREQS_FREQ_B2  124.03  //!<  B2      124.03     278.15
#define NOTEFREQS_FREQ_C3  131.41  //!<  C3      131.41     262.54
#define NOTEFREQS_FREQ_C_3 139.22  //!<  C#3     139.22     247.81
#define NOTEFREQS_FREQ_Db3 139.22  //!<  Db3     139.22     247.81
#define NOTEFREQS_FREQ_D3  147.50  //!<  D3      147.50     233.90
#define NOTEFREQS_FREQ_D_3 156.27  //!<  D#3     156.27     220.77
#define NOTEFREQS_FREQ_Eb3 156.27  //!<  Eb3     156.27     220.77
#define NOTEFREQS_FREQ_E3  165.56  //!<  E3      165.56     208.38
#define NOTEFREQS_FREQ_F3  175.41  //!<  F3      175.41     196.68
#define NOTEFREQS_FREQ_F_3 185.84  //!<  F#3     185.84     185.65
#define NOTEFREQS_FREQ_Gb3 185.84  //!<  Gb3     185.84     185.65
#define NOTEFREQS_FREQ_G3  196.89  //!<  G3      196.89     175.23
#define NOTEFREQS_FREQ_G_3 208.60  //!<  G#3     208.60     165.39
#define NOTEFREQS_FREQ_Ab3 208.60  //!<  Ab3     208.60     165.39
#define NOTEFREQS_FREQ_A3  221.00  //!<  A3      221.00     156.11
#define NOTEFREQS_FREQ_A_3 234.14  //!<  A#3     234.14     147.35
#define NOTEFREQS_FREQ_Bb3 234.14  //!<  Bb3     234.14     147.35
#define NOTEFREQS_FREQ_B3  248.06  //!<  B3      248.06     139.08
#define NOTEFREQS_FREQ_C4  262.81  //!<  C4      262.81     131.27
#define NOTEFREQS_FREQ_C_4 278.44  //!<  C#4     278.44     123.90
#define NOTEFREQS_FREQ_Db4 278.44  //!<  Db4     278.44     123.90
#define NOTEFREQS_FREQ_D4  295.00  //!<  D4      295.00     116.95
#define NOTEFREQS_FREQ_D_4 312.54  //!<  D#4     312.54     110.39
#define NOTEFREQS_FREQ_Eb4 312.54  //!<  Eb4     312.54     110.39
#define NOTEFREQS_FREQ_E4  331.13  //!<  E4      331.13     104.19
#define NOTEFREQS_FREQ_F4  350.82  //!<  F4      350.82      98.34
#define NOTEFREQS_FREQ_F_4 371.68  //!<  F#4     371.68      92.82
#define NOTEFREQS_FREQ_Gb4 371.68  //!<  Gb4     371.68      92.82
#define NOTEFREQS_FREQ_G4  393.78  //!<  G4      393.78      87.61
#define NOTEFREQS_FREQ_G_4 417.19  //!<  G#4     417.19      82.70
#define NOTEFREQS_FREQ_Ab4 417.19  //!<  Ab4     417.19      82.70
#define NOTEFREQS_FREQ_A4  442.00  //!<  A4      442.00      78.05
#define NOTEFREQS_FREQ_A_4 468.28  //!<  A#4     468.28      73.67
#define NOTEFREQS_FREQ_Bb4 468.28  //!<  Bb4     468.28      73.67
#define NOTEFREQS_FREQ_B4  496.13  //!<  B4      496.13      69.54
#define NOTEFREQS_FREQ_C5  525.63  //!<  C5      525.63      65.64
#define NOTEFREQS_FREQ_C_5 556.88  //!<  C#5     556.88      61.95
#define NOTEFREQS_FREQ_Db5 556.88  //!<  Db5     556.88      61.95
#define NOTEFREQS_FREQ_D5  590.00  //!<  D5      590.00      58.47
#define NOTEFREQS_FREQ_D_5 625.08  //!<  D#5     625.08      55.19
#define NOTEFREQS_FREQ_Eb5 625.08  //!<  Eb5     625.08      55.19
#define NOTEFREQS_FREQ_E5  662.25  //!<  E5      662.25      52.10
#define NOTEFREQS_FREQ_F5  701.63  //!<  F5      701.63      49.17
#define NOTEFREQS_FREQ_F_5 743.35  //!<  F#5     743.35      46.41
#define NOTEFREQS_FREQ_Gb5 743.35  //!<  Gb5     743.35      46.41
#define NOTEFREQS_FREQ_G5  787.55  //!<  G5      787.55      43.81
#define NOTEFREQS_FREQ_G_5 834.38  //!<  G#5     834.38      41.35
#define NOTEFREQS_FREQ_Ab5 834.38  //!<  Ab5     834.38      41.35
#define NOTEFREQS_FREQ_A5  884.00  //!<  A5      884.00      39.03
#define NOTEFREQS_FREQ_A_5 936.57  //!<  A#5     936.57      36.84
#define NOTEFREQS_FREQ_Bb5 936.57  //!<  Bb5     936.57      36.84
#define NOTEFREQS_FREQ_B5  992.26  //!<  B5      992.26      34.77
#define NOTEFREQS_FREQ_C6  1051.26 //!<  C6     1051.26      32.82
#define NOTEFREQS_FREQ_C_6 1113.77 //!<  C#6    1113.77      30.98
#define NOTEFREQS_FREQ_Db6 1113.77 //!<  Db6    1113.77      30.98
#define NOTEFREQS_FREQ_D6  1180.00 //!<  D6     1180.00      29.24
#define NOTEFREQS_FREQ_D_6 1250.16 //!<  D#6    1250.16      27.60
#define NOTEFREQS_FREQ_Eb6 1250.16 //!<  Eb6    1250.16      27.60
#define NOTEFREQS_FREQ_E6  1324.50 //!<  E6     1324.50      26.05
#define NOTEFREQS_FREQ_F6  1403.26 //!<  F6     1403.26      24.59
#define NOTEFREQS_FREQ_F_6 1486.70 //!<  F#6    1486.70      23.21
#define NOTEFREQS_FREQ_Gb6 1486.70 //!<  Gb6    1486.70      23.21
#define NOTEFREQS_FREQ_G6  1575.11 //!<  G6     1575.11      21.90
#define NOTEFREQS_FREQ_G_6 1668.77 //!<  G#6    1668.77      20.67
#define NOTEFREQS_FREQ_Ab6 1668.77 //!<  Ab6    1668.77      20.67
#define NOTEFREQS_FREQ_A6  1768.00 //!<  A6     1768.00      19.51
#define NOTEFREQS_FREQ_A_6 1873.13 //!<  A#6    1873.13      18.42
#define NOTEFREQS_FREQ_Bb6 1873.13 //!<  Bb6    1873.13      18.42
#define NOTEFREQS_FREQ_B6  1984.51 //!<  B6     1984.51      17.38
#define NOTEFREQS_FREQ_C7  2102.52 //!<  C7     2102.52      16.41
#define NOTEFREQS_FREQ_C_7 2227.54 //!<  C#7    2227.54      15.49
#define NOTEFREQS_FREQ_Db7 2227.54 //!<  Db7    2227.54      15.49
#define NOTEFREQS_FREQ_D7  2360.00 //!<  D7     2360.00      14.62
#define NOTEFREQS_FREQ_D_7 2500.33 //!<  D#7    2500.33      13.80
#define NOTEFREQS_FREQ_Eb7 2500.33 //!<  Eb7    2500.33      13.80
#define NOTEFREQS_FREQ_E7  2649.01 //!<  E7     2649.01      13.02
#define NOTEFREQS_FREQ_F7  2806.52 //!<  F7     2806.52      12.29
#define NOTEFREQS_FREQ_F_7 2973.41 //!<  F#7    2973.41      11.60
#define NOTEFREQS_FREQ_Gb7 2973.41 //!<  Gb7    2973.41      11.60
#define NOTEFREQS_FREQ_G7  3150.22 //!<  G7     3150.22      10.95
#define NOTEFREQS_FREQ_G_7 3337.54 //!<  G#7    3337.54      10.34
#define NOTEFREQS_FREQ_Ab7 3337.54 //!<  Ab7    3337.54      10.34
#define NOTEFREQS_FREQ_A7  3536.00 //!<  A7     3536.00       9.76
#define NOTEFREQS_FREQ_A_7 3746.26 //!<  A#7    3746.26       9.21
#define NOTEFREQS_FREQ_Bb7 3746.26 //!<  Bb7    3746.26       9.21
#define NOTEFREQS_FREQ_B7  3969.03 //!<  B7     3969.03       8.69
#define NOTEFREQS_FREQ_C8  4205.03 //!<  C8     4205.03       8.20
#define NOTEFREQS_FREQ_C_8 4455.08 //!<  C#8    4455.08       7.74
#define NOTEFREQS_FREQ_Db8 4455.08 //!<  Db8    4455.08       7.74
#define NOTEFREQS_FREQ_D8  4719.99 //!<  D8     4719.99       7.31
#define NOTEFREQS_FREQ_D_8 5000.66 //!<  D#8    5000.66       6.90
#define NOTEFREQS_FREQ_Eb8 5000.66 //!<  Eb8    5000.66       6.90
#define NOTEFREQS_FREQ_E8  5298.01 //!<  E8     5298.01       6.51
#define NOTEFREQS_FREQ_F8  5613.05 //!<  F8     5613.05       6.15
#define NOTEFREQS_FREQ_F_8 5946.82 //!<  F#8    5946.82       5.80
#define NOTEFREQS_FREQ_Gb8 5946.82 //!<  Gb8    5946.82       5.80
#define NOTEFREQS_FREQ_G8  6300.44 //!<  G8     6300.44       5.48
#define NOTEFREQS_FREQ_G_8 6675.08 //!<  G#8    6675.08       5.17
#define NOTEFREQS_FREQ_Ab8 6675.08 //!<  Ab8    6675.08       5.17
#define NOTEFREQS_FREQ_A8  7072.00 //!<  A8     7072.00       4.88
#define NOTEFREQS_FREQ_A_8 7492.52 //!<  A#8    7492.52       4.60
#define NOTEFREQS_FREQ_Bb8 7492.52 //!<  Bb8    7492.52       4.60
#define NOTEFREQS_FREQ_B8  7938.05 //!<  B8     7938.05       4.35

#elif NOTEFREQS_MIDDLE_A4 == 444

#define NOTEFREQS_FREQ_C0  16.50   //!<  C0       16.50    2090.88
#define NOTEFREQS_FREQ_C_0 17.48   //!<  C#0      17.48    1973.53
#define NOTEFREQS_FREQ_Db0 17.48   //!<  Db0      17.48    1973.53
#define NOTEFREQS_FREQ_D0  18.52   //!<  D0       18.52    1862.76
#define NOTEFREQS_FREQ_D_0 19.62   //!<  D#0      19.62    1758.21
#define NOTEFREQS_FREQ_Eb0 19.62   //!<  Eb0      19.62    1758.21
#define NOTEFREQS_FREQ_E0  20.79   //!<  E0       20.79    1659.53
#define NOTEFREQS_FREQ_F0  22.03   //!<  F0       22.03    1566.39
#define NOTEFREQS_FREQ_F_0 23.33   //!<  F#0      23.33    1478.47
#define NOTEFREQS_FREQ_Gb0 23.33   //!<  Gb0      23.33    1478.47
#define NOTEFREQS_FREQ_G0  24.72   //!<  G0       24.72    1395.49
#define NOTEFREQS_FREQ_G_0 26.19   //!<  G#0      26.19    1317.17
#define NOTEFREQS_FREQ_Ab0 26.19   //!<  Ab0      26.19    1317.17
#define NOTEFREQS_FREQ_A0  27.75   //!<  A0       27.75    1243.24
#define NOTEFREQS_FREQ_A_0 29.40   //!<  A#0      29.40    1173.47
#define NOTEFREQS_FREQ_Bb0 29.40   //!<  Bb0      29.40    1173.47
#define NOTEFREQS_FREQ_B0  31.15   //!<  B0       31.15    1107.60
#define NOTEFREQS_FREQ_C1  33.00   //!<  C1       33.00    1045.44
#define NOTEFREQS_FREQ_C_1 34.96   //!<  C#1      34.96     986.76
#define NOTEFREQS_FREQ_Db1 34.96   //!<  Db1      34.96     986.76
#define NOTEFREQS_FREQ_D1  37.04   //!<  D1       37.04     931.38
#define NOTEFREQS_FREQ_D_1 39.24   //!<  D#1      39.24     879.11
#define NOTEFREQS_FREQ_Eb1 39.24   //!<  Eb1      39.24     879.11
#define NOTEFREQS_FREQ_E1  41.58   //!<  E1       41.58     829.77
#define NOTEFREQS_FREQ_F1  44.05   //!<  F1       44.05     783.19
#define NOTEFREQS_FREQ_F_1 46.67   //!<  F#1      46.67     739.24
#define NOTEFREQS_FREQ_Gb1 46.67   //!<  Gb1      46.67     739.24
#define NOTEFREQS_FREQ_G1  49.44   //!<  G1       49.44     697.75
#define NOTEFREQS_FREQ_G_1 52.39   //!<  G#1      52.39     658.59
#define NOTEFREQS_FREQ_Ab1 52.39   //!<  Ab1      52.39     658.59
#define NOTEFREQS_FREQ_A1  55.50   //!<  A1       55.50     621.62
#define NOTEFREQS_FREQ_A_1 58.80   //!<  A#1      58.80     586.73
#define NOTEFREQS_FREQ_Bb1 58.80   //!<  Bb1      58.80     586.73
#define NOTEFREQS_FREQ_B1  62.30   //!<  B1       62.30     553.80
#define NOTEFREQS_FREQ_C2  66.00   //!<  C2       66.00     522.72
#define NOTEFREQS_FREQ_C_2 69.93   //!<  C#2      69.93     493.38
#define NOTEFREQS_FREQ_Db2 69.93   //!<  Db2      69.93     493.38
#define NOTEFREQS_FREQ_D2  74.08   //!<  D2       74.08     465.69
#define NOTEFREQS_FREQ_D_2 78.49   //!<  D#2      78.49     439.55
#define NOTEFREQS_FREQ_Eb2 78.49   //!<  Eb2      78.49     439.55
#define NOTEFREQS_FREQ_E2  83.16   //!<  E2       83.16     414.88
#define NOTEFREQS_FREQ_F2  88.10   //!<  F2       88.10     391.60
#define NOTEFREQS_FREQ_F_2 93.34   //!<  F#2      93.34     369.62
#define NOTEFREQS_FREQ_Gb2 93.34   //!<  Gb2      93.34     369.62
#define NOTEFREQS_FREQ_G2  98.89   //!<  G2       98.89     348.87
#define NOTEFREQS_FREQ_G_2 104.77  //!<  G#2     104.77     329.29
#define NOTEFREQS_FREQ_Ab2 104.77  //!<  Ab2     104.77     329.29
#define NOTEFREQS_FREQ_A2  111.00  //!<  A2      111.00     310.81
#define NOTEFREQS_FREQ_A_2 117.60  //!<  A#2     117.60     293.37
#define NOTEFREQS_FREQ_Bb2 117.60  //!<  Bb2     117.60     293.37
#define NOTEFREQS_FREQ_B2  124.59  //!<  B2      124.59     276.90
#define NOTEFREQS_FREQ_C3  132.00  //!<  C3      132.00     261.36
#define NOTEFREQS_FREQ_C_3 139.85  //!<  C#3     139.85     246.69
#define NOTEFREQS_FREQ_Db3 139.85  //!<  Db3     139.85     246.69
#define NOTEFREQS_FREQ_D3  148.17  //!<  D3      148.17     232.85
#define NOTEFREQS_FREQ_D_3 156.98  //!<  D#3     156.98     219.78
#define NOTEFREQS_FREQ_Eb3 156.98  //!<  Eb3     156.98     219.78
#define NOTEFREQS_FREQ_E3  166.31  //!<  E3      166.31     207.44
#define NOTEFREQS_FREQ_F3  176.20  //!<  F3      176.20     195.80
#define NOTEFREQS_FREQ_F_3 186.68  //!<  F#3     186.68     184.81
#define NOTEFREQS_FREQ_Gb3 186.68  //!<  Gb3     186.68     184.81
#define NOTEFREQS_FREQ_G3  197.78  //!<  G3      197.78     174.44
#define NOTEFREQS_FREQ_G_3 209.54  //!<  G#3     209.54     164.65
#define NOTEFREQS_FREQ_Ab3 209.54  //!<  Ab3     209.54     164.65
#define NOTEFREQS_FREQ_A3  222.00  //!<  A3      222.00     155.41
#define NOTEFREQS_FREQ_A_3 235.20  //!<  A#3     235.20     146.68
#define NOTEFREQS_FREQ_Bb3 235.20  //!<  Bb3     235.20     146.68
#define NOTEFREQS_FREQ_B3  249.19  //!<  B3      249.19     138.45
#define NOTEFREQS_FREQ_C4  264.00  //!<  C4      264.00     130.68
#define NOTEFREQS_FREQ_C_4 279.70  //!<  C#4     279.70     123.35
#define NOTEFREQS_FREQ_Db4 279.70  //!<  Db4     279.70     123.35
#define NOTEFREQS_FREQ_D4  296.33  //!<  D4      296.33     116.42
#define NOTEFREQS_FREQ_D_4 313.96  //!<  D#4     313.96     109.89
#define NOTEFREQS_FREQ_Eb4 313.96  //!<  Eb4     313.96     109.89
#define NOTEFREQS_FREQ_E4  332.62  //!<  E4      332.62     103.72
#define NOTEFREQS_FREQ_F4  352.40  //!<  F4      352.40      97.90
#define NOTEFREQS_FREQ_F_4 373.36  //!<  F#4     373.36      92.40
#define NOTEFREQS_FREQ_Gb4 373.36  //!<  Gb4     373.36      92.40
#define NOTEFREQS_FREQ_G4  395.56  //!<  G4      395.56      87.22
#define NOTEFREQS_FREQ_G_4 419.08  //!<  G#4     419.08      82.32
#define NOTEFREQS_FREQ_Ab4 419.08  //!<  Ab4     419.08      82.32
#define NOTEFREQS_FREQ_A4  444.00  //!<  A4      444.00      77.70
#define NOTEFREQS_FREQ_A_4 470.40  //!<  A#4     470.40      73.34
#define NOTEFREQS_FREQ_Bb4 470.40  //!<  Bb4     470.40      73.34
#define NOTEFREQS_FREQ_B4  498.37  //!<  B4      498.37      69.23
#define NOTEFREQS_FREQ_C5  528.01  //!<  C5      528.01      65.34
#define NOTEFREQS_FREQ_C_5 559.40  //!<  C#5     559.40      61.67
#define NOTEFREQS_FREQ_Db5 559.40  //!<  Db5     559.40      61.67
#define NOTEFREQS_FREQ_D5  592.67  //!<  D5      592.67      58.21
#define NOTEFREQS_FREQ_D_5 627.91  //!<  D#5     627.91      54.94
#define NOTEFREQS_FREQ_Eb5 627.91  //!<  Eb5     627.91      54.94
#define NOTEFREQS_FREQ_E5  665.25  //!<  E5      665.25      51.86
#define NOTEFREQS_FREQ_F5  704.81  //!<  F5      704.81      48.95
#define NOTEFREQS_FREQ_F_5 746.72  //!<  F#5     746.72      46.20
#define NOTEFREQS_FREQ_Gb5 746.72  //!<  Gb5     746.72      46.20
#define NOTEFREQS_FREQ_G5  791.12  //!<  G5      791.12      43.61
#define NOTEFREQS_FREQ_G_5 838.16  //!<  G#5     838.16      41.16
#define NOTEFREQS_FREQ_Ab5 838.16  //!<  Ab5     838.16      41.16
#define NOTEFREQS_FREQ_A5  888.00  //!<  A5      888.00      38.85
#define NOTEFREQS_FREQ_A_5 940.80  //!<  A#5     940.80      36.67
#define NOTEFREQS_FREQ_Bb5 940.80  //!<  Bb5     940.80      36.67
#define NOTEFREQS_FREQ_B5  996.75  //!<  B5      996.75      34.61
#define NOTEFREQS_FREQ_C6  1056.02 //!<  C6     1056.02      32.67
#define NOTEFREQS_FREQ_C_6 1118.81 //!<  C#6    1118.81      30.84
#define NOTEFREQS_FREQ_Db6 1118.81 //!<  Db6    1118.81      30.84
#define NOTEFREQS_FREQ_D6  1185.34 //!<  D6     1185.34      29.11
#define NOTEFREQS_FREQ_D_6 1255.82 //!<  D#6    1255.82      27.47
#define NOTEFREQS_FREQ_Eb6 1255.82 //!<  Eb6    1255.82      27.47
#define NOTEFREQS_FREQ_E6  1330.50 //!<  E6     1330.50      25.93
#define NOTEFREQS_FREQ_F6  1409.61 //!<  F6     1409.61      24.47
#define NOTEFREQS_FREQ_F_6 1493.43 //!<  F#6    1493.43      23.10
#define NOTEFREQS_FREQ_Gb6 1493.43 //!<  Gb6    1493.43      23.10
#define NOTEFREQS_FREQ_G6  1582.24 //!<  G6     1582.24      21.80
#define NOTEFREQS_FREQ_G_6 1676.32 //!<  G#6    1676.32      20.58
#define NOTEFREQS_FREQ_Ab6 1676.32 //!<  Ab6    1676.32      20.58
#define NOTEFREQS_FREQ_A6  1776.00 //!<  A6     1776.00      19.43
#define NOTEFREQS_FREQ_A_6 1881.61 //!<  A#6    1881.61      18.34
#define NOTEFREQS_FREQ_Bb6 1881.61 //!<  Bb6    1881.61      18.34
#define NOTEFREQS_FREQ_B6  1993.49 //!<  B6     1993.49      17.31
#define NOTEFREQS_FREQ_C7  2112.03 //!<  C7     2112.03      16.33
#define NOTEFREQS_FREQ_C_7 2237.62 //!<  C#7    2237.62      15.42
#define NOTEFREQS_FREQ_Db7 2237.62 //!<  Db7    2237.62      15.42
#define NOTEFREQS_FREQ_D7  2370.67 //!<  D7     2370.67      14.55
#define NOTEFREQS_FREQ_D_7 2511.64 //!<  D#7    2511.64      13.74
#define NOTEFREQS_FREQ_Eb7 2511.64 //!<  Eb7    2511.64      13.74
#define NOTEFREQS_FREQ_E7  2660.99 //!<  E7     2660.99      12.97
#define NOTEFREQS_FREQ_F7  2819.22 //!<  F7     2819.22      12.24
#define NOTEFREQS_FREQ_F_7 2986.86 //!<  F#7    2986.86      11.55
#define NOTEFREQS_FREQ_Gb7 2986.86 //!<  Gb7    2986.86      11.55
#define NOTEFREQS_FREQ_G7  3164.47 //!<  G7     3164.47      10.90
#define NOTEFREQS_FREQ_G_7 3352.64 //!<  G#7    3352.64      10.29
#define NOTEFREQS_FREQ_Ab7 3352.64 //!<  Ab7    3352.64      10.29
#define NOTEFREQS_FREQ_A7  3552.00 //!<  A7     3552.00       9.71
#define NOTEFREQS_FREQ_A_7 3763.21 //!<  A#7    3763.21       9.17
#define NOTEFREQS_FREQ_Bb7 3763.21 //!<  Bb7    3763.21       9.17
#define NOTEFREQS_FREQ_B7  3986.99 //!<  B7     3986.99       8.65
#define NOTEFREQS_FREQ_C8  4224.06 //!<  C8     4224.06       8.17
#define NOTEFREQS_FREQ_C_8 4475.24 //!<  C#8    4475.24       7.71
#define NOTEFREQS_FREQ_Db8 4475.24 //!<  Db8    4475.24       7.71
#define NOTEFREQS_FREQ_D8  4741.35 //!<  D8     4741.35       7.28
#define NOTEFREQS_FREQ_D_8 5023.29 //!<  D#8    5023.29       6.87
#define NOTEFREQS_FREQ_Eb8 5023.29 //!<  Eb8    5023.29       6.87
#define NOTEFREQS_FREQ_E8  5321.99 //!<  E8     5321.99       6.48
#define NOTEFREQS_FREQ_F8  5638.45 //!<  F8     5638.45       6.12
#define NOTEFREQS_FREQ_F_8 5973.73 //!<  F#8    5973.73       5.78
#define NOTEFREQS_FREQ_Gb8 5973.73 //!<  Gb8    5973.73       5.78
#define NOTEFREQS_FREQ_G8  6328.94 //!<  G8     6328.94       5.45
#define NOTEFREQS_FREQ_G_8 6705.28 //!<  G#8    6705.28       5.15
#define NOTEFREQS_FREQ_Ab8 6705.28 //!<  Ab8    6705.28       5.15
#define NOTEFREQS_FREQ_A8  7104.00 //!<  A8     7104.00       4.86
#define NOTEFREQS_FREQ_A_8 7526.43 //!<  A#8    7526.43       4.58
#define NOTEFREQS_FREQ_Bb8 7526.43 //!<  Bb8    7526.43       4.58
#define NOTEFREQS_FREQ_B8  7973.97 //!<  B8     7973.97       4.33

#elif NOTEFREQS_MIDDLE_A4 == 446

#define NOTEFREQS_FREQ_C0  16.57   //!<  C0       16.57    2081.50
#define NOTEFREQS_FREQ_C_0 17.56   //!<  C#0      17.56    1964.68
#define NOTEFREQS_FREQ_Db0 17.56   //!<  Db0      17.56    1964.68
#define NOTEFREQS_FREQ_D0  18.60   //!<  D0       18.60    1854.41
#define NOTEFREQS_FREQ_D_0 19.71   //!<  D#0      19.71    1750.33
#define NOTEFREQS_FREQ_Eb0 19.71   //!<  Eb0      19.71    1750.33
#define NOTEFREQS_FREQ_E0  20.88   //!<  E0       20.88    1652.09
#define NOTEFREQS_FREQ_F0  22.12   //!<  F0       22.12    1559.36
#define NOTEFREQS_FREQ_F_0 23.44   //!<  F#0      23.44    1471.84
#define NOTEFREQS_FREQ_Gb0 23.44   //!<  Gb0      23.44    1471.84
#define NOTEFREQS_FREQ_G0  24.83   //!<  G0       24.83    1389.24
#define NOTEFREQS_FREQ_G_0 26.31   //!<  G#0      26.31    1311.26
#define NOTEFREQS_FREQ_Ab0 26.31   //!<  Ab0      26.31    1311.26
#define NOTEFREQS_FREQ_A0  27.88   //!<  A0       27.88    1237.67
#define NOTEFREQS_FREQ_A_0 29.53   //!<  A#0      29.53    1168.20
#define NOTEFREQS_FREQ_Bb0 29.53   //!<  Bb0      29.53    1168.20
#define NOTEFREQS_FREQ_B0  31.29   //!<  B0       31.29    1102.64
#define NOTEFREQS_FREQ_C1  33.15   //!<  C1       33.15    1040.75
#define NOTEFREQS_FREQ_C_1 35.12   //!<  C#1      35.12     982.34
#define NOTEFREQS_FREQ_Db1 35.12   //!<  Db1      35.12     982.34
#define NOTEFREQS_FREQ_D1  37.21   //!<  D1       37.21     927.20
#define NOTEFREQS_FREQ_D_1 39.42   //!<  D#1      39.42     875.16
#define NOTEFREQS_FREQ_Eb1 39.42   //!<  Eb1      39.42     875.16
#define NOTEFREQS_FREQ_E1  41.77   //!<  E1       41.77     826.04
#define NOTEFREQS_FREQ_F1  44.25   //!<  F1       44.25     779.68
#define NOTEFREQS_FREQ_F_1 46.88   //!<  F#1      46.88     735.92
#define NOTEFREQS_FREQ_Gb1 46.88   //!<  Gb1      46.88     735.92
#define NOTEFREQS_FREQ_G1  49.67   //!<  G1       49.67     694.62
#define NOTEFREQS_FREQ_G_1 52.62   //!<  G#1      52.62     655.63
#define NOTEFREQS_FREQ_Ab1 52.62   //!<  Ab1      52.62     655.63
#define NOTEFREQS_FREQ_A1  55.75   //!<  A1       55.75     618.83
#define NOTEFREQS_FREQ_A_1 59.07   //!<  A#1      59.07     584.10
#define NOTEFREQS_FREQ_Bb1 59.07   //!<  Bb1      59.07     584.10
#define NOTEFREQS_FREQ_B1  62.58   //!<  B1       62.58     551.32
#define NOTEFREQS_FREQ_C2  66.30   //!<  C2       66.30     520.38
#define NOTEFREQS_FREQ_C_2 70.24   //!<  C#2      70.24     491.17
#define NOTEFREQS_FREQ_Db2 70.24   //!<  Db2      70.24     491.17
#define NOTEFREQS_FREQ_D2  74.42   //!<  D2       74.42     463.60
#define NOTEFREQS_FREQ_D_2 78.84   //!<  D#2      78.84     437.58
#define NOTEFREQS_FREQ_Eb2 78.84   //!<  Eb2      78.84     437.58
#define NOTEFREQS_FREQ_E2  83.53   //!<  E2       83.53     413.02
#define NOTEFREQS_FREQ_F2  88.50   //!<  F2       88.50     389.84
#define NOTEFREQS_FREQ_F_2 93.76   //!<  F#2      93.76     367.96
#define NOTEFREQS_FREQ_Gb2 93.76   //!<  Gb2      93.76     367.96
#define NOTEFREQS_FREQ_G2  99.34   //!<  G2       99.34     347.31
#define NOTEFREQS_FREQ_G_2 105.24  //!<  G#2     105.24     327.82
#define NOTEFREQS_FREQ_Ab2 105.24  //!<  Ab2     105.24     327.82
#define NOTEFREQS_FREQ_A2  111.50  //!<  A2      111.50     309.42
#define NOTEFREQS_FREQ_A_2 118.13  //!<  A#2     118.13     292.05
#define NOTEFREQS_FREQ_Bb2 118.13  //!<  Bb2     118.13     292.05
#define NOTEFREQS_FREQ_B2  125.15  //!<  B2      125.15     275.66
#define NOTEFREQS_FREQ_C3  132.60  //!<  C3      132.60     260.19
#define NOTEFREQS_FREQ_C_3 140.48  //!<  C#3     140.48     245.58
#define NOTEFREQS_FREQ_Db3 140.48  //!<  Db3     140.48     245.58
#define NOTEFREQS_FREQ_D3  148.83  //!<  D3      148.83     231.80
#define NOTEFREQS_FREQ_D_3 157.68  //!<  D#3     157.68     218.79
#define NOTEFREQS_FREQ_Eb3 157.68  //!<  Eb3     157.68     218.79
#define NOTEFREQS_FREQ_E3  167.06  //!<  E3      167.06     206.51
#define NOTEFREQS_FREQ_F3  177.00  //!<  F3      177.00     194.92
#define NOTEFREQS_FREQ_F_3 187.52  //!<  F#3     187.52     183.98
#define NOTEFREQS_FREQ_Gb3 187.52  //!<  Gb3     187.52     183.98
#define NOTEFREQS_FREQ_G3  198.67  //!<  G3      198.67     173.65
#define NOTEFREQS_FREQ_G_3 210.48  //!<  G#3     210.48     163.91
#define NOTEFREQS_FREQ_Ab3 210.48  //!<  Ab3     210.48     163.91
#define NOTEFREQS_FREQ_A3  223.00  //!<  A3      223.00     154.71
#define NOTEFREQS_FREQ_A_3 236.26  //!<  A#3     236.26     146.03
#define NOTEFREQS_FREQ_Bb3 236.26  //!<  Bb3     236.26     146.03
#define NOTEFREQS_FREQ_B3  250.31  //!<  B3      250.31     137.83
#define NOTEFREQS_FREQ_C4  265.19  //!<  C4      265.19     130.09
#define NOTEFREQS_FREQ_C_4 280.96  //!<  C#4     280.96     122.79
#define NOTEFREQS_FREQ_Db4 280.96  //!<  Db4     280.96     122.79
#define NOTEFREQS_FREQ_D4  297.67  //!<  D4      297.67     115.90
#define NOTEFREQS_FREQ_D_4 315.37  //!<  D#4     315.37     109.40
#define NOTEFREQS_FREQ_Eb4 315.37  //!<  Eb4     315.37     109.40
#define NOTEFREQS_FREQ_E4  334.12  //!<  E4      334.12     103.26
#define NOTEFREQS_FREQ_F4  353.99  //!<  F4      353.99      97.46
#define NOTEFREQS_FREQ_F_4 375.04  //!<  F#4     375.04      91.99
#define NOTEFREQS_FREQ_Gb4 375.04  //!<  Gb4     375.04      91.99
#define NOTEFREQS_FREQ_G4  397.34  //!<  G4      397.34      86.83
#define NOTEFREQS_FREQ_G_4 420.97  //!<  G#4     420.97      81.95
#define NOTEFREQS_FREQ_Ab4 420.97  //!<  Ab4     420.97      81.95
#define NOTEFREQS_FREQ_A4  446.00  //!<  A4      446.00      77.35
#define NOTEFREQS_FREQ_A_4 472.52  //!<  A#4     472.52      73.01
#define NOTEFREQS_FREQ_Bb4 472.52  //!<  Bb4     472.52      73.01
#define NOTEFREQS_FREQ_B4  500.62  //!<  B4      500.62      68.91
#define NOTEFREQS_FREQ_C5  530.39  //!<  C5      530.39      65.05
#define NOTEFREQS_FREQ_C_5 561.92  //!<  C#5     561.92      61.40
#define NOTEFREQS_FREQ_Db5 561.92  //!<  Db5     561.92      61.40
#define NOTEFREQS_FREQ_D5  595.34  //!<  D5      595.34      57.95
#define NOTEFREQS_FREQ_D_5 630.74  //!<  D#5     630.74      54.70
#define NOTEFREQS_FREQ_Eb5 630.74  //!<  Eb5     630.74      54.70
#define NOTEFREQS_FREQ_E5  668.24  //!<  E5      668.24      51.63
#define NOTEFREQS_FREQ_F5  707.98  //!<  F5      707.98      48.73
#define NOTEFREQS_FREQ_F_5 750.08  //!<  F#5     750.08      46.00
#define NOTEFREQS_FREQ_Gb5 750.08  //!<  Gb5     750.08      46.00
#define NOTEFREQS_FREQ_G5  794.68  //!<  G5      794.68      43.41
#define NOTEFREQS_FREQ_G_5 841.94  //!<  G#5     841.94      40.98
#define NOTEFREQS_FREQ_Ab5 841.94  //!<  Ab5     841.94      40.98
#define NOTEFREQS_FREQ_A5  892.00  //!<  A5      892.00      38.68
#define NOTEFREQS_FREQ_A_5 945.04  //!<  A#5     945.04      36.51
#define NOTEFREQS_FREQ_Bb5 945.04  //!<  Bb5     945.04      36.51
#define NOTEFREQS_FREQ_B5  1001.24 //!<  B5     1001.24      34.46
#define NOTEFREQS_FREQ_C6  1060.77 //!<  C6     1060.77      32.52
#define NOTEFREQS_FREQ_C_6 1123.85 //!<  C#6    1123.85      30.70
#define NOTEFREQS_FREQ_Db6 1123.85 //!<  Db6    1123.85      30.70
#define NOTEFREQS_FREQ_D6  1190.68 //!<  D6     1190.68      28.98
#define NOTEFREQS_FREQ_D_6 1261.48 //!<  D#6    1261.48      27.35
#define NOTEFREQS_FREQ_Eb6 1261.48 //!<  Eb6    1261.48      27.35
#define NOTEFREQS_FREQ_E6  1336.49 //!<  E6     1336.49      25.81
#define NOTEFREQS_FREQ_F6  1415.96 //!<  F6     1415.96      24.37
#define NOTEFREQS_FREQ_F_6 1500.16 //!<  F#6    1500.16      23.00
#define NOTEFREQS_FREQ_Gb6 1500.16 //!<  Gb6    1500.16      23.00
#define NOTEFREQS_FREQ_G6  1589.36 //!<  G6     1589.36      21.71
#define NOTEFREQS_FREQ_G_6 1683.87 //!<  G#6    1683.87      20.49
#define NOTEFREQS_FREQ_Ab6 1683.87 //!<  Ab6    1683.87      20.49
#define NOTEFREQS_FREQ_A6  1784.00 //!<  A6     1784.00      19.34
#define NOTEFREQS_FREQ_A_6 1890.08 //!<  A#6    1890.08      18.25
#define NOTEFREQS_FREQ_Bb6 1890.08 //!<  Bb6    1890.08      18.25
#define NOTEFREQS_FREQ_B6  2002.47 //!<  B6     2002.47      17.23
#define NOTEFREQS_FREQ_C7  2121.54 //!<  C7     2121.54      16.26
#define NOTEFREQS_FREQ_C_7 2247.70 //!<  C#7    2247.70      15.35
#define NOTEFREQS_FREQ_Db7 2247.70 //!<  Db7    2247.70      15.35
#define NOTEFREQS_FREQ_D7  2381.35 //!<  D7     2381.35      14.49
#define NOTEFREQS_FREQ_D_7 2522.96 //!<  D#7    2522.96      13.67
#define NOTEFREQS_FREQ_Eb7 2522.96 //!<  Eb7    2522.96      13.67
#define NOTEFREQS_FREQ_E7  2672.98 //!<  E7     2672.98      12.91
#define NOTEFREQS_FREQ_F7  2831.92 //!<  F7     2831.92      12.18
#define NOTEFREQS_FREQ_F_7 3000.32 //!<  F#7    3000.32      11.50
#define NOTEFREQS_FREQ_Gb7 3000.32 //!<  Gb7    3000.32      11.50
#define NOTEFREQS_FREQ_G7  3178.73 //!<  G7     3178.73      10.85
#define NOTEFREQS_FREQ_G_7 3367.74 //!<  G#7    3367.74      10.24
#define NOTEFREQS_FREQ_Ab7 3367.74 //!<  Ab7    3367.74      10.24
#define NOTEFREQS_FREQ_A7  3568.00 //!<  A7     3568.00       9.67
#define NOTEFREQS_FREQ_A_7 3780.16 //!<  A#7    3780.16       9.13
#define NOTEFREQS_FREQ_Bb7 3780.16 //!<  Bb7    3780.16       9.13
#define NOTEFREQS_FREQ_B7  4004.95 //!<  B7     4004.95       8.61
#define NOTEFREQS_FREQ_C8  4243.09 //!<  C8     4243.09       8.13
#define NOTEFREQS_FREQ_C_8 4495.40 //!<  C#8    4495.40       7.67
#define NOTEFREQS_FREQ_Db8 4495.40 //!<  Db8    4495.40       7.67
#define NOTEFREQS_FREQ_D8  4762.71 //!<  D8     4762.71       7.24
#define NOTEFREQS_FREQ_D_8 5045.91 //!<  D#8    5045.91       6.84
#define NOTEFREQS_FREQ_Eb8 5045.91 //!<  Eb8    5045.91       6.84
#define NOTEFREQS_FREQ_E8  5345.96 //!<  E8     5345.96       6.45
#define NOTEFREQS_FREQ_F8  5663.85 //!<  F8     5663.85       6.09
#define NOTEFREQS_FREQ_F_8 6000.64 //!<  F#8    6000.64       5.75
#define NOTEFREQS_FREQ_Gb8 6000.64 //!<  Gb8    6000.64       5.75
#define NOTEFREQS_FREQ_G8  6357.45 //!<  G8     6357.45       5.43
#define NOTEFREQS_FREQ_G_8 6735.49 //!<  G#8    6735.49       5.12
#define NOTEFREQS_FREQ_Ab8 6735.49 //!<  Ab8    6735.49       5.12
#define NOTEFREQS_FREQ_A8  7136.00 //!<  A8     7136.00       4.83
#define NOTEFREQS_FREQ_A_8 7560.33 //!<  A#8    7560.33       4.56
#define NOTEFREQS_FREQ_Bb8 7560.33 //!<  Bb8    7560.33       4.56
#define NOTEFREQS_FREQ_B8  8009.89 //!<  B8     8009.89       4.31

#else

#error NOTEFREQS_MIDDLE_A4 must be one of 432,434,436,438,440,442,444,446

#endif /* NOTEFREQS_MIDDLE_A4 */

#define NOTEFREQS_C0  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C0))
#define NOTEFREQS_C_0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_0))
#define NOTEFREQS_Db0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db0))
#define NOTEFREQS_D0  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D0))
#define NOTEFREQS_D_0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_0))
#define NOTEFREQS_Eb0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb0))
#define NOTEFREQS_E0  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E0))
#define NOTEFREQS_F0  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F0))
#define NOTEFREQS_F_0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_0))
#define NOTEFREQS_Gb0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb0))
#define NOTEFREQS_G0  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G0))
#define NOTEFREQS_G_0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_0))
#define NOTEFREQS_Ab0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab0))
#define NOTEFREQS_A0  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A0))
#define NOTEFREQS_A_0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_0))
#define NOTEFREQS_Bb0 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb0))
#define NOTEFREQS_B0  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B0))
#define NOTEFREQS_C1  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C1))
#define NOTEFREQS_C_1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_1))
#define NOTEFREQS_Db1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db1))
#define NOTEFREQS_D1  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D1))
#define NOTEFREQS_D_1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_1))
#define NOTEFREQS_Eb1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb1))
#define NOTEFREQS_E1  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E1))
#define NOTEFREQS_F1  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F1))
#define NOTEFREQS_F_1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_1))
#define NOTEFREQS_Gb1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb1))
#define NOTEFREQS_G1  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G1))
#define NOTEFREQS_G_1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_1))
#define NOTEFREQS_Ab1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab1))
#define NOTEFREQS_A1  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A1))
#define NOTEFREQS_A_1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_1))
#define NOTEFREQS_Bb1 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb1))
#define NOTEFREQS_B1  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B1))
#define NOTEFREQS_C2  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C2))
#define NOTEFREQS_C_2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_2))
#define NOTEFREQS_Db2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db2))
#define NOTEFREQS_D2  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D2))
#define NOTEFREQS_D_2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_2))
#define NOTEFREQS_Eb2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb2))
#define NOTEFREQS_E2  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E2))
#define NOTEFREQS_F2  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F2))
#define NOTEFREQS_F_2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_2))
#define NOTEFREQS_Gb2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb2))
#define NOTEFREQS_G2  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G2))
#define NOTEFREQS_G_2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_2))
#define NOTEFREQS_Ab2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab2))
#define NOTEFREQS_A2  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A2))
#define NOTEFREQS_A_2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_2))
#define NOTEFREQS_Bb2 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb2))
#define NOTEFREQS_B2  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B2))
#define NOTEFREQS_C3  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C3))
#define NOTEFREQS_C_3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_3))
#define NOTEFREQS_Db3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db3))
#define NOTEFREQS_D3  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D3))
#define NOTEFREQS_D_3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_3))
#define NOTEFREQS_Eb3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb3))
#define NOTEFREQS_E3  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E3))
#define NOTEFREQS_F3  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F3))
#define NOTEFREQS_F_3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_3))
#define NOTEFREQS_Gb3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb3))
#define NOTEFREQS_G3  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G3))
#define NOTEFREQS_G_3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_3))
#define NOTEFREQS_Ab3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab3))
#define NOTEFREQS_A3  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A3))
#define NOTEFREQS_A_3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_3))
#define NOTEFREQS_Bb3 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb3))
#define NOTEFREQS_B3  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B3))
#define NOTEFREQS_C4  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C4))
#define NOTEFREQS_C_4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_4))
#define NOTEFREQS_Db4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db4))
#define NOTEFREQS_D4  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D4))
#define NOTEFREQS_D_4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_4))
#define NOTEFREQS_Eb4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb4))
#define NOTEFREQS_E4  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E4))
#define NOTEFREQS_F4  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F4))
#define NOTEFREQS_F_4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_4))
#define NOTEFREQS_Gb4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb4))
#define NOTEFREQS_G4  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G4))
#define NOTEFREQS_G_4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_4))
#define NOTEFREQS_Ab4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab4))
#define NOTEFREQS_A4  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A4))
#define NOTEFREQS_A_4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_4))
#define NOTEFREQS_Bb4 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb4))
#define NOTEFREQS_B4  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B4))
#define NOTEFREQS_C5  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C5))
#define NOTEFREQS_C_5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_5))
#define NOTEFREQS_Db5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db5))
#define NOTEFREQS_D5  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D5))
#define NOTEFREQS_D_5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_5))
#define NOTEFREQS_Eb5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb5))
#define NOTEFREQS_E5  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E5))
#define NOTEFREQS_F5  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F5))
#define NOTEFREQS_F_5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_5))
#define NOTEFREQS_Gb5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb5))
#define NOTEFREQS_G5  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G5))
#define NOTEFREQS_G_5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_5))
#define NOTEFREQS_Ab5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab5))
#define NOTEFREQS_A5  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A5))
#define NOTEFREQS_A_5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_5))
#define NOTEFREQS_Bb5 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb5))
#define NOTEFREQS_B5  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B5))
#define NOTEFREQS_C6  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C6))
#define NOTEFREQS_C_6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_6))
#define NOTEFREQS_Db6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db6))
#define NOTEFREQS_D6  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D6))
#define NOTEFREQS_D_6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_6))
#define NOTEFREQS_Eb6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb6))
#define NOTEFREQS_E6  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E6))
#define NOTEFREQS_F6  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F6))
#define NOTEFREQS_F_6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_6))
#define NOTEFREQS_Gb6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb6))
#define NOTEFREQS_G6  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G6))
#define NOTEFREQS_G_6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_6))
#define NOTEFREQS_Ab6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab6))
#define NOTEFREQS_A6  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A6))
#define NOTEFREQS_A_6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_6))
#define NOTEFREQS_Bb6 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb6))
#define NOTEFREQS_B6  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B6))
#define NOTEFREQS_C7  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C7))
#define NOTEFREQS_C_7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_7))
#define NOTEFREQS_Db7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db7))
#define NOTEFREQS_D7  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D7))
#define NOTEFREQS_D_7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_7))
#define NOTEFREQS_Eb7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb7))
#define NOTEFREQS_E7  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E7))
#define NOTEFREQS_F7  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F7))
#define NOTEFREQS_F_7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_7))
#define NOTEFREQS_Gb7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb7))
#define NOTEFREQS_G7  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G7))
#define NOTEFREQS_G_7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_7))
#define NOTEFREQS_Ab7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab7))
#define NOTEFREQS_A7  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A7))
#define NOTEFREQS_A_7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_7))
#define NOTEFREQS_Bb7 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb7))
#define NOTEFREQS_B7  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B7))
#define NOTEFREQS_C8  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C8))
#define NOTEFREQS_C_8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_C_8))
#define NOTEFREQS_Db8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Db8))
#define NOTEFREQS_D8  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D8))
#define NOTEFREQS_D_8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_D_8))
#define NOTEFREQS_Eb8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Eb8))
#define NOTEFREQS_E8  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_E8))
#define NOTEFREQS_F8  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F8))
#define NOTEFREQS_F_8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_F_8))
#define NOTEFREQS_Gb8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Gb8))
#define NOTEFREQS_G8  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G8))
#define NOTEFREQS_G_8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_G_8))
#define NOTEFREQS_Ab8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Ab8))
#define NOTEFREQS_A8  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A8))
#define NOTEFREQS_A_8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_A_8))
#define NOTEFREQS_Bb8 ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_Bb8))
#define NOTEFREQS_B8  ((NOTEFREQS_TYPE)(NOTEFREQS_PROPORT / NOTEFREQS_FREQ_B8))

/* Enddef to prevent recursive inclusion */
#endif /* __A_NOTEFREQS_H__ */
