#include <veamy/postprocess/computables/DisplacementComputable.h>
#include <delynoi/models/polygon/Polygon.h>

template <typename T>
DisplacementComputable<T>::DisplacementComputable(DisplacementValue *value) {
    this->value = value;
}

template <typename T>
double DisplacementComputable<T>::apply(double x, double y, int index, T container) {
    std::vector<double> u = value->getValue(Point(x,y));
    double result = 0;

    for (int i = 0; i < u.size(); ++i) {
        result += std::pow(u[i],2);
    }

    return result;
}

template class DisplacementComputable<Polygon>;
template class DisplacementComputable<Triangle>;