#ifndef __EULER_UTILS
#define __EULER_UTILS

#include "main.h"

double get_density(double T, double p, double m, double R);

double get_temperature(double r, double p, double m, double R);

double get_sound_velocity(double g, double r, double p);

#endif /* __EULER_UTILS */