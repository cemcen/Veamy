#include <veamy/postprocess/analytic/DisplacementValue.h>

DisplacementValue::DisplacementValue(func_pair f) {
    this->f = f;
}

Pair<double> DisplacementValue::getValue(Point p) {
    return f(p.getX(), p.getY());
}
