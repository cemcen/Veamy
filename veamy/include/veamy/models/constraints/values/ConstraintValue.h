#ifndef VEAMY_CONSTRAINTVALUE_H
#define VEAMY_CONSTRAINTVALUE_H

#include <delynoi/models/basic/Point.h>

/*
 * Models a value of a constraint (a load or a dirichlet condition)
 */
class ConstraintValue {
public:
    /* Evaluates the constraint in a point
     * @param p point where the constraint will be evaluated
     * @return value of the constraint on the given point
     */
    virtual double getValue(Point p) = 0;
};

#endif
