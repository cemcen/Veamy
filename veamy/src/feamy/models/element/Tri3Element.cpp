#include <feamy/models/shapefunctions/Tri3ShapeFunctions.h>
#include "feamy/models/element/Tri3Element.h"

Tri3Element::Tri3Element(Conditions conditions, Triangle t, UniqueList<Point>& points, DOFS& out) {
    ShapeFunctions* N = new Tri3ShapeFunctions(t, points.getList());
    FemElement::initializeElement(conditions, t, points, out, N);
}

void Tri3Element::computeK(DOFS d, UniqueList<Point> points, Conditions &conditions) {
    Eigen::MatrixXd Be;
    Be = Eigen::MatrixXd::Zero(3,6);

    std::vector<Pair<double>> dN = N->evaluateDerivatives(Point(0,0));
    for (int v = 0; v < 3; ++v) {
        Be(0,2*v) = dN[v].first;
        Be(1,2*v+1) = dN[v].second;
        Be(2,2*v) = dN[v].second;
        Be(2,2*v+1) = dN[v].first;
    }

    this->K = this->p.getArea()*Be.transpose()*conditions.material->getMaterialMatrix()*Be;
}
