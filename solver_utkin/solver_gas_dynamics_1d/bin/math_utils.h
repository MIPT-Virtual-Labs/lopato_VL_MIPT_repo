/*
 * math_utils.h
 *
 * �������������� ������� �������.
 *
 * (c) ����� �����, 2013
 *
 * ������: 24 ��� 2013 �.
 *
 */

#ifndef __MATH_UTILS_H
#define __MATH_UTILS_H

#include "main.h"

#define SMALL_EPS    1.e-8

/* ������� signum
   x - �������� (in) */
int sign( double x );

/* ������� max, ������������ ���������� �� ���� �����
   a - ������ ����� (in)
   b - ������ ����� (in) */
double max( double a, double b );

/* ������� min, ������������ ���������� �� ���� �����
   a - ������ ����� (in)
   b - ������ ����� (in) */
double min( double a, double b );

/* ������������ ���� ���������� ������, C = A * B
   A[M][M] - ������ ������� (in)
   B[M][M] - ������ ������� (in)
   C[M][M] - ��������� (out) */
void mult_matrixes( double A[M][M], double B[M][M], double C[M][M] );

/* ��������, �������� �� ������� B �������� � ������� A
   A[M][M] - �������� ������� (in)
   B[M][M] - �������� ������� (in) */
bool check_inverse_matrix( double A[M][M], double B[M][M] );

#endif /* __MATH_UTILS_H */
