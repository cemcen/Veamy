#include <feamy/physics/FeamyBodyForceVector.h>
#include <feamy/integration/AreaIntegrator.h>
#include <feamy/integration/integrables/BodyForceIntegrable.h>
#include <veamy/geometry/VeamyTriangle.h>

FeamyBodyForceVector::FeamyBodyForceVector(Triangle t, UniqueList<Point> points, ShapeFunctions *N, int nGauss) {
    this->t = t;
    this->points = points.getList();
    this->N = N;
    this->nGauss = nGauss;
}

Eigen::VectorXd FeamyBodyForceVector::computeForceVector(BodyForce *f) {
    IntegrableFunction<Eigen::VectorXd>* function = new BodyForceIntegrable(this->N, f);
    VeamyTriangle veamyTriangle(t);
    Eigen::VectorXd forceVector;
    forceVector = Eigen::VectorXd::Zero(f->numberOfComponents()* this->N->numberOfShapeFunctions());

    AreaIntegrator<VeamyTriangle,Eigen::VectorXd>::integrate(forceVector, nGauss, veamyTriangle, points, function);

    delete function;
    return forceVector;
}

