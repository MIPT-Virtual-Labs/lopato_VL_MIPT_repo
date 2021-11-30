/*
 * utils.h
 *
 * ������� �������, ����������� ��� ������� ��������� ������� ��������.
 *
 * (c) ����� �����, 2012
 *
 * ������: 24 ����� 2012 �.
 *
 */

#ifndef __UTILS_H_
#define __UTILS_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "main.h"

#define BIG_NUMBER  1.e10   /* ������� ����� ��� ������������� ��������� ���������� */

/* ������� ������� ��������� ������
   u_cons_l[M] - ������ �������������� ���������� ����� �� ������� (in)
   u_cons_r[M] - ������ �������������� ���������� ������ �� ������� (in)
   flux[M] - ������ ������ (out) */
void calc_flux( double u_cons_l[M], double u_cons_r[M], double flux[M] );

/* �������������� ������� �������������� ���������� � ������ ����������������
   v_cons[M] - ������ �������������� ���������� (in)
   v_ncons[M] - ������ ���������������� ���������� (out) */
void convert_cons_to_noncons( double v_cons[M], double v_ncons[M] );

/* �������������� ������� ���������������� ���������� � ������ ��������������
   v_ncons[M] - ������ ���������������� ���������� (in)
   v_cons[M] - ������ �������������� ���������� (out) */
void convert_noncons_to_cons( double v_ncons[M], double v_cons[M] );

/* ������ ������� ����������������� ������ �� ������� �������������� ����������
   v_cons[M] - ������ �������������� ���������� (in)
   flux[M] - �������������� ������ ����������������� ������ (out) */
void diff_flux_cons( double v_cons[M], double flux[M] );

/* ������ ������� ����������������� ������ �� ������� ����������� ����������
   v_ncons[M] - ������ ����������� ���������� (in)
   flux[M] - �������������� ������ ����������������� ������ (out) */
void diff_flux_ncons( double v_ncons[M], double flux[M] );

/* ��������� ���������� �������
   v_cons[M] - ������ �������������� ���������� (in)
   boun_v[M] - ������ �������������� ����������, ����������� ��� ���������� ���������� ������� (out)
   boun_type - ��� ���������� ������� (in) */
void boundary( double v_cons[M], double boun_v[M], int boun_type );

/* ������������� �������-�������
   u_cons[N][M] - �������� ������� �������������� ���������� � ������� ���� ����� (out) 
   ������ ���� ���������������� ��������� ����� � ������ �� �������
   r_left, r_right - ��������� (in)
   u_left, u_right - �������� (in)
   p_left, p_right - �������� (in)
*/
void init_solution( double u_cons[N][M], double r_left, double r_right, double u_left, double u_right, double p_left, double p_right );

/* ������ �������� �����
   v_cons[M] - ������ �������������� ���������� (in) */
double calc_sound_velocity( double v_ncons[M] );

/* ������ ������� ����� ���������� ������� ��������� ������� ��������
   v_cons[M] - ������ �������������� ���������� (in)
   jacob[M][M] - ������� ����� ���������� ������� ��������� ������� �������� (out) */
void calc_jacob( double v_cons[M], double jacob[M][M] );

/* ������ ������� �� ����������� �������� ���������� ������� ��������� ������� ��������
   v_cons[M] - ������ �������������� ���������� (in)
   omega[M][M] - ������� �� ����������� �������� ���������� ������� ��������� ������� �������� (out) */
void calc_omega( double v_cons[M], double omega[M][M] );

/* ������ �������� ������� �� ����������� �������� ���������� ������� ��������� ������� ��������
   v_cons[M] - ������ �������������� ���������� (in)
   omega_inverse[M][M] - �������, �������� ������� �� ����������� �������� ���������� ������� ��������� ������� �������� (out) */
void calc_omega_inverse( double v_cons[M], double omega_inverse[M][M] );

/* ������ ������������ ������� � �������� ����������� ����� ���������� ������� ��������� ������� �������� �� ���������
   v_cons[M] - ������ �������������� ���������� (in)
   lambda[M][M] - ������������ ������� � �������� ����������� ����� ���������� ������� ��������� ������� �������� �� ��������� */
void calc_lambda( double v_cons[M], double lambda[M][M] );

/* ������ ������ ���� �� �������

   ��������: Toro E.F. Riemann Solvers and Numerical Methods for Fluid Dynamics. - 2nd Edition. - Springer,
   1999. - P. 221, 225.

   x[N] - ���������� ����� ����� (in)
   v_cons[N][M] - ������� �������������� ���������� � ������� ����� (in)
   time_step_number - ����� �������� ���� �� ������� (in) */
double calc_time_step( double x[N], double v_cons[N][M], int time_step_number );

#endif /* __UTILS_H_ */