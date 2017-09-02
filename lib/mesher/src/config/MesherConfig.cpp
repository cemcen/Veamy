#include <mesher/config/MesherConfig.h>

MesherConfig* MesherConfig::s_instance = nullptr;

MesherConfig::MesherConfig() {
    this->circle_discretization_grade = 12;
    this->double_comparison_tolerance = 0.0000001;
    this->scale_for_clipper = 100000;
    this->precision = 6;
}

void MesherConfig::setDiscretizationGrade(int d) {
    this->circle_discretization_grade = d;
}

void MesherConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

void MesherConfig::setScale(int s) {
    this->scale_for_clipper = s;
}

void MesherConfig::setPrecision(Precision::precision p) {
    this->precision = p;
}

void MesherConfig::setPrecision(int p) {
    this->precision = p;
}

int MesherConfig::getDiscretizationGrade() {
    return this->circle_discretization_grade;
}

double MesherConfig::getTolerance() {
    return this->double_comparison_tolerance;
}

int MesherConfig::getScale() {
    return this->scale_for_clipper;
}

int MesherConfig::getPrecision() {
    return this->precision;
}

MesherConfig *MesherConfig::instance() {
    if(!s_instance){
        s_instance = new MesherConfig;
    }

    return s_instance;
}
