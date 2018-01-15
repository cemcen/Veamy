#include <veamy/postprocess/analytic/StressValue.h>

StressValue::StressValue(func_pair f) {
    this->f = f;
}

std::vector<double> StressValue::getValue(Point p) {
    return f(p.getX(), p.getY());
}
