#ifndef VEAMY_CONSTANT_H
#define VEAMY_CONSTANT_H

#include <delynoi/models/basic/Point.h>
#include "ConstraintValue.h"

/*
 * Models a constant constraint (has the same value in all constrained points)
 */
class Constant : public ConstraintValue{
private:
    /*
     * Value of the constraint
     */
    double value;
public:
    /*
     * Constructor
     */
    Constant(double val);

    /* Returns the value of the constraint
     * @param p point to apply the constraint (as it is constant, it is not used)
     * @return value of the constraint
     */
    double getValue(Point p);
};

#endif
