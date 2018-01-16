#ifndef VEAMY_FUNCTIONS_TYPES_H
#define VEAMY_FUNCTIONS_TYPES_H

#include <vector>
/*
 * Definition of the different function pointers used
 */
typedef double(*func)(double, double);
typedef std::vector<double>(*func_pair)(double, double);

#endif