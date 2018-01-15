#include <veamy/postprocess/analytic/DisplacementValue.h>

DisplacementValue::DisplacementValue(func_pair f) {
    this->f = f;
}

std::vector<double> DisplacementValue::getValue(Point p) {
    return f(p.getX(), p.getY());
}
