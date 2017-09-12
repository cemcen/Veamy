#include <delynoi/config/DelynoiConfig.h>

DelynoiConfig* DelynoiConfig::s_instance = nullptr;

DelynoiConfig::DelynoiConfig() {
    this->circle_discretization_grade = 12;
    this->double_comparison_tolerance = 0.000000000001;
    this->scale_for_clipper = 100000;
    this->precision = 6;
}

void DelynoiConfig::setDiscretizationGrade(int d) {
    this->circle_discretization_grade = d;
}

void DelynoiConfig::setTolerance(double t) {
    this->double_comparison_tolerance = t;
}

void DelynoiConfig::setScale(int s) {
    this->scale_for_clipper = s;
}

void DelynoiConfig::setPrecision(Precision::precision p) {
    this->precision = p;
}

void DelynoiConfig::setPrecision(int p) {
    this->precision = p;
}

int DelynoiConfig::getDiscretizationGrade() {
    return this->circle_discretization_grade;
}

double DelynoiConfig::getTolerance() {
    return this->double_comparison_tolerance;
}

int DelynoiConfig::getScale() {
    return this->scale_for_clipper;
}

int DelynoiConfig::getPrecision() {
    return this->precision;
}

DelynoiConfig *DelynoiConfig::instance() {
    if(!s_instance){
        s_instance = new DelynoiConfig;
    }

    return s_instance;
}
