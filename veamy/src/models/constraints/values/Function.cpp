#include <veamy/models/constraints/values/Function.h>

Function::Function(func_t f) {
    this->f = f;
}

double Function::getValue(Point p) {
    return f(p.getX(), p.getY());
}

