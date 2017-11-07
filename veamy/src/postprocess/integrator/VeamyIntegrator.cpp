#include <veamy/postprocess/integrator/VeamyIntegrator.h>
#include <veamy/utilities/veamy_functions.h>
#include <delynoi/models/polygon/Triangle.h>

template <typename T>
VeamyIntegrator<T>::VeamyIntegrator() {}

template <typename T>
VeamyIntegrator<T>::VeamyIntegrator(Computable<T>* computable) {
    this->computable = computable;
}

template <typename T>
double VeamyIntegrator<T>::getIntegral(T poly, std::vector<Point> points) {
    return veamy_functions::nodal_quadrature<T>(poly, points, this->computable);
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