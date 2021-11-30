/*
 * cir.cc
 *
 * Метод Куранта-Изаксона-Рис расчета потоков для одномерной системы уравнений газовой динамики.
 *
 * Холодов А.С. О построении разностных схем с положительной аппроксимацией для уравнений гиперболического типа //
 * ЖВМиМФ. - 1978. - Т. 18, № 6. - С. 1485.
 *
 * Куликовский А.Г., Погорелов Н.В., Семенов А.Ю. Математические вопросы численного решения гиперболических систем
 * уравнений. - М.: Физматлит, 2001. - С. 63. - Формулы (2.3.25), (2.3.26).
 *
 * (c) Уткин Павел, 2012
 *
 * Создан: 24 марта 2012 г.
 *
 */

#include "cir.h"

#include "utils.h"
#include "math_utils.h"

/*  Метод Куранта-Изаксона-Рис расчета потоков
    left_params[M] - вектор консервативных переменных слева от разрыва (in)
    right_params[M] - вектор консервативных переменных справа от разрыва (in)
    flux[M] - рассчитанный вектор потока (out) */
void cir_flux( double left_params[M], double right_params[M], double flux[M] ) {

    int i, j;

    /* результат перемножения всех матриц для параметров слева и справа от разрыва */
    double m_left[M][M], m_right[M][M];

    /* вектора дифференциальных потоков для параметров слева и справа от разрыва */
    double left_diff_flux[M], right_diff_flux[M];

    /* расчет дифференциальных потоков */
    diff_flux_cons( left_params, left_diff_flux );
    diff_flux_cons( right_params, right_diff_flux );

    /* определение матрицы в функции потока для параметров слева от разрыва */
    cir_util( left_params, m_left );

    /* определение матрицы в функции потока для параметров справа от разрыва */
    cir_util( right_params, m_right );

    for ( i = 0; i < M; i++ ) {
        flux[i] = 0.5 * ( left_diff_flux[i] + right_diff_flux[i] );
            for ( j = 0; j < M; j++ )
                flux[i] += 0.5 * ( 0.5 * ( m_left[i][j] + m_right[i][j] ) ) * ( left_params[j] - right_params[j] );
    }

}

/*  Расчет матрицы, входящей в функцию потока
    cons_params[M] - вектор неконсервативных переменных (in)
    m[M][M] - искомая матрица (out) */
void cir_util( double cons_params[M], double m[M][M] ) {

    /* матрица из собственных векторов системы уравнений газовой динамики */
    double omega[M][M];

    /* обратная к матрице из собственных векторов системы уравнений газовой динамики */
    double omega_inverse[M][M];

    /* диагональная матрица с модулями собственных чисел системы уравнений газовой динамики */
    double lambda[M][M];

    /* результат перемножения матриц омега и лямбда */
    double m_tmp[M][M];

    calc_omega( cons_params, omega );
    calc_lambda( cons_params, lambda );
    calc_omega_inverse( cons_params, omega_inverse );
    mult_matrixes( omega, lambda, m_tmp );
    mult_matrixes( m_tmp, omega_inverse, m );

}
