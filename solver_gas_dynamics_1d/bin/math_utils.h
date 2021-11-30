/*
 * math_utils.h
 *
 * Математические рабочие функции.
 *
 * (c) Уткин Павел, 2013
 *
 * Создан: 24 мая 2013 г.
 *
 */

#ifndef __MATH_UTILS_H
#define __MATH_UTILS_H

#include "main.h"

#define SMALL_EPS    1.e-8

/* Функция signum
   x - аргумент (in) */
int sign( double x );

/* Функция max, возвращающая наибольшее из двух чисел
   a - первое число (in)
   b - второе число (in) */
double max( double a, double b );

/* Функция min, возвращающая наименьшее из двух чисел
   a - первое число (in)
   b - второе число (in) */
double min( double a, double b );

/* Перемножение двух квадратных матриц, C = A * B
   A[M][M] - первая матрица (in)
   B[M][M] - вторая матрица (in)
   C[M][M] - результат (out) */
void mult_matrixes( double A[M][M], double B[M][M], double C[M][M] );

/* Проверка, является ли матрица B обратной к матрице A
   A[M][M] - исходная матрица (in)
   B[M][M] - обратная матрица (in) */
bool check_inverse_matrix( double A[M][M], double B[M][M] );

#endif /* __MATH_UTILS_H */
