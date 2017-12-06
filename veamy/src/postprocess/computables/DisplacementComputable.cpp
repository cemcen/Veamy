#include <veamy/postprocess/computables/DisplacementComputable.h>
#include <delynoi/models/polygon/Polygon.h>

template <typename T>
DisplacementComputable<T>::DisplacementComputable(DisplacementValue *value) {
    this->value = value;
}

template <typename T>
double DisplacementComputable<T>::apply(double x, double y, int index, T container) {
    Pair<double> u = value->getValue(Point(x,y));
    return std::pow(u.first,2) + std::pow(u.second,2);
}

template class DisplacementComputable<Polygon>;
template class DisplacementComputable<Triangle>;