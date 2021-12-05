#ifndef __IO_H
#define __IO_H

#include "main.h"

void get_parameters_values(struct Parameters* param);

void write_solution( double ZND_solution[_N_OUT][_K_OUT]);

#endif /* __IO_H */