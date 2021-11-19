/*
 * math_utils.cc
 *
 * �������������� ������� �������.
 *
 * (c) ����� �����, 2013
 *
 * ������: 17 ��� 2013 �.
 *
 */

#include "math_utils.h"

/* ������� signum
   x - �������� (in) */
int sign( double x ) {

    if ( fabs( x ) < SMALL_EPS )
        return 0;
    else if ( x > 0.0 )
        return 1;
    else
        return -1;

}

/* ������� max, ������������ ���������� �� ���� �����
   a - ������ ����� (in)
   b - ������ ����� (in) */
double max( double a, double b ) {

    return ( a < b ) ? b : a;

}

/* ������� min, ������������ ���������� �� ���� �����
   a - ������ ����� (in)
   b - ������ ����� (in) */
double min( double a, double b ) {

    return ( a < b ) ? a : b;

}

/* ������������ ���� ���������� ������, C = A * B
   A[M][M] - ������ ������� (in)
   B[M][M] - ������ ������� (in)
   C[M][M] - ��������� (out) */
void mult_matrixes( double A[M][M], double B[M][M], double C[M][M] ) {

    int i, j, k;
	
    for ( i = 0; i < M; i++ ) {
        for ( j = 0; j < M; j++ ) {
            C[i][j] = 0.0;
                for ( k = 0; k < M; k++ )
                    C[i][j] += A[i][k] * B[k][j];
	}
    }

}

/* ��������, �������� �� ������� B �������� � ������� A
   A[M][M] - �������� ������� (in)
   B[M][M] - �������� ������� (in) */
bool check_inverse_matrix( double A[M][M], double B[M][M] ) {

    int i, j;

    double C[M][M]; /* ��������� ��������� ������ A � B */

    mult_matrixes( A, B, C );

    for ( i = 0; i < M; i++ ) {
        for ( j = 0; j < M; j++ ) {
            if ( i != j ) {
                /* ��� ������������ �������� */
                if ( fabs( C[i][j] ) > SMALL_EPS )
                    return false;
            }
            else {
                /* ������������ �������� */
                if ( fabs( C[i][j] - 1.0 ) > SMALL_EPS )
                    return false;
            }
        }
    }

    return true;

}