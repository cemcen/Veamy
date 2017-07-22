#include <veamy/physics/Material.h>
#include <veamy/config/VeamyConfig.h>
#include <iostream>

Material::Material(double E, double v) {
    this->material_v = v;
    this->material_E = E;
}

Material::Material() {}

Material::Material(Materials::material m) {
    material_info info = Materials::properties[m];

    this->material_E = info.E;
    this->material_v = info.v;
}

Eigen::MatrixXd Material::getMaterialMatrix() {
    Eigen::MatrixXd D;
    D = Eigen::MatrixXd::Zero(3,3);

    double c = (this->material_E)/((1 + this->material_v)*(1 - 2*this->material_v));

    D(0,0) = c*(1 - this->material_v);
    D(0,1) = c*this->material_v;

    D(1,0) = c*this->material_v;
    D(1,1) = c*(1 - this->material_v);

    D(2,2) = 2*c*(1 - 2*this->material_v);

    return D;
}

double Material::trace() {
    double c = (this->material_E)/((1 + this->material_v)*(1 - 2*this->material_v));

    return c*(2*(1 - this->material_v) + 2*(1 - 2*this->material_v));
}

double Material::k() {
    return (3 - 4*this->material_v);
}

double Material::v() {
    return this->material_v;
}

double Material::E() {
    return this->material_E;
}

bool Material::operator==(const Material &other) const{
    VeamyConfig* config = VeamyConfig::instance();
    return std::abs(this->material_E-other.material_E) < config->getTolerance() &&
            std::abs(this->material_v-other.material_v) < config->getTolerance();
}




