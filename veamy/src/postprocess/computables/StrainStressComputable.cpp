#include <veamy/postprocess/computables/StrainStressComputable.h>
#include <delynoi/models/polygon/Polygon.h>
#include <veamy/utilities/veamy_functions.h>

template <typename T>
StrainStressComputable<T>::StrainStressComputable(StrainValue *strain, StressValue *value) {
    this->strainValue = strain;
    this->stressValue = value;
}

template <typename T>
double StrainStressComputable<T>::apply(double x, double y, int index, T container) {
    std::vector<double> stress = this->stressValue->getValue(Point(x,y));
    std::vector<double> strain = this->strainValue->getValue(Point(x,y));

    return veamy_functions::dot(stress, strain);
}

template class StrainStressComputable<Polygon>;
template class StrainStressComputable<Triangle>;