#include <veamy/physics/bodyforces/BodyForce.h>

BodyForce::BodyForce(func fX, func fY) {
    this->fX = new FunctionComputable(fX);
    this->fY = new FunctionComputable(fY);
}

BodyForce::BodyForce() {}

Computable* BodyForce::getX() {
    return this->fX;
}

Computable* BodyForce::getY() {
    return this->fY;
}
