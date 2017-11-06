#include <veamy/postprocess/computables/StrainStressDifferenceComputable.h>

StrainStressDifferenceComputable::StrainStressDifferenceComputable(StrainValue *strain, StressValue *stress,
                                                                   Eigen::VectorXd u, DOFS d, ShapeFunctions *N,
                                                                   std::vector<Point> p, Eigen::MatrixXd C) {
    this->strainValue = strain;
    this->stressValue = stress;
    this->nodalValues = u;
    this->dofs = d;
    this->N = N;
    this->points = p;
    this->C = C;
}

double StrainStressDifferenceComputable::apply(double x, double y, int index, Triangle container) {
    Pair<int> point_dofs = dofs.pointToDOFS(index);
    Pair<double> uH = Pair<double>(nodalValues[point_dofs.first], nodalValues[point_dofs.second]);

    Eigen::Matrix Be = StiffnessMatrixIntegrable::BeMatrix(Point(x,y), VeamyTriangle(container).getJacobian(this->points),
                                                           this->N);

    Eigen::VectorXd strain = Be*veamy_functions::to_vector(uH);
    Eigen::VectorXd stress = this->C*strain;

    Trio<double> eH = veamy_functions::to_trio(strain);
    Trio<double> sH = veamy_functions::to_trio(stress);
    Trio<double> e = this->strainValue->getValue(Point(x,y));
    Trio<double> s = this->stressValue->getValue(Point(x,y));

    return (e - eH).dot(s - sH);
}

