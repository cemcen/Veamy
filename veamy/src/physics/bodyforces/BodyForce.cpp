#include <veamy/physics/bodyforces/BodyForce.h>

BodyForce::BodyForce(func fX, func fY) {
    this->f.push_back(new FunctionComputable(fX));
    this->f.push_back(new FunctionComputable(fY));

    this->components = 2;
}

BodyForce::BodyForce(func f) {
    this->f.push_back(new FunctionComputable(f));
    this->components = 1;
}

BodyForce::BodyForce() {}

std::vector<FunctionComputable *> BodyForce::getComponents() {
    return this->f;
}

int BodyForce::numberOfComponents() {
    return this->components;
}
