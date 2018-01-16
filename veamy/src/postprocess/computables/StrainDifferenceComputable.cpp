#include <veamy/postprocess/computables/StrainDifferenceComputable.h>
#include <veamy/utilities/veamy_functions.h>

template <typename T>
StrainDifferenceComputable<T>::StrainDifferenceComputable(StrainValue *value) {
    this->strainValue = value;
}

template <typename T>
double StrainDifferenceComputable<T>::apply(double x, double y, int index, T container) {
    Eigen::VectorXd sH = this->calculator->getStrain(x,y,container,this->polygonIndex);

    std::vector<double> sTrio = this->strainValue->getValue(Point(x,y));
    Eigen::VectorXd s = veamy_functions::to_vector(sTrio);

    double value = (s - sH).transpose()*this->D*(s - sH);

    return value;
}

template <typename T>
void StrainDifferenceComputable<T>::setPolygonIndex(int polyIndex) {
    this->polygonIndex = polyIndex;
}
template class StrainDifferenceComputable<Polygon>;
template class StrainDifferenceComputable<Triangle>;
