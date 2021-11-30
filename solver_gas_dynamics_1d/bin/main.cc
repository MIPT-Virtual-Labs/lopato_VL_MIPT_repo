/*
 * main.cc
 *
 * Программа для тестирования различных методов расчета потоков
 * для решения одномерных задач газовой динамики.
 *
 * (c) Уткин Павел, 2012
 *
 * Создан: 27 января 2012 г.
 *
 */

#include "main.h"

/* общие для всех методов функции */
#include "grid.h"
#include "utils.h"
#include "io.h"

int main( int argc, char* argv[] ) {
    if (argc > 7 || argc < 7) {
        printf("Incorrect number of arguments. Please provide density_left, density_right, velocity_left, velocity_right, pressure_left, pressure_right.\n");
        exit(EXIT_FAILURE);
    }

    double r_left = atof(argv[1]);
    double r_right = atof(argv[2]);

    double u_left = atof(argv[3]);
    double u_right = atof(argv[4]);

    double p_left = atof(argv[5]);
    double p_right = atof(argv[6]);

    int i, j;
    double x[N+1];                                  /* массив координат узлов сетки */
    double xc[N];                                   /* массив координат центров ячеек сетки */
    double u_prev[N][M];                            /* вектора консервативных переменных на n-ом слое */
    double u_next[N][M];                            /* вектора консервативных переменных на (n+1)-ом слое */
    double boun_v[M];                               /* вектор консервативных переменных для реализации граничного условия */					
    double flux_left[M], flux_right[M];             /* потоки через грани расчетной ячейки */
    double dt;                                      /* шаг по времени */						
    int steps_num = 0;                              /* счетчик числа шагов */
    double curr_t = 0.0;                            /* текущее время */

    /* определение координат узлов сетки */
    build_grid( x, xc );

    /* инициализация вектора-решения */
    init_solution( u_prev, r_left, r_right, u_left, u_right, p_left, p_right );

    /* основной цикл по времени */
    while ( T_END - curr_t > 0 ) {

        dt = calc_time_step( x, u_prev, steps_num );

        /* цикл по ячейкам */
	for ( i = 0; i < N; i++ ) {

            /* расчет потока через левую грань ячейки */
            if ( i != 0 )
                calc_flux( u_prev[i-1], u_prev[i], flux_left );
            else {
                /* обработка граничного условия */
                boundary( u_prev[0], boun_v, LEFT_BOUN );
		calc_flux( boun_v, u_prev[0], flux_left );
            }
			
            /* расчет потока через правую грань ячейки */
            if ( i != N-1 )
                calc_flux( u_prev[i], u_prev[i+1], flux_right );
            else {
                /* обработка граничного условия */
                boundary( u_prev[N-1], boun_v, RIGHT_BOUN );
                calc_flux( u_prev[N-1], boun_v, flux_right );
            }

            /* цикл по компонентам вектора */
            for ( j = 0; j < M; j++ )
                u_next[i][j] = u_prev[i][j] - dt * ( flux_right[j] - flux_left[j] ) / ( x[i+1] - x[i] );
            }

            for ( i = 0; i < N; i++ )
                for ( j = 0; j < M; j++ )
                    u_prev[i][j] = u_next[i][j];

            curr_t += dt;
            steps_num += 1;

    }

    printf( "Step %d is finished, current time is %f\n", steps_num, curr_t );

    /* запись результатов на нужный момент времени */
    write_solution( xc, u_prev, curr_t );

    return 0;

}