#include <veamy/postprocess/integrator/VeamyIntegrator.h>
#include <veamy/utilities/veamy_functions.h>


VeamyIntegrator::VeamyIntegrator() {}

VeamyIntegrator::VeamyIntegrator(Computable *computable) {
    this->computable = computable;
}

double VeamyIntegrator::getIntegral(Polygon poly, std::vector<Point> points) {
    return veamy_functions::nodal_quadrature(poly, points, this->computable);
}

void VeamyIntegrator::setComputable(Computable *c) {
    this->computable = c;
}

NormIntegrator *VeamyIntegrator::clone() {
    return new VeamyIntegrator;
}
