#ifndef VEAMY_CONSTRAINT_H
#define VEAMY_CONSTRAINT_H

#include <delynoi/models/basic/Point.h>
#include <vector>
#include <unordered_map>
#include <veamy/models/constraints/values/ConstraintValue.h>
#include <delynoi/models/basic/IndexSegment.h>
#include <utilities/UniqueList.h>
#include <utilities/Pair.h>
#include <veamy/models/dof/DOF.h>

class Constraint{
public:
    enum Direction {Vertical, Horizontal, Total};
private:
    ConstraintValue* v;
    Direction direction;
public:
    Constraint();
    Constraint(Direction d, ConstraintValue* value);

    double getValue(Point p);
    Direction getDirection();
    int isAffected(DOF::Axis axis);
};


#endif
