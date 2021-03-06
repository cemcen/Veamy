#include <feamy/config/FeamyConfig.h>

FeamyConfig* FeamyConfig::s_instance = nullptr;

FeamyConfig::FeamyConfig() {
    this->gaussPoints = 2; //order!
}

void FeamyConfig::setNumberOfGaussPoints(int gauss) {
    this->gaussPoints = gauss;
}

int FeamyConfig::getNumberOfGaussPoints() {
    return this->gaussPoints;
}

FeamyConfig *FeamyConfig::instance() {
    if(!s_instance){
        s_instance = new FeamyConfig;
    }

    return s_instance;
}
