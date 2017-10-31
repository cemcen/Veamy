#ifndef VEAMY_FUNCTIONS_TYPES_H
#define VEAMY_FUNCTIONS_TYPES_H

#include <utilities/Trio.h>

typedef double(*func)(double, double);
typedef Trio<double>(*func_trio)(double, double);
typedef Pair<double>(*func_pair)(double, double);

#endif