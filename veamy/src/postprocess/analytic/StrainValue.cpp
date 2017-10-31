#include <veamy/postprocess/analytic/StrainValue.h>

StrainValue::StrainValue(func_trio f) {
    this->f = f;
}

Trio<double> StrainValue::getValue(Point p) {
    return f(p.getX(), p.getY());
}
