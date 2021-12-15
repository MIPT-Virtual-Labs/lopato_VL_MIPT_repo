#ifndef __ZND_UTILS_H
#define __ZND_UTILS_H

#include "main.h"

double get_Arrhenius_arg(double r, double p, double E, double m);

double get_ZND_density(struct Parameters* param, double Z);

double get_ZND_pressure(struct Parameters* param, double Z);

double get_ZND_velocity(struct Parameters* param, double Z);

double get_ZND_rate(struct Parameters* param, double Z) ;

double get_CJ_velocity(struct Parameters* param);

double get_ZND_length_integrand(struct Parameters* param, double Z);

double get_ZND_length(struct Parameters* param, double Z0, double Z1, double n);

void get_ZND_solution(struct Parameters* param, double ZND_solution[_N_OUT][_K_OUT]);

#endif /* __ZND_UTILS_H */
