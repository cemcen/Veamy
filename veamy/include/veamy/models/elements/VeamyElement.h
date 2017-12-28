#ifndef VEAMY_VEMELEMENT_H
#define VEAMY_VEMELEMENT_H

#include <veamy/models/dof/DOF.h>
#include <veamy/models/dof/DOFS.h>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/lib/Eigen/Dense>
#include <veamy/utilities/SegmentPair.h>
#include <veamy/physics/bodyforces/BodyForce.h>
#include <iostream>
#include <veamy/models/constraints/NaturalConstraints.h>
#include <veamy/models/constraints/ConstraintsContainer.h>
#include <veamy/physics/conditions/Conditions.h>
#include <veamy/models/Edge.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/physics/bodyforces/BodyForceVector.h>
#include "veamy/models/Element.h"
#include <veamy/physics/bodyforces/VeamyBodyForceVector.h>
#include <veamy/physics/traction/TractionVector.h>

/*
 * Models an element using VEM to solve the linear elasticity problem
 */
class VeamyElement: public Element<Polygon> {
public:
    /*
     * Constructor
     */
    VeamyElement(Conditions *conditions, Polygon &p, UniqueList<Point> &points, DOFS &out, int n_dofs);

    /* Computes the elemental stiffness matrix
     * @param d degrees of freedom of the system
     * @param points mesh points
     * @param conditions conditions of the problem
     */
    virtual void computeK(DOFS d, UniqueList<Point> points) = 0;

    /* Computes the elemental load vector
    * @param d degrees of freedom of the system
    * @param points mesh points
    * @param conditions conditions of the problem
    */
    void computeF(DOFS d, UniqueList<Point> points, Conditions* conditions);

};


#endif
