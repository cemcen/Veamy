#include <veamy/postprocess/analytic/StrainValue.h>

StrainValue::StrainValue(func_pair f) {
    this->f = f;
}

std::vector<double> StrainValue::getValue(Point p) {
    return f(p.getX(), p.getY());
}
