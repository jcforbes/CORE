#ifndef SF_H
#define SF_H
#include "define.h"
int star_formation_hierarchy(int i);
int star_formation(int i);
int star_formation_binary(int i);
void sf_rate_gen(double *sf_rate, double *m);
#endif
