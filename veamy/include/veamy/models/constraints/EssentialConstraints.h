#ifndef VEAMY_ESSENTIALCONSTRAINTS_H
#define VEAMY_ESSENTIALCONSTRAINTS_H

#include <delynoi/models/basic/Point.h>
#include <unordered_map>
#include <vector>
#include <veamy/lib/Eigen/Dense>
#include <veamy/models/constraints/values/ConstraintValue.h>
#include <veamy/models/dof/DOF.h>
#include "Constraint.h"
#include "Constraints.h"
#include <veamy/utilities/SegmentPair.h>

/*
 * Contains the essential (Dirichlet) boundary conditions
 */
class EssentialConstraints : public Constraints{
public:
    /*
     * Default constructor
     */
    EssentialConstraints();

    /* Returns the value of the essential constraints evaluated in each constrained DOF
     * @param points mesh points
     * @param dofs list of essentially constrained DOF
     */
    Eigen::VectorXd getBoundaryValues(std::vector<Point> points, UniqueList<DOF> dofs);
};


#endif
