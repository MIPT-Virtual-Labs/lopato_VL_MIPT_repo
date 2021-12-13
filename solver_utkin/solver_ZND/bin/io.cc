#include "io.h"
#include "ZND_utils.h"
#include "Euler_utils.h"

// заполенение некоторые полей структуры
void get_parameters_values(struct Parameters* param)
{
    double Tf = param->Tf;
    double pf = param->pf;
    double m = param->m;
    double R = _R;
    param->R = _R;
    double rf = get_density(Tf, pf, m, R);
    param->rf = rf;
    param->cf = get_sound_velocity(param->g, rf, pf);
    double Zf = _Z_H;
    param->Zf = Zf;
    param->D = get_CJ_velocity(param);
    param->D2 = param->D * param->D;
    param->X = get_ZND_length(param, Zf, _Z_L, _N_TOT);
}

void write_solution( double ZND_solution[_N_OUT][_K_OUT])
{
    // массив, в котором будет храниться имя файла
    char file_name[MAX_STRING_SIZE];
    // файловый дескриптор
    FILE *f_out;
    // помещаем в массив имени файла название solution.dat
    sprintf( file_name, "solution.dat" );
    // открываем или создаем файл для записи (w) в текстовом формате (t)
    f_out = fopen( file_name, "wt" );
    // обязательно проверяем, удалось ли это сделать, иначе - выход
    if ( NULL == f_out )
    {
        printf( "Error - can't open file %s for writing.\n" );
        exit( EXIT_FAILURE );
    }
    for(int i = 0; i < _N_OUT; i++)
    {
        for(int j = 0; j < _K_OUT; j++)
            fprintf( f_out, "%e    ", ZND_solution[i][j] );
        fprintf( f_out, "\n" );
    }
    // правило хорошего тона программирования - закрываем открытый для записи файл
    fclose( f_out );
}
