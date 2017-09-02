#include <veamy/config/VeamyConfig.h>
#include <mesher/config/MesherConfig.h>

VeamyConfig* VeamyConfig::s_instance = nullptr;

VeamyConfig::VeamyConfig() {
    this->double_comparison_tolerance = 0.001;
    this->gamma = 1;
    this->precision = 6;
}

void VeamyConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

void VeamyConfig::setPrecision(Precision::precision p) {
    this->precision = p;
    MesherConfig::instance()->setPrecision(this->precision);
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
