#include <veamy/physics/materials/MaterialPlaneStrain.h>

MaterialPlaneStrain::MaterialPlaneStrain(Materials::material m) : Material(m) {}

MaterialPlaneStrain::MaterialPlaneStrain(double young, double poisson) : Material(young, poisson) {}

Eigen::MatrixXd MaterialPlaneStrain::getMaterialMatrix() {
    Eigen::MatrixXd D;
    D = Eigen::MatrixXd::Zero(3,3);

    double c = (this->material_E)/((1 + this->material_v)*(1 - 2*this->material_v));

    D(0,0) = c*(1 - this->material_v);
    D(0,1) = c*this->material_v;

    D(1,0) = c*this->material_v;
    D(1,1) = c*(1 - this->material_v);

    D(2,2) = this->factor * c*(1 - 2*this->material_v);

    return D;
}

double MaterialPlaneStrain::trace() {
    double c = (this->material_E)/((1 + this->material_v)*(1 - 2*this->material_v));

    return c*(2*(1 - this->material_v) + 2*(1 - 2*this->material_v));
}
