#include <veamy/postprocess/integrator/VeamyIntegrator.h>
#include <veamy/utilities/veamy_functions.h>
#include <delynoi/models/polygon/Triangle.h>
#include <feamy/config/FeamyConfig.h>

template <typename T>
VeamyIntegrator<T>::VeamyIntegrator() {}

template <typename T>
VeamyIntegrator<T>::VeamyIntegrator(Computable<T>* computable) {
    this->computable = computable;
}

template <typename T>
double VeamyIntegrator<T>::getIntegral(T poly, int polyIndex, std::vector<Point>& points) {
    this->computable->setPolygonIndex(polyIndex);

    FeamyConfig* config = FeamyConfig::instance();
    double result = veamy_functions::gauss_integration(poly, points, config->getNumberOfGaussPoints(), this->computable);

    return result;
}

template <typename T>
NormIntegrator<T>* VeamyIntegrator<T>::clone() {
    return new VeamyIntegrator<T>;
}

template <typename T>
void VeamyIntegrator<T>::setComputable(Computable<T> *c) {
    this->computable = c;
}

template class VeamyIntegrator<Polygon>;
template class VeamyIntegrator<Triangle>;