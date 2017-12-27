#ifndef VEAMY_POINTFORCES_H
#define VEAMY_POINTFORCES_H

#include <veamy/models/constraints/NaturalConstraints.h>

/*
 * Namespace that contains all functions related to the operation and inclusion of puntual forces
 */
namespace point_forces{
    /* Adds a puntual force to the elemental load vector if any of the points is loaded
     * @param tractionVector traction part of the elemental load vector
     * @param natural natural (Neumann) boundary conditions
     * @param p1 p2 points to check
     */
    extern void
    addPointForces(Eigen::VectorXd &tractionVector, NaturalConstraints natural, Point p1, Point p2, int n_dofs);
}

#endif