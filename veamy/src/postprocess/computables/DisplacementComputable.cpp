#include <veamy/postprocess/computables/DisplacementComputable.h>

DisplacementComputable::DisplacementComputable(DisplacementValue *value) {
    this->value = value;
}

double DisplacementComputable::apply(double x, double y, int index) {
    Pair<double> u = value->getValue(Point(x,y));
    return std::pow(u.first,2) + std::pow(u.second,2);
}
