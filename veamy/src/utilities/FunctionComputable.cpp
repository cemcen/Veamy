#include <veamy/postprocess/computables/FunctionComputable.h>
#include <delynoi/models/polygon/Polygon.h>

FunctionComputable::FunctionComputable(func f) {
    this->f = f;
}

double FunctionComputable::apply(double x, double y, int index, Polygon container) {
    return f(x, y);
}
