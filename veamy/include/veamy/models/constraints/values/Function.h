#ifndef VEAMY_FUNCTION_H
#define VEAMY_FUNCTION_H

#include <delynoi/models/basic/Point.h>
#include "ConstraintValue.h"

typedef double(*func_t)(double, double);

class Function : public ConstraintValue{
private:
    func_t f;
public:
    Function(func_t f);

    double getValue(Point p);
};


#endif