#ifndef VEAMY_CONSTANT_H
#define VEAMY_CONSTANT_H

#include <delynoi/models/basic/Point.h>
#include "ConstraintValue.h"

class Constant : public ConstraintValue{
private:
    double value;
public:
    Constant(double val);

    double getValue(Point p);
};

#endif
