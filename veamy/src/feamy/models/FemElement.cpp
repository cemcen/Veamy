#include <feamy/models/FemElement.h>
#include <feamy/integration/AreaIntegrator.h>
#include <feamy/integration/integrables/BodyForceIntegrable.h>


FemElement::FemElement(VeamyConditions &conditions, Triangle &p, UniqueList<Point> &points, DOFS &out) {
    initializeElement(conditions, p, points, out);
    this->N = ShapeFunctions(p, points.getList());
}

void FemElement::computeK(DOFS d, UniqueList<Point> points, VeamyConditions &conditions) {
    Eigen::MatrixXd Be;
    Be = Eigen::MatrixXd::Zero(3,6);

    std::vector<Pair<double>> dN = N.evaluateDerivatives(Point(0,0));
    for (int v = 0; v < 3; ++v) {
        Be(0,2*v) = dN[v].first;
        Be(1,2*v+1) = dN[v].second;
        Be(2,2*v) = dN[v].second;
        Be(2,2*v+1) = dN[v].first;
    }

    this->K = this->p.getArea()*Be.transpose()*conditions.material->getMaterialMatrix()*Be;
}

void FemElement::computeF(DOFS d, UniqueList<Point> points, FeamyConditions &conditions) {
    this->f = Eigen::VectorXd::Zero(2*this->p.numberOfSides());
    int nGauss = 3;

    Eigen::VectorXd fBody;
    fBody = AreaIntegrator::integrate(nGauss, this->p, points.getList(), new BodyForceIntegrable(this->N, conditions.));

}
