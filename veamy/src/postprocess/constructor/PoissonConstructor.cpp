#include <veamy/postprocess/constructors/PoissonConstructor.h>

template <typename T>
PoissonConstructor<T>::PoissonConstructor(DOFS d, Eigen::VectorXd u) : CalculatorConstructor<T>(d, u) {}

template <typename T>
DisplacementCalculator<T> *PoissonConstructor<T>::getDisplacementCalculator(std::vector<Point> &points) {
    return nullptr;
}

template <typename T>
StrainCalculator<T> *PoissonConstructor<T>::getStrainCalculator(std::vector<Point> &points) {
    return nullptr;
}

template class PoissonConstructor<Polygon>;
template class PoissonConstructor<Triangle>;