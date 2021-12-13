#include "ZND_utils.h"
#include "Euler_utils.h"
#include "io.h"
#include "main.h"

int main(int argc, char* argv[])
{
    struct Parameters param;

    if (argc > 8 || argc < 8) {
        printf("Incorrect number of arguments. Please provide temperature fon, pressure fon, gamma, molar mass, heat energy, activation energy, preexponential factor.\n");
        exit(EXIT_FAILURE);
    }
    param.Tf = atof(argv[1]);
    param.pf = atof(argv[2]);

    param.g = atof(argv[3]);
    param.m = atof(argv[4]);

    param.Q = atof(argv[5]);
    param.E = atof(argv[6]);
    param.k = atof(argv[7]);

    get_parameters_values(&param);

    double ZND_solution[_N_OUT][_K_OUT];
    get_ZND_solution(&param, ZND_solution);

    write_solution(ZND_solution);

    return 0;
}
