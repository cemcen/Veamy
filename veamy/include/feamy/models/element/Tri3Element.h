#ifndef VEAMY_TRI3ELEMENT_H
#define VEAMY_TRI3ELEMENT_H

#include <veamy/models/dof/DOFS.h>
#include <feamy/models/FeamyElement.h>
#include <veamy/lib/Eigen/Dense>
#include <feamy/models/shapefunctions/Tri3ShapeFunctions.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>

/*
 * Represents a linear triangular element
 */
class Tri3Element : public FeamyElement{
public:
    /*
     * Constructor
     */
    Tri3Element(Conditions& conditions, Triangle t, UniqueList<Point>& points, DOFS& out);
};

#endif