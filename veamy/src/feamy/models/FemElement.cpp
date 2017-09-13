#include <feamy/models/FemElement.h>
#include <feamy/integration/AreaIntegrator.h>
#include <feamy/integration/integrables/BodyForceIntegrable.h>
#include <veamy/physics/bodyforces/BodyForceVector.h>
#include <feamy/physics/FeamyBodyForceVector.h>

FemElement::FemElement() {}

void FemElement::initializeElement(Conditions &conditions, Triangle &p, UniqueList<Point> &points, DOFS &out, ShapeFunctions* N) {
    this->N = N;
    Element<Triangle>::initializeElement(conditions, p, points, out);
}

void FemElement::computeF(DOFS d, UniqueList<Point> points, Conditions &conditions) {
    int nGauss = 3;
    BodyForceVector * bodyForceVector = new FeamyBodyForceVector(this->p, points, this->N, nGauss);


}
