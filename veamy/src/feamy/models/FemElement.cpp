#include <feamy/models/FemElement.h>

FemElement::FemElement() {}

void FemElement::initializeElement(Conditions &conditions, Triangle &p, UniqueList<Point> &points, DOFS &out, ShapeFunctions* N) {
    this->N = N;
    Element<Triangle>::initializeElement(conditions, p, points, out);
}

void FemElement::computeK(DOFS d, UniqueList<Point> points, Conditions &conditions) {
    int nGauss = 3;
    int n = this->N->numberOfShapeFunctions();
    K = Eigen::MatrixXd::Zero(2*n, 2*n);

    VeamyTriangle t(this->p);
    IntegrableFunction<Eigen::MatrixXd>* integrable = new StiffnessMatrixIntegrable(t, points.getList(),
                                                                   conditions.material->getMaterialMatrix(), this->N);

    AreaIntegrator<VeamyTriangle,Eigen::MatrixXd>::integrate(K, nGauss, t, points.getList(), integrable);

    delete integrable;
}

void FemElement::computeF(DOFS d, UniqueList<Point> points, Conditions &conditions) {
    int nGauss = 3;
    BodyForceVector * bodyForceVector = new FeamyBodyForceVector(this->p, points, this->N, nGauss);
    TractionVector* tractionVector = new FeamyTractionVector(this->p, points, this->N,
                                                             conditions.constraints.getNaturalConstraints(), nGauss);

    Element::computeF(d, points, conditions, bodyForceVector, tractionVector);

    delete bodyForceVector;
    delete tractionVector;
}
