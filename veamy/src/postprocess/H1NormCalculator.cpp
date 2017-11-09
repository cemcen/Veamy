#include <veamy/postprocess/H1NormCalculator.h>
#include <veamy/postprocess/integrator/VeamyH1Integrator.h>
#include <veamy/postprocess/integrator/IdentityIntegrator.h>

template <typename T>
H1NormCalculator<T>::H1NormCalculator(StrainValue *strain, StressValue *stress, DisplacementValue* value, Eigen::VectorXd u, DOFS d,
                                   std::vector<Point> points) : NormCalculator<T>(u, d){
    this->strainValue = strain;
    this->stressValue = stress;
    this->value = value;
}

template <typename T>
void H1NormCalculator<T>::setCalculator(FeamyIntegrator<T>* integrator, FeamyAdditionalInfo info) {
    NormIntegrator<T>* den = integrator->clone();

    this->num = integrator;
    this->den = den;

    this->num->setComputable(new StrainStressDifferenceComputable<T>(this->strainValue, this->stressValue, this->nodalDisplacements,
                                                            this->dofs, info.elements, info.points, info.C));
    this->den->setComputable(new StrainStressComputable<T>(this->strainValue, this->stressValue));
}

template <typename T>
void H1NormCalculator<T>::setCalculator(VeamyIntegrator<T>* integrator) {
    this->num = new VeamyH1Integrator<T>(this->value, this->dofs, this->nodalDisplacements);
    this->den = new IdentityIntegrator<T>;
}

template class H1NormCalculator<Triangle>;
template class H1NormCalculator<Polygon>;