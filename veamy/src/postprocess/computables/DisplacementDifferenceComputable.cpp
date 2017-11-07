#include <veamy/postprocess/computables/DisplacementDifferenceComputable.h>

template <typename T>
DisplacementDifferenceComputable<T>::DisplacementDifferenceComputable(DisplacementValue *v, Eigen::VectorXd u, DOFS d) {
    this->value = v;
    this->nodalValues = u;
    this->dofs = d;
}

template <typename T>
double DisplacementDifferenceComputable<T>::apply(double x, double y, int index, T container) {
    Pair<double> u = value->getValue(Point(x,y));

    Pair<int> point_dofs = dofs.pointToDOFS(index);
    Pair<double> uH = Pair<double>(nodalValues[point_dofs.first], nodalValues[point_dofs.second]);

    return std::pow(u.first - uH.first, 2) + std::pow(u.second - uH.second,2);
}

template class DisplacementDifferenceComputable<Polygon>;
template class DisplacementDifferenceComputable<Triangle>;