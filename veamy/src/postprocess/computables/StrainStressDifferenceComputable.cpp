#include <veamy/postprocess/computables/StrainStressDifferenceComputable.h>

template <typename T>
StrainStressDifferenceComputable<T>::StrainStressDifferenceComputable(StrainValue *strain, StressValue *stress,
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

template <typename T>
double StrainStressDifferenceComputable<T>::apply(double x, double y, int index, T container) {
    Pair<int> point_dofs = dofs.pointToDOFS(index);
    Pair<double> uH = Pair<double>(nodalValues[point_dofs.first], nodalValues[point_dofs.second]);

    Eigen::MatrixXd Be = StiffnessMatrixIntegrable::BeMatrix(Point(x,y), VeamyTriangle(container).getJacobian(this->points),
                                                           this->N);

    Eigen::VectorXd strain = Be*veamy_functions::to_vector<double>(uH);
    Eigen::VectorXd stress = this->C*strain;

    Trio<double> eH = veamy_functions::to_trio<double>(strain);
    Trio<double> sH = veamy_functions::to_trio<double>(stress);
    Trio<double> e = this->strainValue->getValue(Point(x,y));
    Trio<double> s = this->stressValue->getValue(Point(x,y));

    return (e - eH).dot(s - sH);
}

template class StrainStressDifferenceComputable<Polygon>;
template class StrainStressDifferenceComputable<Triangle>;