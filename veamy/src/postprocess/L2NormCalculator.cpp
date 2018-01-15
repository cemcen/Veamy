#include <veamy/postprocess/L2NormCalculator.h>
#include <feamy/postprocess/calculators/FeamyDisplacementCalculator.h>

template <typename T>
L2NormCalculator<T>::L2NormCalculator(DisplacementValue *value, Eigen::VectorXd u, DOFS d) : NormCalculator<T>(u, d) {
    this->value = value;
}

template <typename T>
void L2NormCalculator<T>::setCalculator(FeamyIntegrator<T>* num, FeamyAdditionalInfo info) {
    NormIntegrator<T>* den = num->clone();

    this->num = num;
    this->den = den;

    DisplacementCalculator<T>* calculator = new FeamyDisplacementCalculator<T>(this->dofs, this->nodalDisplacements,
                                                                               info.elements);

    this->num->setComputable(new DisplacementDifferenceComputable<T>(this->value, calculator));
    this->den->setComputable(new DisplacementComputable<T>(this->value));
}

template <typename T>
void L2NormCalculator<T>::setCalculator(VeamyIntegrator<T> *integrator, DisplacementCalculator<T> *calculator) {
    NormIntegrator<T>* den = integrator->clone();

    this->num = integrator;
    this->den = den;

    this->num->setComputable(new DisplacementDifferenceComputable<T>(this->value, calculator));
    this->den->setComputable(new DisplacementComputable<T>(this->value));
}

template <typename T>
void L2NormCalculator<T>::setExtraInformation(Conditions *conditions) {}

template class L2NormCalculator<Triangle>;
template class L2NormCalculator<Polygon>;