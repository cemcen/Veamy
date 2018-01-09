#include <veamy/postprocess/computables/StrainStressDifferenceComputable.h>

template <typename T>
StrainStressDifferenceComputable<T>::StrainStressDifferenceComputable(StrainValue *strain, StressValue *stress) {
    this->strainValue = strain;
    this->stressValue = stress;
}

template <typename T>
double StrainStressDifferenceComputable<T>::apply(double x, double y, int index, T container) {
    Eigen::VectorXd strain = this->calculator->getStrain(x, y, container, this->polygonIndex);

    Eigen::VectorXd stress = this->D*strain;

    Trio<double> eH = veamy_functions::to_trio<double>(strain);
    Trio<double> sH = veamy_functions::to_trio<double>(stress);
    Trio<double> e = this->strainValue->getValue(Point(x,y));
    Trio<double> s = this->stressValue->getValue(Point(x,y));

    return (e - eH).dot(s - sH);
}

template <typename T>
void StrainStressDifferenceComputable<T>::setPolygonIndex(int polyIndex) {
    this->polygonIndex = polyIndex;
}

template class StrainStressDifferenceComputable<Polygon>;
template class StrainStressDifferenceComputable<Triangle>;