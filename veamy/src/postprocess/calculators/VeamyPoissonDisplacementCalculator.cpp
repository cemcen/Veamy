#include <veamy/postprocess/calculators/VeamyPoissonDisplacementCalculator.h>
#include <veamy/postprocess/utilities/norm_utilities.h>

template <typename T>
VeamyPoissonDisplacementCalculator<T>::VeamyPoissonDisplacementCalculator(DOFS d, Eigen::VectorXd u, std::vector<Point>& points) :
        DisplacementCalculator<T>(d, u) {
    this->points = points;
}

template <typename T>
std::vector<double> VeamyPoissonDisplacementCalculator<T>::getDisplacement(double x, double y, int index, T container) {
    return std::vector<double>();
}

template class VeamyPoissonDisplacementCalculator<Triangle>;
template class VeamyPoissonDisplacementCalculator<Polygon>;