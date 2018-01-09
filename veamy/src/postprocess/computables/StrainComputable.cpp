#include <veamy/postprocess/computables/StrainComputable.h>
#include <veamy/utilities/veamy_functions.h>

template <typename T>
StrainComputable<T>::StrainComputable(StrainValue *strain) {
    this->strainValue = strain;
}

template <typename T>
double StrainComputable<T>::apply(double x, double y, int index, T container) {
    Trio<double> strain = this->strainValue->getValue(Point(x,y));
    Eigen::VectorXd strainVector = veamy_functions::to_vector(strain);

    double value = strainVector.transpose()*this->D*strainVector;

    return value;
}
