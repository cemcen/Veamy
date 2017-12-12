#ifndef VEAMY_FUNCTION_H
#define VEAMY_FUNCTION_H

#include <delynoi/models/basic/Point.h>
#include "ConstraintValue.h"


typedef double(*func_t)(double, double);

/*
 * Defines a constraint value following a function, created from a function pointer
 */
class Function : public ConstraintValue{
private:
    /*
     * Pointer to function defining a constraint
     */
    func_t f;
public:
    /*
     * Constructor
     */
    Function(func_t f);

    /* Evaluates the function in a given point
     * @param p point used to evaluate
     * @return function value
     */
    double getValue(Point p);
};


#endif