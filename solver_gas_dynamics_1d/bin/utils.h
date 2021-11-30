/*
 * utils.h
 *
 * Рабочие функции, специфичные для системы уравнений газовой динамики.
 *
 * (c) Уткин Павел, 2012
 *
 * Создан: 24 марта 2012 г.
 *
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define BIG_NUMBER  1.e10   /* большое число для инициализации некоторых переменных */

/* Функция расчета числового потока
   u_cons_l[M] - вектор консервативных переменных слева от разрыва (in)
   u_cons_r[M] - вектор консервативных переменных справа от разрыва (in)
   flux[M] - вектор потока (out) */
void calc_flux( double u_cons_l[M], double u_cons_r[M], double flux[M] );

/* Преобразование вектора консервативных переменных в вектор неконсервативных
   v_cons[M] - вектор консервативных переменных (in)
   v_ncons[M] - вектор неконсервативных переменных (out) */
void convert_cons_to_noncons( double v_cons[M], double v_ncons[M] );

/* Преобразование вектора неконсервативных переменных в вектор консервативных
   v_ncons[M] - вектор неконсервативных переменных (in)
   v_cons[M] - вектор консервативных переменных (out) */
void convert_noncons_to_cons( double v_ncons[M], double v_cons[M] );

/* Расчет вектора дифференциального потока по вектору консервативных переменных
   v_cons[M] - вектор консервативных переменных (in)
   flux[M] - рассчитываемый вектор дифференциального потока (out) */
void diff_flux_cons( double v_cons[M], double flux[M] );

/* Расчет вектора дифференциального потока по вектору примитивных переменных
   v_ncons[M] - вектор примитивных переменных (in)
   flux[M] - рассчитываемый вектор дифференциального потока (out) */
void diff_flux_ncons( double v_ncons[M], double flux[M] );

/* Обработка граничного условия
   v_cons[M] - вектор консервативных переменных (in)
   boun_v[M] - вектор консервативных переменных, необходимый для реализации граничного условия (out)
   boun_type - тип граничного условия (in) */
void boundary( double v_cons[M], double boun_v[M], int boun_type );

/* Инициализация вектора-решения
   u_cons[N][M] - значения вектора консервативных переменных в центрах всех ячеек (out) 
   дальше идут неконсервативные параметры слева и справа от разрыва
   r_left, r_right - плотности (in)
   u_left, u_right - скорости (in)
   p_left, p_right - давления (in)
*/
void init_solution( double u_cons[N][M], double r_left, double r_right, double u_left, double u_right, double p_left, double p_right );

/* Расчет скорости звука
   v_cons[M] - вектор консервативных переменных (in) */
double calc_sound_velocity( double v_ncons[M] );

/* Расчет матрицы Якоби одномерной системы уравнений газовой динамики
   v_cons[M] - вектор консервативных переменных (in)
   jacob[M][M] - матрица Якоби одномерной системы уравнений газовой динамики (out) */
void calc_jacob( double v_cons[M], double jacob[M][M] );

/* Расчет матрицы из собственных векторов одномерной системы уравнений газовой динамики
   v_cons[M] - вектор консервативных переменных (in)
   omega[M][M] - матрица из собственных векторов одномерной системы уравнений газовой динамики (out) */
void calc_omega( double v_cons[M], double omega[M][M] );

/* Расчет обратной матрицы из собственных векторов одномерной системы уравнений газовой динамики
   v_cons[M] - вектор консервативных переменных (in)
   omega_inverse[M][M] - матрица, обратная матрице из собственных векторов одномерной системы уравнений газовой динамики (out) */
void calc_omega_inverse( double v_cons[M], double omega_inverse[M][M] );

/* Расчет диагональной матрицы с модулями собственных чисел одномерной системы уравнений газовой динамики на диагонали
   v_cons[M] - вектор консервативных переменных (in)
   lambda[M][M] - диагональная матрица с модулями собственных чисел одномерной системы уравнений газовой динамики на диагонали */
void calc_lambda( double v_cons[M], double lambda[M][M] );

/* Расчет нового шага по времени

   Методика: Toro E.F. Riemann Solvers and Numerical Methods for Fluid Dynamics. - 2nd Edition. - Springer,
   1999. - P. 221, 225.

   x[N] - координаты узлов сетки (in)
   v_cons[N][M] - вектора консервативных переменных в центрах ячеек (in)
   time_step_number - номер текущего шага по времени (in) */
double calc_time_step( double x[N], double v_cons[N][M], int time_step_number );

#endif /* __UTILS_H_ */