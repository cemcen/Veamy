#ifndef VEAMY_CONSTRAINTVALUE_H
#define VEAMY_CONSTRAINTVALUE_H

#include <delynoi/models/basic/Point.h>

class ConstraintValue {
public:
    virtual double getValue(Point p) = 0;
};

#endif
