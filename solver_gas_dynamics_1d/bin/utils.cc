/*
 * utils.cc
 *
 * ������� �������, ����������� ��� ������� ��������� ������� ��������.
 *
 * (c) ����� �����, 2012
 *
 * ������: 24 ����� 2012 �.
 *
 */

#include "utils.h"

/* ��������� ������ ������� ������� */
#include "cir.h"

/* ������� ������� ��������� ������
   u_cons_l[M] - ������ �������������� ���������� ����� �� ������� (in)
   u_cons_r[M] - ������ �������������� ���������� ������ �� ������� (in)
   flux[M] - ������ ������ (out) */
void calc_flux( double u_cons_l[M], double u_cons_r[M], double flux[M] ) {

    int scheme = SCHEME;                            /* ��������� ����� */

    switch ( scheme ) {
        case CIR:
            cir_flux( u_cons_l, u_cons_r, flux );
            break;
        default:
            printf( "Error: wrong scheme number.\n" );
            exit( EXIT_FAILURE );
    }

}

/* �������������� ������� �������������� ���������� � ������ ����������������
   v_cons[M] - ������ �������������� ���������� (in)
   v_ncons[M] - ������ ���������������� ���������� (out) */
void convert_cons_to_noncons( double v_cons[M], double v_ncons[M] ) {

    v_ncons[0] = v_cons[0];                                                                     /* ��������� */
    v_ncons[1] = v_cons[1] / v_cons[0];                                                         /* �������� */
    v_ncons[2] = ( GAMMA - 1 ) * ( v_cons[2] - 0.5 * v_cons[0] * pow( v_ncons[1], 2.0 ) );      /* �������� */

}

/* �������������� ������� ���������������� ���������� � ������ ��������������
   v_ncons[M] - ������ ���������������� ���������� (in)
   v_cons[M] - ������ �������������� ���������� (out) */
void convert_noncons_to_cons( double v_ncons[M], double v_cons[M] ) {

    v_cons[0] = v_ncons[0];                                                                     /* ����� */
    v_cons[1] = v_ncons[0] * v_ncons[1];                                                        /* ������� */
    v_cons[2] = 0.5 * v_ncons[0] * pow( v_ncons[1], 2.0) + v_ncons[2] / ( GAMMA - 1.0 );        /* ������ ������� */

}

/* ������ ������� ����������������� ������ �� ������� �������������� ����������
   v_cons[M] - ������ �������������� ���������� (in)
   flux[M] - �������������� ������ ����������������� ������ (out) */
void diff_flux_cons( double v_cons[M], double flux[M] ) {

    double v_ncons[M];                                      /* ������ ����������� ���������� */

    convert_cons_to_noncons( v_cons, v_ncons );

    flux[0] = v_cons[1];                                    /* ����� */
    flux[1] = v_cons[1] * v_ncons[1] + v_ncons[2];          /* ������� */
    flux[2] = ( v_cons[2] + v_ncons[2] ) * v_ncons[1];      /* ������ ������� */

}

/* ������ ������� ����������������� ������ �� ������� ����������� ����������
   v_ncons[M] - ������ ����������� ���������� (in)
   flux[M] - �������������� ������ ����������������� ������ (out) */
void diff_flux_ncons( double v_ncons[M], double flux[M] ) {

    double v_cons[M];                                       /* ������ �������������� ���������� */

    convert_noncons_to_cons( v_ncons, v_cons );

    flux[0] = v_cons[1];                                    /* ����� */
    flux[1] = v_cons[1] * v_ncons[1] + v_ncons[2];          /* ������� */
    flux[2] = ( v_cons[2] + v_ncons[2] ) * v_ncons[1];      /* ������ ������� */

}

/* ��������� ���������� �������
   v_cons[M] - ������ �������������� ���������� (in)
   boun_v[M] - ������ �������������� ����������, ����������� ��� ���������� ���������� ������� (out)
   boun_type - ��� ���������� ������� (in) */
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

/* ������������� �������-�������
   u_cons[N][M] - �������� ������� �������������� ���������� � ������� ���� ����� (out) 
   ������ ���� ���������������� ��������� ����� � ������ �� �������
   r_left, r_right - ��������� (in)
   u_left, u_right - �������� (in)
   p_left, p_right - �������� (in)
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

/* ������ �������� �����
   v_cons[M] - ������ �������������� ���������� (in) */
double calc_sound_velocity( double v_ncons[M] ) {
	
    return ( sqrt( GAMMA * v_ncons[2] / v_ncons[0] ) );

}

/* ������ ������� ����� ���������� ������� ��������� ������� ��������
   v_cons[M] - ������ �������������� ���������� (in)
   jacob[M][M] - ������� ����� ���������� ������� ��������� ������� �������� (out) */
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

/* ������ ������� �� ����������� �������� ���������� ������� ��������� ������� ��������
   v_cons[M] - ������ �������������� ���������� (in)
   omega[M][M] - ������� �� ����������� �������� ���������� ������� ��������� ������� �������� (out) */
void calc_omega( double v_cons[M], double omega[M][M] ) {

    double v_ncons[M];
    double c;				/* �������� ����� */
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

/* ������ �������� ������� �� ����������� �������� ���������� ������� ��������� ������� ��������
   v_cons[M] - ������ �������������� ���������� (in)
   omega_inverse[M][M] - �������, �������� ������� �� ����������� �������� ���������� ������� ��������� ������� �������� (out) */
void calc_omega_inverse( double v_cons[M], double omega_inverse[M][M] ) {

    double v_ncons[M];
    double c;				/* �������� ����� */
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

/* ������ ������������ ������� � �������� ����������� ����� ���������� ������� ��������� ������� �������� �� ���������
   v_cons[M] - ������ �������������� ���������� (in)
   lambda[M][M] - ������������ ������� � �������� ����������� ����� ���������� ������� ��������� ������� �������� �� ��������� */
void calc_lambda( double v_cons[M], double lambda[M][M] ) {

    double v_ncons[M];
    double c;				/* �������� ����� */

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

/* ������ ������ ���� �� �������

   ��������: Toro E.F. Riemann Solvers and Numerical Methods for Fluid Dynamics. - 2nd Edition. - Springer,
   1999. - P. 221, 225.

   x[N] - ���������� ����� ����� (in)
   v_cons[N][M] - ������� �������������� ���������� � ������� ����� (in)
   time_step_number - ����� �������� ���� �� ������� (in) */
double calc_time_step( double x[N], double v_cons[N][M], int time_step_number ) {

    int i;
    double new_step = BIG_NUMBER;   /* �������������� ����� ��� �� ������� */
    double v_ncons[M];              /* ������ ����������� ���������� � ������� ������ */
    double c;                       /* �������� ����� � ������� ������ */
    double curr_step;               /* ����� ��� �� �������, ������������ �� ���������� � ������� ������ */

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