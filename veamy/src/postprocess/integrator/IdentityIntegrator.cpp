#include <veamy/postprocess/integrator/IdentityIntegrator.h>
#include <delynoi/models/polygon/Triangle.h>

template <typename T>
double IdentityIntegrator<T>::getIntegral(T poly, int polyIndex, std::vector<Point>& points) {
    return 1;
}

template <typename T>
NormIntegrator<T>* IdentityIntegrator<T>::clone() {
    return new IdentityIntegrator<T>;
}

template <typename T>
void IdentityIntegrator<T>::setComputable(Computable<T> *c) {
    return;
}

template class IdentityIntegrator<Polygon>;
template class IdentityIntegrator<Triangle>;