#include <veamy/postprocess/computables/DisplacementDifferenceComputable.h>

template <typename T>
DisplacementDifferenceComputable<T>::DisplacementDifferenceComputable(DisplacementValue *v,
                                                                      DisplacementCalculator<T> *calculator) {
    this->value = v;
    this->calculator = calculator;
}

template <typename T>
double DisplacementDifferenceComputable<T>::apply(double x, double y, int index, T container) {
    Pair<double> u = value->getValue(Point(x,y));
    calculator->setPolygonIndex(this->polygonIndex);
    Pair<double> uH = calculator->getDisplacement(x, y, index, container);

    return std::pow(u.first - uH.first, 2) + std::pow(u.second - uH.second, 2);
}

template <typename T>
void DisplacementDifferenceComputable<T>::setPolygonIndex(int polyIndex) {
    this->polygonIndex = polyIndex;
}

template class DisplacementDifferenceComputable<Polygon>;
template class DisplacementDifferenceComputable<Triangle>;