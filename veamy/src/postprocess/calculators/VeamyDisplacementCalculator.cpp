#include <veamy/postprocess/calculators/VeamyDisplacementCalculator.h>

template <typename T>
VeamyDisplacementCalculator<T>::VeamyDisplacementCalculator(DOFS d, Eigen::VectorXd u) : DisplacementCalculator<T>(d, u) {}

template <typename T>
Pair<double> VeamyDisplacementCalculator<T>::getDisplacement(double x, double y, int index, T container) {
    Pair<int> point_dofs = this->dofs.pointToDOFS(index);
    Pair<double> uH = Pair<double>(this->nodalValues[point_dofs.first], this->nodalValues[point_dofs.second]);
}

template class VeamyDisplacementCalculator<Triangle>;
template class VeamyDisplacementCalculator<Polygon>;