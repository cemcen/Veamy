#include <veamy/models/constraints/values/Constant.h>

Constant::Constant(double val) {
    this->value = val;
}

double Constant::getValue(Point p) {
    return this->value;
}

