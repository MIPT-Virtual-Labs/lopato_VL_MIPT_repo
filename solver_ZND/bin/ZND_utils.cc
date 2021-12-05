#include "ZND_utils.h"
#include "Euler_utils.h"

// значение множителя в экспоненте (одностадийная модель Аррениуса)
double get_Arrhenius_arg(double r, double p, double E, double m)
{
    return ( - E * r / (p * m) );
}
// значение плотности ЗНД (можно вычислить через Z)
double get_ZND_density(struct Parameters* param, double Z) 
{
    double rf = param->rf;
    double pf = param->pf;
    double D2 = param->D2;
    double g = param->g;
    double func_z = 1 - sqrt(Z) * (rf * D2 - g * pf) / (g * (rf * D2 + pf));
    return ( rf * (g+1) * rf * D2 / (g * (pf + rf * D2) * func_z) );
}
// значение давления ЗНД (можно вычислить через Z)
double get_ZND_pressure(struct Parameters* param, double Z) 
{
    double pf = param->pf;
    double rf = param->rf;
    double D2 = param->D2;
    double g = param->g;
    return (pf + rf * D2) / (g + 1) * (1 + sqrt(Z) * (rf * D2 - g * pf) / (pf + rf * D2)); 
}
// значение скорости ЗНД в лабораторной системе (можно вычислить через Z)
double get_ZND_velocity(struct Parameters* param, double Z) 
{
    double pf = param->pf;
    double rf = param->rf;
    double g = param->g;
    double D = param->D;
    double D2 = param->D2;
    return sqrt(pf / rf) * (1 + sqrt(Z)) * (rf * D2 - g * pf) / (sqrt(rf * pf) * D) / (g + 1.0);
}
// значение скорости реакции (можно вычислить через Z)
double get_ZND_rate(struct Parameters* param, double Z) 
{
    double r = get_ZND_density(param, Z); 
    double p = get_ZND_pressure(param, Z); 
    double k = param->k;
    double E = param->E;
    double m = param->m;
    double arg = get_Arrhenius_arg(r, p, E, m);
    return k * Z * r * exp(arg);
}
// значение скорости фронта ДВ
double get_CJ_velocity(struct Parameters* param)
{
    double g = param->g;
    double Q = param->Q;
    double s = 0.5 * (g*g - 1) * Q;
    double cf = param->cf;
    double cf2 = cf * cf;
    return sqrt(cf2 + s) + sqrt(s);
}
// значение подынтегральной функции при определении длины ЗНД
double get_ZND_length_integrand(struct Parameters* param, double Z)
{
    double D = param->D;
    double D2 = param->D2;
    double E = param->E;
    double m = param->m;
    double k = param->k;
    double u = get_ZND_velocity(param, Z); 
    double r = get_ZND_density(param, Z);
    double p = get_ZND_pressure(param, Z);
    double arg = get_Arrhenius_arg(r, p, E, m);
    double aaa = (k * r * Z * exp(arg) );
    return (u - D) / (k * r * Z * exp(arg) );
}
// значение длины ЗНД
double get_ZND_length(struct Parameters* param, double Z0, double Z1, double n)
{
    double Zf = Z0;
    double dZ = (Z1 - Zf) / (n - 1);
    double Zk = Zf;
    double Stot = 0;
    double xk = get_ZND_length_integrand(param, Zk);
    int ii = 0;
    for(int i = 0; i < n; i++)
    {
        double Zk1 = Zk + dZ;
        double xk1 = get_ZND_length_integrand(param, Zk1);
        double S = 0.5 * (xk + xk1);
        Stot = Stot + S;
        xk = xk1;
        Zk = Zk1;
    }
    double Itot = Stot * dZ;
    return Itot;
}
// заполнение массива решения 
void get_ZND_solution(struct Parameters* param, double ZND_solution[_N_OUT][_K_OUT])
{
    double X = param->X;
    double dx = X / (_N_TOT - 1);
    // значение длины до текущего узла
    double contribution = 0;
    double zm = param->Zf;
    int ii = 0;
    ZND_solution[ii][_X_O] = 0;
    ZND_solution[ii][_R_O] = get_ZND_density(param, zm);
    ZND_solution[ii][_U_O] = get_ZND_velocity(param, zm);
    ZND_solution[ii][_P_O] = get_ZND_pressure(param, zm);
    ZND_solution[ii][_T_O] = get_temperature(ZND_solution[0][_R_O], ZND_solution[0][_P_O], param->m, param->R);
    ZND_solution[ii][_Z_O] = zm;
    ii++;
    for(int m = 1; m < _N_TOT; m++) 
    {
        double xm1 = m * dx;
        double zm1 = zm;
        double small_integral;
        double eps;
        do
        {
            small_integral = get_ZND_length(param, zm, zm1, _N_SML);
            double df_to_dz =  get_ZND_length_integrand(param, zm1); 	
            double f = contribution + small_integral - xm1;
            double dz = - f / df_to_dz;
            zm1 = zm1 + dz;
            eps = fabs(dz);
        } while (eps > 1e-9);
        contribution += small_integral;
        double um1 = get_ZND_velocity(param, zm1); 
        double rm1 = get_ZND_density(param, zm1);
        double pm1 = get_ZND_pressure(param, zm1);
        double Tm1 = get_temperature(rm1, pm1, param->m, param->R);
        if (m % ((_N_TOT - 1)/(_N_OUT - 1)) == 0)
        {
            ZND_solution[ii][_X_O] = xm1;
            ZND_solution[ii][_R_O] = rm1;
            ZND_solution[ii][_U_O] = um1;
            ZND_solution[ii][_P_O] = pm1;
            ZND_solution[ii][_T_O] = Tm1;
            ZND_solution[ii][_Z_O] = zm1;
            ii++;
        }
        zm = zm1;
    }
}