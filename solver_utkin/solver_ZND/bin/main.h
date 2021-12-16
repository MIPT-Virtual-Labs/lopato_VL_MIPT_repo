#ifndef __HEAD_H
#define __HEAD_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING_SIZE 100
// ����� ����� ��� ������ ����������� � ����
#define _N_OUT  101
// ����� ������������� ��������������� ����� ��� ������� ��������� �� �������� �� ���������� ����
#define _N_SML  (101)
// ����� ����� ��� �������������� �� x
#define _N_TOT  (100 * (_N_OUT - 1) + 1)
// ����� �������� � ������� ZND_solution
#define _K_OUT  6
// ������� � ������� ZND_solution
#define _X_O 0
#define _R_O 1
#define _U_O 2
#define _P_O 3
#define _T_O 4
#define _Z_O 5
// ������������� ������� ����������
#define _R  8.31
// ��������� ������ �������� Z
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
    // ��������� ���������� � ���������� �����
    double g;       // ���������� ��������              (in)
    double E;       // ������� ��������� �����          (in)
    double Q;       // ������� �������                  (in)
    double m;       // �������� �����                   (in)
    double k;       // �������������������� ���������   (in)

    double pf;      // �������� ����� �������           (in)
    double Tf;      // ����������� ����� �������        (in)
    double rf;      // ��������� ����� �������          (get)
    double cf;      // �������� ����� ����� �������     (get)
    double Zf;      // ���� �������� ����� �������      (in)

    double X;       // ����� ��������� �������          (get)
    double R;       // ������������� ������� ���������� (get)

    double D;       // �������� �������-����            (get)
    double D2;      // �������� �������-���� � �������� (get)
};

#endif /* __HEAD_H */
