#ifndef VEAMY_POINTCONSTRAINT_H
#define VEAMY_POINTCONSTRAINT_H

#include "Constraint.h"

class PointConstraint: public Constraint{
private:
    UniqueList<Point> constraints;
public:
    PointConstraint();
    PointConstraint(Point p, Constraint::Direction d, ConstraintValue* value);
    PointConstraint(std::vector<Point> p, Constraint::Direction d, ConstraintValue* value);

    UniqueList<Point> getPoints();
};

#endif