#include <feamy/problem/linear_elasticity/LinearElasticityStiffnessMatrixIntegrable.h>

LinearElasticityStiffnessMatrixIntegrable::LinearElasticityStiffnessMatrixIntegrable(VeamyTriangle &t,
                                                                                     std::vector<Point> &points,
                                                                                     Eigen::MatrixXd D) :
        StiffnessMatrixIntegrable(t,points){
    this->D = D;
}

LinearElasticityStiffnessMatrixIntegrable::LinearElasticityStiffnessMatrixIntegrable() {}

Eigen::MatrixXd LinearElasticityStiffnessMatrixIntegrable::apply(Point point) {
    Eigen::MatrixXd Be = LinearElasticityStiffnessMatrixIntegrable::BeMatrix(point, this->J, this->N);
    return Be.transpose()*D*Be;
}

Eigen::MatrixXd LinearElasticityStiffnessMatrixIntegrable::BeMatrix(Point p, Eigen::MatrixXd J, ShapeFunctions *N) {
    Eigen::MatrixXd Be;
    Be = Eigen::MatrixXd::Zero(3, N->numberOfShapeFunctions()*2);

    std::vector<Pair<double>> dN = N->evaluateDerivatives(p);
    Eigen::MatrixXd invJ = J.inverse();

    for (int v = 0; v < N->numberOfShapeFunctions(); ++v) {
        Be(0,2*v) = dN[v].first*invJ(0,0) + dN[v].second*invJ(0,1);
        Be(1,2*v+1) = dN[v].first*invJ(1,0) + dN[v].second*invJ(1,1);
        Be(2,2*v) = dN[v].first*invJ(1,0) + dN[v].second*invJ(1,1);
        Be(2,2*v+1) = dN[v].first*invJ(0,0) + dN[v].second*invJ(0,1);
    }

    return Be;
}
