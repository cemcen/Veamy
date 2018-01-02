#include <veamy/postprocess/calculators/VeamyDisplacementCalculator.h>

template <typename T>
VeamyDisplacementCalculator<T>::VeamyDisplacementCalculator(DOFS d, Eigen::VectorXd u) : DisplacementCalculator<T>(d, u) {}

template <typename T>
Pair<double> VeamyDisplacementCalculator<T>::getDisplacement(double x, double y, int index, T container) {
    std::vector<int> point_dofs = this->dofs.pointToDOFS(index);
    Pair<double> uH = Pair<double>(this->nodalValues[point_dofs[0]], this->nodalValues[point_dofs[1]]);

    return uH;
}

template class VeamyDisplacementCalculator<Triangle>;
template class VeamyDisplacementCalculator<Polygon>;