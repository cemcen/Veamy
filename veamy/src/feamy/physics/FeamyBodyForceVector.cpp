#include <feamy/physics/FeamyBodyForceVector.h>
#include <feamy/integration/AreaIntegrator.h>
#include <feamy/problem/linear_elasticity/LinearElasticityBodyForceIntegrable.h>
#include <veamy/geometry/VeamyTriangle.h>

FeamyBodyForceVector::FeamyBodyForceVector(Triangle t, UniqueList<Point>& points, ShapeFunctions *N, int nGauss,
                                           BodyForceIntegrable *integrable) {
    this->t = t;
    this->points = points.getList();
    this->N = N;
    this->nGauss = nGauss;
    this->integrable = integrable;
}

Eigen::VectorXd FeamyBodyForceVector::computeForceVector(BodyForce *f) {
    VeamyTriangle veamyTriangle(t);
    Eigen::VectorXd forceVector;
    forceVector = Eigen::VectorXd::Zero(f->numberOfComponents()* this->N->numberOfShapeFunctions());

    AreaIntegrator<VeamyTriangle,Eigen::VectorXd>::integrate(forceVector, nGauss, veamyTriangle, points, integrable);

    return forceVector;
}

