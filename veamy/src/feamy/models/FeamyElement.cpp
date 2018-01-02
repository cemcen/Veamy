#include <feamy/models/FeamyElement.h>
#include <feamy/config/FeamyConfig.h>

FeamyElement::FeamyElement(Conditions *conditions, Triangle &p, UniqueList<Point> &points, DOFS &out, int n_dofs) {
    initializeElement(conditions, p, points, out, n_dofs);
}

void FeamyElement::setShapeFunctions(ShapeFunctions *N) {
    this->N = N;

    this->stiffnessMatrixIntegrable->setShapeFunctions(this->N);
    this->bodyForceIntegrable->setShapeFunctions(this->N);
    this->boundaryVectorIntegrable->setShapeFunctions(this->N);
}

void FeamyElement::setIntegrables(BodyForceIntegrable *bodyForceIntegrable,
                                  BoundaryVectorIntegrable *boundaryVectorIntegrable,
                                  StiffnessMatrixIntegrable *stiffnessMatrixIntegrable) {
    this->bodyForceIntegrable = bodyForceIntegrable;
    this->boundaryVectorIntegrable = boundaryVectorIntegrable;
    this->stiffnessMatrixIntegrable = stiffnessMatrixIntegrable;
}

void FeamyElement::computeK(DOFS &d, UniqueList<Point> &points) {
    FeamyConfig* config = FeamyConfig::instance();
    int n = this->N->numberOfShapeFunctions();
    K = Eigen::MatrixXd::Zero(this->n_dofs*n, this->n_dofs*n);

    VeamyTriangle t(this->p);

    AreaIntegrator<VeamyTriangle,Eigen::MatrixXd>::integrate(K, config->getNumberOfGaussPoints(), t,
                                                             points.getList(), stiffnessMatrixIntegrable);
}

void FeamyElement::computeF(DOFS &d, UniqueList<Point> &points, Conditions *conditions) {
    FeamyConfig* config = FeamyConfig::instance();
    int nGauss = config->getNumberOfGaussPoints();
    BodyForceVector * bodyForceVector = new FeamyBodyForceVector(this->p, points, this->N, nGauss, bodyForceIntegrable);
    TractionVector* tractionVector = new FeamyTractionVector(this->p, points, this->N,
                                                             conditions->constraints.getNaturalConstraints(), nGauss, this->n_dofs,
                                                             boundaryVectorIntegrable);

    Element::computeF(d, points, conditions, bodyForceVector, tractionVector);

    delete bodyForceVector;
    delete tractionVector;
}

ShapeFunctions *FeamyElement::getShapeFunctions() {
    return this->N;
}
