#ifndef VEAMY_POINTCONSTRAINT_H
#define VEAMY_POINTCONSTRAINT_H

#include "Constraint.h"

/*
 * Models a constraint applied to a set of points of the domain
 */
class PointConstraint: public Constraint{
private:
    /*
     * Constrained points
     */
    UniqueList<Point> constraints;
public:
    /*
     * Default constructor
     */
    PointConstraint();

    /*
     * Constructor. Constraints a single point
     */
    PointConstraint(Point p, Constraint::Direction d, ConstraintValue* value);

    /*
     * Constructor. Constraints a set of points
     */
    PointConstraint(std::vector<Point> p, Constraint::Direction d, ConstraintValue* value);

    /*
     * @return list of constrained points
     */
    UniqueList<Point> getPoints();
};

#endif