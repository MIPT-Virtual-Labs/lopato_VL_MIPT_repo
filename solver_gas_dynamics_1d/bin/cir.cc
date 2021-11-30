/*
 * cir.cc
 *
 * ����� �������-��������-��� ������� ������� ��� ���������� ������� ��������� ������� ��������.
 *
 * ������� �.�. � ���������� ���������� ���� � ������������� �������������� ��� ��������� ���������������� ���� //
 * ������. - 1978. - �. 18, � 6. - �. 1485.
 *
 * ����������� �.�., ��������� �.�., ������� �.�. �������������� ������� ���������� ������� ��������������� ������
 * ���������. - �.: ���������, 2001. - �. 63. - ������� (2.3.25), (2.3.26).
 *
 * (c) ����� �����, 2012
 *
 * ������: 24 ����� 2012 �.
 *
 */

#include "cir.h"

#include "utils.h"
#include "math_utils.h"

/*  ����� �������-��������-��� ������� �������
    left_params[M] - ������ �������������� ���������� ����� �� ������� (in)
    right_params[M] - ������ �������������� ���������� ������ �� ������� (in)
    flux[M] - ������������ ������ ������ (out) */
void cir_flux( double left_params[M], double right_params[M], double flux[M] ) {

    int i, j;

    /* ��������� ������������ ���� ������ ��� ���������� ����� � ������ �� ������� */
    double m_left[M][M], m_right[M][M];

    /* ������� ���������������� ������� ��� ���������� ����� � ������ �� ������� */
    double left_diff_flux[M], right_diff_flux[M];

    /* ������ ���������������� ������� */
    diff_flux_cons( left_params, left_diff_flux );
    diff_flux_cons( right_params, right_diff_flux );

    /* ����������� ������� � ������� ������ ��� ���������� ����� �� ������� */
    cir_util( left_params, m_left );

    /* ����������� ������� � ������� ������ ��� ���������� ������ �� ������� */
    cir_util( right_params, m_right );

    for ( i = 0; i < M; i++ ) {
        flux[i] = 0.5 * ( left_diff_flux[i] + right_diff_flux[i] );
            for ( j = 0; j < M; j++ )
                flux[i] += 0.5 * ( 0.5 * ( m_left[i][j] + m_right[i][j] ) ) * ( left_params[j] - right_params[j] );
    }

}

/*  ������ �������, �������� � ������� ������
    cons_params[M] - ������ ���������������� ���������� (in)
    m[M][M] - ������� ������� (out) */
void cir_util( double cons_params[M], double m[M][M] ) {

    /* ������� �� ����������� �������� ������� ��������� ������� �������� */
    double omega[M][M];

    /* �������� � ������� �� ����������� �������� ������� ��������� ������� �������� */
    double omega_inverse[M][M];

    /* ������������ ������� � �������� ����������� ����� ������� ��������� ������� �������� */
    double lambda[M][M];

    /* ��������� ������������ ������ ����� � ������ */
    double m_tmp[M][M];

    calc_omega( cons_params, omega );
    calc_lambda( cons_params, lambda );
    calc_omega_inverse( cons_params, omega_inverse );
    mult_matrixes( omega, lambda, m_tmp );
    mult_matrixes( m_tmp, omega_inverse, m );

}
