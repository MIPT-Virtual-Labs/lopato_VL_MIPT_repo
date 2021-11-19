/*
 * utils.cc
 *
 * Рабочие функции, специфичные для системы уравнений газовой динамики.
 *
 * (c) Уткин Павел, 2012
 *
 * Создан: 24 марта 2012 г.
 *
 */

#include "utils.h"

/* различные методы расчета потоков */
#include "cir.h"

/* Функция расчета числового потока
   u_cons_l[M] - вектор консервативных переменных слева от разрыва (in)
   u_cons_r[M] - вектор консервативных переменных справа от разрыва (in)
   flux[M] - вектор потока (out) */
void calc_flux( double u_cons_l[M], double u_cons_r[M], double flux[M] ) {

    int scheme = SCHEME;                            /* расчетная схема */

    switch ( scheme ) {
        case CIR:
            cir_flux( u_cons_l, u_cons_r, flux );
            break;
        default:
            printf( "Error: wrong scheme number.\n" );
            exit( EXIT_FAILURE );
    }

}

/* Преобразование вектора консервативных переменных в вектор неконсервативных
   v_cons[M] - вектор консервативных переменных (in)
   v_ncons[M] - вектор неконсервативных переменных (out) */
void convert_cons_to_noncons( double v_cons[M], double v_ncons[M] ) {

    v_ncons[0] = v_cons[0];                                                                     /* плотность */
    v_ncons[1] = v_cons[1] / v_cons[0];                                                         /* скорость */
    v_ncons[2] = ( GAMMA - 1 ) * ( v_cons[2] - 0.5 * v_cons[0] * pow( v_ncons[1], 2.0 ) );      /* давление */

}

/* Преобразование вектора неконсервативных переменных в вектор консервативных
   v_ncons[M] - вектор неконсервативных переменных (in)
   v_cons[M] - вектор консервативных переменных (out) */
void convert_noncons_to_cons( double v_ncons[M], double v_cons[M] ) {

    v_cons[0] = v_ncons[0];                                                                     /* масса */
    v_cons[1] = v_ncons[0] * v_ncons[1];                                                        /* импульс */
    v_cons[2] = 0.5 * v_ncons[0] * pow( v_ncons[1], 2.0) + v_ncons[2] / ( GAMMA - 1.0 );        /* полная энергия */

}

/* Расчет вектора дифференциального потока по вектору консервативных переменных
   v_cons[M] - вектор консервативных переменных (in)
   flux[M] - рассчитываемый вектор дифференциального потока (out) */
void diff_flux_cons( double v_cons[M], double flux[M] ) {

    double v_ncons[M];                                      /* вектор примитивных переменных */

    convert_cons_to_noncons( v_cons, v_ncons );

    flux[0] = v_cons[1];                                    /* масса */
    flux[1] = v_cons[1] * v_ncons[1] + v_ncons[2];          /* импульс */
    flux[2] = ( v_cons[2] + v_ncons[2] ) * v_ncons[1];      /* полная энергия */

}

/* Расчет вектора дифференциального потока по вектору примитивных переменных
   v_ncons[M] - вектор примитивных переменных (in)
   flux[M] - рассчитываемый вектор дифференциального потока (out) */
void diff_flux_ncons( double v_ncons[M], double flux[M] ) {

    double v_cons[M];                                       /* вектор консервативных переменных */

    convert_noncons_to_cons( v_ncons, v_cons );

    flux[0] = v_cons[1];                                    /* масса */
    flux[1] = v_cons[1] * v_ncons[1] + v_ncons[2];          /* импульс */
    flux[2] = ( v_cons[2] + v_ncons[2] ) * v_ncons[1];      /* полная энергия */

}

/* Обработка граничного условия
   v_cons[M] - вектор консервативных переменных (in)
   boun_v[M] - вектор консервативных переменных, необходимый для реализации граничного условия (out)
   boun_type - тип граничного условия (in) */
void boundary( double v_cons[M], double boun_v[M], int boun_type ) {

    switch ( boun_type ) {
        case WALL:
            boun_v[0] = v_cons[0];
	    boun_v[1] = -v_cons[1];
	    boun_v[2] = v_cons[2];
	    break;
        case FREE:
            boun_v[0] = v_cons[0];
	    boun_v[1] = v_cons[1];
	    boun_v[2] = v_cons[2];
            break;
        default:
            printf( "Error - wrong boundary condition.\n" );
            break;
    }

}

/* Инициализация вектора-решения
   u_cons[N][M] - значения вектора консервативных переменных в центрах всех ячеек (out) 
   дальше идут неконсервативные параметры слева и справа от разрыва
   r_left, r_right - плотности (in)
   u_left, u_right - скорости (in)
   p_left, p_right - давления (in)
*/
void init_solution( double u_cons[N][M], double r_left, double r_right, double u_left, double u_right, double p_left, double p_right ) {

    int i;
    double v[M];
	
    for ( i = 0; i < N; i++ ) {
        if ( i < CELLS_LEFT ) {
            v[0] = r_left;
            v[1] = u_left;
            v[2] = p_left;
        }
        else {
            v[0] = r_right;
            v[1] = u_right;
            v[2] = p_right;
        }
        convert_noncons_to_cons( v, u_cons[i] );
    }		

}

/* Расчет скорости звука
   v_cons[M] - вектор консервативных переменных (in) */
double calc_sound_velocity( double v_ncons[M] ) {
	
    return ( sqrt( GAMMA * v_ncons[2] / v_ncons[0] ) );

}

/* Расчет матрицы Якоби одномерной системы уравнений газовой динамики
   v_cons[M] - вектор консервативных переменных (in)
   jacob[M][M] - матрица Якоби одномерной системы уравнений газовой динамики (out) */
void calc_jacob( double v_cons[M], double jacob[M][M] ) {

    double v_ncons[M];
    double teta, b, h;

    convert_cons_to_noncons( v_cons, v_ncons );
	
    teta = 0.5 * v_ncons[1] * v_ncons[1];
    b = GAMMA - 1.0;
    h = 0.5 * v_ncons[1] * v_ncons[1] + GAMMA * v_ncons[2] / v_ncons[0] / ( GAMMA - 1.0 ); 

    jacob[0][0] = 0.0;
    jacob[0][1] = 1.0;
    jacob[0][2] = 0.0;

    jacob[1][0] = - v_ncons[1] * v_ncons[1] + teta * b;
    jacob[1][1] = v_ncons[1] * ( 2.0 - b );
    jacob[1][2] = b;

    jacob[2][0] = v_ncons[1] * ( teta * b - h );
    jacob[2][1] = h - v_ncons[1] * v_ncons[1] * b;
    jacob[2][2] = v_ncons[1] * ( 1.0 + b );

}

/* Расчет матрицы из собственных векторов одномерной системы уравнений газовой динамики
   v_cons[M] - вектор консервативных переменных (in)
   omega[M][M] - матрица из собственных векторов одномерной системы уравнений газовой динамики (out) */
void calc_omega( double v_cons[M], double omega[M][M] ) {

    double v_ncons[M];
    double c;				/* скорость звука */
    double teta, b, h;

    convert_cons_to_noncons( v_cons, v_ncons );
	
    c = calc_sound_velocity( v_ncons );
	
    teta = 0.5 * v_ncons[1] * v_ncons[1];
    b = GAMMA - 1.0;
    h = 0.5 * v_ncons[1] * v_ncons[1] + GAMMA * v_ncons[2] / v_ncons[0] / ( GAMMA - 1.0 ); 

    omega[0][0] = 1.0;
    omega[0][1] = 1.0;
    omega[0][2] = 1.0;

    omega[1][0] = v_ncons[1] - c;
    omega[1][1] = v_ncons[1];
    omega[1][2] = v_ncons[1] + c;

    omega[2][0] = h - v_ncons[1] * c;
    omega[2][1] = h - c * c / b;
    omega[2][2] = h + v_ncons[1] * c;

}

/* Расчет обратной матрицы из собственных векторов одномерной системы уравнений газовой динамики
   v_cons[M] - вектор консервативных переменных (in)
   omega_inverse[M][M] - матрица, обратная матрице из собственных векторов одномерной системы уравнений газовой динамики (out) */
void calc_omega_inverse( double v_cons[M], double omega_inverse[M][M] ) {

    double v_ncons[M];
    double c;				/* скорость звука */
    double teta, b, h;

    convert_cons_to_noncons( v_cons, v_ncons );
	
    c = calc_sound_velocity( v_ncons );
	
    teta = 0.5 * v_ncons[1] * v_ncons[1];
    b = GAMMA - 1.0;
    h = 0.5 * v_ncons[1] * v_ncons[1] + GAMMA * v_ncons[2] / v_ncons[0] / ( GAMMA - 1.0 ); 

    omega_inverse[0][0] = 0.5 * b * ( teta + v_ncons[1] * c / b ) / pow( c, 2.0 );
    omega_inverse[0][1] = 0.5 * b * ( -v_ncons[1] - c / b ) / pow( c, 2.0 );
    omega_inverse[0][2] = 0.5 * b / pow( c, 2.0 );

    omega_inverse[1][0] = 0.5 * b * ( 2.0 * h - 2.0 * pow( v_ncons[1], 2.0 ) ) / pow( c, 2.0 );
    omega_inverse[1][1] = 0.5 * b * ( 2.0 * v_ncons[1] ) / pow( c, 2.0 );
    omega_inverse[1][2] = 0.5 * b * ( - 2.0 ) / pow( c, 2.0 );

    omega_inverse[2][0] = 0.5 * b * ( teta - v_ncons[1] * c / b ) / pow( c, 2.0 );
    omega_inverse[2][1] = 0.5 * b * ( -v_ncons[1] + c / b ) / pow( c, 2.0 );
    omega_inverse[2][2] = 0.5 * b / pow( c, 2.0 );

}

/* Расчет диагональной матрицы с модулями собственных чисел одномерной системы уравнений газовой динамики на диагонали
   v_cons[M] - вектор консервативных переменных (in)
   lambda[M][M] - диагональная матрица с модулями собственных чисел одномерной системы уравнений газовой динамики на диагонали */
void calc_lambda( double v_cons[M], double lambda[M][M] ) {

    double v_ncons[M];
    double c;				/* скорость звука */

    convert_cons_to_noncons( v_cons, v_ncons );
	
    c = calc_sound_velocity( v_ncons );

    lambda[0][0] = fabs( v_ncons[1] - c );
    lambda[0][1] = 0.0;
    lambda[0][2] = 0.0;

    lambda[1][0] = 0.0;
    lambda[1][1] = fabs( v_ncons[1] );
    lambda[1][2] = 0.0;

    lambda[2][0] = 0.0;
    lambda[2][1] = 0.0;
    lambda[2][2] = fabs( v_ncons[1] + c );

}

/* Расчет нового шага по времени

   Методика: Toro E.F. Riemann Solvers and Numerical Methods for Fluid Dynamics. - 2nd Edition. - Springer,
   1999. - P. 221, 225.

   x[N] - координаты узлов сетки (in)
   v_cons[N][M] - вектора консервативных переменных в центрах ячеек (in)
   time_step_number - номер текущего шага по времени (in) */
double calc_time_step( double x[N], double v_cons[N][M], int time_step_number ) {

    int i;
    double new_step = BIG_NUMBER;   /* рассчитываемый новый шаг по времени */
    double v_ncons[M];              /* вектор примитивных переменных в текущей ячейке */
    double c;                       /* скорость звука в текущей ячейке */
    double curr_step;               /* новый шаг по времени, рассчитанный по параметрам в текущей ячейке */

    for ( i = 0; i < N; i++ ) {
        convert_cons_to_noncons( v_cons[i], v_ncons );
        c = calc_sound_velocity( v_ncons );
        curr_step = ( x[i+1] - x[i] ) / ( fabs( v_ncons[1] ) + c );
        if ( time_step_number < N1 ) {
            curr_step *= CFL1;
        }
        else {
            curr_step *= CFL2;
        }
        if ( curr_step < new_step )
            new_step = curr_step;
    }

    return new_step;

}