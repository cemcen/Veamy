#include <veamy/postprocess/constructors/PoissonConstructor.h>
#include <veamy/postprocess/calculators/VeamyPoissonDisplacementCalculator.h>
#include <veamy/postprocess/calculators/VeamyPoissonStrainCalculator.h>

template <typename T>
PoissonConstructor<T>::PoissonConstructor(DOFS d, Eigen::VectorXd u) : CalculatorConstructor<T>(d, u) {}

template <typename T>
DisplacementCalculator<T> *PoissonConstructor<T>::getDisplacementCalculator(std::vector<Point> &points) {
    return new VeamyPoissonDisplacementCalculator<T>(this->dofs, this->u, points);
}

template <typename T>
StrainCalculator<T> *PoissonConstructor<T>::getStrainCalculator(std::vector<Point> &points) {
    return new VeamyPoissonStrainCalculator<T>(this->dofs, this->u, points);
}

template class PoissonConstructor<Polygon>;
template class PoissonConstructor<Triangle>;