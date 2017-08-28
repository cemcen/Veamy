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




