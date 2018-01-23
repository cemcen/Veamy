#ifndef VEAMY_POISSONVEAMYELEMENT_H
#define VEAMY_POISSONVEAMYELEMENT_H

#include <veamy/physics/conditions/PoissonConditions.h>
#include "VeamyElement.h"

/*
 * Models a VEM element solving the poisson problem
 */
class PoissonVeamyElement : public VeamyElement{
protected:
    /*
     * Conditions of the poisson problem
     */
    PoissonConditions* conditions;
public:
    /*
     * Constructor
     */
    PoissonVeamyElement(PoissonConditions *conditions, Polygon &p, UniqueList<Point> &points, DOFS &out, int n_dofs);

    /* Computes the elemental stiffness matrix
     * @param d degrees of freedom of the system
     * @param points mesh points
     */
    void computeK(DOFS &d, UniqueList<Point> &points);
};

#endif