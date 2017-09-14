#ifndef VEAMY_TRI3ELEMENT_H
#define VEAMY_TRI3ELEMENT_H

#include <veamy/models/dof/DOFS.h>
#include <feamy/models/FemElement.h>
#include <veamy/lib/Eigen/Dense>
#include <feamy/models/shapefunctions/Tri3ShapeFunctions.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>

class Tri3Element : public FemElement{
public:
    Tri3Element(Conditions conditions, Triangle t, UniqueList<Point>& points, DOFS& out);
};

#endif