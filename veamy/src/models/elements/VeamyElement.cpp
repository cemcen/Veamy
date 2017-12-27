#include <veamy/models/elements/VeamyElement.h>
#include <veamy/physics/traction/VeamyTractionVector.h>
#include <veamy/config/VeamyConfig.h>

VeamyElement::VeamyElement(Conditions* conditions, Polygon &p, UniqueList<Point> &points, DOFS &out) {
    initializeElement(conditions, p, points, out);
}

void VeamyElement::computeF(DOFS d, UniqueList<Point> points, Conditions* conditions) {
    BodyForceVector* bodyForceVector = new VeamyBodyForceVector(this->p, points);
    TractionVector* tractionVector = new VeamyTractionVector(this->p, points,
                                                             conditions->constraints.getNaturalConstraints(),);

    Element::computeF(d, points, conditions, bodyForceVector, tractionVector);

    delete bodyForceVector;
    delete tractionVector;
}













