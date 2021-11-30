/*
 * math_utils.cc
 *
 * Математические рабочие функции.
 *
 * (c) Уткин Павел, 2013
 *
 * Создан: 17 мая 2013 г.
 *
 */

#include "math_utils.h"

/* Функция signum
   x - аргумент (in) */
int sign( double x ) {

    if ( fabs( x ) < SMALL_EPS )
        return 0;
    else if ( x > 0.0 )
        return 1;
    else
        return -1;

}

/* Функция max, возвращающая наибольшее из двух чисел
   a - первое число (in)
   b - второе число (in) */
double max( double a, double b ) {

    return ( a < b ) ? b : a;

}

/* Функция min, возвращающая наименьшее из двух чисел
   a - первое число (in)
   b - второе число (in) */
double min( double a, double b ) {

    return ( a < b ) ? a : b;

}

/* Перемножение двух квадратных матриц, C = A * B
   A[M][M] - первая матрица (in)
   B[M][M] - вторая матрица (in)
   C[M][M] - результат (out) */
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

/* Проверка, является ли матрица B обратной к матрице A
   A[M][M] - исходная матрица (in)
   B[M][M] - обратная матрица (in) */
bool check_inverse_matrix( double A[M][M], double B[M][M] ) {

    int i, j;

    double C[M][M]; /* результат умножения матриц A и B */

    mult_matrixes( A, B, C );

    for ( i = 0; i < M; i++ ) {
        for ( j = 0; j < M; j++ ) {
            if ( i != j ) {
                /* вне диагональные элементы */
                if ( fabs( C[i][j] ) > SMALL_EPS )
                    return false;
            }
            else {
                /* диагональные элементы */
                if ( fabs( C[i][j] - 1.0 ) > SMALL_EPS )
                    return false;
            }
        }
    }

    return true;

}