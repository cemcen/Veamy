#include <veamy/postprocess/computables/StrainStressComputable.h>
#include <delynoi/models/polygon/Polygon.h>

template <typename T>
StrainStressComputable<T>::StrainStressComputable(StrainValue *strain, StressValue *value) {
    this->strainValue = strain;
    this->stressValue = value;
}

template <typename T>
double StrainStressComputable<T>::apply(double x, double y, int index, T container) {
    Trio<double> stress = this->stressValue->getValue(Point(x,y));
    Trio<double> strain = this->strainValue->getValue(Point(x,y));

    return stress.dot(strain);
}

template class StrainStressComputable<Polygon>;
template class StrainStressComputable<Triangle>;