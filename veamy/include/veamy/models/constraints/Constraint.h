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
protected:
    /*
     * Value of the constraint
     */
    ConstraintValue* v;
    /*
     * Indexes of the DOFs affected by this constraint
     */
    std::vector<int> direction;
public:
    /*
     * Default constructor
     */
    Constraint();

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
    std::vector<int> getDirection();

    /* Checks if a given axis is affected by this constraint
     * @param axis axis to check
     * @return if the axis is affected (1) or not (0)
     */
    int isAffected(int axis);

    /* Sets the indexes of the dofs associated to a point affected by this constraint. Example: in the linear elasticity
     * problem, each point has two dofs (x or y), and a constraint can affect x(0), y(1) or both(0,1)
     * @param d directions to set
     */
    void setDirection(std::vector<int> d);
};


#endif
