#include <veamy/physics/MaterialPlaneStress.h>

MaterialPlaneStress::MaterialPlaneStress(Materials::material m) : Material(m) {}

MaterialPlaneStress::MaterialPlaneStress(double young, double poisson) : Material(young, poisson) {}

Eigen::MatrixXd MaterialPlaneStress::getMaterialMatrix() {
    Eigen::MatrixXd D;
    D = Eigen::MatrixXd::Zero(3,3);

    double c = (this->material_E)/(1 - std::pow(this->material_v,2));

    D(0,0) = c;
    D(0,1) = c*this->material_v;

    D(1,0) = c*this->material_v;
    D(1,1) = c;

    D(2,2) = 2*c*(1 - this->material_v);

    return D;
}

double MaterialPlaneStress::trace() {
    double c = (this->material_E)/(1 - std::pow(this->material_v,2));

    return c*(2 + 2*(1- this->material_v));
}
