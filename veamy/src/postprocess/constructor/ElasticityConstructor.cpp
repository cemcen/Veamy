#include <veamy/postprocess/constructors/ElasticityConstructor.h>
#include <veamy/postprocess/calculators/VeamyElasticityDisplacementCalculator.h>
#include <veamy/postprocess/calculators/VeamyElasticityStrainCalculator.h>

template <typename T>
ElasticityConstructor<T>::ElasticityConstructor(DOFS &d, const Eigen::VectorXd &u) : CalculatorConstructor<T>(d, u) {}

template <typename T>
DisplacementCalculator<T> *
ElasticityConstructor<T>::getDisplacementCalculator(std::vector<Point> &points) {
    return new VeamyElasticityDisplacementCalculator<T>(this->dofs, this->u, points);
}

template <typename T>
StrainCalculator<T>* ElasticityConstructor<T>::getStrainCalculator(std::vector<Point> &points) {
    return new VeamyElasticityStrainCalculator<T>(this->dofs, this->u, points);
}

template class ElasticityConstructor<Polygon>;
template class ElasticityConstructor<Triangle>;