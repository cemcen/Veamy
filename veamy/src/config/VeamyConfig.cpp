#include <veamy/config/VeamyConfig.h>

VeamyConfig* VeamyConfig::s_instance = nullptr;

VeamyConfig::VeamyConfig() {
    this->double_comparison_tolerance = 0.001;
    this->gamma = 1;
}

void VeamyConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

void VeamyConfig::setPrecision(VeamyConfig::Precision p) {
    this->precision = p;
}

void VeamyConfig::setPrecision(int p) {
    this->precision = p;
}

void VeamyConfig::setGamma(double g) {
    this->gamma = g;
}

double VeamyConfig::getTolerance() {
    return this->double_comparison_tolerance;
}

double VeamyConfig::getGamma() {
    return this->gamma;
}

int VeamyConfig::getPrecision() {
    return this->precision;
}

VeamyConfig *VeamyConfig::instance() {
    if(!s_instance){
        s_instance = new VeamyConfig;
    }

    return s_instance;
}
