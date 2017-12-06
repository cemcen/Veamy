#include <veamy/postprocess/analytic/StressValue.h>

StressValue::StressValue(func_trio f) {
    this->f = f;
}

Trio<double> StressValue::getValue(Point p) {
    return f(p.getX(), p.getY());
}
