#include <feamy/integration/integrables/StiffnessMatrixIntegrable.h>

StiffnessMatrixIntegrable::StiffnessMatrixIntegrable(VeamyTriangle t, std::vector<Point> points, Eigen::MatrixXd D,
                                                             ShapeFunctions *N) {
    this->J = t.getJacobian(points);
    this->D = D;
    this->N = N;
}

Eigen::MatrixXd StiffnessMatrixIntegrable::apply(Point point) {
    Eigen::MatrixXd Be;
    Be = Eigen::MatrixXd::Zero(3,this->N->numberOfShapeFunctions()*2);

    std::vector<Pair<double>> dN = N->evaluateDerivatives(point);
    Eigen::MatrixXd invJ = J.inverse();

    for (int v = 0; v < this->N->numberOfShapeFunctions(); ++v) {
        Be(0,2*v) = dN[v].first*invJ(0,0) + dN[v].second*invJ(0,1);
        Be(1,2*v+1) = dN[v].first*invJ(1,0) + dN[v].second*invJ(1,1);
        Be(2,2*v) = dN[v].first*invJ(1,0) + dN[v].second*invJ(1,1);
        Be(2,2*v+1) = dN[v].first*invJ(0,0) + dN[v].second*invJ(0,1);
    }

    return Be.transpose()*D*Be;
}
