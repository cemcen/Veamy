#include <veamy/postprocess/computables/DisplacementDifferenceComputable.h>

DisplacementDifferenceComputable::DisplacementDifferenceComputable(DisplacementValue *v, Eigen::VectorXd u, DOFS d) {
    this->value = v;
    this->nodalValues = u;
    this->dofs = d;
}

double DisplacementDifferenceComputable::apply(double x, double y, int index) {
    Pair<double> u = value->getValue(Point(x,y));

    Pair<int> point_dofs = dofs.pointToDOFS(index);
    Pair<double> uH = Pair<double>(nodalValues[point_dofs.first], nodalValues[point_dofs.second]);

    return std::pow(u.first - uH.first, 2) + std::pow(u.second - uH.second,2);
}
