#include <veamy/postprocess/computables/DisplacementDifferenceComputable.h>

template <typename T>
DisplacementDifferenceComputable<T>::DisplacementDifferenceComputable(DisplacementValue *v,
                                                                      DisplacementCalculator<T> *calculator) {
    this->value = v;
    this->calculator = calculator;
}

template <typename T>
double DisplacementDifferenceComputable<T>::apply(double x, double y, int index, T container) {
    std::vector<double> u = value->getValue(Point(x,y));
    calculator->setPolygonIndex(this->polygonIndex);
    std::vector<double> uH = calculator->getDisplacement(x, y, index, container);

    double result = 0;

    for (int i = 0; i < u.size(); ++i) {
        result += std::pow(u[i] - uH[i], 2);
    }

    return result;
}

template <typename T>
void DisplacementDifferenceComputable<T>::setPolygonIndex(int polyIndex) {
    this->polygonIndex = polyIndex;
}

template class DisplacementDifferenceComputable<Polygon>;
template class DisplacementDifferenceComputable<Triangle>;