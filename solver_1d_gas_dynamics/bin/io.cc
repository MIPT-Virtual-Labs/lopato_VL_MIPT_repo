/*
 * io.cc
 *
 * ������� �����/������.
 *
 * (c) ����� �����, 2012
 *
 * ������: 25 ����� 2012 �.
 *
 */

#include <stdio.h>

#include "io.h"
#include "utils.h"

/* ������ ������� � ����
   xc[N] - ���������� ������� ����� (in)
   v_cons[N][M] - ������� �������������� ���������� � ������� ����� (in)
   time - ������ �������, �������� ������������� ������������� (in) */
void write_solution( double xc[N], double v_cons[N][M], double time ) {

    char file_name[MAX_FILE_NAME];
    double v_ncons[M];
    int i, j;

    sprintf( file_name, "solution.dat" );

    FILE *f_out = fopen(file_name, "wt");
    if ( NULL == f_out ) {
        printf( "Error - can't open file %s for writing.\n" );
    }

    for ( i = 0; i < N; i++ ) {
        fprintf( f_out, "%e", xc[i] );
        convert_cons_to_noncons( v_cons[i], v_ncons );
        for ( j = 0; j < M; j++ )
            fprintf( f_out, " %e", v_ncons[j] );
        fprintf( f_out, " %e", v_ncons[2] / v_ncons[0] / ( GAMMA - 1.0 ) );
        fprintf( f_out, "\n" );
    }

    fclose( f_out );

}
