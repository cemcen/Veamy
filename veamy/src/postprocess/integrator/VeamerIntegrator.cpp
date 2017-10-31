#include <veamy/postprocess/integrator/VeamerIntegrator.h>
#include <veamy/utilities/veamy_functions.h>

template <typename T>
VeamerIntegrator<T>::VeamerIntegrator() {}

template <typename T>
VeamerIntegrator<T>::VeamerIntegrator(Computable *computable) {
    this->computable = computable;
}

template <typename T>
double VeamerIntegrator<T>::getIntegral(T poly, std::vector<Point> points) {
    return veamy_functions::volume_nodal_quadrature(poly, points, this->computable);
}

template <typename T>
void VeamerIntegrator<T>::setComputable(Computable *c) {
    this->computable = c;
}
