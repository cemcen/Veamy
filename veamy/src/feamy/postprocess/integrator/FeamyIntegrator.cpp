#include <feamy/postprocess/integrator/FeamyIntegrator.h>
#include <feamy/integration/integrables/IntegrableFunction.h>
#include <feamy/integration/AreaIntegrator.h>
#include <veamy/geometry/VeamyPolygon.h>
#include <veamy/postprocess/computables/IntegrableFunctionComputable.h>

template <typename T>
FeamyIntegrator<T>::FeamyIntegrator() {}

template <typename T>
FeamyIntegrator<T>::FeamyIntegrator(Computable<T>* computable) {
    this->computable = computable;
}

template <typename T>
double FeamyIntegrator<T>::getIntegral(T poly, int polyIndex, std::vector<Point> points) {
    this->computable->setPolygonIndex(polyIndex);
    IntegrableFunctionComputable<T>* computable = new IntegrableFunctionComputable<T>(this->computable);
    double result;

    FeamyConfig* config = FeamyConfig::instance();
    AreaIntegrator<VeamyPolygon,double>::integrate(result, config->getNumberOfGaussPoints(), VeamyPolygon(poly), points, computable);

    return result;
}

template <typename T>
NormIntegrator<T> *FeamyIntegrator<T>::clone() {
    return new FeamyIntegrator<T>;
}

template <typename T>
void FeamyIntegrator<T>::setComputable(Computable<T> *c) {
    this->computable = c;
}

template class FeamyIntegrator<Triangle>;
template class FeamyIntegrator<Polygon>;
