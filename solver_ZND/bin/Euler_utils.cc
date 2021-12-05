#include "Euler_utils.h"

double get_density(double T, double p, double m, double R)
{
    return p * m / (T * R);
}
double get_temperature(double r, double p, double m, double R)
{
    return p * m / (r * R);
}
double get_sound_velocity(double g, double r, double p)
{
    return sqrt(g * p / r);
}