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

/*
 * Models a single constraint of the system
 */
class Constraint{
public:
    /*
     * Possible directions of the constraints
     */
    enum Direction {Vertical, Horizontal, Total, None};
private:
    /*
     * Value of the constraint
     */
    ConstraintValue* v;
    /*
     * Direction of this particular constraint
     */
    Direction direction;
public:
    /*
     * Default constructor
     */
    Constraint();

    /*
     * Constructor
     */
    Constraint(Direction d, ConstraintValue* value);

    /*
    * Constructor
    */
    Constraint(ConstraintValue* value);

    /* Returns the value of the constraint evaluated at a given point
     * @param p point to evaluate the constraint
     * @return value of the constraint in p
     */
    double getValue(Point p);

    /*
     * @return direction of the constraint
     */
    Direction getDirection();

    /* Checks if a given axis is affected by this constraint
     * @param axis axis to check
     * @return if the axis is affected (1) or not (0)
     */
    int isAffected(DOF::Axis axis);
};


#endif
