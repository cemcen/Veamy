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
#include <veamy/physics/Conditions.h>
#include <veamy/models/Edge.h>
#include <veamy/physics/materials/Material.h>
#include <veamy/physics/bodyforces/BodyForceVector.h>
#include "Element.h"
#include <veamy/physics/bodyforces/VeamyBodyForceVector.h>
#include <veamy/physics/traction/TractionVector.h>

class VemElement: public Element<Polygon> {
public:
    VemElement(Conditions &conditions, Polygon &p, UniqueList<Point> &points, DOFS &out);

    void computeK(DOFS d, UniqueList<Point> points, Conditions &conditions);
    void computeF(DOFS d, UniqueList<Point> points, Conditions &conditions);

};


#endif
