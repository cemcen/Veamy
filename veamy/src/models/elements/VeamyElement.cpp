#include <veamy/models/elements/VeamyElement.h>
#include <veamy/physics/traction/VeamyTractionVector.h>

VeamyElement::VeamyElement(Conditions *conditions, Polygon &p, UniqueList<Point> &points, DOFS &out, int n_dofs) {
    initializeElement(conditions, p, points, out, n_dofs);
}

void VeamyElement::computeF(DOFS &d, UniqueList<Point> &points, Conditions *conditions) {
    BodyForceVector* bodyForceVector = new VeamyBodyForceVector(this->p, points);
    TractionVector* tractionVector = new VeamyTractionVector(this->p, points,
                                                             conditions->constraints.getNaturalConstraints(), this->n_dofs);

    Element::computeF(d, points, conditions, bodyForceVector, tractionVector);

    delete bodyForceVector;
    delete tractionVector;
}













