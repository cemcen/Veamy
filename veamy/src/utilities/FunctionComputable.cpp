#include <veamy/utilities/FunctionComputable.h>

FunctionComputable::FunctionComputable(func f) {
    this->f = f;
}

double FunctionComputable::apply(double x, double y, int index) {
    return f(x, y);
}
