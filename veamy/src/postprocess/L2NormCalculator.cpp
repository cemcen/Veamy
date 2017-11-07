#include <veamy/postprocess/L2NormCalculator.h>
#include <veamy/postprocess/computables/DisplacementDifferenceComputable.h>
#include <veamy/postprocess/computables/DisplacementComputable.h>

template <typename T>
L2NormCalculator<T>::L2NormCalculator(DisplacementValue *value, Eigen::VectorXd u, DOFS d) : NormCalculator<T>(u, d) {
    this->value = value;
}

template <typename T>
void L2NormCalculator<T>::setCalculator(FeamyIntegrator<T>* num, FeamyAdditionalInfo info) {
    NormIntegrator<T>* den = num->clone();

    this->num = num;
    this->den = den;

    this->num->setComputable(new DisplacementDifferenceComputable<T>(this->value, this->nodalDisplacements, this->dofs));
    this->den->setComputable(new DisplacementComputable<T>(this->value));
}

template <typename T>
void L2NormCalculator<T>::setCalculator(VeamyIntegrator<T>* integrator) {
    NormIntegrator<T>* den = integrator->clone();

    this->num = integrator;
    this->den = den;

    this->num->setComputable(new DisplacementDifferenceComputable<T>(this->value, this->nodalDisplacements, this->dofs));
    this->den->setComputable(new DisplacementComputable<T>(this->value));
}

template class L2NormCalculator<Triangle>;
template class L2NormCalculator<Polygon>;