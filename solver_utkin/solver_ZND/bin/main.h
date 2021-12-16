#ifndef __HEAD_H
#define __HEAD_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 100
// число узлов при выводе результатов в файл
#define _N_OUT  101
// число промежуточных вспомогательных узлов при расчете интеграла от текущего до следующего узла
#define _N_SML  (101)
// число узлов при интегрировании по x
#define _N_TOT  (100 * (_N_OUT - 1) + 1)
// число столбцов в массиве ZND_solution
#define _K_OUT  6
// индексы в массива ZND_solution
#define _X_O 0
#define _R_O 1
#define _U_O 2
#define _P_O 3
#define _T_O 4
#define _Z_O 5
// универсальная газовая постоянная
#define _R  8.31
// некоторые важные значения Z
#define _Z_H 1
#define _Z_M 0.5
#define _Z_L 0.001
/*
#define _PREEXP_FACTOR 6.85e+9
#define _HEAT_ENERGY 5.02e+6
#define _GAMMA 1.17
#define _ACTIVATION_ENERGY 113.0e+3
#define _MOL_MASS 0.021
#define _TEMPERETURE_FON 290
#define _PRESSURE_FON 100000
*/
/*
#define _PREEXP_FACTOR 1.0e+9
#define _HEAT_ENERGY 2.94e+6
#define _GAMMA 1.25
#define _ACTIVATION_ENERGY 71.0e+3
#define _MOL_MASS 0.029
#define _TEMPERETURE_FON 273
#define _PRESSURE_FON 100000
*/
/*
#define _PREEXP_FACTOR 1.64e+9
#define _HEAT_ENERGY 3.58e+6
#define _GAMMA 1.197
#define _ACTIVATION_ENERGY 167.0e+3
#define _MOL_MASS 0.027
#define _TEMPERETURE_FON 273
#define _PRESSURE_FON 100000
*/
struct Parameters
{
    // параметры химической и физической части
    double g;       // показатель адиабаты              (in)
    double E;       // энергия активации смеси          (in)
    double Q;       // теплота реакции                  (in)
    double m;       // молярная масса                   (in)
    double k;       // предэкспоненциальный множитель   (in)

    double pf;      // давление перед фронтом           (in)
    double Tf;      // температура перед фронтом        (in)
    double rf;      // плотность перед фронтом          (get)
    double cf;      // скорость звука перед фронтом     (get)
    double Zf;      // доля реагента перед фронтом      (in)

    double X;       // длина расчетной области          (get)
    double R;       // универсальная газовая постоянная (get)

    double D;       // скорость Чепмена-Жуге            (get)
    double D2;      // скорость Чепмена-Жуге в квадрате (get)
};

#endif /* __HEAD_H */
