#ifndef VEAMY_FEMELEMENT_H
#define VEAMY_FEMELEMENT_H

#include <delynoi/models/polygon/Triangle.h>
#include <veamy/physics/Conditions.h>
#include <veamy/models/Element.h>
#include <feamy/models/shapefunctions/ShapeFunctions.h>
#include <vector>
#include <feamy/integration/AreaIntegrator.h>
#include <feamy/integration/integrables/BodyForceIntegrable.h>
#include <veamy/physics/bodyforces/BodyForceVector.h>
#include <feamy/physics/FeamyBodyForceVector.h>
#include <feamy/physics/FeamyTractionVector.h>
#include <veamy/geometry/VeamyTriangle.h>
#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>

class FeamyElement: public Element<Triangle> {
protected:
    ShapeFunctions* N;
public:
    FeamyElement();
    void initializeElement(Conditions &conditions, Triangle &p, UniqueList<Point> &points, DOFS &out, ShapeFunctions* N);
    void computeK(DOFS d, UniqueList<Point> points, Conditions &conditions);
    void computeF(DOFS d, UniqueList<Point> points, Conditions& conditions);
};

#endif